(defun f(l)
    (* (car l) (cadr l))
)

; (setq q 'f) -> initializeaza simbolul Q cu valoarea f
; (setq p q) -> initializeaza simbolul P cu valoarea simbolului Q, adica f
; (apply p '((2 3 4)))
; apply ia valoarea lui p, adica f, care are o definitie de functie, si o va aplica pe lista (2 3 4), adica e echivalent cu (f '(2 3 4)) -> 6