(defun g(l)
    (maplist #'list l)
)
    
; (apply #'append (mapcon #'g '(1 2)))
;        3.          2.       1.

; mapcon functioneaza ca si mapcan, dar in loc sa mearga pe fiecare element din lista,
; el merge pe lista fara primul element (cdr l) dupa ce verifica intreaga lista.

; 1. Deci mapcon #'list (1 2) = ((1 2) (2))
; 2. mapcon ((1 2) (2)) este ((1 2) (2) (2))
; 3. asa ca append ((1 2) (2) (2)) este (1 2 2 2)