; Functia verifica daca o lista contine un numar
; exist-num(l:list)
; l - lista in care ne uitam
;
; model recursiv:
;   exist-num(l1..ln) = | false, daca n = 0
;                       | true, daca l1 e numar
;                       | exist-num(l2..ln), daca l1 atom
;                       | exist-num(l1) OR exist-num(l2..ln), daca l1 e lista
(defun exist-num(l)
    (cond
        ((null l) nil)
        ((numberp (car l)) t)
        ((atom (car l)) (exist-num (cdr l)))
        (t (or (exist-num (car l)) (exist-num (cdr l))))
    )
)
        
        
; Functia calculeaza suma numerelor de pe nivele impare
; sum (l:list, lvl:int)
; l - lista unde se calculeaza suma
; lvl - nivelul la care ne aflam
;
; model recursiv:
; sum(l, lvl) = | l, daca l e numar si lvl % 2 = 1
;                    | 0, daca l e atom
;                    | E(sum(li, lvl + 1)), i = 1..n, altfel
(defun sum(l lvl)
    (cond
        ((and (numberp l) (oddp lvl)) l)
        ((atom l) 0)
        (t (apply #'+ (mapcar #'(lambda (x)
                                    (sum x (+ 1 lvl))
                                ) l
                      )
           )
        )
    )
)


; Functia returneaza nr de subliste care au suma para de pe nivele impare
; sum-impar(l:list)
; l - lista unde calculam
;
; model recursiv:
; sum-impar(l) = | 0, daca l atom
;                | 1 + E(sum-impar(li)), daca exist-num l = true si sum(l, 0) % 2 = 0
;                | E(sum-impar(li)), altfel, i = 1..n
(defun sum-impar (l)
    (cond
        ((atom l) 0)
        (t (+
                (if (and (exist-num l) (evenp (sum l 0))) 1 0)
                
                (apply #'+ (mapcar #'sum-impar l))
            )
        )
    )
)