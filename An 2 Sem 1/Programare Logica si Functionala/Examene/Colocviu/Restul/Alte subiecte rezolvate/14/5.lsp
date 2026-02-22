; Functia afla maximul unei liste
; maxim(l:list)
; l - lista unde ne uitam
;
; model recursiv:
; maxim(l) = | l ,daca l e numar
;            | -infinit, daca l e atom
;            | max(maxim(li)), altfel, i = 1..n
(defun maxim(l)
    (cond
        ((numberp l) l)
        ((atom l) most-negative-fixnum)
        (t (apply #'max (mapcar #'maxim l)))
    )
)

; Functia returneaza nr de subliste a carui max e par
; nr-max(l:list)
; l - lista unde ne uitam
;
; model recursiv:
; nr-max(l) = | 0, daca l e atom
;             | 1 + E(nr-max(li)), daca mare != infinit si mare e par
;                                 , unde mare = maxim(li)
;             | E(nr-max(li)), altfel
(defun nr-max(l)
    (cond
        ((atom l) 0)
        (t 
            ((lambda (mare)
                (cond
                    ((and (not (equal most-negative-fixnum mare)) (evenp mare)) (+ 1 (apply #'+ (mapcar #'nr-max l))))
                    (t (apply #'+ (mapcar #'nr-max l)))
                )
             ) (maxim l)
            )
        )
    )
)