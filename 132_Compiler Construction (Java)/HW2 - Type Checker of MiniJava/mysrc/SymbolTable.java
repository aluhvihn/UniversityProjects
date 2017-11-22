package mysrc;

import syntaxtree.*;
import visitor.GJNoArguDepthFirst;
import java.util.*;

public class SymbolTable extends GJNoArguDepthFirst<Boolean> {
	public HashMap<String, ClassType> classTable;
	public ClassType classScope = null;
	public MethodType methodScope = null;

	public SymbolTable() {
		classTable = new HashMap<String, ClassType>();
	}

	ClassType addClass(String id) {
		ClassType classType = classTable.get(id);

		if (classType == null) {
			// class not added, add it
			classType = new ClassType(id);
			classTable.put(id, classType);
		} else if (!classType.found) {
			// class added
			classType.found = true;
		} else {
			// duplicate class
			return null;
		}

		return classType;
	}

	ClassType addClass(String id, String parent) {
		ClassType classType = addClass(id);
		if (classType == null) {
			return null;
		}
		classType.parent = classTable.get(parent);
		if (classType.parent == null) {
			classType.parent = new ClassType(parent);
			classType.parent.found = false;
			classTable.put(parent, classType.parent);
		}
		return classType;
	}

	BaseType getType(Type type) {
		switch (type.f0.which) {
			case 0:
				return BaseType.ARRAY;
			case 1:
				return BaseType.BOOLEAN;
			case 2:
				return BaseType.INTEGER;
			case 3:	// IDENTIFIER
				String id = ((Identifier) type.f0.choice).f0.toString();
				BaseType baseType = new BaseType("Custom", id);
				// Not in table; add it
				if (classTable.get(id) == null) {
					ClassType classType = new ClassType(id);
					classType.found = false;
					classTable.put(id, classType);
				}
				return baseType;
			default:
				return null;
		}
	}

	boolean addMethod(String id, BaseType returnType) {
		if (classScope.addMethod(id, returnType) == null) {
			return false;
		}
		return true;
	}

	boolean addVar(String id, BaseType varType) {
		if (methodScope != null) {
			return methodScope.addVar(id, varType);
		}
		if (classScope.classVariables.get(id) == null) {
			classScope.classVariables.put(id, varType);
			return true;
		}
		return false;

	}

	boolean addParameter(String id, BaseType paramType) {
		return methodScope.addParameter(id, paramType);
	}

	boolean hasOverloading() {
		ClassType parent = null;
		for (ClassType classType : classTable.values()) {
			parent = classType.parent;
			// if class has no parent, it won't be overloading anything
			while (parent != null) {
				for (MethodType classMethod : classType.classMethods.values()) {
					MethodType parentMethod = parent.classMethods.get(classMethod.name);
					// if parentMethod exists, there is a method in the parent class with same name
					if (parentMethod != null) {
						Iterator<BaseType> parentParams = parentMethod.methodParameters.values().iterator();
						for (BaseType methodParams : classMethod.methodParameters.values()) {
							// method has more parameters than parent, or different type of parameter
							if (!parentParams.hasNext()) {
								return true;
							}
							BaseType currParentParam = parentParams.next();
							if (!methodParams.type.equals(currParentParam.type)) {
								return true;
							}
							if (!methodParams.id.equals(currParentParam.id)) {
								return true;
							}
						}
						// method has less parameters than parent
						if (parentParams.hasNext()) {
							return true;
						}
						// method returns different type from parent
						if (parent.classMethods.get(classMethod.name).returnType != classMethod.returnType) {
							return true;
						}
					}
				}
				// Check if parent has overloading
				parent = parent.parent;
			}
		}
		return false;
	}

	boolean hasCycles() {
		ClassType parent;
		int i, numClasses = classTable.size() - 1;
		for (ClassType classType : classTable.values()) {
			parent = classType.parent;
			i = 0;
			// Check through all of parent's parents to see if same class occurs
			while (parent != null && i < numClasses) {
				if (classType == parent) {
					return true;
				}
				parent = parent.parent;
				++i;
			}
		}
		return false;
	}

	@Override
	public Boolean visit(Goal n) {
		// MainClass
		if (n.f0.accept(this) == null) {
			return null;
		}
		// TypeDeclaration
		if (n.f1.accept(this) == null) {
			return null;
		}
		// Check for class cycles
		if (hasCycles()) {
			return null;
		}
		// Check for overloading
		if (hasOverloading()) {
			return null;
		}
		// Check that all classes initialized
		for (ClassType classType : classTable.values()) {
			if (!classType.found) {
				return null;
			}
		}
		return true;
	}

