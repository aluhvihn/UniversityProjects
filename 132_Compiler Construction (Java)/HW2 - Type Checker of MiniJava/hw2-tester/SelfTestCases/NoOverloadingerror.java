class Main {
	public static void main(String[] a){
		System.out.println(new A().run());
	}
}

class A {
	public int run() {
		int x;
		x = 1;
		return x;
	}
}

class C extends A {
}

class B extends C {
	public int run(int x) { // TE
		return x;
	}
}
