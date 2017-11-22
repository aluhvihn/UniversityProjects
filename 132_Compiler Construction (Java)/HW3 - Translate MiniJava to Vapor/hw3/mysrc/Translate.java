package mysrc;

import syntaxtree.*;
import visitor.DepthFirstVisitor;
import java.util.*;

public class Translate extends DepthFirstVisitor {
    private int andElseCount = 0;
    private int andEndCount = 0;
    private int boundCount = 0;
    private int elseCount = 0;
    private int ifEndCount = 0;
    private int indent = 0;
    private int notElseCount = 0;
    private int notEndCount = 0;
    private int nullCount = 0;
    private int varCount = 0;
    private int whileCount = 0;
    private int whileElseCount = 0;

    private BaseType lastType;

    private boolean allocatingArray;
    private boolean classIdentifier;

    private LastExpression lastExpression;
    private final SymbolTable symbolTable;

    public Translate(SymbolTable symbolTable) {
        this.symbolTable = symbolTable;
        this.allocatingArray = false;
        this.classIdentifier = false;
    }

    void print(String s, Object... arg) {
        String ret = "";
        for (int i = 0; i < indent * 2; i++)
            ret += " ";
        System.out.println(String.format(ret + s, arg));
    }

    String printVar(LastExpression variable) {
        String ret;
        ret = String.format("t.%d", varCount++);
        print("%s = %s", ret, variable.string);
        return ret;
    }

    private void printNull(String address) {
        String nullLabel = "null" + nullCount++;
        print("if %s goto :%s", address, nullLabel);
        indent++;
        print("Error(\"null pointer\")");
        indent--;
        print("%s:", nullLabel);
    }

    private void printBounds(String startAddr, String index) {
        String boundLabel = "bounds_error_" + boundCount++;
        String cond1 = String.format("t.%d", varCount++);
        String cond2 = String.format("t.%d", varCount++);
        String t_len = String.format("t.%d", varCount++);
        String t_neg = String.format("t.%d", varCount++);
        print("%s = [%s+0]", t_len, startAddr);
        print("%s = LtS(%s 0)", t_neg, index);
        print("%s = Eq(%s %s)", cond1, index, t_len);
        print("%s = LtS(%s %s)", cond2, t_len, index);
        print("%s = Add(%s %s)", cond1, t_neg, cond1);
        print("%s = Add(%s %s)", cond2, cond1, cond2);
        print("if0 %s goto :%s", cond2, boundLabel);
        indent++;
        print("Error(\"array index out of bounds\")");
        indent--;
        print("%s:", boundLabel);
    }

    @Override
    public void visit(Goal n) {
        print("");
        for (ClassType classType : symbolTable.classTable.values()) {
            if (!classType.name.equals(n.f0.f1.f0.toString())) {
                print("const vmt_%s", classType.name);
                indent++;
                for (String methodName : classType.classMethods.keySet())
                    print(":%s.%s", classType.name, methodName);
                indent--;
                print("");
            }
        }

        // Main Class
        n.f0.accept(this);

        // Type Declaration
        n.f1.accept(this);
        if (allocatingArray) {
            print("");
            printAllocArray();
        }
    }

    @Override
    public void visit(MainClass n) {
        print("func Main()");
        indent++;
        n.f15.accept(this);
        print("ret");
        indent--;
    }

    /**
     * f0 -> ClassDeclaration()
     *       | ClassExtendsDeclaration()
     */

    @Override
    public void visit(ClassDeclaration n) {
        symbolTable.classScope = symbolTable.classTable.get(n.f1.f0.toString());
        n.f4.accept(this);
        symbolTable.classScope = null;
    }

    @Override
    public void visit(ClassExtendsDeclaration n) {
        symbolTable.classScope = symbolTable.classTable.get(n.f1.f0.toString());
        n.f6.accept(this);
        symbolTable.classScope = null;
    }

    /** STATEMENTS
     * f0 -> Block()
     *       | AssignmentStatement()
     *       | ArrayAssignmentStatement()
     *       | IfStatement()
     *       | WhileStatement()
     *       | PrintStatement()
     */

    @Override
    public void visit(AssignmentStatement n) {
        LastExpression lhs, rhs;
        n.f0.accept(this);
        lhs = lastExpression;
        n.f2.accept(this);
        rhs = lastExpression;
        if (lhs.type.equals("EXPR") && rhs.type.equals("EXPR")) {
            String var = String.format("t.%d", varCount++);
            print("%s = %s", var, rhs.string);
            print("%s = %s", lhs.string, var);
        } else {
            print("%s = %s", lhs.string, rhs.string);
        }
    }

