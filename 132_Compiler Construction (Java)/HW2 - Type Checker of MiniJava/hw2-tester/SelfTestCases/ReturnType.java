class Main {
	public static void main(String[] a){
		System.out.println(37);
	}
}

class A {

}

class B extends A {

}

class C  {
	public A foo() {
		return new A();
	}
}

