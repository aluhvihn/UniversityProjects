;
; CS161 Hw3: Sokoban
; 
; *********************
;    READ THIS FIRST
; ********************* 
;
; All functions that you need to modify are marked with 'EXERCISE' in their header comments.
; Do not modify a-star.lsp.
; This file also contains many helper functions. You may call any of them in your functions.
;
; *Warning*: The provided A* code only supports the maximum cost of 4999 for any node.
; That is f(n)=g(n)+h(n) < 5000. So, be careful when you write your heuristic functions.
; Do not make them return anything too large.
;
; For Allegro Common Lisp users: The free version of Allegro puts a limit on memory.
; So, it may crash on some hard sokoban problems and there is no easy fix (unless you buy 
; Allegro). 
; Of course, other versions of Lisp may also crash if the problem is too hard, but the amount
; of memory available will be relatively more relaxed.
; Improving the quality of the heuristic will mitigate this problem, as it will allow A* to
; solve hard problems with fewer node expansions.
; 
; In either case, this limitation should not significantly affect your grade.
; 
; Remember that most functions are not graded on efficiency (only correctness).
; Efficiency can only influence your heuristic performance in the competition (which will
; affect your score).
;  
;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; General utility functions
; They are not necessary for this homework.
; Use/modify them for your own convenience.
;

;
; For reloading modified code.
; I found this easier than typing (load "filename") every time. 
;
(defun reload()
  (load "hw3.lsp")
  )

;
; For loading a-star.lsp.
;
(defun load-a-star()
  (load "a-star.lsp"))

;
; Reloads hw3.lsp and a-star.lsp
;
(defun reload-all()
  (reload)
  (load-a-star)
  )

