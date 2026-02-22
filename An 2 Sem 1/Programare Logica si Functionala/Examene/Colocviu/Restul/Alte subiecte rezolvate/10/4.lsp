; Functia elimina toate aparitiile unui atom dintr-o lista
; elim(l:list, e:list)
; l - lista de unde elimina
; e - elementul pe care il elimina
;
; model recursiv:
; elim(l, e) = U (li), li = | (elim(li, e), daca li e lista
;                           | nil, daca li = e
;                           | (li), altfel, i = 1..n
(defun elim(l e)
    (mapcan #'(lambda (x)
                (cond
                    ((listp x) (list (elim x e)))
                    ((equal x e) nil)
                    (t (list x))
                )
               ) l
    )
)