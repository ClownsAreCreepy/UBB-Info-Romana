; Functie care calculeaza adancimea unei functii
; tree-height(l:list)
; l - lista unde calculam
; 
; model recursiv:
; tree-height(l) = | 0, daca l e atom
;                  | 1 + max(tree-height(li)), unde i = 1..n, altfel
(defun tree-height (l)
    (cond
        ((atom l) 0)
        (t (+ 1 (apply #'max (mapcar #'tree-height l))))
    )
)

; Functie care calculeaza nr de subliste care au un nr par de nivele
; even-lvls(l:list)
; l - lista unde calculam
;
; model recursiv:
; even-lvls(l) = | 0, daca l e atom
;                | 1 + E(even-lvls(li)), daca tree-height(li) e par
;                | E(even-lvls(li)), altfel, i = 1..n
(defun even-lvls (l)
    (cond
        ((atom l) 0)
        (t
            (+
                (if (evenp (tree-height l)) 1 0)
                
                (apply #'+ (mapcar #'even-lvls l))
            )
        )
    )
)