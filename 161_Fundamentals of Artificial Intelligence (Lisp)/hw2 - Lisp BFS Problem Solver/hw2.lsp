;;;;;;;;;;;;;;
; Homework 2 ;    Alvin Lim
;;;;;;;;;;;;;;    804 011 675

;;;;;;;;;;;;;;
; Question 1 ;
;;;;;;;;;;;;;;

; TODO: comment code
(defun BFS (FRINGE)
  (cond
    ((and (= (list-length FRINGE) 1) (atom (car FRINGE))) FRINGE) ; root node
    ((atom (car FRINGE)) (append (list (car FRINGE)) (BFS (cdr FRINGE)))) ; if first is leaf, return list (first (BFS rest))
    (t (BFS (append (cdr FRINGE) (car FRINGE))))))    ; otherwise, pop first node's children to end of queue

;;;;;;;;;;;;;;
; Question 2 ;
;;;;;;;;;;;;;;


; These functions implement a depth-first solver for the homer-baby-dog-poison
; problem. In this implementation, a state is represented by a single list
; (homer baby dog poison), where each variable is T if the respective entity is
; on the west side of the river, and NIL if it is on the east side.
; Thus, the initial state for this problem is (NIL NIL NIL NIL) (everybody 
; is on the east side) and the goal state is (T T T T).