;
; A shortcut function.
; goal-test and next-states stay the same throughout the assignment.
; So, you can just call (sokoban <init-state> #'<heuristic-name>).
; 
;
(defun sokoban (s h)
  (a* s #'goal-test #'next-states h)
  )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; end general utility functions
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; We now begin actual Sokoban code
;

; Define some global variables
(setq blank 0)
(setq wall 1)
(setq box 2)
(setq keeper 3)
(setq star 4)
(setq boxstar 5)
(setq keeperstar 6)

; Some helper functions for checking the content of a square
(defun isBlank (v)
  (= v blank)
  )

(defun isWall (v)
  (= v wall)
  )

(defun isBox (v)
  (= v box)
  )

(defun isKeeper (v)
  (= v keeper)
  )

(defun isStar (v)
  (= v star)
  )

(defun isBoxStar (v)
  (= v boxstar)
  )

(defun isKeeperStar (v)
  (= v keeperstar)
  )

;
; Helper function of getKeeperPosition
;
(defun getKeeperColumn (r col)
  (cond ((null r) nil)
    (t (if (or (isKeeper (car r)) (isKeeperStar (car r)))
           col
         (getKeeperColumn (cdr r) (+ col 1))
         );end if
       );end t
    );end cond
  )

;
; getKeeperPosition (s firstRow)
; Returns a list indicating the position of the keeper (c r).
; 
; Assumes that the keeper is in row >= firstRow.
; The top row is the zeroth row.
; The first (right) column is the zeroth column.
;
(defun getKeeperPosition (s row)
  (cond ((null s) nil)
    (t (let ((x (getKeeperColumn (car s) 0)))
         (if x
         ;keeper is in this row
         (list x row)
         ;otherwise move on
         (getKeeperPosition (cdr s) (+ row 1))
         );end if
           );end let
     );end t
    );end cond
  );end defun

;
; cleanUpList (l)
; returns l with any NIL element removed.
; For example, if l is '(1 2 NIL 3 NIL), returns '(1 2 3).
;
(defun cleanUpList (L)
  (cond ((null L) nil)
    (t (let ((cur (car L))
         (res (cleanUpList (cdr L)))
         )
         (if cur 
         (cons cur res)
          res
         )
         );end let
       );end t
    );end cond
  );end 

; EXERCISE: Modify this function to return true (t)
; if and only if s is a goal state of a Sokoban game.
; (no box is on a non-goal square)
;
; Currently, it always returns NIL. If A* is called with
; this function as the goal testing function, A* will never
; terminate until the whole search space is exhausted.
;
(defun goal-test (s)
  (cond
    ; base case: looked through all of state: no box found
    ((null s) t)
    (t (cond
        ; if box found, return NIL
        ((/= 0 (count box (car s))) NIL)
        ; otherwise, call goal-test on remainder lists of s
        (t (goal-test (cdr s)))
        );end cond
      );end t
    );end cond
  );end defun

; EXERCISE: Modify this function to return the list of 
; sucessor states of s.
;
; This is the top-level next-states (successor) function.
; Some skeleton code is provided below.
; You may delete them totally, depending on your approach.
; 
; If you want to use it, you will need to set 'result' to be 
; the set of states after moving the keeper in each of the 4 directions.
; A pseudo-code for this is:
; 
; ...
; (result (list (try-move s UP) (try-move s DOWN) (try-move s LEFT) (try-move s RIGHT)))
; ...
; 
; You will need to define the function try-move and decide how to represent UP,DOWN,LEFT,RIGHT.
; Any NIL result returned from try-move can be removed by cleanUpList.
; 
;
(defun next-states (s)
  (let* ((pos (getKeeperPosition s 0))
     (x (car pos))
     (y (cadr pos))
     ;x and y are now the coordinate of the keeper in s.
     (result (list (try-move s 'UP) (try-move s 'DOWN) (try-move s 'LEFT) (try-move s 'RIGHT)))
     )
    (cleanUpList result);end
   );end let
  );end defun

(defun try-move (s dir)
  (let* ((pos (getKeeperPosition s 0))
      (x (car pos))
      (y (cadr pos)))
    ; get coordinates of keeper into x & y
    (cond
      ((equal dir 'UP)
        (cond
          ;block above is a star - move player there
          ((isStar (get-square s (- y 1) x))
            (move-star s y x (- y 1) x))
          ;block above is blank - move player there
          ((isBlank (get-square s (- y 1) x))
            (move-blank s y x (- y 1) x))
          ;block above is a box - move box+player
          ((or (isBox (get-square s (- y 1) x)) (isBoxStar (get-square s (- y 1) x)))
            (move-box s y x (- y 1) x (- y 2) x))
          );end UP cond
        );end UP
      ((equal dir 'DOWN)
        (cond
          ;block below is a star - move player there
          ((isStar (get-square s (+ y 1) x))
            (move-star s y x (+ y 1) x))
          ;block below is blank - move player there
          ((isBlank (get-square s (+ y 1) x))
            (move-blank s y x (+ y 1) x))
          ;block above is a box - move box+player
          ((or (isBox (get-square s (+ y 1) x)) (isBoxStar (get-square s (+ y 1) x)))
            (move-box s y x (+ y 1) x (+ y 2) x))
          );end DOWN cond
        )
      ((equal dir 'LEFT)
        (cond
          ;block left is a star - move player there
          ((isStar (get-square s y (- x 1)))
            (move-star s y x y (- x 1)))
          ;block left is blank - move player there
          ((isBlank (get-square s y (- x 1)))
            (move-blank s y x y (- x 1)))
          ;block above is a box - move box+player
          ((or (isBox (get-square s y (- x 1))) (isBoxStar (get-square s y (- x 1))))
            (move-box s y x y (- x 1) y (- x 2)))
          );end LEFT cond
        )
      ((equal dir 'RIGHT)
        (cond
          ;block right is a star - move player there
          ((isStar (get-square s y (+ x 1)))
            (move-star s y x y (+ x 1)))
          ;block right is blank - move player there
          ((isBlank (get-square s y (+ x 1)))
            (move-blank s y x y (+ x 1)))
          ;block above is a box - move box+player
          ((or (isBox (get-square s y (+ x 1))) (isBoxStar (get-square s y (+ x 1))))
            (move-box s y x y (+ x 1) y (+ x 2)))
          );end RIGHT cond
        )
      (t NIL)
      );end cond
    );end let
  );end defun

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; HELPER FUNCTIONS OF try-move
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;
; get-square returns the integer content of state S at
; (r,c)
;
(defun get-square (s r c)
  (cond
    ;if r or c out of bounds, return wall
    ((> 0 r) 1)
    ((> 0 c) 1)
    ((< (- (length s) 1) r) 1)
    ((< (- (length (car s)) 1) c) 1)
    ;otherwise, retreive the square
    (t (car (nthcdr c (car (nthcdr r s)))))
    );end cond
  );end defun

;
; Helper function of set-row
;
(defun get-prec-cols (s r c)
  (cond
    ;if no preceding cols, return nil list
    ((= 0 c) (list NIL))
    ;if more than all cols, return row
    ((<= (length (car s)) c) (car (nthcdr r s)))
    ;otherwise, return all preceding cols
    (t (butlast (car (nthcdr r s)) (- (length (car s)) c)))
    );end cond
  );end defun

;
; Helper function of set-row
;
(defun get-rest-cols (s r c)
  (cond
    ;if no following cols, return nil list
    ((<= (- (length (car s)) 1) c) (list NIL))
    ;otherwise, return all following cols
    (t (nthcdr (+ c 1) (car (nthcdr r s))))
    );end cond
  );end defun

;
; Helper function of set-square
; sets targeted cell to value v in corresponding row
;
(defun set-row (s r c v)
  ;create new row out with v set
  (cleanUpList (append (append (get-prec-cols s r c) (list v)) (get-rest-cols s r c)))
  );end defun

;
; Helper function of set-square
;
(defun get-prec-rows (s r)
  (cond
    ;if no preceding rows, return nil list
    ((= 0 r) (list NIL))
    ;if more than all cols, return s
    ((<= (length s) r) s)
    ;otherwise, return all preceding rows
    (t (butlast s (- (length s) r)))
    );end cond
  );end defun

;
; Helper function of set-square
;
(defun get-rest-rows (s r)
  (cond
    ;if no following rows, return nil list
    ((<= (- (length s) 1) r) (list NIL))
    ;otherwise, return following rows
    (t (nthcdr (+ r 1) s))
    );end cond
  );end defun

;
; Helper function of try-move
; Returns altered state with cell (r,c) changed to value v
;
(defun set-square (s r c v)
  (cleanUpList (append (append (get-prec-rows s r) (list (set-row s r c v))) (get-rest-rows s r)))
  );end defun

;
; Helper function of try-move
; moves keeper from (keeper_r,keeper_c) to star on (star_r,star_c)
;
(defun move-star (s keeper_r keeper_c star_r star_c)
  (cond
    ;if keeper is on a star
    ((isKeeperStar (get-square s keeper_r keeper_c))
      (set-square (set-square s star_r star_c keeperstar) keeper_r keeper_c star))
    ;if keeper is on a blank
    (t (set-square (set-square s star_r star_c keeperstar) keeper_r keeper_c blank))
    );end cond
  );end defun

;
; Helper function of try-move
; moves keeper from (keeper_r,keeper_c) to blank on (blank_r,blank_c)
;
(defun move-blank (s keeper_r keeper_c blank_r blank_c)
  (cond
    ;if keeper is on a star
    ((isKeeperStar (get-square s keeper_r keeper_c))
      (set-square (set-square s blank_r blank_c keeper) keeper_r keeper_c star))
    ;if keeper is on a blank
    (t (set-square (set-square s blank_r blank_c keeper) keeper_r keeper_c blank))
    );end cond
  );end defun

;
; Helper function of try-move
; moves keeper from (keeper_r,keeper_c) and box from (box_r,box_c)
;
(defun move-box (s keeper_r keeper_c box_r box_c dest_r dest_c)
  (cond
    ;if destination cell is a star
    ((isStar (get-square s dest_r dest_c))
      (cond
        ;if box is on a star
        ((isBoxStar (get-square s box_r box_c))
          (set-square (move-star s keeper_r keeper_c box_r box_c) dest_r dest_c boxstar))
        ;if box is on a blank
        ((isBox (get-square s box_r box_c))
          (set-square (move-blank s keeper_r keeper_c box_r box_c) dest_r dest_c boxstar))
        );end isStar cond
      );end isStar
    ;if destination cell is a blank
    ((isBlank (get-square s dest_r dest_c))
      (cond
        ;if box is on a star
        ((isBoxStar (get-square s box_r box_c))
          (set-square (move-star s keeper_r keeper_c box_r box_c) dest_r dest_c box))
        ;if box is on a blank
        ((isBox (get-square s box_r box_c))
          (set-square (move-blank s keeper_r keeper_c box_r box_c) dest_r dest_c box))
        );end isBlank cond
      );end isBlank
    (t NIL)
    );end cond
  );end defun

; EXERCISE: Modify this function to compute the trivial 
; admissible heuristic.
;
(defun h0 (s)
  0
  );end defun

; EXERCISE: Modify this function to compute the 
; number of misplaced boxes in s.
;
; This heuristic function is admissible. If there are
; N boxes not on goal positions, then at least N boxes
; need to be moved to those goal positions still.
; Boxes on goal positions may need to be moved off
; in order to reach the goal state, but that means
; that this is an optimistic cost, which makes it admissible.
;
(defun h1 (s)
  (cond
    ; base case: no box found
    ((null s) 0)
    (t (+ (count box (car s)) (h1 (cdr s)))
      );end t
    );end cond
  );end defun

; EXERCISE: Change the name of this function to h<UID> where
; <UID> is your actual student ID number. Then, modify this 
; function to compute an admissible heuristic value of s. 
; 
; This function will be entered in the competition.
; Objective: make A* solve problems as fast as possible.
; The Lisp 'time' function can be used to measure the 
; running time of a function call.
;
; My heuristic takes the distance from the keeper, the
; top-leftmost box, and top-leftmost goal and computes
; the Manhattan distance from the box to the goal, the
; Manhattan distance from the keeper to the box, and adds 
; the distance of the box to the goal with the 
; distance of the keeper to the box.
;
(defun h804011675 (s)
  (let* (
    ;get number of boxes not on goal
    ; (numBox (h1 s))
    ;get Keeper coordinates
    (pos (getKeeperPosition s 0))
    (x (car pos))
    (y (cadr pos))
    ;get Box coordinates
    (boxPos (getBoxPosition s 0))
    (box_x (car boxPos))
    (box_y (cadr boxPos))
    ;get Star coordinates
    (starPos (getStarPosition s 0))
    (star_x (car starPos))
    (star_y (cadr starPos))
    ;get keeperStar coordinates (in case keeper is on star)
    (keeperstarPos (getKeeperStarPosition s 0))
    (keeperstar_x (car keeperstarPos))
    (keeperstar_y (cadr keeperstarPos))
    )
    (cond
      ;if boxPos is NIL, return cost of 0 (no boxes left)
      ((null boxPos) 0)
      ;Deadlock
      ((or
        (and (isWall (get-square s (- box_y 1) box_x)) (isWall (get-square s box_y (- box_x 1))))
        (and (isWall (get-square s (- box_y 1) box_x)) (isWall (get-square s box_y (+ box_x 1))))
        (and (isWall (get-square s (+ box_y 1) box_x)) (isWall (get-square s box_y (- box_x 1))))
        (and (isWall (get-square s (+ box_y 1) box_x)) (isWall (get-square s box_y (+ box_x 1))))
        )
        1000)
      ;heuristic is [Manhattan Distance (box-star)] + [Manhattan Dist (keeper-box)]
      (t (cond
          ;if keeper is on star, use KeeperStar position for star coordinates
          ((null starPos) (+ (abs (- box_x keeperstar_x)) (abs (- box_y keeperstar_y))
            ; (* numBox (abs (- box_x x)) (abs (- box_y y)))))
            (abs (- box_x x)) (abs (- box_y y))))
          (t (+ (abs (- box_x star_x)) (abs (- box_y star_y))
            ; (* numBox (abs (- box_x x)) (abs (- box_y y)))))
            (abs (- box_x x)) (abs (- box_y y))))
        );end cond
        );end t
      );end cond
    );end let
  );end defun

;
; HELPER FUNCTIONS of h804011675
; getBoxPosition and getStarPosition retreive the coordinates
; of a box and star to compute a heuristic (Manhattan Distance)

;
; Helper function of getBoxPosition
;
(defun getBoxColumn (r col)
  (cond ((null r) nil)
    (t (if (isBox (car r))
           col
         (getBoxColumn (cdr r) (+ col 1))
         );end if
       );end t
    );end cond
  )

;
; getBoxPosition (s firstRow)
; Returns a list indicating the position of the box (c r).
; 
; Assumes that the box is in row >= firstRow.
; The top row is the zeroth row.
; The first (right) column is the zeroth column.
;
(defun getBoxPosition (s row)
  (cond ((null s) nil)
    (t (let ((x (getBoxColumn (car s) 0)))
         (if x
         ;box is in this row
         (list x row)
         ;otherwise move on
         (getBoxPosition (cdr s) (+ row 1))
         );end if
           );end let
     );end t
    );end cond
  );end defun

;
; Helper function of getStarPosition
;
(defun getStarColumn (r col)
  (cond ((null r) nil)
    (t (if (isStar (car r))
           col
         (getStarColumn (cdr r) (+ col 1))
         );end if
       );end t
    );end cond
  )

;
; getStarPosition (s firstRow)
; Returns a list indicating the position of the star (c r).
; 
; Assumes that the star is in row >= firstRow.
; The top row is the zeroth row.
; The first (right) column is the zeroth column.
;
(defun getStarPosition (s row)
  (cond ((null s) nil)
    (t (let ((x (getStarColumn (car s) 0)))
         (if x
         ;star is in this row
         (list x row)
         ;otherwise move on
         (getStarPosition (cdr s) (+ row 1))
         );end if
           );end let
     );end t
    );end cond
  );end defun

;
; Helper function of getKeeperStarPosition
;
(defun getKeeperStarColumn (r col)
  (cond ((null r) nil)
    (t (if (isKeeperStar (car r))
           col
         (getKeeperStarColumn (cdr r) (+ col 1))
         );end if
       );end t
    );end cond
  )

;
; getKeeperStarPosition (s firstRow)
; Returns a list indicating the position of the keeperstar (c r).
; 
; Assumes that the keeperstar is in row >= firstRow.
; The top row is the zeroth row.
; The first (right) column is the zeroth column.
;
(defun getKeeperStarPosition (s row)
  (cond ((null s) nil)
    (t (let ((x (getKeeperStarColumn (car s) 0)))
         (if x
         ;keeperstar is in this row
         (list x row)
         ;otherwise move on
         (getKeeperStarPosition (cdr s) (+ row 1))
         );end if
           );end let
     );end t
    );end cond
  );end defun

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

#|
 | Some predefined problems.
 | Each problem can be visualized by calling (printstate <problem>). For example, (printstate p1).
 | Problems are ordered roughly by their difficulties.
 | For most problems, we also privide 2 additional number per problem:
 |    1) # of nodes expanded by A* using our next-states and h0 heuristic.
 |    2) the depth of the optimal solution.
 | These numbers are located at the comments of the problems. For example, the first problem below 
 | was solved by 80 nodes expansion of A* and its optimal solution depth is 7.
 | 
 | Your implementation may not result in the same number of nodes expanded, but it should probably
 | give something in the same ballpark. As for the solution depth, any admissible heuristic must 
 | make A* return an optimal solution. So, the depths of the optimal solutions provided could be used
 | for checking whether your heuristic is admissible.
 |
 | Warning: some problems toward the end are quite hard and could be impossible to solve without a good heuristic!
 | 
 |#

