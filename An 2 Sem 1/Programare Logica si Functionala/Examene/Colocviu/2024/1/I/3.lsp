(defun g(l)
    (list (car l) (caddr l))
)

; (setq q 'g) -> initializeaza simbolul q cu valoarea g
; (setq p 'q) -> initializeaza simbolul p cu valoarea q
; (apply (eval p) (list '(a b c)))
;    3.     1.             2.
; 1. (Eval p) se evalueaza la Q in momentul asta
; 2. list '(a b c) va fi ((a b c))
; 3. (apply q ((a b c))) va folosi definitia valorii lui q (ca si funcall), adica g,
; si va risipi primul strat de functie si va fi echivalent cu (g '(1 2 3)), care este (a c)