; The main entry point for this solver is the function DFS, which is called
; with (a) the state to search from and (b) the path to this state. It returns
; the complete path from the initial state to the goal state: this path is a
; list of intermediate problem states. The first element of the path is the
; initial state and the last element is the goal state. Each intermediate state
; is the state that results from applying the appropriate operator to the
; preceding state. If there is no solution, DFS returns NIL.
; To call DFS to solve the original problem, one would call 
; (DFS '(NIL NIL NIL NIL) NIL) 
; However, it should be possible to call DFS with a different initial
; state or with an initial path.

; First, we define the helper functions of DFS.

; FINAL-STATE takes a single argument S, the current state, and returns T if it
; is the goal state (T T T T) and NIL otherwise.
(defun FINAL-STATE (S)
  (cond
    ((equal S (list T T T T)) T)  ; returns T if S is goal state
    (t NIL)))           ; returns NIL otherwise

; NEXT-STATE returns the state that results from applying an operator to the
; current state. It takes three arguments: the current state (S), and which entity
; to move (A, equal to h for homer only, b for homer with baby, d for homer 
; with dog, and p for homer with poison). 
; It returns a list containing the state that results from that move.
; If applying this operator results in an invalid state (because the dog and baby,
; or poisoin and baby are left unsupervised on one side of the river), or when the
; action is impossible (homer is not on the same side as the entity) it returns NIL.
; NOTE that next-state returns a list containing the successor state (which is
; itself a list); the return should look something like ((NIL NIL T T)).
(defun NEXT-STATE (S A)
  (cond
    ((equal A 'h)   ; if moving homer
      (cond
        ((or (equal (cdr S) (list NIL T T)) (equal (cdr S) (list T NIL NIL))) ; if baby isn't w/ dog/poison
          (cond
            ((equal (car S) NIL) (append (list T) (cdr S))) ; move homer from east to west
            (t (append (list NIL) (cdr S)))))       ; move homer from west to east
        (t NIL))) ; otherwise, baby is w/ dog/poison, so invalid

    ((equal A 'b)   ; if moving homer + baby
      (cond
        ((equal (car S) (cadr S))
          (cond
            ((equal (car S) NIL) (append (list T T) (cddr S)))  ; move homer+baby from east to west
            (t (append (list NIL NIL) (cddr S)))))        ; move homer+baby from west to east
        (t NIL))) ; homer + baby not on same side, so invalid

    ((equal A 'd)   ; if moving homer + dog
      (cond
        ((equal (car S) (caddr S))
          (cond
            ((equal (car S) NIL)    ; move homer+dog from east to west
              (append (append (list T) (list (cadr S))) (append (list T) (cdddr S))))
            (t                ; move homer+dog from west to east
              (append (append (list NIL) (list (cadr S))) (append (list NIL) (cdddr S))))))
        (t NIL))) ; homer + dog not on same side, so invalid

    ((equal A 'p)   ; if moving homer + poison
      (cond
        ((equal (car S) (cadddr S))
          (cond
            ((equal (car S) NIL)    ; move homer+poison from east to west
              (append (append (list T) (list (cadr S))) (append (list (caddr S)) (list T))))
            (t                ; move homer+poison from east to west
              (append (append (list NIL) (list (cadr S))) (append (list (caddr S)) (list NIL))))))
        (t NIL))))) ; homer + poison not on same side, so invalid

; SUCC-FN returns all of the possible legal successor states to the current
; state. It takes a single argument (s), which encodes the current state, and
; returns a list of each state that can be reached by applying legal operators
; to the current state.
(defun SUCC-FN (S)
  (cond
    ((equal S (list NIL NIL NIL NIL)) (list (list T T NIL NIL)))
    ((equal S (list NIL NIL T NIL)) (list (list T T T NIL) (list T NIL T T)))
    ((equal S (list NIL NIL NIL T)) (list (list T T NIL T) (list T NIL T T)))
    ((equal S (list NIL NIL T T)) (list (list T NIL T T) (list T T T T)))
    ((equal S (list T T NIL NIL)) (list (list NIL T NIL NIL) (list NIL NIL NIL NIL)))
    ((equal S (list T T T NIL)) (list (list NIL NIL T NIL) (list NIL T NIL NIL)))
    ((equal S (list T T NIL T)) (list (list NIL NIL NIL T) (list NIL T NIL NIL)))
    ((equal S (list T T T T)) (list (list NIL NIL T T)))
    ((equal S (list T NIL T T)) (list (list NIL NIL T T) (list NIL NIL NIL T) (list NIL NIL T NIL)))
    ((equal S (list NIL T NIL NIL)) (list (list T T NIL NIL) (list T T T NIL) (list T T NIL T)))
    (t NIL)))

; ON-PATH checks whether the current state is on the stack of states visited by
; this depth-first search. It takes two arguments: the current state (S) and the
; stack of states visited by DFS (STATES). It returns T if s is a member of
; states and NIL otherwise.
(defun ON-PATH (S STATES)
  (cond
    ((null STATES) NIL) ; base case: no match, return NIL
    (t      ; otherwise, check S against the top of the stack of STATES
      (cond
        ((equal S (car STATES)) T)  ; if they are equal, return T
        (t (ON-PATH S (cdr STATES))))))) ; check S against the rest of the path

; MULT-DFS is a helper function for DFS. It takes two arguments: a list of
; states from the initial state to the current state (PATH), and the legal
; successor states to the last, current state in the PATH (STATES). PATH is a
; first-in first-out list of states; that is, the first element is the initial
; state for the current search and the last element is the most recent state
; explored. MULT-DFS does a depth-first search on each element of STATES in
; turn. If any of those searches reaches the final state, MULT-DFS returns the
; complete path from the initial state to the goal state. Otherwise, it returns
; NIL.
(defun MULT-DFS (STATES PATH)
  (cond
    ((null STATES) NIL) ; base case: no match, return NIL
    ((FINAL-STATE (car STATES)) (append PATH (list (car STATES))))  ; base case: goal state found
    (t (MULT-DFS (cdr STATES) PATH))))  ; check the rest of STATES against goal

; DFS does a depth first search from a given state to the goal state. It
; takes two arguments: a state (S) and the path from the initial state to S
; (PATH). If S is the initial state in our search, PATH is set to NIL. DFS
; performs a depth-first search starting at the given state. It returns the path
; from the initial state to the goal state, if any, or NIL otherwise. DFS is
; responsible for checking if S is already the goal state, as well as for
; ensuring that the depth-first search does not revisit a node already on the
; search path.
(defun DFS (S PATH)
  (cond
    ((null S) NIL)    ; base case: no path to goal
    ((FINAL-STATE S) (append PATH (list S)))  ; base case: if goal state, return path+goal
    ((ON-PATH S PATH) NIL)  ; ensures DFS doesn't revisit nodes on search path
    ((MULT-DFS (SUCC-FN S) (append PATH (list S))) (MULT-DFS (SUCC-FN S) (append PATH (list S)))) ; check expanded nodes for goal
    ; recursively call DFS on child nodes of S
    ((DFS (car (SUCC-FN S)) (append PATH (list S))) (DFS (car (SUCC-FN S)) (append PATH (list S))))
    ((DFS (cadr (SUCC-FN S)) (append PATH (list S))) (DFS (cadr (SUCC-FN S)) (append PATH (list S))))
    ((DFS (caddr (SUCC-FN S)) (append PATH (list S))) (DFS (caddr (SUCC-FN S)) (append PATH (list S))))))


; Test Cases
;(BFS '(ROOT))                ; (ROOT)
;(BFS '((((L E) F) T)))       ; (T F L E)
;(BFS '((R (I (G (H T))))))   ; (R I G H T)
;(BFS '(((A (B)) C (D))))     ; (C A D B)
;(BFS '((T (H R E) E)))       ; (T E H R E)
;(BFS '((A ((C ((E) D)) B)))) ; (A B C D E)

;(DFS '(NIL NIL NIL NIL) NIL)     ; Default DFS starting case: all starting on EAST side

;(DFS '(T T T T) NIL)
;(DFS '(NIL NIL NIL T) NIL)
;(DFS '(NIL NIL T T) NIL)
;(DFS '(NIL T T T) NIL)        ; Baby alone w/ dog+poison: return NIL
;(DFS '(NIL NIL T NIL) NIL)
;(DFS '(NIL T NIL NIL) NIL)
;(DFS '(T NIL NIL NIL) NIL)    ; Baby alone w/ dog+poison: return NIL
