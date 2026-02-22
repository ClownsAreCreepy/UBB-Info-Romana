;; Functia determina calea de la radacina la un nod dat
;; path(L:list, nod:atom)
;; L - arborele in care cautam
;; nod - nodul pe care il cautam
;;
;; model recursiv:
;; path(l1..ln, nod) = 
;;      1. (x), daca l1 = x
;;      2. l1 U rez, daca rez != nil, 
;;                 , unde rez = U { cale(sub, x) | sub apartine {l2..ln} }
;;      3. nil, altfel
(defun path(L nod)
    (cond
        ((equal (car L) nod) (list nod))
        (t
            (let ((rezultat-copii (mapcan #'(lambda(sub) (path sub nod)) (cdr L))))
                (cond
                    (rezultat-copii (cons (car L) rezultat-copii))
                    (t nil)
                )
            )
        )
    )
)
        