;
; CS161 Spring 2016: Graph coloring to SAT conversion
;
; All functions you need to write are marked with 'EXERCISE' in their header comments.
; Same rules apply regarding Lisp functions you are allowed to use.
; In fact, you do not need a lot of Lisp functions to finish this assignment.
;

;;;;;;;;;;;;;;;;;;;;;;
; General util.
;
(defun reload()
  (load "hw4.lsp")
  );end defun

; EXERCISE: Fill this function.
; returns the index of the variable
; that corresponds to the fact that 
; "node n gets color c" (when there are k possible colors).
;
(defun node2var (n c k)
  ; variable_index = (n-1)*k + c
  (+ c (* k (- n 1)))
  )

; EXERCISE: Fill this function
; returns *a clause* for the constraint:
; "node n gets at least one color from the set {c,c+1,...,k}."
;
(defun at-least-one-color (n c k)
  (cond
    ; k must be positive integer
    ((<= k 0) NIL)
    ; if (c < k), generate variable index for this c, n and recursively
    ; call at-least-one-color with the next color (+ c 1)
    ((< c k) (append (list (node2var n c k)) (at-least-one-color n (+ c 1) k)))
    ; if (c = k), this is the last color to use for the node, generate variable index
    ((= c k) (list (node2var n c k)))
    (t NIL)
    );end cond
  );end defun

; EXERCISE: Fill this function
; returns *a list of clauses* for the constraint:
; "node n gets at most one color from the set {c,c+1,...,k}."
;
(defun at-most-one-color (n c k)
  ; (at-most-one-color-helper 1 (at-least-one-color n c k))
  (cond
    ; Base case: only one color, return clause of literal and
    ;            its negative (always true, like empty clause)
    ((= k c) (list (list (- (* k n)) (* k n))))
    ; Otherwise: make clause from list of variable indexes (literals)
    (t (at-most-one-helper (at-least-one-color n c k)))
    );end cond
  )

;
; Helper function for at-most-one-color
;
(defun at-most-one-helper (var_ind)
  (cond 
    ; Base case: one element left; terminate
    ((<= (length var_ind) 1) NIL)
    ; Otherwise: append the clauses of the permutations between the negated car and (cdr var_ind)
    ;           recursively call the function on (cdr var_ind) for the rest of the clauses
    (t (append (make-clauses (- (car var_ind)) (cdr var_ind)) (at-most-one-helper (cdr var_ind))))
  );end cond
)

;
; Helper function for at-most-one-helper
; Creates clauses permutations of the literal x and the negated values of y
;
(defun make-clauses(x y)
  (cond
    ; Base case: No more literals
    ((null y) NIL)
    ; Otherwise: make a list of clauses with literal x and negated (cdr y)
    (t (append (list (list x (- (car y)))) (make-clauses x (cdr y))))
  );end cond
)

; EXERCISE: Fill this function
; returns *a list of clauses* to ensure that
; "node n gets exactly one color from the set {1,2,...,k}."
;
(defun generate-node-clauses (n k)
  ; Exactly 1 color = (at least 1 color) AND (at most 1 color)
  (append (list (at-least-one-color n 1 k)) (at-most-one-color n 1 k))
  )

; EXERCISE: Fill this function
; returns *a list of clauses* to ensure that
; "the nodes at both ends of edge e cannot have the same color from the set {1,2,...,k}."
;
(defun generate-edge-clauses (e k)
  (generate-edge-clauses-helper e 1 k)
  )

;
; Helper function for generate-edge-clauses
; For any two nodes, to make sure that they
; are never painted the same, we just have clauses which each contain the negation of
; the respective color on the variable (-node1_color1 -node2_color1)
;
(defun generate-edge-clauses-helper (e c k)
  (cond
    ; Done
    ((> c k) NIL)
    ; Make clause with negated values of the car values of both node's variable indexes
    ; Recursively call the function using the next color
    (t (append
          (list (list (- (node2var (car e) c k)) (- (node2var (cadr e) c k))))
          (generate-edge-clauses-helper e (+ c 1) k)))
    );end cond
  )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Your exercises end here. Below are top-level
; and utility functions that you do not need to understand.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; 
; Top-level function for converting the graph coloring problem
; of the graph defined in 'fname' using k colors into a SAT problem.
; The resulting SAT problem is written to 'out-name' in a simplified DIMACS format.
; (http://www.satcompetition.org/2004/format-solvers2004.html)
;
; This function also returns the cnf written to file.
; 
; *works only for k>0*
;
(defun graph-coloring-to-sat (fname out-name k)
  (progn
    (setf in-path (make-pathname :name fname))
    (setf in (open in-path :direction :input))
    (setq info (get-number-pair-from-string (read-line in) #\ ))
    (setq cnf nil)
    (do ((node 1
         (+ node 1)
         ))
  ((> node (car info)))
      (setq cnf (append (generate-node-clauses node k) cnf))
      );end do
    (do ((line (read-line in nil 'eof)
         (read-line in nil 'eof)))
  ((eql line 'eof) (close in))
      (let ((edge (get-number-pair-from-string line #\ )))
  (setq cnf (append (generate-edge-clauses edge k) cnf))
  );end let
      );end do
    (close in)
    (write-cnf-to-file out-name (* (car info) k) cnf)
    (return-from graph-coloring-to-sat cnf)
    );end progn  
  );end defun

;
; A utility function for parsing a pair of integers.
; 
(defun get-number-pair-from-string (string token)
  (if (and string token)
      (do* ((delim-list (if (and token (listp token)) token (list token)))
            (char-list (coerce string 'list))
            (limit (list-length char-list))
            (char-count 0 (+ 1 char-count))
            (char (car char-list) (nth char-count char-list))
            )
           ((or (member char delim-list)
                (= char-count limit))
            (return
               (if (= char-count limit)
                   (list string nil)
                   (list (parse-integer (coerce (butlast char-list (- limit char-count))
                                 'string))
                         (parse-integer (coerce (nthcdr (+ char-count 1) char-list) 'string))
       )))))))

;
; Writes clause to file handle 'out'.
;
(defun write-clause-to-file (out clause)
  (cond ((null clause) (format out "0~%"))
  (t (progn 
       (format out "~A " (car clause))
       (write-clause-to-file out (cdr clause))
       );end progn
     );end t
  );end cond
  );end defun

;
; Writes the formula cnf with vc variables to 'fname'.
;
(defun write-cnf-to-file (fname vc cnf)
  (progn
    (setf path (make-pathname :name fname))
    (setf out (open path :direction :output))
    (setq cc (length cnf))  
    (format out "p cnf ~A ~A~%" vc cc)
    (dolist (clause cnf)
      (write-clause-to-file out clause)
      );end dolist
    (close out)
    );end progn
  );end defun