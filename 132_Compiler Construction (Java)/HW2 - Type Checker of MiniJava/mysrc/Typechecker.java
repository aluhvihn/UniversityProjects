package mysrc;

import syntaxtree.*;
import visitor.GJNoArguDepthFirst;
import java.util.*;

public class Typechecker extends GJNoArguDepthFirst<BaseType> {
    private final SymbolTable symbolTable;
    public boolean typeIdentifier = false;

    public Typechecker(SymbolTable symbolTable) {
        this.symbolTable = symbolTable;
    }

    @Override
    public BaseType visit(Type n) {
        typeIdentifier = true;
        BaseType result = n.f0.accept(this);
        typeIdentifier = false;
        return result;
    }

    @Override
    public BaseType visit(ArrayType n) {
        return BaseType.ARRAY;
    }

    @Override
    public BaseType visit(BooleanType n) {
        return BaseType.BOOLEAN;
    }

    @Override
    public BaseType visit(IntegerType n) {
        return BaseType.INTEGER;
    }

    @Override
    public BaseType visit(Block n) {
        return n.f1.accept(this);
    }

    @Override
    public BaseType visit(Goal n) {
        if (n.f0.accept(this) == null) {
            return null;
        }
        return n.f1.accept(this);
    }

    @Override
    public BaseType visit(MainClass n) {
        // set scopes
        symbolTable.classScope = symbolTable.classTable.get(n.f1.f0.toString());
        symbolTable.methodScope = symbolTable.classScope.classMethods.get("main");

        // Statements
        BaseType result = n.f15.accept(this);

        // clear scopes
        symbolTable.classScope = null;
        symbolTable.methodScope = null;

        return result;
    }

    /* TYPE DECLARATIONS (INSIDE NodeListOptional) */
    @Override
    public BaseType visit(NodeListOptional n) {
        // go through each Node in NodeListOptional
        if ( n.present() ) {
            for ( Enumeration<Node> e = n.elements(); e.hasMoreElements(); ) {
                if (e.nextElement().accept(this) == null)
                    return null;
            }
        }
        // if NodeListOptional empty, return true
        return BaseType.OTHER;
    }

    @Override
    public BaseType visit(TypeDeclaration n) {
        return n.f0.accept(this);
    }

    @Override
    public BaseType visit(ClassDeclaration n) {
        symbolTable.classScope = symbolTable.classTable.get(n.f1.f0.toString());
        BaseType ret = n.f4.accept(this);
        symbolTable.classScope = null;
        return ret;
    }

    @Override
    public BaseType visit(ClassExtendsDeclaration n) {
        symbolTable.classScope = symbolTable.classTable.get(n.f1.f0.toString());
        BaseType ret = n.f6.accept(this);
        symbolTable.classScope = null;
        return ret;
    }

    @Override
    public BaseType visit(VarDeclaration n) {
        return null;
    }

    @Override
    public BaseType visit(MethodDeclaration n) {
        symbolTable.methodScope = symbolTable.classScope.getMethod(n.f2.f0.toString());
        if (n.f8.accept(this) == null) {
            return null;
        }
        if (n.f10.accept(this) == null) {
            return null;
        }
        BaseType ret = null;
        if (symbolTable.equalTypes(n.f10.accept(this), symbolTable.methodScope.returnType)) {
            ret = BaseType.OTHER;
        }
//        if (symbolTable.isSubclass(n.f10.accept(this), symbolTable.methodScope.returnType)) {
//            ret = BaseType.OTHER;
//        }
        symbolTable.methodScope = null;
        return ret;
    }

    @Override //TODO
    public BaseType visit(NodeOptional n) {
        return null;
    }

    @Override
    public BaseType visit(FormalParameterList n) {
        return null;
    }

    @Override
    public BaseType visit(FormalParameter n) {
        return null;
    }

    @Override
    public BaseType visit(FormalParameterRest n) {
        return null;
    }

    @Override
    public BaseType visit(Statement n) {
        return n.f0.choice.accept(this);
    }

    @Override
    public BaseType visit(AssignmentStatement n) {
        BaseType lhs = n.f0.accept(this);
        BaseType rhs = n.f2.accept(this);
        if (lhs != null && rhs != null && symbolTable.isSubclass(rhs, lhs)) {
            return BaseType.OTHER;
        }
        return null;
    }

    @Override
    public BaseType visit(ArrayAssignmentStatement n) {
        if (n.f0.accept(this) == BaseType.ARRAY &&
                n.f2.accept(this) == BaseType.INTEGER &&
                n.f5.accept(this) == BaseType.INTEGER) {
            return BaseType.OTHER;
        }
        return null;
    }

    @Override
    public BaseType visit(IfStatement n) {
        if (n.f2.accept(this) == BaseType.BOOLEAN &&
                n.f4.accept(this) != null && n.f6.accept(this) != null) {
            return BaseType.OTHER;
        }
        return null;
    }

    @Override
    public BaseType visit(WhileStatement n) {
        if (n.f2.accept(this) == BaseType.BOOLEAN && n.f4.accept(this) != null) {
            return BaseType.OTHER;
        }
        return null;
    }

    @Override
    public BaseType visit(PrintStatement n) {
        // Expression
        if (n.f2.accept(this) == BaseType.INTEGER) {
            return BaseType.OTHER;
        }
        return null;
    }

