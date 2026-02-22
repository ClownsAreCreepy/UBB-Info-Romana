; e-liniara(l1..ln) = | true, daca n = 0
; |                   | false, daca l1 e lista
;                     | e-liniara(l2..ln), altfel
(defun e-liniara(l)
    (cond
        ((null l) t)
        ((listp (car l)) nil)
        (t (e-liniara (cdr l)))
    )
)

; nr-numere(l) = | 1, daca l e numar
;                | 0, daca l e atom nenumaric
;                | E(nr-numere(li), altfel, i = 1..n
(defun nr-numere(l)
    (cond
        ((numberp l) 1)
        ((atom l) 0)
        (t (apply #'+ (mapcar #'nr-numere l)))
    )
)

; sterg(l1..ln) = | [], daca n = 0
;                 | l1 (+) sterg(l2..ln), daca l1 e atom
;                 | sterg(l2..ln), daca l1 e lista si e-liniara(l1) = true si nr-numere(l1) % 2 = 0
;                 | sterg(l1) (+) sterg(l2..ln), altfel
(defun sterg(l)
    (cond
        ((null l) nil)
        ((atom (car l)) (cons (car l) (sterg (cdr l))))
        ((and (listp (car l)) (e-liniara (car l)) (evenp (nr-numere (car l)))) (sterg (cdr l)))
        (t (cons (sterg (car l)) (sterg (cdr l))))
    )
)
