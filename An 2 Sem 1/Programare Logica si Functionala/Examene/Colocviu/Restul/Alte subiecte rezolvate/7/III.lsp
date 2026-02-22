; Functia elimina numerele divizibile cu 3
; elim3(l:list)
; l - lista de unde eliminam
;
; model recursiv:
; elim3(l) = U | (elim3(li), daca li lista
;              | [], daca li e numar si li % 3 = 0
;              | (li), altfel
(defun elim3 (l)
    (mapcan #'(lambda (x)
                (cond
                    ((listp x) (list (elim3 x)))
                    ((and (numberp x) (equal 0 (mod x 3))) nil)
                    (t (list x))
                )
               ) l
    )
)