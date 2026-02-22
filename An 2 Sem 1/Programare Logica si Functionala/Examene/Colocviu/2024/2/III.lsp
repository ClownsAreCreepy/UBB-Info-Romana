; Functia returneaza toate nodurile de pe un anumit nivel
; lista-impar(l:list, k:int)
; l - arborele in care ne uitam
; k - nivelul de la care scoatem
;
; model recursiv:
; lista-impar(l, k) = | (l), daca l e atom si k = -1
;                     | [], daca l e atom
;                     | U(lista-impar(li, k - 1)), i = 1..n, altfel
(defun lista-impar (l k)
    (cond
        ((and (atom l) (equal k -1)) (list l))
        ((atom l) nil)
        (t (mapcan #'(lambda (x)
                        (lista-impar x (- k 1))
                     ) l
           )
        )
    )
)