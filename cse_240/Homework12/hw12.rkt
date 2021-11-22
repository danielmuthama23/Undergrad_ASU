;Your Name: Tyler Fichiera
;Course: CSE 240
;Use the template for your programming assignment

;Q1 (6 points)
(define OR-GATE (lambda (a b)
    ; Check both values, one at a time
    (if (= a 1)
        1
        (if (= b 1) 1 0)
    )
))

(define AND-GATE (lambda (a b)
    (if (= a b 1) 1 0)
))

(define XOR-GATE (lambda (a b)
    ; Return 0 if a and b are both true
    (if (= a b 1)
        0
        ; Check if a or b is true
        (if (= a 1) 1
            (if (= b 1) 1 0)
        )
    )
))

;Test cases
(AND-GATE 0 0)
(AND-GATE 0 1)
(AND-GATE 1 0)
(AND-GATE 1 1)
;0
;0
;0
;1
(newline)
(OR-GATE 0 0)
(OR-GATE 0 1)
(OR-GATE 1 0)
(OR-GATE 1 1)
;0
;1
;1
;1
(newline)
(XOR-GATE 0 0)
(XOR-GATE 0 1)
(XOR-GATE 1 0)
(XOR-GATE 1 1)
;0
;1
;1
;0

;Q2 
;(4 points each)
(define bitAdder (lambda (x a b)
    (cons (sum-bits x a b) (carry-out x a b))
))

;(5 points each)
(define sum-bits (lambda (x a b)
    (XOR-GATE x (XOR-GATE a b))
))

;(5 points each)
(define carry-out (lambda (x a b)
    (OR-GATE (AND-GATE x (OR-GATE a b)) (AND-GATE a b))
))

;Test cases
(newline)
(bitAdder 0 0 0) 	
(bitAdder 0 0 1) 	
(bitAdder 0 1 0) 	
(bitAdder 0 1 1)	
(bitAdder 1 0 0) 	
(bitAdder 1 0 1)	
(bitAdder 1 1 0) 	
(bitAdder 1 1 1) 
;(0 . 0)
;(1 . 0)
;(1 . 0)
;(0 . 1)
;(1 . 0)
;(0 . 1)
;(0 . 1)
;(1 . 1)


;Q3.1 (4 points)
(define tail (lambda (lst)
    ; reverse list and then get first element
    (car (reverse lst))
))

;Q3.2 (4 points)
(define rmtail (lambda (lst)
    ; reverse list, remove first element and then reverse back
    (reverse (cdr (reverse lst)))
))

;Q3.3 (4 points)
; (1) size n: number of bits in L1 and L2
; (2) Stopping condition: if L1 is null, return (list (list c))
; (3) size-(n-1) problem: (rmtail L1)
; (4) to go from size n to size n-1, we use the first call of (recursiveAdd) b/c
;     that will return the list without the last element (n-1) 

;Q3.4 (14 points)
(define X1 '(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0))	
(define X2 '(1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1))	
(define X3 '(0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1))	
(define X4 '(1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0))
(define X5 '(0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1))	
(define X6 '(1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1))

(define recursiveAdd (lambda (A B c)
    ; Check if list is null
    ; use methods from Q3.1
    (if (null? A)
        (list (list c))
        (
            cons (car (bitAdder (tail A) (tail B) c))
            (recursiveAdd (rmtail A) (rmtail B)
                (cdr (bitAdder (tail A) (tail B) c))
            )
        )
    )
))

(define n-bit-adder1 (lambda (L1 L2 n)
    ; Call recursive method with the supplied params
    (reverse (recursiveAdd L1 L2 n))
))

; Did not use the following helper methods:
; (define n-bit-adderhelper1 (lambda (L1 L2 n resulti)
; (define n-bit-adder-carry-out (lambda (L1 L2 n resulti)

;Test cases
(newline)
(n-bit-adder1  X1 X2 32)
(n-bit-adder1  X3 X4 32)
(n-bit-adder1  X5 X6 32)
(n-bit-adder1  X2 X3 32)
(n-bit-adder1  X4 X5 32)
(n-bit-adder1  X1 X6 32)
(newline)
(n-bit-adder1  X1 X3 32)
(n-bit-adder1  X1 X4 32)
(n-bit-adder1  X1 X5 32)
(n-bit-adder1  X2 X4 32)
(n-bit-adder1  X2 X5 32)
(n-bit-adder1  X2 X6 32)

;((0) 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1)
;((0) 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1)
;((1) 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0)
;((1) 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 0)
;((1) 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1)
;((0) 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1)

;((0) 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1)
;((0) 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0)
;((0) 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1)
;((1) 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 0 1)
;((1) 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 0)
;((1) 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0)
