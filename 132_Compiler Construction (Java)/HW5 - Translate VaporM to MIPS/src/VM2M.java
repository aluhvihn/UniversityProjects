import cs132.util.*;
import cs132.vapor.ast.*;
import cs132.vapor.ast.VBuiltIn.Op;
import cs132.vapor.parser.VaporParser;

import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.LinkedHashMap;
import java.util.LinkedList;

public class VM2M extends VInstr.Visitor<Throwable> {
    private IndentPrinter indentPrinter;
    private VaporProgram program;
    private int currSPOffset;
    private LinkedHashMap<String, Integer> stringMapping;

    public static void main(String[] args) throws Throwable {
        Op[] ops = {Op.Add, Op.Sub, Op.MulS, Op.Eq, Op.Lt, Op.LtS, Op.PrintIntS, Op.HeapAllocZ, Op.Error,};
        boolean allowLocals = false;
        String[] registers = {
            "v0", "v1",
            "a0", "a1", "a2", "a3",
            "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
            "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
            "t8",
        };
        boolean allowStack = true;

        VaporProgram program = null;
        try {
            program = VaporParser.run(new InputStreamReader(System.in), 1, 1, java.util.Arrays.asList(ops), allowLocals, registers, allowStack);
        } catch (ProblemException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
        VM2M vm2m = new VM2M(program);
        vm2m.translate();
    }

    public VM2M(VaporProgram program) {
        this.program = program;
        this.indentPrinter = new IndentPrinter(new PrintWriter(System.out), "  ");
        this.stringMapping = new LinkedHashMap<String, Integer>();
    }

    private void translate() throws Throwable{
        // Print data segments
        if (this.program.dataSegments.length > 0) {
            this.indentPrinter.println(".data");
            this.indentPrinter.println("");
            for (VDataSegment segment : this.program.dataSegments) {
                this.indentPrinter.println(String.format("%s:", segment.ident));

                this.indentPrinter.indent();
                for (VOperand.Static data : segment.values)
                    this.indentPrinter.println(String.format("%s", data.toString().substring(1)));
                this.indentPrinter.dedent();

                this.indentPrinter.println("");
            }
        }

        // Print text
        this.indentPrinter.println(".text");
        this.indentPrinter.println("");

        this.indentPrinter.indent();
        this.indentPrinter.println("jal Main");
        sysCall(10);
        this.indentPrinter.dedent();
        this.indentPrinter.println("");

        // Print each function
        for (VFunction function : this.program.functions) {
            this.indentPrinter.println(String.format("%s:", function.ident));

            this.currSPOffset = (2 + function.stack.out + function.stack.local) * 4;
            this.indentPrinter.indent();
            this.indentPrinter.println("sw $fp -8($sp)");
            this.indentPrinter.println("move $fp $sp");
            this.indentPrinter.println(String.format("subu $sp $sp %d", currSPOffset));
            this.indentPrinter.println("sw $ra -4($fp)");
            this.indentPrinter.dedent();

            LinkedList<VCodeLabel> labels = new LinkedList<VCodeLabel>(Arrays.asList(function.labels));
            for (VInstr instruction : function.body) {
                while (!labels.isEmpty() && labels.peek().sourcePos.line < instruction.sourcePos.line) {
                    this.indentPrinter.println(String.format("%s:", labels.pop().ident));
                }
                this.indentPrinter.indent();
                instruction.accept(this);
                this.indentPrinter.dedent();
            }
            this.indentPrinter.println("");
        }

        // Print Print function
        this.indentPrinter.println("_print:");
        this.indentPrinter.indent();
        sysCall(1);
        this.indentPrinter.println("la $a0 _newline");
        sysCall(4);
        this.indentPrinter.println("jr $ra");
        this.indentPrinter.dedent();
        this.indentPrinter.println("");

        // Print Error function
        this.indentPrinter.println("_error:");
        this.indentPrinter.indent();
        sysCall(4);
        sysCall(10);
        this.indentPrinter.dedent();
        this.indentPrinter.println("");

        // Print HeapAlloc function
        this.indentPrinter.println("_heapAlloc:");
        this.indentPrinter.indent();
        sysCall(9);
        this.indentPrinter.println("jr $ra");
        this.indentPrinter.dedent();
        this.indentPrinter.println("");

        // Print data
        this.indentPrinter.println(".data");
        this.indentPrinter.println(".align 0");
        this.indentPrinter.println("_newline: .asciiz \"\\n\"");

        for (String str : stringMapping.keySet()) {
            this.indentPrinter.println(String.format("_str%d: .asciiz \"%s\\n\"", stringMapping.get(str), str));
        }
        this.indentPrinter.close();
    }

    private void sysCall(int code) throws Throwable {
        this.indentPrinter.println(String.format("li $v0 %d", code));
        this.indentPrinter.println("syscall");
    }

    @Override
    public void visit(VAssign var1) throws Throwable {
        if (var1.source instanceof VOperand.Static) {
            if (var1.source instanceof  VLabelRef) {
                this.indentPrinter.println(String.format("la %s %s", var1.dest.toString(), ((VLabelRef) var1.source).ident));
            } else {
                this.indentPrinter.println(String.format("li %s %s", var1.dest.toString(), var1.source));
            }
        } else if (var1.source instanceof VVarRef) {
            this.indentPrinter.println(String.format("move %s %s", var1.dest.toString(), var1.source.toString()));
        }
    }

    @Override
    public void visit(VCall var1) throws Throwable {
        if (var1.addr instanceof VAddr.Label) {
            this.indentPrinter.println(String.format("jal %s", var1.addr.toString().substring(1)));
        } else {
            this.indentPrinter.println(String.format("jalr %s", var1.addr.toString()));
        }

        if (var1.dest != null) {
            this.indentPrinter.println(String.format("%s = $v0", var1.dest));
        }
    }

    @Override
    public void visit(VBuiltIn var1) throws Throwable {
        if (var1.op == Op.Error) {
            String arg = ((VLitStr)var1.args[0]).value;
            if (!stringMapping.containsKey(arg))
                stringMapping.put(arg, stringMapping.size());
            String dataStr = "_str" + stringMapping.get(arg);
            this.indentPrinter.println(String.format("la $a0 %s", dataStr));
            this.indentPrinter.println("j _error");
        } else if (var1.op == Op.HeapAllocZ || var1.op == Op.PrintIntS) {
            for (int i = 0; i < var1.args.length; i++) {
                if (var1.args[i] instanceof VVarRef.Register)
                    this.indentPrinter.println(String.format("move $a%d %s", i, var1.args[i].toString()));
                else
                    this.indentPrinter.println(String.format("li $a%d %s", i, var1.args[i]));
            }
            if (var1.op == Op.HeapAllocZ)
                this.indentPrinter.println("jal _heapAlloc");
            else if (var1.op == Op.PrintIntS)
                this.indentPrinter.println("jal _print");
            if (var1.dest != null)
                this.indentPrinter.println(String.format("move %s $v0", var1.dest));
        } else {
            String op = "";
            boolean doMath = false;
            if (var1.op == Op.Lt) {
                op = "sltu";
            } else if (var1.op == Op.LtS) {
                if (var1.args[1] instanceof VLitInt)
                    op = "slti";
                else
                    op = "slt";
            } else if (var1.op == Op.Sub) {
                op = "subu";
                doMath = true;
            } else if (var1.op == Op.Add) {
                op = "addu";
                doMath = true;
            } else if (var1.op == Op.MulS) {
                op = "mul";
                doMath = true;
            }
            if (var1.args[0] instanceof VLitInt && var1.args[1] instanceof VLitInt && doMath) {
                int firstOp = Integer.parseInt(var1.args[0].toString());
                int secondOp = Integer.parseInt(var1.args[1].toString());
                if (op.equals("subu"))
                    this.indentPrinter.println(String.format("li %s %d", var1.dest, firstOp - secondOp));
                else if (op.equals("addu"))
                    this.indentPrinter.println(String.format("li %s %d", var1.dest, firstOp + secondOp));
                else if (op.equals("mul"))
                    this.indentPrinter.println(String.format("li %s %d", var1.dest, firstOp * secondOp));
            } else if (var1.args[0] instanceof VLitInt) {
                this.indentPrinter.println(String.format("li $t9 %s", var1.args[0]));
                this.indentPrinter.println(String.format("%s %s $t9 %s", op, var1.dest, var1.args[1]));
            } else {
                this.indentPrinter.println(String.format("%s %s %s %s", op, var1.dest, var1.args[0], var1.args[1]));
            }
        }
    }

    @Override
    public void visit(VMemWrite var1) throws Throwable {
        if (var1.dest instanceof VMemRef.Stack) {
            VMemRef.Stack stack = (VMemRef.Stack)var1.dest;
            int offset = stack.index * 4;
            if (var1.source instanceof VVarRef.Register) {
                this.indentPrinter.println(String.format("sw %s %d($sp)", var1.source, offset));
            } else {
                this.indentPrinter.println(String.format("li $t9 %s", var1.source));
                this.indentPrinter.println(String.format("sw $t9 %d($sp)", offset));
            }
        } else {
            VMemRef.Global global = (VMemRef.Global) var1.dest;
            int offset = global.byteOffset;
            if (var1.source instanceof VLabelRef) {
                this.indentPrinter.println(String.format("la $t9 %s", ((VLabelRef) var1.source).ident));
                this.indentPrinter.println(String.format("sw $t9 %d(%s)", offset, global.base.toString()));
            } else {
                if (var1.source instanceof VLitInt) {
                    this.indentPrinter.println(String.format("li $t9 %s", var1.source.toString()));
                    this.indentPrinter.println(String.format("sw $t9 %d(%s)", offset, global.base.toString()));
                }
                else {
                    this.indentPrinter.println(String.format("sw %s %d(%s)", var1.source.toString(), offset, global.base.toString()));
                }
            }
        }
    }

    @Override
    public void visit(VMemRead var1) throws Throwable {
        String base = "";
        int offset;
        if (var1.source instanceof VMemRef.Stack) {
            VMemRef.Stack stack = (VMemRef.Stack)var1.source;
            offset = stack.index * 4;
            if (stack.region == VMemRef.Stack.Region.In)
                base = "$fp";
            else if (stack.region == VMemRef.Stack.Region.Local)
                base = "$sp";
        } else {
            VMemRef.Global global = (VMemRef.Global)var1.source;
            offset = global.byteOffset;
            base = global.base.toString();
        }
        this.indentPrinter.println(String.format("lw %s %d(%s)", var1.dest.toString(), offset, base));
    }

    @Override
    public void visit(VBranch var1) throws Throwable {
        String instr = var1.positive ? "bnez" : "beqz";
        this.indentPrinter.println(String.format("%s %s %s", instr, var1.value.toString(), var1.target.ident));
    }

    @Override
    public void visit(VGoto var1) throws Throwable {
        this.indentPrinter.println(String.format("j %s", var1.target.toString().substring(1)));
    }

    @Override
    public void visit(VReturn var1) throws Throwable {
        this.indentPrinter.println("lw $ra -4($fp)");
        this.indentPrinter.println("lw $fp -8($fp)");
        this.indentPrinter.println(String.format("addu $sp $sp %d", this.currSPOffset));
        this.indentPrinter.println("jr $ra");
    }
}
