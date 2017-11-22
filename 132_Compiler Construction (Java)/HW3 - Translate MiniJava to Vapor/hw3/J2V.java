import syntaxtree.*;
import mysrc.*;

import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class J2V {
    public static void main (String [] args) {
        try {
            Goal goal = new MiniJavaParser(System.in).Goal();
//            Goal goal = new MiniJavaParser(new FileInputStream("hw3tester/hw3-tester/SelfTestCases/LinkedList.java")).Goal();
//            Goal goal = new MiniJavaParser(new FileInputStream("hw3tester/hw3-tester/SelfTestCases/Factorial.java")).Goal();
//            Goal goal = new MiniJavaParser(new FileInputStream("hw3tester/hw3-tester/SelfTestCases/BinaryTree.java")).Goal();
//            Goal goal = new MiniJavaParser(new FileInputStream("hw3tester/hw3-tester/SelfTestCases/5-OutOfBounds.java")).Goal();
            SymbolTable symTable = new SymbolTable();
            if (goal.accept(symTable) == null) {
                System.out.println("Type error");
                System.exit(1);
            }
//            BaseType result = goal.accept(new Typechecker(symTable));
//            if (result == null) {
//                System.out.println("Type error");
//                System.exit(1);
//            }
//            System.out.println("Program type checked successfully");

            // Translate MiniJava to Vapor
            Translate translate = new Translate(symTable);
            goal.accept(translate);
        } catch (ParseException e) {
            System.out.println(e.toString());
            System.exit(-1);
        }
//        catch (FileNotFoundException e) {
//            e.printStackTrace();
//        }
    }
}
