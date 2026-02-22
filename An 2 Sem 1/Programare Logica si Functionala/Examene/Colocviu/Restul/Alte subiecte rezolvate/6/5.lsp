; Functia verifica daca exista un numar in lista
; exist-num(l:list)
; l - lista in care ne uitam
;
; model recursiv:
; exist-num(l1..ln) = 
;   1. false, daca n = 0
;   2. true, daca l1 e numar
;   3. exist-num(l2..ln), daca l1 e atom
;   4. exist-num(l1) sau exist-num (l2..ln), daca l1 lista
(defun exist-num(l)
    (cond
        ((null l) nil)
        ((numberp (car l)) t)
        ((atom (car l)) (exist-num (cdr l)))
        (t (or (exist-num (car l)) (exist-num (cdr l))))
    )
)


; Functia calculeaza suma numerelor de pe nivele impare
; sum(l:list, lvl:nivel)
; l - lista in care ne uitam
; lvl - nivelul la care suntem
;
; model recursiv:
; sum(l, lvl) = 
;   1. l, daca l e numar si lvl e impar
;   2. 0, daca l e atom
;   3. E(sum(li, lvl + 1)), i = 1..k, daca l = (l1..lk) este lista
(defun sum(l lvl)
    (cond
        ((and (numberp l) (oddp lvl)) l)
        ((atom l) 0)
        (t (apply #'+(mapcar #'(lambda (x)
                                    (sum x (+ lvl 1))
                                ) l
                      )
           )
        )
    )
)


; Functia returneaza numarul de subliste dupa cerinta
; sum-list(l:list)
; l - lista in care ne uitam
;
; model recursiv:
; sum-list(l1..ln) = 
;   1. 0, daca l e atom
;   2. 1 + E(sum-list(li)), i = 1..n, daca exist-num(l) = true
;                                          si sum(l, 0) e par
;   3. E(sum-list(li)), i = 1..n, altfel
(defun sum-list(l)
    (cond
        ((atom l) 0)
        (t
            (+
                (if (and (exist-num l) (evenp (sum l 0))) 1 0)  
                
                (apply #'+ (mapcar #'sum-list l))
            )
        )
    )
)