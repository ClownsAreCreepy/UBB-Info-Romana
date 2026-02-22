(defun G(l)
    (+ (car l) (cadr l))
)


; (setq H 'F) ; H devine nume pentru F
; (setq H 'G) ; H devine nume pentru G
;
; (F '(2 3 4 5 6)) ; Va da eroare 'Function F undefined', deoarece nu exista o functie de nume F

; Daca am vrea sa corectam cat de cat, trebuie sa ii spunem la Lisp sa se uite unde arata numele F cu Funcall

; (Funcall F '(2 3 4 5 6)) ; Dar tot va da eroare 'Function F has no value', pentru ca nu pointeaza la nimic. setq H 'F a facut H sa arate spre F, nu invers. Daca am vrea sa redenumim G ar trebui sa apelam H

; (Funcall H '(2 3 4 5 6)) ; Va returna 5. 