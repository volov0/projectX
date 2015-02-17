; scheme sample

(define (sum numlist)
  (if (null? numlist) 0
  (+ (car numlist) (sum (cdr numlist)))))

