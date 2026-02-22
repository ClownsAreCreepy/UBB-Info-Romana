; Functia returneaza ultimul numar dintr-o lista
; get-last(l:list)
; l - lista unde ne uitam
;
; model recursiv:
; get-last(l1..ln) =
;   1. l, daca l e numar
;   2. nil, daca l e atom
;   3. rez, daca rez != nil, unde rez = get-last(l2..ln)
;   4. get-last(car l), altfel
(defun get-last(l)
    (cond
        ((numberp l) l)
        ((atom l) nil)
        (t 
            ((lambda (x)
                (cond
                    (x x)
                    (t (get-last (car l)))
                )
             )
            (get-last (cdr l))
            )
        )
    )
)


; Functia numara cate subliste au  un numar impar ca ultimul numar
; nr_ultim(l:list)
; l - lista unde ne uitam
;
; model recursiv:
; nr_ultim(l1..n) =
;   1. 0, daca l e atom
;   2. 1 + E(nr_ultim(li)), i = 1..n, daca get-last (l1) este impar
;   3. 0 + E(nr_ultim(li)), i = 1..n, altfel
(defun nr_ultim(l)
    (cond
        ((atom l) 0)
        (t 
            ((lambda (last-num)
                (+
                    (cond
                        ((and last-num (oddp last-num)) 1)
                        (t 0)
                    )
                    (apply #'+ (mapcar #'nr_ultim l))
                )
            )
            (get-last l))
        )
    )
)