    @Override
    public void visit(ArrayAssignmentStatement n) {
        String bytes, index, offset, startAddr;
        n.f0.accept(this);
        startAddr = printVar(lastExpression);
        printNull(startAddr);
        n.f2.accept(this);
        index = printVar(lastExpression);
        printBounds(startAddr, index);
        offset = String.format("t.%d", varCount++);
        bytes = String.format("t.%d", varCount++);
        print("%s = Add(%s 1)", offset, index);
        print("%s = MulS(%s 4)", offset, offset);
        print("%s = Add(%s %s)", bytes, startAddr, offset);
        n.f5.accept(this);
        print("[%s] = %s", bytes, printVar(lastExpression));
    }

    @Override
    public void visit(IfStatement n) {
        String condVar, elseLabel, ifEndLabel;
        n.f2.accept(this);
        condVar = printVar(lastExpression);
        elseLabel = "if1_else_" + elseCount++;
        ifEndLabel = "if1_end_" + ifEndCount++;
        print("if0 %s goto :%s", condVar, elseLabel);
        indent++;
        n.f4.accept(this);
        print("goto :%s", ifEndLabel);
        indent--;
        print("%s:", elseLabel);
        indent++;
        n.f6.accept(this);
        indent--;
        print("%s:", ifEndLabel);
    }

    @Override
    public void visit(WhileStatement n) {
        String elseLabel, whileLabel;
        elseLabel = "while_else_" + whileElseCount++;
        whileLabel = "while_" + whileCount++;
        print("%s:", whileLabel);
        n.f2.accept(this);
        print("if0 %s goto :%s", printVar(lastExpression), elseLabel);
        indent++;
        n.f4.accept(this);
        print("goto :%s", whileLabel);
        indent--;
        print("%s:", elseLabel);
    }

    @Override
    public void visit(PrintStatement n) {
        n.f2.accept(this);
        print("PrintIntS(%s)", printVar(lastExpression));
    }

    /** EXPRESSIONS
     * f0 -> AndExpression()
     *       | CompareExpression()
     *       | PlusExpression()
     *       | MinusExpression()
     *       | TimesExpression()
     *       | ArrayLookup()
     *       | ArrayLength()
     *       | MessageSend()
     *       | PrimaryExpression()
     */

    @Override
    public void visit(AndExpression n) {
        n.f0.accept(this);
        String andElseLabel = "and_else_" + andElseCount++;
        String andEndLabel = "and_end_" + andEndCount++;
        String lhs = printVar(lastExpression);
        print("if0 %s goto :%s", lhs, andElseLabel);
        indent++;
        n.f2.accept(this);
        String rhs = printVar(lastExpression);
        String result = String.format("t.%d", varCount++);
        print("%s = %s", result, rhs);
        print("goto :%s", andEndLabel);
        indent--;
        print("%s:", andElseLabel);
        print("%s = 0", result);
        print("%s:", andEndLabel);
        lastExpression = new LastExpression(result, "ID");
    }

    @Override
    public void visit(CompareExpression n) {
        n.f0.accept(this);
        LastExpression lhs = lastExpression;
        n.f2.accept(this);
        LastExpression rhs = lastExpression;
        lastExpression = new LastExpression(String.format("LtS(%s %s)", printVar(lhs), printVar(rhs)), "EXPR");
    }

    @Override
    public void visit(PlusExpression n) {
        n.f0.accept(this);
        LastExpression lhs = lastExpression;
        n.f2.accept(this);
        LastExpression rhs = lastExpression;
        lastExpression = new LastExpression(String.format("Add(%s %s)", printVar(lhs), printVar(rhs)), "EXPR");
    }

    @Override
    public void visit(MinusExpression n){
        n.f0.accept(this);
        LastExpression lhs = lastExpression;
        n.f2.accept(this);
        LastExpression rhs = lastExpression;
        lastExpression = new LastExpression(String.format("Sub(%s %s)", printVar(lhs), printVar(rhs)), "EXPR");
    }

    @Override
    public void visit(TimesExpression n) {
        n.f0.accept(this);
        LastExpression lhs = lastExpression;
        n.f2.accept(this);
        LastExpression rhs = lastExpression;
        lastExpression = new LastExpression(String.format("MulS(%s %s)", printVar(lhs), printVar(rhs)), "EXPR");
    }

