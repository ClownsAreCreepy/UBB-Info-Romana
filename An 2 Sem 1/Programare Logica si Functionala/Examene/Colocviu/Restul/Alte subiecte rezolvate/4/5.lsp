; Functia returneaza 1 daca primul atom e nenumeric, 0 altfel
; prim_atom(l:list)
; l - lista unde ne uitam
;
; model recursiv:
; prim_atom(l1..ln) = 
;   1. 0, daca n = 0 sau daca l1 e atom numeric
;   2. 1, daca 11 e atom
;   3. prim_atom(l1), altfel
(defun prim_atom (l)
    (cond
        ((or (null l) (and (atom l) (numberp l))) 0)
        ((atom l) 1)
        (t (prim_atom (car l)))
    )
)


; Functia returneaza cate subliste au primul atom nenumeric
; prim_nenumeric(l:list)
; l - lista unde ne uitam
;
; model recursiv:
; prim_nenumeric(l1..ln) = 
;   1. 0, daca l e atom
;   2. prim_atom(l) + E(prim_nenumeric(li)), altfel, i=1..n
(defun prim_nenumeric(l)
    (cond
        ((atom l) 0)
        (t
            (+
                (prim_atom l)
                (apply #'+ (mapcar #'prim_nenumeric l))
            )
        )
    )
)