; Q1 (5 points)
(- (+ (* 8 4) 3) 1) ; 1.1
(+ (* (+ 2 8) (- 10 2 5)) 15) ; 1.2
(* 9 (- (+ 5 (/ 32 8)) (* 3 (+ 7 9)))) ; 1.3
(* 3 (+ 9 (* (- (+ 2 (/ 36 4)) (* 2 5)) (- 10 2)))) ; 1.4
(- (/ (- (* (* (* (+ 4 6) (+ 6 4)) 2) 2) 10) 2) (+ (/ (* (+ (* 4 5) (* 6 4)) 3) 2) (* 4 5))) ; 1.5

; Q2 (5 points)
(define (Multiply x y) (* x y))
(Multiply 10 40) ; test case

; Q3 (5 points)
(define (Exponent x n) (if (< n 1) 1 (* x (Exponent x (- n 1)))))
(Exponent 2 5) ; test case

; Q4: Please enter test values 2 and 5. It should return 32. (5 points)
(display "Enter 2 5 as test case. It returns 32")
(newline)
(define (ReadForExponent) (Exponent (read) (read)))
(ReadForExponent) ; test func w/ inputs

; Q5 (5 points)
(define (MultiplyExponents w x y z) (Multiply (Exponent w x) (Exponent y z)))
(MultiplyExponents 2 5 3 4) ; test case

; Q6 (5 points)
(define (MultiplyLet x y) (
  let ((first-num x) (second-num y))
  (* first-num second-num)
))
(MultiplyLet 60 40) ; test case

; Q7 (10 points)
(define (Letexpression) (
  let ((two 2) (four 4) (five 5) (six 6) (ten 10))
  (- (/ (- (* (* (* (+ four six) (+ six four)) two) two) ten) two) (+ (/ (* (+ (* four five) (* six four)) 3) two) (* four five)))
))

(Letexpression)

; Q8: Enter values 1 2 3 4 5 6 7 8, and it should return 20. (10 points)
(display "Eenter 1 2 3 4 5 6 7 8 and e, and it returns 20.")
(newline)
(define (accumulator even-sum next) (
  ; check if input is a number
  if (number? next) (
    ; check if input is even
    if (= (modulo next 2) 0) (
      accumulator (+ even-sum next) (read)
    ) (
      accumulator even-sum (read)
    ))
    ; else display even-sum
    even-sum
  )
)
  
(accumulator 0 0)
