(defun f(x &rest y)
    (cond
        ((null y) x)
        (t (append x (mapcar #'car y)))
    )
)

; (append (f '(1 2)) (f '(3 4) '(5 6) '(7 8)))
;     3.       1.              2. 
; 1. (f '(1 2)) se evalueaza la (1 2), deoarece parametrul optional y e gol
; 2. (f '(3 4) '(5 6) '(7 8)): x e '(3 4), y e ((5 6) (7 8))
;   mapcar #' car y returneaza (5 7), iar append x (5 7) va returna (3 4 5 7)
; 3. append tot returneaza (1 2 3 4 5 7)