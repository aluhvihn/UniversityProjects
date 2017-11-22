; Alvin Lim       804 011 675

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; PAD takes in a single integer argument N and returns the Nth Padovan number
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun PAD (N)
  (cond
    ((= N 0) 1) ; Base Case: the 0th Padovan number is 1
    ((= N 1) 1) ; Base Case: the 1st Padovan number is 1
    ((= N 2) 1) ; Base Case: the 2nd Padovan number is 1
    (t (+ (PAD (- N 2)) (PAD (- N 3)))))) ; For all other numbers N, the result
                                          ; is the a recursive addition of the
                                          ; (N-1)th and (N-2)th Padovan numbers

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SUM takes in a single integer argument N and returns the number of additions
; required to calculate the Nth Padovan number
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun SUM (N)
  (cond
    ((= N 0) 0) ; Base Case: the 0th Padovan number is 1, needs no addition
    ((= N 1) 0) ; Base Case: the 1st Padovan number is 1, needs no addition
    ((= N 2) 0) ; Base Case: the 2nd Padovan number is 1, needs no addition
    (t (+ 1 (SUM (- N 2)) (SUM (- N 3)))))) ; For all other numbers N, the
                                            ; result is the a recursive
                                            ; addition of 1 and the
                                            ; additions required for
                                            ; calculating the (N-1)th and
                                            ; (N-2)th Padovan numbers

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ANON takes a single argument TREE that represents a tree, and returns an
; anonymized tree w/ the same structure, but with all symbols and numbers
; in the tree replaced by a question mark.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun ANON (TREE)
  (cond
    ((atom TREE) '?)  ; If the node is an atom (leaf), replace it with a "?"
    (t (cond          ; If the node is a list (has children), go into its branches
          ((= (list-length TREE) 1)
            ; If the list has a length of one:
            (cond
                ((atom (car TREE)) (list '?))
                  ; 1) If the one item is an atom,
                  ;    return '(?) instead of '(? ?)
                (t (list (ANON (car TREE))))))
                  ; 2) If the one item is a list,
                  ;    return the recursive result of
                  ;    (ANON (car TREE)) in a list
          ((atom (car TREE)) (cons '? (ANON (cdr TREE))))
            ; If the first child is an atom:
            ;   1. Replace it with a "?".
            ;   2. Recursively call ANON on the rest of the the tree.
            ;   3. "cons" these parts.
          (t (cons (ANON (car TREE)) (ANON (cdr TREE))))))))
            ; Otherwise, "cons" the recursive results of ANON on the "car" and
            ; "cdr" of TREE

; Test Cases
; (PAD 0)
; (PAD 1)
; (PAD 2)
; (PAD 3)
; (PAD 4)
; (PAD 5)
; (PAD 6)
; (PAD 7)
; (PAD 8)
; (PAD 9)
; (PAD 10)
; (PAD 50)
; (PAD 60)
; (PAD 70)

; (SUM 0)
; (SUM 1)
; (SUM 2)
; (SUM 3)
; (SUM 4)
; (SUM 5)
; (SUM 6)
; (SUM 7)
; (SUM 8)
; (SUM 9)
; (SUM 10)
; (SUM 50)
; (SUM 60)
; (SUM 70)

; (ANON '(FOO 5))                         ; (? ?)
; (ANON '42)                              ; ?
; (ANON 'FOO)                             ; ?
; (ANON '(((L E) F) T))                   ; (((? ?) ?) ?)
; (ANON '(5 FOO 3.1 -0.2))                ; (? ? ? ?)
; (ANON '(1 (FOO 3.1) -0.2))              ; (? (? ?) ?)
; (ANON '(((1 2) (FOO 3.1)) (BAR -0.2)))  ; (((? ?) (? ?)) (? ?))
; (ANON '(R (I (G (H T)))))               ; (? (? (? (? ?))))