;(80,7)
(setq p1 '((1 1 1 1 1 1)
       (1 0 3 0 0 1)
       (1 0 2 0 0 1)
       (1 1 0 1 1 1)
       (1 0 0 0 0 1)
       (1 0 0 0 4 1)
       (1 1 1 1 1 1)))

;(110,10)
(setq p2 '((1 1 1 1 1 1 1)
       (1 0 0 0 0 0 1) 
       (1 0 0 0 0 0 1) 
       (1 0 0 2 1 4 1) 
       (1 3 0 0 1 0 1)
       (1 1 1 1 1 1 1)))

;(211,12)
(setq p3 '((1 1 1 1 1 1 1 1 1)
       (1 0 0 0 1 0 0 0 1)
       (1 0 0 0 2 0 3 4 1)
       (1 0 0 0 1 0 0 0 1)
       (1 0 0 0 1 0 0 0 1)
       (1 1 1 1 1 1 1 1 1)))

;(300,13)
(setq p4 '((1 1 1 1 1 1 1)
       (0 0 0 0 0 1 4)
       (0 0 0 0 0 0 0)
       (0 0 1 1 1 0 0)
       (0 0 1 0 0 0 0)
       (0 2 1 0 0 0 0)
       (0 3 1 0 0 0 0)))

;(551,10)
(setq p5 '((1 1 1 1 1 1)
       (1 1 0 0 1 1)
       (1 0 0 0 0 1)
       (1 4 2 2 4 1)
       (1 0 0 0 0 1)
       (1 1 3 1 1 1)
       (1 1 1 1 1 1)))