	/* MAIN CLASS */
	@Override
	public Boolean visit(MainClass n) {
		// set class scope, add to table
		classScope = addClass(n.f1.f0.toString());
		if (classScope == null) {
			return null;
		}

		// Method Scope, add to class
		methodScope = classScope.addMethod("main", BaseType.OTHER);
		if (methodScope == null) {
			return null;
		}
		if (!methodScope.addParameter(n.f11.f0.toString(), BaseType.OTHER)) {
			return null;
		}

		// Variable Declarations
		Boolean ret = n.f14.accept(this);

		// Clear Scopes
		classScope = null;
		methodScope = null;

		return ret;
	}

	/* TYPE DECLARATIONS (INSIDE NodeListOptional) */
	@Override
	public Boolean visit(NodeListOptional n) {
		// go through each Node in NodeListOptional
		if ( n.present() ) {
			for ( Enumeration<Node> e = n.elements(); e.hasMoreElements(); ) {
				if (e.nextElement().accept(this) == null)
					return null;
			}
		}
		// if NodeListOptional empty, return true
		return true;
	}

	@Override
	public Boolean visit(TypeDeclaration n) {
		return n.f0.accept(this);
	}

	@Override
	public Boolean visit(ClassDeclaration n) {
		// set class scope, add to table
		classScope = addClass(n.f1.f0.toString());
		if (classScope == null) {
			return null;
		}

		// Variable Declarations
		if (n.f3.accept(this) == null) {
			return null;
		}

		// Method Declarations
		Boolean ret = n.f4.accept(this);

		// Clear Class Scope
		classScope = null;

		return ret;
	}

	@Override
	public Boolean visit(ClassExtendsDeclaration n) {
		classScope = addClass(n.f1.f0.toString(), n.f3.f0.toString());
		if (classScope == null) {
			return null;
		}
		if (n.f5.accept(this) == null) {
			return null;
		}
		Boolean ret = n.f6.accept(this);
		classScope = null;
		return ret;
	}

	@Override
	public Boolean visit(VarDeclaration n) {
		if (!addVar(n.f1.f0.toString(), getType(n.f0))) {
			return null;
		}
		return true;
	}

	@Override
	public Boolean visit(MethodDeclaration n) {
		if (!addMethod(n.f2.f0.toString(), getType(n.f1))) {
			return null;
		}
		methodScope = classScope.getMethod(n.f2.f0.tokenImage);

		// Formal Parameters
		if (n.f4.accept(this) == null) {
			return null;
		}
		// Variable Declarations
		Boolean ret = n.f7.accept(this);;
		methodScope = null;
		return ret;
	}

	@Override
	public Boolean visit(NodeOptional n) {
		if (n.present()) {
			return n.node.accept(this);
		}
		return true;
	}

	@Override
	public Boolean visit(FormalParameterList n) {
		if (n.f0.accept(this) == null) {
			return null;
		}
		return n.f1.accept(this);
	}

	@Override
	public Boolean visit(FormalParameter n) {
		if (addParameter(n.f1.f0.toString(), getType(n.f0))) {
			return true;
		}
		return null;
	}

	@Override
	public Boolean visit(FormalParameterRest n) {
		return n.f1.accept(this);
	}

	public boolean isSubclass(BaseType child, BaseType parent) {
		if (child == null || parent == null) {
			return false;
		}
		if (!child.type.equals("Custom") || !parent.type.equals("Custom")) {
			return equalTypes(child, parent);
		}
		while (!equalTypes(child, parent)) {
			ClassType classType = classTable.get(child.id);
			if (classType.parent == null) {
				return false;
			}
			child = new BaseType("Custom", classType.parent.name);
		}
		return true;
	}

	public boolean equalTypes(Object object1, Object object2) {
		if (!(object1 instanceof BaseType) || !(object2 instanceof BaseType)) {
			return false;
		}
		if (object1 == object2) {
			return true;
		}
		BaseType type1 = (BaseType) object1;
		BaseType type2 = (BaseType) object2;

		if (type1.type.equals(type2.type)) {
			if (type1.type.equals("Custom") && type2.type.equals("Custom")) {
				return (type1.id.equals(type2.id));
			}
			return true;
		}
		return false;
	}

	public MethodType getMethod(String classID, String methodID) {
		ClassType classType = classTable.get(classID);
		if (classType == null) {
			return null;
		}
		MethodType methodType = classType.classMethods.get(methodID);
		if (methodType != null) {
			return methodType;
		}
		ClassType parent = classType.parent;
		while (parent != null) {
			methodType = parent.classMethods.get(methodID);
			if (methodType != null) {
				return methodType;
			}
			parent = parent.parent;
		}
		return null;
	}
}