    @Override
    public BaseType visit(Expression n) {
        return n.f0.accept(this);
    }

    @Override
    public BaseType visit(AndExpression n) {
        if (n.f0.accept(this) == BaseType.BOOLEAN && n.f2.accept(this) == BaseType.BOOLEAN) {
            return BaseType.BOOLEAN;
        }
        return null;
    }

    @Override
    public BaseType visit(CompareExpression n) {
        if (n.f0.accept(this) == BaseType.INTEGER && n.f2.accept(this) == BaseType.INTEGER) {
            return BaseType.BOOLEAN;
        }
        return null;
    }

    @Override
    public BaseType visit(PlusExpression n) {
        if (n.f0.accept(this) == BaseType.INTEGER && n.f2.accept(this) == BaseType.INTEGER) {
            return BaseType.INTEGER;
        }
        return null;
    }

    @Override
    public BaseType visit(MinusExpression n) {
        if (n.f0.accept(this) == BaseType.INTEGER && n.f2.accept(this) == BaseType.INTEGER) {
            return BaseType.INTEGER;
        }
        return null;
    }

    @Override
    public BaseType visit(TimesExpression n) {
        if (n.f0.accept(this) == BaseType.INTEGER && n.f2.accept(this) == BaseType.INTEGER) {
            return BaseType.INTEGER;
        }
        return null;
    }

    @Override
    public BaseType visit(ArrayLookup n) {
        if (n.f0.accept(this) == BaseType.ARRAY && n.f2.accept(this) == BaseType.INTEGER) {
            return BaseType.INTEGER;
        }
        return null;
    }

    @Override
    public BaseType visit(ArrayLength n) {
        if (n.f0.accept(this) == BaseType.ARRAY) {
            return BaseType.INTEGER;
        }
        return null;
    }

    @Override
    public BaseType visit(MessageSend n) {
        BaseType type = n.f0.accept(this);
        if (type == null || !type.type.equals("Custom")) {
            return null;
        }
        MethodType methodType = symbolTable.getMethod(type.id, n.f2.f0.toString());
        if (methodType == null) {
            return null;
        }
        // check parameters
        Collection<BaseType> parameters = methodType.methodParameters.values();
        if (n.f4.present()) {
            if (parameters == null) {
                return null;
            }
            LinkedList<BaseType> queue = new LinkedList<BaseType>(parameters);
            ExpressionList list = (ExpressionList)n.f4.node;
            if (!symbolTable.isSubclass(list.f0.accept(this), queue.remove())) {
                return null;
            }
            if (list.f1.present()) {
                for (Node node : list.f1.nodes) {
                    if (queue.isEmpty()) {
                        return null;
                    }
                    if (!symbolTable.isSubclass(node.accept(this), queue.remove())) {
                        return null;
                    }
                }
            }
            if (!queue.isEmpty()) {
                return null;
            }
        } else if (!parameters.isEmpty()) {
            return null;
        }
        return methodType.returnType;
    }

    @Override
    public BaseType visit(ExpressionRest n) {
        return n.f1.accept(this);
    }

    @Override
    public BaseType visit(PrimaryExpression n) {
        return n.f0.accept(this);
    }

    @Override
    public BaseType visit(IntegerLiteral n) {
        return BaseType.INTEGER;
    }

    @Override
    public BaseType visit(TrueLiteral n) {
        return BaseType.BOOLEAN;
    }

    @Override
    public BaseType visit(FalseLiteral n) {
        return BaseType.BOOLEAN;
    }

    @Override
    public BaseType visit(Identifier n) {
        if (typeIdentifier) {
            ClassType classType = symbolTable.classTable.get(n.f0.toString());
            if (classType == null) {
                return null;
            }
            return new BaseType("Custom", classType.name);
        }
        // check local vars
        BaseType identifierType = symbolTable.methodScope.methodVariables.get(n.f0.toString());
        if (identifierType != null) {
            return identifierType;
        }
        // check params
        identifierType = symbolTable.methodScope.methodParameters.get(n.f0.toString());
        if (identifierType != null) {
            return identifierType;
        }
        // check class vars
        ClassType classType = symbolTable.classScope;
        while (classType != null) {
            identifierType = classType.classVariables.get(n.f0.toString());
            if (identifierType != null) {
                return  identifierType;
            }
            classType = classType.parent;
        }
        return null;
    }

    @Override
    public BaseType visit(ThisExpression n) {
        return new BaseType("Custom", symbolTable.classScope.name);
    }

    @Override
    public BaseType visit(ArrayAllocationExpression n) {
        // Expression
        if (n.f3.accept(this) == BaseType.INTEGER) {
            return BaseType.ARRAY;
        }
        return null;
    }

    @Override
    public BaseType visit(AllocationExpression n) {
        typeIdentifier = true;
        BaseType identifierType = n.f1.accept(this);
        typeIdentifier = false;
        return identifierType;
    }

    @Override
    public BaseType visit(NotExpression n) {
        if (n.f1.accept(this) == BaseType.BOOLEAN) {
            return BaseType.BOOLEAN;
        }
        return null;
    }

    @Override
    public BaseType visit(BracketExpression n) {
        return n.f1.accept(this);
    }
}