;(722,12)
(setq p6 '((1 1 1 1 1 1 1 1)
       (1 0 0 0 0 0 4 1)
       (1 0 0 0 2 2 3 1)
       (1 0 0 1 0 0 4 1)
       (1 1 1 1 1 1 1 1)))

;(1738,50)
(setq p7 '((1 1 1 1 1 1 1 1 1 1)
       (0 0 1 1 1 1 0 0 0 3)
       (0 0 0 0 0 1 0 0 0 0)
       (0 0 0 0 0 1 0 0 1 0)
       (0 0 1 0 0 1 0 0 1 0)
       (0 2 1 0 0 0 0 0 1 0)
       (0 0 1 0 0 0 0 0 1 4)))

;(1763,22)
(setq p8 '((1 1 1 1 1 1)
       (1 4 0 0 4 1)
       (1 0 2 2 0 1)
       (1 2 0 1 0 1)
       (1 3 0 0 4 1)
       (1 1 1 1 1 1)))

;(1806,41)
(setq p9 '((1 1 1 1 1 1 1 1 1) 
       (1 1 1 0 0 1 1 1 1) 
       (1 0 0 0 0 0 2 0 1) 
       (1 0 1 0 0 1 2 0 1) 
       (1 0 4 0 4 1 3 0 1) 
       (1 1 1 1 1 1 1 1 1)))

