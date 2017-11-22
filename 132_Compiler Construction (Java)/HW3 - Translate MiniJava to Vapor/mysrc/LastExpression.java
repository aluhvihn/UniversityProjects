package mysrc;

public class LastExpression {
    String string;
    String type;    // INTEGER, BOOLEAN, ID, EXPR
    ClassType classType;

    public LastExpression(String string, String type) {
        this.string = string;
        this.type = type;
        classType = null;
    }

    public LastExpression(String string, String type, ClassType classType) {
        this.string = string;
        this.type = type;
        this.classType = classType;
    }
}
