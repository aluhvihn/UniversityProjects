let accept_all derivation string = Some (derivation, string)
let accept_empty_suffix derivation = function
   | [] -> Some (derivation, [])
   | _ -> None

(* An example grammar for a small subset of Awk, derived from but not
   identical to the grammar in
   <http://web.cs.ucla.edu/classes/winter06/cs132/hw/hw1.html>.
   Note that this grammar is not the same as Homework 1; it is
   instead the same as the grammar under "Theoretical background"
   above.  *)

type awksub_nonterminals =
  | Expr | Term | Lvalue | Incrop | Binop | Num

let awkish_grammar =
  (Expr,
   function
     | Expr ->
         [[N Term; N Binop; N Expr];
          [N Term]]
     | Term ->
   [[N Num];
    [N Lvalue];
    [N Incrop; N Lvalue];
    [N Lvalue; N Incrop];
    [T"("; N Expr; T")"]]
     | Lvalue ->
   [[T"$"; N Expr]]
     | Incrop ->
   [[T"++"];
    [T"--"]]
     | Binop ->
   [[T"+"];
    [T"-"]]
     | Num ->
   [[T"0"]; [T"1"]; [T"2"]; [T"3"]; [T"4"];
    [T"5"]; [T"6"]; [T"7"]; [T"8"]; [T"9"]])

let test0 =
  ((parse_prefix awkish_grammar accept_all ["ouch"]) = None)

let test1 =
  ((parse_prefix awkish_grammar accept_all ["9"])
   = Some ([(Expr, [N Term]); (Term, [N Num]); (Num, [T "9"])], []))

let test2 =
  ((parse_prefix awkish_grammar accept_all ["9"; "+"; "$"; "1"; "+"])
   = Some
       ([(Expr, [N Term; N Binop; N Expr]); (Term, [N Num]); (Num, [T "9"]);
   (Binop, [T "+"]); (Expr, [N Term]); (Term, [N Lvalue]);
   (Lvalue, [T "$"; N Expr]); (Expr, [N Term]); (Term, [N Num]);
   (Num, [T "1"])],
  ["+"]))

let test3 =
  ((parse_prefix awkish_grammar accept_empty_suffix ["9"; "+"; "$"; "1"; "+"])
   = None)