;(10082,51)
(setq p10 '((1 1 1 1 1 0 0)
        (1 0 0 0 1 1 0)
        (1 3 2 0 0 1 1)
        (1 1 0 2 0 0 1)
        (0 1 1 0 2 0 1)
        (0 0 1 1 0 0 1)
        (0 0 0 1 1 4 1)
        (0 0 0 0 1 4 1)
        (0 0 0 0 1 4 1)
        (0 0 0 0 1 1 1)))

;(16517,48)
(setq p11 '((1 1 1 1 1 1 1)
        (1 4 0 0 0 4 1)
        (1 0 2 2 1 0 1)
        (1 0 2 0 1 3 1)
        (1 1 2 0 1 0 1)
        (1 4 0 0 4 0 1)
        (1 1 1 1 1 1 1)))

;(22035,38)
(setq p12 '((0 0 0 0 1 1 1 1 1 0 0 0)
        (1 1 1 1 1 0 0 0 1 1 1 1)
        (1 0 0 0 2 0 0 0 0 0 0 1)
        (1 3 0 0 0 0 0 0 0 0 0 1)
        (1 0 0 0 2 1 1 1 0 0 0 1)
        (1 0 0 0 0 1 0 1 4 0 4 1)
        (1 1 1 1 1 1 0 1 1 1 1 1)))

