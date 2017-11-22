package mysrc;

import java.util.*;

public class ClassType {
    public LinkedHashMap<String, BaseType> classVariables = new LinkedHashMap<String, BaseType>();
    public LinkedHashMap<String, MethodType> classMethods = new LinkedHashMap<String, MethodType>();

    public String name;
    public ClassType parent = null;
    public boolean found;

    public ClassType(String id) {
        name = id;
        found = true;
    }

    public MethodType addMethod(String id, BaseType returnType) {
        MethodType methodType = classMethods.get(id);
        // Add method
        if (methodType == null) {
            methodType = new MethodType(id, returnType);
            classMethods.put(id, methodType);
            return  methodType;
        }
        // Duplicate method
        return null;
    }

    public MethodType getMethod(String id) {
        ClassType classType = this;
        while (classType != null) {
            MethodType ret = classType.classMethods.get(id);
            if (ret != null) {
                return ret;
            }
            classType = classType.parent;
        }
        return null;
    }
}