(* This one might take a bit longer.... *)
let test4 =
 ((parse_prefix awkish_grammar accept_all
     ["("; "$"; "8"; ")"; "-"; "$"; "++"; "$"; "--"; "$"; "9"; "+";
      "("; "$"; "++"; "$"; "2"; "+"; "("; "8"; ")"; "-"; "9"; ")";
      "-"; "("; "$"; "$"; "$"; "$"; "$"; "++"; "$"; "$"; "5"; "++";
      "++"; "--"; ")"; "-"; "++"; "$"; "$"; "("; "$"; "8"; "++"; ")";
      "++"; "+"; "0"])
  = Some
     ([(Expr, [N Term; N Binop; N Expr]); (Term, [T "("; N Expr; T ")"]);
       (Expr, [N Term]); (Term, [N Lvalue]); (Lvalue, [T "$"; N Expr]);
       (Expr, [N Term]); (Term, [N Num]); (Num, [T "8"]); (Binop, [T "-"]);
       (Expr, [N Term; N Binop; N Expr]); (Term, [N Lvalue]);
       (Lvalue, [T "$"; N Expr]); (Expr, [N Term; N Binop; N Expr]);
       (Term, [N Incrop; N Lvalue]); (Incrop, [T "++"]);
       (Lvalue, [T "$"; N Expr]); (Expr, [N Term; N Binop; N Expr]);
       (Term, [N Incrop; N Lvalue]); (Incrop, [T "--"]);
       (Lvalue, [T "$"; N Expr]); (Expr, [N Term; N Binop; N Expr]);
       (Term, [N Num]); (Num, [T "9"]); (Binop, [T "+"]); (Expr, [N Term]);
       (Term, [T "("; N Expr; T ")"]); (Expr, [N Term; N Binop; N Expr]);
       (Term, [N Lvalue]); (Lvalue, [T "$"; N Expr]);
       (Expr, [N Term; N Binop; N Expr]); (Term, [N Incrop; N Lvalue]);
       (Incrop, [T "++"]); (Lvalue, [T "$"; N Expr]); (Expr, [N Term]);
       (Term, [N Num]); (Num, [T "2"]); (Binop, [T "+"]); (Expr, [N Term]);
       (Term, [T "("; N Expr; T ")"]); (Expr, [N Term]); (Term, [N Num]);
       (Num, [T "8"]); (Binop, [T "-"]); (Expr, [N Term]); (Term, [N Num]);
       (Num, [T "9"]); (Binop, [T "-"]); (Expr, [N Term]);
       (Term, [T "("; N Expr; T ")"]); (Expr, [N Term]); (Term, [N Lvalue]);
       (Lvalue, [T "$"; N Expr]); (Expr, [N Term]); (Term, [N Lvalue]);
       (Lvalue, [T "$"; N Expr]); (Expr, [N Term]); (Term, [N Lvalue]);
       (Lvalue, [T "$"; N Expr]); (Expr, [N Term]); (Term, [N Lvalue; N Incrop]);
       (Lvalue, [T "$"; N Expr]); (Expr, [N Term]); (Term, [N Lvalue; N Incrop]);
       (Lvalue, [T "$"; N Expr]); (Expr, [N Term]); (Term, [N Incrop; N Lvalue]);
       (Incrop, [T "++"]); (Lvalue, [T "$"; N Expr]); (Expr, [N Term]);
       (Term, [N Lvalue; N Incrop]); (Lvalue, [T "$"; N Expr]); (Expr, [N Term]);
       (Term, [N Num]); (Num, [T "5"]); (Incrop, [T "++"]); (Incrop, [T "++"]);
       (Incrop, [T "--"]); (Binop, [T "-"]); (Expr, [N Term]);
       (Term, [N Incrop; N Lvalue]); (Incrop, [T "++"]);
       (Lvalue, [T "$"; N Expr]); (Expr, [N Term]); (Term, [N Lvalue; N Incrop]);
       (Lvalue, [T "$"; N Expr]); (Expr, [N Term]);
       (Term, [T "("; N Expr; T ")"]); (Expr, [N Term]);
       (Term, [N Lvalue; N Incrop]); (Lvalue, [T "$"; N Expr]); (Expr, [N Term]);
       (Term, [N Num]); (Num, [T "8"]); (Incrop, [T "++"]); (Incrop, [T "++"]);
       (Binop, [T "+"]); (Expr, [N Term]); (Term, [N Num]); (Num, [T "0"])],
      []))

let rec contains_lvalue = function
  | [] -> false
  | (Lvalue,_)::_ -> true
  | _::rules -> contains_lvalue rules

let accept_only_non_lvalues rules frag =
  if contains_lvalue rules
  then None
  else Some (rules, frag)

let test5 =
  ((parse_prefix awkish_grammar accept_only_non_lvalues
      ["3"; "-"; "4"; "+"; "$"; "5"; "-"; "6"])
   = Some
      ([(Expr, [N Term; N Binop; N Expr]); (Term, [N Num]); (Num, [T "3"]);
  (Binop, [T "-"]); (Expr, [N Term]); (Term, [N Num]); (Num, [T "4"])],
       ["+"; "$"; "5"; "-"; "6"]))

(* Test your implementation of convert_grammar on the test grammars
   given in Homework 1. For example, the top-level definition let
   awksub_grammar_2 = convert_grammar awksub_grammar should bind
   awksub_grammar_2 to a Homework 2-style grammar that is equivalent
   to the Homework 1-style grammar awksub_grammar.*)
let awksub_rules =
   [Expr, [T"("; N Expr; T")"];
    Expr, [N Num];
    Expr, [N Expr; N Binop; N Expr];
    Expr, [N Lvalue];
    Expr, [N Incrop; N Lvalue];
    Expr, [N Lvalue; N Incrop];
    Lvalue, [T"$"; N Expr];
    Incrop, [T"++"];
    Incrop, [T"--"];
    Binop, [T"+"];
    Binop, [T"-"];
    Num, [T"0"];
    Num, [T"1"];
    Num, [T"2"];
    Num, [T"3"];
    Num, [T"4"];
    Num, [T"5"];
    Num, [T"6"];
    Num, [T"7"];
    Num, [T"8"];
    Num, [T"9"]];;

