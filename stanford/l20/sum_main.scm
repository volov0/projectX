; scheme sample

(define (fact n)
  (if (= n 0)
      1
	  (* n (fact (- n 1)))))

(define (sum numlist)
  (if (null? numlist) 0
  (+ (car numlist) (sum (cdr numlist)))))

(define (main args)
  (display (fact 6))
  (newline)
  (display (sum '(1 2 3 4 5 6 7)))
  (newline))
