; Functia returneaza nr de atomi de pe nivelul k
; nod-nivel(l:list, k:int)
; l - lista pe care vrem sa o parcurgem
; k - nivelul de la care numaram
;
; model recursiv:
; nod-nivel(l, k) = | 1, daca l e atom si k = 0
;                   | 0, daca l e atom
;                   | E(nod-nivel(li, k-1)), altfel
(defun nod-nivel(l k)
    (cond
        ((and (atom l) (equal k 0)) 1)
        ((atom l) 0)
        (t (apply #'+ (mapcar #'(lambda (x)
                                    (nod-nivel x (- k 1))
                                ) l
                      )
            )
        )
    )
)