; Functia inlocuieste nodurile de la nivele impare cu e
; replace(l:list, e:atom, lvl:int)
; l - arborele unde inlocuim
; e - elementul cu care inlocuim
; lvl - nivelul curent la care ne aflam
;
; model recursiv:
; replace(l, e, lvl) = U(li)| replace(li, e, lvl + 1), daca li e lista
;                           | e, daca lvl e impar
;                           | li, altfel, i = 1..n
(defun replace(l e lvl)
    (mapcar #'(lambda (x)
                (cond 
                    ((listp x) (replace x e (+ lvl 1)))
                    ((oddp lvl) e)
                    (t x)
                )
               ) l
    )
)

; Functia inlocuieste nodurile de la nivele impare cu e
; replace(l:list, e:atom)
; l - arborele unde inlocuim
; e - elementul cu care inlocuim
;
; model recursiv:
; replace-main = replace(l, e, 0)
(defun replace-main(l e)
    (replace l e 0)
)