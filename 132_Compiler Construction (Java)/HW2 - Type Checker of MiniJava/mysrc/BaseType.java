package mysrc;

public class BaseType {
    public String type;
    public String id;

    public static BaseType OTHER = new BaseType("Other");
    public static BaseType ARRAY = new BaseType("Array");
    public static BaseType BOOLEAN = new BaseType("Boolean");
    public static BaseType INTEGER = new BaseType("Integer");
    public static BaseType CUSTOM = new BaseType("Custom");

    public BaseType(String type) {
        this.type = type;
        this.id = "";
    }

    public BaseType(String type, String id) {
        this.type = type;
        this.id = id;
    }
}
