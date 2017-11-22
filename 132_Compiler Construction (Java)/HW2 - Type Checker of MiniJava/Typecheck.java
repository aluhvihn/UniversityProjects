import syntaxtree.*;
import mysrc.*;

/** The typechecker for MiniJava. **/
public class Typecheck {
  public static void main (String [] args) {
    try {
      Goal goal = new MiniJavaParser(System.in).Goal();
      SymbolTable symTable = new SymbolTable();
      if (goal.accept(symTable) == null) {
        System.out.println("Type error");
        System.exit(1);
      }
      BaseType result = goal.accept(new Typechecker(symTable));
      if (result == null) {
        System.out.println("Type error");
        System.exit(1);
      }
      System.out.println("Program type checked successfully");
    } catch (ParseException e) {
      System.out.println("Type error");
      System.exit(-1);
    }
  }
}
