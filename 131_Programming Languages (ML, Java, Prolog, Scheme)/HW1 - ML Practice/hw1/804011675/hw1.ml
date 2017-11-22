(* Write a function subset a b that returns true iff a is subset of b
 * This function should be generic to lists of any type:
 * that is, the type of subset should be a generalization of 
 * 'a list -> 'a list -> bool. 
 *)
let rec subset a b =
  match a, b with
    [], _           ->  true
  | _, []           ->  false
  | [a], [b]        ->  if a=b then true
                          else false
  | ha::ta, hb::tb  ->  if (if ha=hb then true else subset [ha] tb)
                          then subset ta b
                          else false;;


(* equal_sets a b returns true iff the represented sets are equal *)
let equal_sets a b =
  if (subset a b && subset b a)
    then true
    else false;;


(* set_union a b returns a list representing the union of a and b *)
let set_union a b =
  a @ b;;


(* set_intersection a b returns a list of the intersect between a b *)
let rec set_intersection a b =
  match a with
    []    ->  []
  | h::t  ->  if subset [h] b
                then h::(set_intersection t b)
                else set_intersection t b;;

(* set_diff a b returns a list representing a−b, that is, the set of all members of a that are not also members of b. *)
let rec set_diff a b =
  match a with
    []    ->  []
  | h::t  ->  if not (subset [h] b)
                then h::(set_diff t b)
                else set_diff t b;;

(* Write a function computed_fixed_point eq f x that returns 
 * the computed fixed point for f with respect to x, assuming
 * that eq is the equality predicate for f's domain.  *)
let rec computed_fixed_point eq f x =
  if eq (f x) x
    then x
    else computed_fixed_point eq f (f x);;

(* Write a function computed_periodic_point eq f p x that 
 * returns the computed periodic point for f with period p and 
 * with respect to x, assuming that eq is the equality 
 * predicate for f's domain. *)
let rec periodic_helper f p x =
  if p=0
    then x
    else periodic_helper f (p-1) (f x);;

let rec computed_periodic_point eq f p x =
  if eq (periodic_helper f p x) x
    then x
    else computed_periodic_point eq f p (f x);;

(* OK, now for the real work. Write a function 
 * filter_blind_alleys g that returns a copy of the grammar g 
 * with all blind-alley rules removed. This function should 
 * preserve the order of rules: that is, all rules that are 
 * returned should be in the same order as the rules in g. *)
type ('nonterminal, 'terminal) symbol =
  | N of 'nonterminal
  | T of 'terminal;;

let is_terminal rule = function
    | T s -> true
    | N s -> subset [s] rule;;

let rec is_rule_terminable rules = function
    | [] -> true
    | h :: t -> if is_terminal rules h
                  then is_rule_terminable rules t
                  else false;;

let rec terminable_symbols_set rules = function
    | [] -> rules
    | (a, b) :: t ->  if is_rule_terminable rules b
                        then  (if (subset [a] rules)
                                then terminable_symbols_set rules t
                                else terminable_symbols_set (a::rules) t)
                        else terminable_symbols_set rules t;;

let computed_fixed_point_set (rules_set, rules) = ((terminable_symbols_set rules_set rules), rules);;

let filter (rules_set, rules) = fst(computed_fixed_point (fun (a, _) (b, _) -> equal_sets a b) computed_fixed_point_set ([], rules));;

let rec check_rules rules = function
    | [] -> []
    | (a, b) :: t -> if (is_rule_terminable rules b)
                       then (a, b)::(check_rules rules t)
                       else check_rules rules t;;

let filter_blind_alleys = function
  (sym, rules) -> (sym, check_rules (filter ([], rules)) rules);;
  

#use "hw1test.ml";;
(* #use "hw1sample.ml";; *)