let awksub_grammar = Expr, awksub_rules;;

let convert_grammar_test0 = (
  (snd (convert_grammar awksub_grammar)) Expr = 
          [[T"("; N Expr; T")"];
           [N Num];
           [N Expr; N Binop; N Expr];
           [N Lvalue];
           [N Incrop; N Lvalue];
           [N Lvalue; N Incrop]
          ]);;

let convert_grammar_test1 = (
  (snd (convert_grammar awksub_grammar)) Lvalue = 
          [[T"$"; N Expr]]);;

let convert_grammar_test2 = (
  (snd (convert_grammar awksub_grammar)) Incrop = 
          [[T"++"];
           [T"--"]
          ]);;

let convert_grammar_test3 = (
  (snd (convert_grammar awksub_grammar)) Binop = 
          [[T"+"];
           [T"-"]
          ]);;

let convert_grammar_test4 = (
  (snd (convert_grammar awksub_grammar)) Num = 
          [[T"0"];
           [T"1"];
           [T"2"];
           [T"3"];
           [T"4"];
           [T"5"];
           [T"6"];
           [T"7"];
           [T"8"];
           [T"9"]
          ]);;

(* Write two good test cases for your parse_prefix function.
   These test cases should all be in the style of the test cases
   given below, but should cover different problem areas. Your test
   cases should be named test_1 and test_2 (note the underscores; this
   distinguishes your test cases from the standard ones given below).
   Your test cases should test at least one grammar of your own. You
   may reuse your test cases for Homework 1 as part of test_1,
   but test_2 should be new. *)
type dangling_else_nonterminals = Expression | ElseStatement

let ambiguous_grammar = (Expression, function 
  | Expression -> 
      [[T "if"; N Expression; T "then"; N Expression; T "else"; N Expression];
       [N ElseStatement];
       [T "if"; N Expression; T "then"; N Expression];
       [T "true"];
       [T "false"]]
  | ElseStatement -> [[T "else"; N ElseStatement]]);;

let test_1 = ((parse_prefix ambiguous_grammar accept_all 
  ["if"; "true";
   "then"; "if"; "false";
           "then"; "false";
           "else"; "true"
  ]) = Some
   ([(Expression, [T "if"; N Expression; T "then"; N Expression; T "else"; N Expression]);
     (Expression, [T "true"]);
     (Expression, [T "if"; N Expression; T "then"; N Expression]);
     (Expression, [T "false"]);
     (Expression, [T "false"]);
     (Expression, [T "true"])],
    []));;
(* This fragment is parsed as:
  ["if"; "true";
   "then"; "if"; "false";
           "then"; "false";
   "else"; "true"
  ]

  due to the amiguity.
 *)

let unambiguous_grammar = (Expression, function 
  | Expression -> 
      [[T "if"; N Expression; T "then"; N Expression; N ElseStatement];
       [T "true"];
       [T "false"]]
  | ElseStatement -> [[T "else"; N Expression]; []]);;

let test_2 = ((parse_prefix unambiguous_grammar accept_all 
  ["if"; "true";
   "then"; "if"; "false";
           "then"; "false";
           "else"; "true"
  ]) = Some
   ([(Expression, [T "if"; N Expression; T "then"; N Expression; N ElseStatement]);
     (Expression, [T "true"]);
     (Expression, [T "if"; N Expression; T "then"; N Expression; N ElseStatement]);
     (Expression, [T "false"]);
     (Expression, [T "false"]);
     (ElseStatement, []);
     (ElseStatement, [T "else"; N Expression]);
     (Expression, [T "true"])],
    []));;
(* Using the same fragment as test_1, this unambiguous grammar parses
   the fragment correctly, because it forces the 'else' statement to
   first be parsed as an else statement, not including it in the
   outermost expression *)