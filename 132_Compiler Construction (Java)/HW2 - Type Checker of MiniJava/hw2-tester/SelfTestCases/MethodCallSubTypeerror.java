class Main {
	public static void main(String[] s){
		A myVar;
		int x;
		x = new A().run(1); // TE
        }
}

class Base {
}

class Derived extends Base {
}

class A {
        public int run(Base b) {
		return 1;
	}
}
