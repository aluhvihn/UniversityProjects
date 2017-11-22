import cs132.util.*;
import cs132.vapor.ast.*;
import cs132.vapor.ast.VBuiltIn.Op;
import cs132.vapor.parser.VaporParser;

import java.io.InputStreamReader;
import java.io.PrintWriter;


public class V2VM {
    private static IndentPrinter indentPrinter;
    private VaporProgram program;

    public static void main(String[] args) throws Throwable {
        Op[] ops = {Op.Add, Op.Sub, Op.MulS, Op.Eq, Op.Lt, Op.LtS, Op.PrintIntS, Op.HeapAllocZ, Op.Error,};
        boolean allowLocals = true;
        String[] registers = null;
        boolean allowStack = false;

        VaporProgram program = null;
        try {
            program = VaporParser.run(new InputStreamReader(System.in), 1, 1, java.util.Arrays.asList(ops), allowLocals, registers, allowStack);
        } catch (ProblemException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }

        indentPrinter = new IndentPrinter(new PrintWriter(System.out), "  ");

        // Print data segments
        for (VDataSegment vDataSegment: program.dataSegments) {
            indentPrinter.println(String.format("%s %s", vDataSegment.mutable ? "var" : "const", vDataSegment.ident));
            if (vDataSegment.values.length > 0) {
                indentPrinter.indent();
                for (VOperand operand : vDataSegment.values) {
                    indentPrinter.println(String.format(":%s", ((VLabelRef) operand).ident));
                }
                indentPrinter.dedent();
                indentPrinter.println("");
            }
        }
        indentPrinter.flush();

        // Print functions
        for (VFunction function : program.functions) {
            InstructionAnalysis instructionScan = new InstructionAnalysis(function, indentPrinter);
            instructionScan.analyze();
        }
        indentPrinter.close();
    }

    public V2VM(VaporProgram program) {
        this.program = program;
    }
}