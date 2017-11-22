let my_subset_test0 = subset [] []
let my_subset_test1 = subset [] [1]
let my_subset_test2 = not (subset [2] [])
let my_subset_test3 = subset [2] [2]
let my_subset_test4 = subset [2;3;4] [2;3;4]
let my_subset_test5 = subset [2;3;4] [2;4;3;5;6]
let my_subset_test6 = subset [2] [2;3;4]
let my_subset_test7 = subset [2;2] [2;3;4]
let my_subset_test8 = not (subset [1] [2;3;4])

let my_equal_sets_test0 = equal_sets [] []
let my_equal_sets_test1 = not (equal_sets [] [1])
let my_equal_sets_test2 = not (equal_sets [1] [])
let my_equal_sets_test3 = equal_sets [2] [2]
let my_equal_sets_test4 = equal_sets [2;3;4] [2;3;4]
let my_equal_sets_test5 = equal_sets [1;1;2] [2;1;1]
let my_equal_sets_test6 = equal_sets [] []

let my_set_union_test0 = equal_sets (set_union [] [2;4;3]) [2;4;3]
let my_set_union_test1 = equal_sets (set_union [2;2;2] [1;2;3]) [1;2;3]
let my_set_union_test2 = not (equal_sets (set_union [1;2;3] [4;5;6]) [1;2;3;4;5])

let my_set_intersection_test0 =
  equal_sets (set_intersection [] [1;2;3;4;5]) []
let my_set_intersection_test1 =
  equal_sets (set_intersection [2;2;3] [1;2;3;4]) [2;3]
let my_set_intersection_test2 =
  not (equal_sets (set_intersection [1;2;3;4] [3;1;2;4]) [3;2;1])

let my_set_diff_test0 = equal_sets (set_diff [1;2;3;4] [1;4;3;1]) [2]
let my_set_diff_test1 = equal_sets (set_diff [2;2;2;3;1] [1;2;3]) []
let my_set_diff_test2 = equal_sets (set_diff [1;2;3] []) [1;2;3]
let my_set_diff_test3 = not (equal_sets (set_diff [] [4;3;1]) [2])

let my_computed_fixed_point_0 =
  computed_fixed_point (=) (fun x -> x / 3) 3000000000 = 0
let my_computed_fixed_point_1 =
  computed_fixed_point (=) (fun x -> x *. 1.5) 0.5 = infinity
let my_computed_fixed_point_2 =
  computed_fixed_point (=) sqrt 100. = 1.

let my_computed_periodic_point_test0 =
  computed_periodic_point (=) (fun x -> x + 1) 0 (-1) = -1
let my_computed_periodic_point_test1 =
  computed_periodic_point (=) (fun x -> x *. -0.5) 3 4.0 = -0.
(* An example grammar for a small subset of Awk, derived from but not
   identical to the grammar in
   <http://web.cs.ucla.edu/classes/winter06/cs132/hw/hw1.html>.  *)

type awksub_nonterminals =
  | Expr | Lvalue | Incrop | Binop | Num

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
    Num, [T"9"]]

let awksub_grammar = Expr, awksub_rules

let awksub_test0 =
  filter_blind_alleys awksub_grammar = awksub_grammar

let awksub_test1 =
  filter_blind_alleys (Expr, List.tl awksub_rules) = (Expr, List.tl awksub_rules)

let awksub_test2 =
  filter_blind_alleys (Expr,
      [Expr, [N Num];
       Expr, [N Lvalue];
       Expr, [N Expr; N Lvalue];
       Expr, [N Lvalue; N Expr];
       Expr, [N Expr; N Binop; N Expr];
       Lvalue, [N Lvalue; N Expr];
       Lvalue, [N Expr; N Lvalue];
       Lvalue, [N Incrop; N Lvalue];
       Lvalue, [N Lvalue; N Incrop];
       Incrop, [T"++"]; Incrop, [T"--"];
       Binop, [T"+"]; Binop, [T"-"];
       Num, [T"0"]; Num, [T"1"]; Num, [T"2"]; Num, [T"3"]; Num, [T"4"];
       Num, [T"5"]; Num, [T"6"]; Num, [T"7"]; Num, [T"8"]; Num, [T"9"]])
  = (Expr,
     [Expr, [N Num];
      Expr, [N Expr; N Binop; N Expr];
      Incrop, [T"++"]; Incrop, [T"--"];
      Binop, [T "+"]; Binop, [T "-"];
      Num, [T "0"]; Num, [T "1"]; Num, [T "2"]; Num, [T "3"]; Num, [T "4"];
      Num, [T "5"]; Num, [T "6"]; Num, [T "7"]; Num, [T "8"]; Num, [T "9"]])

let awksub_test3 =
  filter_blind_alleys (Expr, List.tl (List.tl (List.tl awksub_rules))) =
    filter_blind_alleys (Expr, List.tl (List.tl awksub_rules))

type giant_nonterminals =
  | Conversation | Sentence | Grunt | Snore | Shout | Quiet

let giant_grammar =
  Conversation,
  [Snore, [T"ZZZ"];
   Quiet, [];
   Grunt, [T"khrgh"];
   Shout, [T"aooogah!"];
   Sentence, [N Quiet];
   Sentence, [N Grunt];
   Sentence, [N Shout];
   Conversation, [N Snore];
   Conversation, [N Sentence; T","; N Conversation]]

let giant_test0 =
  filter_blind_alleys giant_grammar = giant_grammar

let giant_test1 =
  filter_blind_alleys (Sentence, List.tl (snd giant_grammar)) =
    (Sentence,
     [Quiet, []; Grunt, [T "khrgh"]; Shout, [T "aooogah!"];
      Sentence, [N Quiet]; Sentence, [N Grunt]; Sentence, [N Shout]])

let giant_test2 =
  filter_blind_alleys (Sentence, List.tl (List.tl (snd giant_grammar))) =
    (Sentence,
     [Grunt, [T "khrgh"]; Shout, [T "aooogah!"];
      Sentence, [N Grunt]; Sentence, [N Shout]])