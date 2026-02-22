;; Functia elimina din lista numerele multiple de 3
;; elim3(l:list)
;; l - lista de unde eliminam
;;
;; model recursiv:
;; elim3(l1..ln) = U F(li), i=1..n, unde F:
;;      F(l) = 
;;          1. (elim3(l)), daca l e lista
;;          2. nil, daca l e numar si l % 3 == 0
;;          3. (l), altfel
(defun elim3(l)
    (mapcan #'(lambda (x)
                          (cond
                                ((listp x) (list (elim3 x)))
                                ((and (numberp x) (equal (mod x 3) 0)) nil)
                                (t (list x))
                          )
              ) l
    )
)