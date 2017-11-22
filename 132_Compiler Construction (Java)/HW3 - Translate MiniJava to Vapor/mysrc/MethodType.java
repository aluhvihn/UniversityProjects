package mysrc;

import java.util.LinkedHashMap;

public class MethodType {
    public String name;
    public BaseType returnType;
    public LinkedHashMap<String, BaseType> methodParameters;
    public LinkedHashMap<String, BaseType> methodVariables;

    MethodType(String name, BaseType returnType) {
        this.name = name;
        this.returnType = returnType;
        methodParameters = new LinkedHashMap<String, BaseType>();
        methodVariables = new LinkedHashMap<String, BaseType>();
    }

    public boolean addParameter(String id, BaseType type) {
        if (methodParameters.containsKey(id)) {
            // Duplicate parameter
            return false;
        }
        // Add parameter
        methodParameters.put(id, type);
        return true;
    }

    public boolean addVar(String id, BaseType type) {
        if (methodParameters.get(id) != null || methodVariables.get(id) != null) {
            return false;
        }
        methodVariables.put(id, type);
        return true;
    }
}
