type ('nonterminal, 'terminal) symbol =
  | N of 'nonterminal
  | T of 'terminal

(* To warm up, notice that the format of grammars is different in this
   assignment, versus Homework 1. Write a function convert_grammar gram1
   that returns a Homework 2-style grammar, which is converted from the 
   Homework 1-style grammar gram1. Test your implementation of convert_grammar
   on the test grammars given in Homework 1. For example, the top-level 
   definition let awksub_grammar_2 = convert_grammar awksub_grammar should 
   bind awksub_grammar_2 to a Homework 2-style grammar that is equivalent to 
   the Homework 1-style grammar awksub_grammar. *)

let rec matching_nonTerms nonTerm rules = match rules with
  | h::t -> if ((fst h) = nonTerm)
              then (snd h)::(matching_nonTerms nonTerm t)
              else matching_nonTerms nonTerm t
  | [] -> []

let convert_grammar gram1 = match gram1 with
  | (start_symbol, rules) -> (start_symbol, fun nonTerm -> (matching_nonTerms nonTerm rules));;

(* Write a function parse_prefix gram that returns a matcher for the 
   grammar gram. When applied to an acceptor accept and a fragment frag,
   the matcher must return the first acceptable match of a prefix of frag, 
   by trying the grammar rules in order; this is not necessarily the shortest
   nor the longest acceptable match. A match is considered to be acceptable if
   accept succeeds when given a derivation and the suffix fragment that 
   immediately follows the matching prefix. When this happens, the matcher
   returns whatever the acceptor returned. If no acceptable match is found,
   the matcher returns None. *)

(* or_matcher - tests each rule in 'rule_list'.
      If a rule passes, that path is returned.
      If a rule doesn't pass, try the next rule.*)
let rec or_matcher start_symbol rule_function rule_list accept path frag =
  match rule_list with
    (* No rules passed *)
    | [] -> None
    (* tests each rule in 'rule_list' *)
    | h::t -> 
        match (and_matcher rule_function h accept (path@[start_symbol, h]) frag) with
          (* if a rule passes, that path is returned *)
          | Some (d,s) -> Some (d,s)
          (* if a rule doesn't pass, try the next rule *)
          | None -> or_matcher start_symbol rule_function t accept path frag
              
and and_matcher rule_function current_rule accept path frag = match current_rule with
  (* Finished going through rules. Test 'path' with 'frag' using 'accept' *)
  | [] -> accept path frag
  (* 'current_rule' is a sequence (list) of terminal and nonterminal symbols.
     Check them against the next prefix (created with 'path' and 'frag') *)
  | h::t ->
      match frag with
        (* 'frag' is empty. Done. *)
        | [] -> None
        | sym1::rest_syms ->
            match current_rule with
              (* if current_rule starts with nonterm, expand it to next level. Apply 'rule_function' to it *)
              | (N nonterm)::rest_rule ->
                   let rule_list = (rule_function nonterm) in
                   let new_accept = (and_matcher rule_function rest_rule accept) in
                   or_matcher nonterm rule_function rule_list new_accept path frag
              | (T term)::rest_rule ->
                   if term = sym1
                   then and_matcher rule_function rest_rule accept path rest_syms
                   else None
              | _ -> failwith "Empty"


(*
gram = (start_symbol,
              function
                | Expr -> [
                            ...
                          ]
                | Term -> [
                            ...
                          ] )
====================================================
start_symbol -> 'nonterminal
rule_function -> <fun>
*)
let parse_prefix gram accept frag = match gram with
  | (start_symbol, rule_function) -> 
      (* list of rules associated with 'start_symbol' *)
      let rule_list = (rule_function start_symbol) in
      or_matcher start_symbol rule_function rule_list accept [] frag;;