;(26905,28)
(setq p13 '((1 1 1 1 1 1 1 1 1 1)
        (1 4 0 0 0 0 0 2 0 1)
        (1 0 2 0 0 0 0 0 4 1)
        (1 0 3 0 0 0 0 0 2 1)
        (1 0 0 0 0 0 0 0 0 1)
        (1 0 0 0 0 0 0 0 4 1)
        (1 1 1 1 1 1 1 1 1 1)))

;(41715,53)
(setq p14 '((0 0 1 0 0 0 0)
        (0 2 1 4 0 0 0)
        (0 2 0 4 0 0 0)    
        (3 2 1 1 1 0 0)
        (0 0 1 4 0 0 0)))

;(48695,44)
(setq p15 '((1 1 1 1 1 1 1)
        (1 0 0 0 0 0 1)
        (1 0 0 2 2 0 1)
        (1 0 2 0 2 3 1)
        (1 4 4 1 1 1 1)
        (1 4 4 1 0 0 0)
        (1 1 1 1 0 0 0)
        ))

;(91344,111)
(setq p16 '((1 1 1 1 1 0 0 0)
        (1 0 0 0 1 0 0 0)
        (1 2 1 0 1 1 1 1)
        (1 4 0 0 0 0 0 1)
        (1 0 0 5 0 5 0 1)
        (1 0 5 0 1 0 1 1)
        (1 1 1 0 3 0 1 0)
        (0 0 1 1 1 1 1 0)))

