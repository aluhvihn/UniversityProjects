import cs132.util.*;
import cs132.vapor.ast.*;

import java.util.*;

public class InstructionAnalysis extends VInstr.Visitor<Throwable> {
    int outCount = 0;

    private final VFunction function;
    private final IndentPrinter indentPrinter;
    private final HashMap<String, String> inVals = new HashMap<String, String>();
    private final HashMap<String, String> localVals = new HashMap<String, String>();

    public InstructionAnalysis(VFunction function, IndentPrinter indentPrinter) {
        this.function = function;
        this.indentPrinter = indentPrinter;
    }

    public void analyze() throws Throwable {
        // Add parameters to inVals HashMap
        for (VVarRef varRef : this.function.params) {
            inVals.put(varRef.toString(), String.valueOf(inVals.size()));
        }

        // Add variables to localVals HashMap
        for (String varRef : this.function.vars) {
            if (!inVals.containsKey(varRef)) {
                localVals.put(varRef, String.valueOf(localVals.size()));
            }
        }

        this.indentPrinter.indent();

        // Go through function body
        outCount = 0;
        int line;

        LinkedList<VCodeLabel> labels = new LinkedList<VCodeLabel>();
        Collections.addAll(labels, this.function.labels);
        for (VInstr instruction : this.function.body) {
            line = instruction.sourcePos.line;
            indentPrinter.dedent();
            while (!labels.isEmpty() && labels.peek().sourcePos.line < line)
                indentPrinter.println(String.format("%s:", labels.pop().ident));
            indentPrinter.indent();
            instruction.accept(this);
        }
        System.out.println(String.format("func %s [in %d, out %d, local %d]", this.function.ident, inVals.size(), outCount, localVals.size()));

        this.indentPrinter.println("");
        this.indentPrinter.dedent();
        indentPrinter.flush();
    }

    public String getVar(String var) {
        if (inVals.containsKey(var)) {
            return "in[" + inVals.get(var) + "]";
        }
        else if (localVals.containsKey(var)){
            return "local[" + localVals.get(var) + "]";
        }
        else
            return null;
    }

    @Override
    public void visit(VAssign var1) throws Throwable {
        String source = getVar(var1.source.toString());
        if (source == null)
            source = var1.source.toString();
        indentPrinter.println(String.format("$v0 = %s", source));
        indentPrinter.println(String.format("%s = $v0", getVar(var1.dest.toString())));
    }

    @Override
    public void visit(VCall var1) throws Throwable {
        for (int i = 0; i < var1.args.length; i++) {
            String rhs = getVar(var1.args[i].toString());
            if (rhs == null)
                rhs = var1.args[i].toString();
            indentPrinter.println(String.format("$v0 = %s", rhs));
            indentPrinter.println(String.format("out[%d] = $v0", i));
        }
        if (var1.args.length > this.outCount)
            this.outCount = var1.args.length;

        String addr = getVar(var1.addr.toString());
        if (addr == null)
            addr = var1.addr.toString();
        indentPrinter.println(String.format("$v0 = %s", addr));
        indentPrinter.println("call $v0");
        indentPrinter.println(String.format("%s = $v0", getVar(var1.dest.toString())));
    }

    @Override
    public void visit(VBuiltIn var1) throws Throwable {
        ArrayList<String> args = new ArrayList<String>();
        int i = 0;
        for (VOperand operand : var1.args) {
            String register = getVar(operand.toString());
            if (register == null) {
                args.add(operand.toString());
            }
            else {
                String x = "$v" + String.valueOf(i);
                indentPrinter.println(String.format("%s = %s", x, register));
                i++;
                args.add(x);
            }
        }
        if (var1.dest != null) {
            indentPrinter.println(String.format("$v0 = %s(%s)", var1.op.name, StringUtil.join(args, " ")));
            indentPrinter.println(String.format("%s = $v0", getVar(var1.dest.toString())));
        }
        else
            indentPrinter.println(String.format("%s(%s)", var1.op.name, StringUtil.join(args, " ")));
    }

    @Override
    public void visit(VMemWrite var1) throws Throwable {
        String source = getVar(var1.source.toString());
        if (source == null)
            source = var1.source.toString();
        VMemRef.Global dest = (VMemRef.Global) var1.dest;
        if (dest.byteOffset == 0) {
            indentPrinter.println(String.format("$v0 = %s", getVar(dest.base.toString())));
            indentPrinter.println(String.format("$v1 = %s", source));
            indentPrinter.println(String.format("[$v0] = $v1"));
        }
        else {
            indentPrinter.println(String.format("$v0 = %s", getVar(dest.base.toString())));
            indentPrinter.println(String.format("$v1 = %s", source));
            indentPrinter.println(String.format("[$v0+%d] = $v1", dest.byteOffset, source));
        }
    }

    @Override
    public void visit(VMemRead var1) throws Throwable {
        VMemRef.Global source = (VMemRef.Global) var1.source;
        if (source.byteOffset == 0){
            indentPrinter.println(String.format("$v0 = %s", getVar(source.base.toString())));
            indentPrinter.println("$v0 = [$v0]");
            indentPrinter.println(String.format("%s = $v0", getVar(var1.dest.toString())));
        }

        else {
            indentPrinter.println(String.format("$v0 = %s", getVar(source.base.toString())));
            indentPrinter.println(String.format("$v0 = [$v0+%d]", source.byteOffset));
            indentPrinter.println(String.format("%s = $v0", getVar(var1.dest.toString())));
        }
    }

    @Override
    public void visit(VBranch var1) throws Throwable {
        indentPrinter.println(String.format("$v0 = %s", getVar(var1.value.toString())));
        if (var1.positive)
            indentPrinter.println(String.format("if $v0 goto %s", var1.target));
        else
            indentPrinter.println(String.format("if0 $v0 goto %s", var1.target));
    }

    @Override
    public void visit(VGoto var1) throws Throwable {
        indentPrinter.println(String.format("goto %s", var1.target.toString()));
    }

    @Override
    public void visit(VReturn var1) throws Throwable {
        if (var1.value!=null) {
            String val = getVar(var1.value.toString());
            if (val == null)
                val = var1.value.toString();
            indentPrinter.println(String.format("$v0 = %s", val));
        }
        indentPrinter.println("ret");
    }
}