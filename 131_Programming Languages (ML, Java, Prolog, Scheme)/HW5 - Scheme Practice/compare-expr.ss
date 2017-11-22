(define (compare-expr x y)
  (if (and (list? x) (list? y))                   ; check if both arguments are lists
    (if (equal? (length x) (length y))              ; both args are lists, check lengths
      (if (equal? (car x) (car y))                    ; both lists are of same length
        (case (car x)                                   ; first item of both are equal, compare based on what it is
          ('quote (compare-term x y))                     ; treat quoted terms as single term
          ('lambda (compare-lambda x y))
          ('let (compare-let x y))
          (else (compare-list x y)))
        (if (special-form x y)                          ; first item of both sides differ - check if one of them is a special form
          (compare-term x y)                              ; treat special forms as whole terms
          (compare-list x y)))                            ; otherwise, treat them as a list
      (compare-term x y))                             ; lists are of different length - compare as two separate terms
    (compare-term x y))                             ; either x or y is a single term - compare accordingly
)

(define (compare-term x y)
    (if (equal? x y)                              ; check if both args are equal
      x                                             ; if so, return x (both args same)
      (if (and (equal? x #t) (equal? y #f))         ; otherwise, check for 'TCP'
        'TCP
        (if (and (equal? x #f) (equal? y #t))         ; if not TCP, check for 'not TCP'
          '(not TCP)
          (list 'if 'TCP x y))))
)

(define (compare-lambda x y)
  (if (equal? (cadr x) (cadr y))                  ; check formals of lambdas
    (compare-list x y)                              ; if formals equal, compare as lists
    (compare-term x y))                             ; otherwise, compare as separate terms
)

(define (compare-let x y)
  (if (check-let-vars (cadr x) (cadr y))          ; check if binding same variable for both args
    (compare-list x y)                              ; if so, compare as lists
    (compare-term x y))                             ; otherwise, treat as separate terms
)

(define (check-let-vars x y)
  (if (and (equal? x '()) (equal? y '()))         ; recursive base case -> all items in 'let' lists are equal
    #t
    (if (equal? (caar x) (caar y))                  ; check the first item of both lists to see if they're equal
      (check-let-vars (cdr x) (cdr y))                ; if they are, recursively check the rest of both lists
      #f))                                            ; otherwise, false
)

(define (compare-list x y)
  (if (or (equal? x '()) (equal? y '()))          ; check if any argument is an empty list
    '()                                             ; if so, return empty list
    (cons (compare-expr (car x) (car y))            ; otherwise, cons the comparison of first item of each list
      (compare-list (cdr x) (cdr y))))              ; with the recursive list-comparison of tail of each list
)

; if any of the arguments contain a special-form, return true - otherwise, false
(define (special-form x y)
  (if (or (equal? (car x) 'quote) (equal? (car y) 'quote))
    #t
    (if (or (equal? (car x) 'lambda) (equal? (car y) 'lambda))
      #t
      (if (or (equal? (car x) 'let) (equal? (car y) 'let))
        #t
        (if (or (equal? (car x) 'if) (equal? (car y) 'if))
          #t
          #f))))
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (test-compare-expr x y)
  (let ((evaluated-expr (compare-expr x y)))
    (if (and
      (equal?
        (eval (make-eval-list evaluated-expr #t))
        (eval x))
      (equal?
        (eval (make-eval-list evaluated-expr #f))
        (eval y)))
      #t      ; if both evaluated expressions are equal, true
      #f))    ; otherwise, false
)

(define (make-eval-list x bool)
  (if bool
    (cons 'let (cons '((TCP #t)) (cons x '())))
    (cons 'let (cons '((TCP #f)) (cons x '()))))
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define test-x
  '(cons
    (+
      ((lambda (a b c)  ; lambda, same formals
        (if a b c))
          #f    ; booleans
          (if #t (let ((d 26)) (+ d 30)) 54)  ; let, same formals, different values
          (car (cons 42 (cons 6 '(90 156)))))  ; functions, quoted lists
      (let ((a #t)) (let ((a 68)) a)))  ; special form (let) vs function (+)
    (cons
      (if #f
        ((lambda (y x) (+ x y)) 2 4)  ; lambda, different formals
        (let ((x 4) (y 6)) (+ x y)))  ; let, different formals
      (cons
        '(if #f 4 6)  ; quoted lists
        (if #t '(46) '(28)))))  ; if
)

(define test-y
  '(cons
    (+
      ((lambda (a b c)
        (if a c b))
          #t
          (if #t (let ((d 28)) (+ d 30)) 54)
          (car (cons 4 (cons 6 '(90 6)))))
      (let ((a 80)) (- a 68)))
    (cons
      (if #t
        ((lambda (x y) (+ y x)) 2 4)
        (let ((y 6) (x 4)) (+ x y)))
      (cons
        (if #f 4 6)
        (if #t '(46) '()))))
)

; (test-compare-expr test-x test-y)