;(3301278,76)
(setq p17 '((1 1 1 1 1 1 1 1 1 1)
        (1 3 0 0 1 0 0 0 4 1)
        (1 0 2 0 2 0 0 4 4 1)
        (1 0 2 2 2 1 1 4 4 1)
        (1 0 0 0 0 1 1 4 4 1)
        (1 1 1 1 1 1 0 0 0 0)))

;(??,25)
(setq p18 '((0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0)
        (0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0)
        (1 1 1 1 1 0 0 0 0 0 0 1 1 1 1 1)
        (0 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0)
        (0 0 0 0 0 0 1 0 0 1 0 0 0 0 0 0)
        (0 0 0 0 0 0 0 0 3 0 0 0 0 0 0 0)
        (0 0 0 0 0 0 1 0 0 1 0 0 0 0 0 0)
        (0 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0)
        (1 1 1 1 1 0 0 0 0 0 0 1 1 1 1 1)
        (0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0)
        (0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0)
        (0 0 0 0 1 0 0 0 0 0 4 1 0 0 0 0)
        (0 0 0 0 1 0 2 0 0 0 0 1 0 0 0 0)       
        (0 0 0 0 1 0 2 0 0 0 4 1 0 0 0 0)
        ))
;(??,21)
(setq p19 '((0 0 0 1 0 0 0 0 1 0 0 0)
        (0 0 0 1 0 0 0 0 1 0 0 0)
        (0 0 0 1 0 0 0 0 1 0 0 0)
        (1 1 1 1 0 0 0 0 1 1 1 1)
        (0 0 0 0 1 0 0 1 0 0 0 0)
        (0 0 0 0 0 0 3 0 0 0 2 0)
        (0 0 0 0 1 0 0 1 0 0 0 4)
        (1 1 1 1 0 0 0 0 1 1 1 1)
        (0 0 0 1 0 0 0 0 1 0 0 0)
        (0 0 0 1 0 0 0 0 1 0 0 0)
        (0 0 0 1 0 2 0 4 1 0 0 0)))

;(??,??)
(setq p20 '((0 0 0 1 1 1 1 0 0)
        (1 1 1 1 0 0 1 1 0)
        (1 0 0 0 2 0 0 1 0)
        (1 0 0 5 5 5 0 1 0)
        (1 0 0 4 0 4 0 1 1)
        (1 1 0 5 0 5 0 0 1)
        (0 1 1 5 5 5 0 0 1)
        (0 0 1 0 2 0 1 1 1)
        (0 0 1 0 3 0 1 0 0)
        (0 0 1 1 1 1 1 0 0)))

