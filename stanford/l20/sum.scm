; scheme sample

(define (sum numlist)
  (if (null? numlist) 0
  (+ (car numlist) (sum (cdr numlist)))))

(write (sum '(1 2 3 4 5 6 7 8 9)))
(newline)