    @Override
    public void visit(ArrayLookup n) {
        String startAddr, index, offset, size;
        n.f0.accept(this);
        startAddr = printVar(lastExpression);
        printNull(startAddr);
        n.f2.accept(this);
        index = printVar(lastExpression);
        printBounds(startAddr, index);
        offset = String.format("t.%d", varCount++);
        print("%s = Add(%s 1)", offset, index);
        print("%s = MulS(%s 4)", offset, offset);
        size = String.format("t.%d", varCount++);
        print("%s = Add(%s %s)", size, startAddr, offset);
        lastExpression = new LastExpression(String.format("[%s]", size), "EXPR");
    }

    @Override
    public void visit(ArrayLength n) {
        n.f0.accept(this);
        String startAddr = printVar(lastExpression);
        printNull(startAddr);
        lastExpression = new LastExpression(String.format("[%s]", startAddr), "EXPR");
    }

    @Override
    public void visit(MessageSend n) {
        n.f0.accept(this);
        LastExpression le = lastExpression;

        String callInstance = printVar(le);
        if (!callInstance.equals("this"))
            printNull(callInstance);

        String method = n.f2.f0.toString();
        String parameters = callInstance;
        if (n.f4.present()) {
            ExpressionList eList = (ExpressionList)n.f4.node;
            eList.f0.accept(this);
            parameters += " " + printVar(lastExpression);
            for (Node node : eList.f1.nodes) {
                node.accept(this);
                parameters += " " + printVar(lastExpression);
            }
        }

        // Get method from class
        ClassType classType = le.classType;
        if (classType == null)
            classType = symbolTable.classTable.get(lastType.id);
        MethodType methodType = classType.classMethods.get(method);
        if (methodType == null) {
            ClassType parent = classType.parent;
            while (parent != null) {
                methodType = parent.classMethods.get(method);
                if (methodType != null) {
                    classType = parent;
                    break;
                }
                parent = parent.parent;
            }
        }
        String var =  String.format("t.%d", varCount++);
        String functionVar = String.format("t.%d", varCount++);
        int index = 0;
        boolean methodFound = false;
        for (MethodType methodType1 : classType.classMethods.values()) {
            if (methodType1.name.equals(method)) {
                methodFound = true;
                break;
            }
            index++;
        }
        if (!methodFound) {
            print("%s = call :%s.%s(%s)", functionVar, classType.name, method, parameters);
        } else {
//            String var =  String.format("t.%d", varCount++);
            print("%s = [%s]", var, callInstance);
            print("%s = [%s+%d]", var, var, index*4);
            print("%s = call %s(%s)", functionVar, var, parameters);
        }
        BaseType retType = methodType.returnType;
        lastType = retType;
        if (retType.type.equals("Other")) {
            lastExpression = new LastExpression(functionVar, "ID", symbolTable.classTable.get(retType.id));
        } else {
            lastExpression = new LastExpression(functionVar, "ID");
        }
    }

    /** PRIMARY EXPRESSIONS
     * f0 -> IntegerLiteral()
     *       | TrueLiteral()
     *       | FalseLiteral()
     *       | Identifier()
     *       | ThisExpression()
     *       | ArrayAllocationExpression()
     *       | AllocationExpression()
     *       | NotExpression()
     *       | BracketExpression()
     */

    @Override
    public void visit(IntegerLiteral n) {
        lastExpression = new LastExpression(n.f0.toString(), "INTEGER");
    }

    @Override
    public void visit(TrueLiteral n) {
        lastExpression = new LastExpression("1", "BOOLEAN");
    }

    @Override
    public void visit(FalseLiteral n) {
        lastExpression = new LastExpression("0", "BOOLEAN");
    }

