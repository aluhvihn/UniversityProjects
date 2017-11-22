%% kenken/3
%%  N   nonnegative integer, # of cells per side
%%  C   list of numeric constraints
%%  T   list of list of integers, from 1 to N
kenken(N, C, T) :-
  length(T, N),
  maplist(check_length(N), T),
  maplist(set_domain(N), T),
  maplist(meet_constraints(T), C),
  maplist(fd_all_different, T),
  transpose(T, Transposed),
  maplist(fd_all_different, Transposed),
  maplist(fd_labeling, T).

%% check_length/2
%%  T       list of list, each list is checked for its length
%%  N       nonnegative integer, # items in each list
check_length(N, T) :-
  length(T, N).

%% set_domain/2
%%  N   maximum of domain
%%  L   list to set the domain of
set_domain(N, L) :- 
  fd_domain(L, 1, N).

%% meet_constraints/2
%% T    grid to meet constraints
%% C    list of constraints for grid to meet
meet_constraints(T, +(S, L)) :-
  add(T, S, L, 0).
meet_constraints(T, *(P, L)) :- 
  mult(T, P, L, 1).
meet_constraints(T, -(D, J, K)) :- 
  sub(T, D, J, K).
meet_constraints(T, /(Q, J, K)) :-
   div(T, Q, J, K).

add(_, S, [], S).
add(T, S, [H|Tail], Result) :- 
  elem_in_T(H, T, V), 
  Accumulator #= Result + V, 
  add(T, S, Tail, Accumulator). 

mult(_, P, [], P).
mult(T, P, [H|Tail], Result) :-
  elem_in_T(H, T, V),
  Accumulator #= Result * V,
  mult(T, P, Tail, Accumulator).

sub(_, D, _, _, D).
sub(T, D, J, K) :-
  elem_in_T(J, T, X),
  elem_in_T(K, T, Y),
  Accumulator #=  X - Y,
  sub(T, D, J, K, Accumulator).
sub(T, D, J, K) :-
  elem_in_T(J, T, X),
  elem_in_T(K, T, Y),
  Accumulator #=  Y - X,
  sub(T, D, J, K, Accumulator).

div(_, Q, _, _, Q).
div(T, Q, J, K) :-
  elem_in_T(J, T, X),
  elem_in_T(K, T, Y),
  Accumulator #= X / Y,
  div(T, Q, J, K, Accumulator).
div(T, Q, J, K) :-
  elem_in_T(J, T, X),
  elem_in_T(K, T, Y),
  Accumulator #= Y / X,
  div(T, Q, J, K, Accumulator).

elem_in_T(I-J, T, E) :- 
  nth(I, T, Row), nth(J, Row, E).

%% "clpfd.pl" transpose functions from SWI-Prolog:
%% http://stackoverflow.com/questions/4280986/how-to-transpose-a-matrix-in-prolog
transpose([], []).
transpose([F|Fs], Ts) :-
  transpose(F, [F|Fs], Ts).

transpose([], _, []).
transpose([_|Rs], Ms, [Ts|Tss]) :-
  transpose_aux(Ms, Ts, Ms1),
  transpose(Rs, Ms1, Tss).

transpose_aux([], [], []).
transpose_aux([[F|Os]|Rest], [F|Fs], [Os|Oss]) :-
  transpose_aux(Rest, Fs, Oss).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% plain_kenken/3
%%  same, but without fd
plain_kenken(N, C, T) :-
  length(T, N),
  maplist(check_length(N), T),
  set_domain2(N, L),
  maplist(permutation(L), T),
  transpose(T, Transposed),
  maplist(distinct, Transposed),
  maplist(meet_constraints2(T), C).

set_domain2(N, L) :-
  findall(X, between(1, N, X), L).

distinct([]).
distinct([H|T]) :- 
  \+(member(H, T)), distinct(T).

meet_constraints2(T, +(S, L)) :- 
  add2(T, S, L, 0).
meet_constraints2(T, -(D, J, K)) :- 
  sub2(T, D, J, K).
meet_constraints2(T, *(P, L)) :- 
  mult2(T, P, L, 1).
meet_constraints2(T, /(Q, J, K)) :-
  div2(T, Q, J, K).

add2(_, S, [], S).
add2(T, S, [H|Tail], Result) :- 
  elem_in_T(H, T, V), 
  Accumulator is Result + V, 
  add2(T, S, Tail, Accumulator). 

sub2(_, D, _, _, D).
sub2(T, D, J, K) :-
  elem_in_T(J, T, X),
  elem_in_T(K, T, Y),
  Accumulator is  X - Y,
  sub2(T, D, J, K, Accumulator).
sub2(T, D, J, K) :-
  elem_in_T(J, T, X),
  elem_in_T(K, T, Y),
  Accumulator is  Y - X,
  sub2(T, D, J, K, Accumulator).

mult2(_, P, [], P).
mult2(T, P, [H|Tail], Result) :-
  elem_in_T(H, T, V),
  Accumulator is Result * V,
  mult2(T, P, Tail, Accumulator).

div2(_, Q, _, _, Q).
div2(T, Q, J, K) :-
  elem_in_T(J, T, X),
  elem_in_T(K, T, Y),
  Accumulator is X / Y,
  div2(T, Q, J, K, Accumulator).
div2(T, Q, J, K) :-
  elem_in_T(J, T, X),
  elem_in_T(K, T, Y),
  Accumulator is Y / X,
  div2(T, Q, J, K, Accumulator).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Test Cases

kenken_testcase1(
  6,
  [
   +(11, [1-1, 2-1]),
   /(2, 1-2, 1-3),
   *(20, [1-4, 2-4]),
   *(6, [1-5, 1-6, 2-6, 3-6]),
   -(3, 2-2, 2-3),
   /(3, 2-5, 3-5),
   *(240, [3-1, 3-2, 4-1, 4-2]),
   *(6, [3-3, 3-4]),
   *(6, [4-3, 5-3]),
   +(7, [4-4, 5-4, 5-5]),
   *(30, [4-5, 4-6]),
   *(6, [5-1, 5-2]),
   +(9, [5-6, 6-6]),
   +(8, [6-1, 6-2, 6-3]),
   /(2, 6-4, 6-5)
  ]
).

kenken_testcase2(
  4,
  [
   +(6, [1-1, 1-2, 2-1]),
   *(96, [1-3, 1-4, 2-2, 2-3, 2-4]),
   -(1, 3-1, 3-2),
   -(1, 4-1, 4-2),
   +(8, [3-3, 4-3, 4-4]),
   *(2, [3-4])
  ]
).