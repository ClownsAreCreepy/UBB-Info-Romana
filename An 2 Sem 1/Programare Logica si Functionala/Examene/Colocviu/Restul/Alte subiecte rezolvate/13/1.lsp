(defun g(l)
    (* (car l) (cadr l))
)

; SETQ CAR 'G
; Prin acest setq, am setat valoarea simbolului car la simbolului g.
; Daca vrem sa facem (car '(2 3 5 6)) vom obtine 2, deoarece functia globala car exista si va fi efectuata
; Pentru o redenumire cumsecade, trebuie sa folosim (funcall car '(2 3 5 6)). Acum lisp evalueaza valoarea simbolului car, care rezulta in g, si se va efectua (g '(2 3 5 6), care va rezulta in 6