    @Override
    public void visit(Identifier n) {
        BaseType type;
        String identifier = n.f0.toString();
        if (classIdentifier) {
            lastExpression = new LastExpression(identifier, "ID", symbolTable.classTable.get(identifier));
        } else {
            type = symbolTable.methodScope.methodVariables.get(identifier);
            if (type != null) {
                if (type.type.equals("Custom"))
                    lastExpression = new LastExpression(identifier, "ID", symbolTable.classTable.get(type.id));
                else
                    lastExpression = new LastExpression(identifier, "ID");
                return;
            }

            type = symbolTable.methodScope.methodParameters.get(identifier);
            if (type != null) {
                if (type.type.equals("Custom"))
                    lastExpression = new LastExpression(identifier, "ID", symbolTable.classTable.get(type.id));
                else
                    lastExpression = new LastExpression(identifier, "ID");
                return;
            }

            boolean found_offset = false;
            ClassType classType = symbolTable.classScope;
            int offset = 0;
            for (String classField : classType.classVariables.keySet()) {
                if (classField.equals(identifier)) {
                    found_offset = true;
                    break;
                }
                offset++;
            }
            if (!found_offset) {
                ClassType parent = classType.parent;
                while (parent != null) {
                    for (String classField : parent.classVariables.keySet()) {
                        if (classField.equals(identifier)) {
                            break;
                        }
                        offset++;
                    }
                    parent = parent.parent;
                }
            }
            String field = String.format("[this+%d]", (offset + 1) * 4);
            type = symbolTable.classScope.classVariables.get(identifier);
            if (type == null) {
                ClassType parentClass = symbolTable.classScope.parent;
                while (parentClass != null) {
                    type = parentClass.classVariables.get(identifier);
                    if (type != null)
                        break;
                    parentClass = parentClass.parent;
                }
            }
            if (type.type.equals("Custom"))
                lastExpression = new LastExpression(field, "EXPR", symbolTable.classTable.get(type.id));
            else
                lastExpression = new LastExpression(field, "EXPR");
        }
    }

    @Override
    public void visit(ThisExpression n) {
        lastExpression = new LastExpression("this", "ID", symbolTable.classScope);
    }

    @Override
    public void visit(ArrayAllocationExpression n) {
        allocatingArray = true;
        n.f3.accept(this);
        String var1 = printVar(lastExpression);
        String var2 = String.format("t.%d", varCount++);
        print("%s = call :AllocArray(%s)", var2, var1);
        lastExpression = new LastExpression(var2, "ID");
    }

    @Override
    public void visit(AllocationExpression n) {
        classIdentifier = true;
        n.f1.accept(this);
        classIdentifier = false;
        String var = String.format("t.%d", varCount++);
//        String nullLabel = "null" + nullCount++;
        ClassType classType = symbolTable.classTable.get(lastExpression.string);
        int fieldCount = classType.classVariables.values().size();
        ClassType parent = classType.parent;
        while (parent != null) {
            fieldCount += parent.classVariables.values().size();
            parent = parent.parent;
        }
        print("%s = HeapAllocZ(%d)", var, (fieldCount + 1) * 4);
        printNull(var);
        print("[%s] = :vmt_%s", var, lastExpression.string);
        lastExpression = new LastExpression(var, "ID", lastExpression.classType);
    }

    @Override
    public void visit(NotExpression n) {
        n.f1.accept(this);
        String notElseLabel = "not_else_" + notElseCount++;
        String notEndLabel = "not_end_" + notEndCount++;
        String var1 = printVar(lastExpression);
        String var2 = String.format("t.%d", varCount++);

        print("if %s goto :%s", var1, notElseLabel);
        indent++;
        print("%s = 1", var2);
        print("goto :%s", notEndLabel);
        indent--;
        print("%s:", notElseLabel);
        print("%s = 0", var2);
        print("%s:", notEndLabel);
        lastExpression = new LastExpression(var2, "ID");
    }

    @Override
    public void visit(MethodDeclaration n) {
        varCount = 0;
        symbolTable.methodScope = symbolTable.classScope.classMethods.get(n.f2.f0.toString());
        print("");
        String argString = "";
        for (String s : symbolTable.methodScope.methodParameters.keySet()) {
            argString = argString + " " + s;
        }
        print("func %s.%s(this%s)", symbolTable.classScope.name, symbolTable.methodScope.name, argString);
        indent++;
        n.f8.accept(this);
        n.f10.accept(this);
        print("ret %s", printVar(lastExpression));
        symbolTable.methodScope = null;
        indent--;
    }


    private void printAllocArray() {
        print("");
        print("func AllocArray(size)");
        indent++;
        print("t.neg = LtS(-1 size)");
        print("if0 t.neg goto :array_size_error");
        indent++;
        print("t.1 = Add(size 1)");
        print("t.0 = MulS(t.1 4)");
        print("a = HeapAllocZ(t.0)");
        print("[a] = size");
        print("goto :array_size_end");
        indent--;
        print("array_size_error:");
        indent++;
        print("Error(\"array index out of bounds\")");
        print("goto :array_size_end");
        indent--;
        print("array_size_end:");
        print("ret a");
    }
}