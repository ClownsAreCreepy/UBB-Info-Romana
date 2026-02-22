Am rezolvat doar exercitiile care contau pentru examenu care il dau eu (in mare parte), adica prolog backtracking, lisp map functions si exercitiile cu intelegere de cod

Pe masura ce fac mai multe subiecte devin mai corecte rezolvarile, sa nu va bazati prea mult pe alea de inceput ca nu mai stiu ce minuni am scris pe acolo



ALSO, mi-am dat seama in noaptea fix inainte de examen, eu foloseam functia max de la lisp in problemele in care trebuia max-ul si nu e bine. Imaginati-va ca folosesc functia asta:

; Functia calculeaza maximul unei liste

; max-aux(l:list, m:int)

; l - lista unde ne uitam

; m - maximul curent

;

; model recursiv:

; max-aux(l1..ln, m) = | m, daca n = 0

;                      | max-aux(l2..ln, m), daca m > l1

;                      | max-aux(l2..ln, l1), altfel

(defun max-aux (l m)

&nbsp;   (cond

&nbsp;       ((null l) m)

&nbsp;       ((> m (car l)) (max-aux (cdr l) m))

&nbsp;       (t (max-aux (cdr l) (car l)))

&nbsp;   )

)



; Functia calculeaza maximul unei liste

; max(l:list)

; l - lista unde ne uitam

;

; model recursiv:

; max(l) = max-aux(l, -infinit)

(defun max (l)

&nbsp;   (max-aux l most-negative-fixnum)

