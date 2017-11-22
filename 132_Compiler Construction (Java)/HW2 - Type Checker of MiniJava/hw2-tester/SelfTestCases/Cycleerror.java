class Main {
	public static void main(String[] a){
		System.out.println(new A().run());
	}
}

class A extends D { // TE
	public int run() {
		int x;
		x = 1;
		return x;
	}
}

class B extends A {
}

class C extends B {
}

class D extends C {
}
