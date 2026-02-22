; Functia inlocuieste un atom la nivele impare
; lvl_impar(l:list, e:atom, lvl:int)
; l - lista unde inlocuim
; e - elementul cu care inlocuim
; lvl - nivelul la care suntem
;
; model recursiv:
; lvl_impar(l, e, lvl) = U(T(li), i = 1..n,
;                   , unde T(x) = | lvl_impar(x, e, lvl + 1), daca x e lista
;                                 | e, daca lvl e impar
;                                 | x, altfel
(defun lvl_impar(l e lvl)
    (mapcar #'(lambda (x)
                (cond
                    ((listp x) (lvl_impar x e (+ 1 lvl)))
                    ((oddp lvl) e)
                    (t x)
                )
              ) l
    )
)

; Functia inlocuieste un atom la nivele impare
; inloc(l:list, e:atom)
; l - lista unde inlocuim
; e - elementul cu care inlocuim
;
; model recursiv:
; inloc(l, e) = lvl_impar(l, e, 0)
(defun inloc(l e)
    (lvl_impar l e 0)
)