;(??,??)
(setq p21 '((0 0 1 1 1 1 1 1 1 0)
        (1 1 1 0 0 1 1 1 1 0)
        (1 0 0 2 0 0 0 1 1 0)
        (1 3 2 0 2 0 0 0 1 0)
        (1 1 0 2 0 2 0 0 1 0)
        (0 1 1 0 2 0 2 0 1 0)
        (0 0 1 1 0 2 0 0 1 0)
        (0 0 0 1 1 1 1 0 1 0)
        (0 0 0 0 1 4 1 0 0 1)
        (0 0 0 0 1 4 4 4 0 1)
        (0 0 0 0 1 0 1 4 0 1)
        (0 0 0 0 1 4 4 4 0 1)
        (0 0 0 0 1 1 1 1 1 1)))

;(??,??)
(setq p22 '((0 0 0 0 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0)
        (0 0 0 0 1 0 0 0 1 0 0 0 0 0 0 0 0 0 0)
        (0 0 0 0 1 2 0 0 1 0 0 0 0 0 0 0 0 0 0)
        (0 0 1 1 1 0 0 2 1 1 0 0 0 0 0 0 0 0 0)
        (0 0 1 0 0 2 0 2 0 1 0 0 0 0 0 0 0 0 0)
        (1 1 1 0 1 0 1 1 0 1 0 0 0 1 1 1 1 1 1)
        (1 0 0 0 1 0 1 1 0 1 1 1 1 1 0 0 4 4 1)
        (1 0 2 0 0 2 0 0 0 0 0 0 0 0 0 0 4 4 1)
        (1 1 1 1 1 0 1 1 1 0 1 3 1 1 0 0 4 4 1)
        (0 0 0 0 1 0 0 0 0 0 1 1 1 1 1 1 1 1 1)
        (0 0 0 0 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

#|
 | Utility functions for printing states and moves.
 | You do not need to understand any of the functions below this point.
 |#

;
; Helper function of prettyMoves
; from s1 --> s2
;
(defun detectDiff (s1 s2)
  (let* ((k1 (getKeeperPosition s1 0))
     (k2 (getKeeperPosition s2 0))
     (deltaX (- (car k2) (car k1)))
     (deltaY (- (cadr k2) (cadr k1)))
     )
    (cond ((= deltaX 0) (if (> deltaY 0) 'DOWN 'UP))
      (t (if (> deltaX 0) 'RIGHT 'LEFT))
      );end cond
    );end let
  );end defun

;
; Translates a list of states into a list of moves.
; Usage: (prettyMoves (a* <problem> #'goal-test #'next-states #'heuristic))
;
(defun prettyMoves (m)
  (cond ((null m) nil)
    ((= 1 (length m)) (list 'END))
    (t (cons (detectDiff (car m) (cadr m)) (prettyMoves (cdr m))))
    );end cond
  );

;
; Print the content of the square to stdout.
;
(defun printSquare (s)
  (cond ((= s blank) (format t " "))
    ((= s wall) (format t "#"))
    ((= s box) (format t "$"))
    ((= s keeper) (format t "@"))
    ((= s star) (format t "."))
    ((= s boxstar) (format t "*"))
    ((= s keeperstar) (format t "+"))
    (t (format t "|"))
    );end cond
  )

;
; Print a row
;
(defun printRow (r)
  (dolist (cur r)
    (printSquare cur)    
    )
  );

;
; Print a state
;
(defun printState (s)
  (progn    
    (dolist (cur s)
      (printRow cur)
      (format t "~%")
      )
    );end progn
  )

;
; Print a list of states with delay.
;
(defun printStates (sl delay)
  (dolist (cur sl)
    (printState cur)
    (sleep delay)
    );end dolist
  );end defun
