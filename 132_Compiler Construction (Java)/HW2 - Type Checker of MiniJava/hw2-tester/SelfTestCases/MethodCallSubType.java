class Main {
	public static void main(String[] s){
		A myVar;
		int x;
		x = new A().run(new Derived());
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
