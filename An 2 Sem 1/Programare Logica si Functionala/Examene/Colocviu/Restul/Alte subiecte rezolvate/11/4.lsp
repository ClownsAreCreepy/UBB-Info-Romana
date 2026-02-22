; Functia verifica daca un atom e in lista
; is_in(l:list, e:atom)
; l - lista in care ne uitam
; e - atomul pe care il cautam
;
; model recursiv:
; is_in(l1..ln, e) = | false, daca n = 0
;                    | true, daca l1 = e
;                    | is_in(l2..ln, e), daca l1 e atom
;                    | is_in(l1, e) OR is_in(l2..ln, e), daca l1 e lista
(defun is_in(l e)
    (cond
        ((null l) nil)
        ((equal (car l) e) t)
        ((atom (car l)) (is_in (cdr l) e))
        (t (or (is_in (car l) e) (is_in (cdr l) e)))
    )
)


; Functia gaseste o cale de la radacina pana la un nod
; find-path(l:list, e:atom)
; l - arborele in care ne uitam
; e - nodul pe care il cautam
;
; model recursiv:
; find-path(l1..ln, e) = | (e), daca l1 = e
;                        | U(li), li = | li (+) find-path(li+1..ln, e)
;                                           , daca is_in(li+1..ln, e) = true
;                                      | [], altfel
(defun find-path(l e)
    (cond
        ((equal (car l) e) (list e))
        (t (mapcan #'(lambda (subtree)
                        (cond
                            ((is_in subtree e) (cons (car l) (find-path subtree e)))
                            (t nil)
                        )
                     )
                     (cdr l)
           )
        )
    )
)

; Functia gaseste o cale de la radacina pana la un nod
; path(l:list, e:atom)
; l - arborele in care ne uitam
; e - nodul pe care il cautam
;
; model recursiv:
; path(l1..ln, e) = | [], daca (l1) = find-path(l1..ln, e) si e != l1 (nu exista) 
;                   | find-path(l1..ln, e), altfel
(defun path(l e)
    ((lambda (rez)
        (cond
            ((and (not (equal e (car l))) (equal (list (car l)) rez))  nil)
            (t rez)
        )
     ) (find-path l e)
    )
)