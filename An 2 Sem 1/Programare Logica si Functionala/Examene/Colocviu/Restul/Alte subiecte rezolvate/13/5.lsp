; Functia extrage primul atom numeric dintr-o lista
; prim-numeric(l:list)
; l - lista de unde luam
;
; model recursiv:
; prim-numeric(l1..ln) = | false, daca n = 0
;                        | l1, daca l1 e numar
;                        | prim-numeric(l2..ln), daca l1 e atom
;                        | prim-numeric(l1) OR prim-numeric(l2..ln), altfel
(defun prim-numeric(l)
    (cond
        ((null l) nil)
        ((numberp (car l)) (car l))
        ((atom (car l)) (prim-numeric (cdr l)))
        (t (or (prim-numeric (car l)) (prim-numeric (cdr l))))
    )
)

; Functia returneaza numarul subliste care au ca prim atom numeric unul impar
; prim-impar(l:list)
; l - lista de unde luam
;
; model recursiv:
; prim-impar(l1..ln) = | 0, daca l e atom
;                      | 1 + E(prim-impar(li)), daca prim-numeric e numar impar
;                      | E(prim-impar(li)), altfel
(defun prim-impar(l)
    (cond
        ((atom l) 0)
        (t
            (+
                ((lambda (num)
                
                    (if (and num (oddp num)) 1 0)
                  
                  ) (prim-numeric l)
                )
                
                (apply #'+(mapcar #'prim-impar l))
            )
        )
    )
)