; Functia inlocuieste toti atomii de pe nivelul lvl cu 0
; inloc(l:int, lvl:int)
; l - lista unde inlocuim
; lvl - nivelul cerut
;
; model recursiv:
; inloc(l1..ln, lvl) = U(li), li = | inloc(li, lvl - 1), daca li e lista
;                                  | 0, daca lvl = 1
;                                  | li, altfel, i = 1..n
(defun inloc(l lvl)
    (mapcar #'(lambda (x)
                (cond
                    ((listp x) (inloc x (- lvl 1)))
                    ((equal lvl 1) 0)
                    (t x)
                )
               ) l
    )
)