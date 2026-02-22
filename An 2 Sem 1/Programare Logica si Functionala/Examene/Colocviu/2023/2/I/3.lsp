(defun f(x &rest y)
    (cond
        ((null y) x)
        (t (append x (mapcar #'car y)))
    )
)

; (append (f '(1 2)) (f '(3 4) '(5 6) '(7 8)))
;    3.       1.                2.
; 1. in (f '(1 2)), x e lista (1 2), iar y e nil,
;    asa ca se intra pe prima forma din cond, si se va returna (1 2)
; 2. in (f '(3 4) '(5 6) '(7 8)), x e lista (3 4), iar y e lista ((5 6) (7 8))
;    mapcar #'car y va returna (5 7), iar astfel functia va va returna (3 4 5 7)
; 3. append-ul final va returna (1 2 3 4 5 7)