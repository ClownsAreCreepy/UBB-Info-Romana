(defun g(l)
    (+ (car l) (cadr l))
)

; SET H 'F
; SET H 'G
; in stadiul cum e, set H va da eroare, deoarece set va incerca sa evalueze H, care nu are nicio valoare. Putem face ori SET 'H 'F or SETQ H 'F. La fel si pentru SET H 'G.

; cand vom incerca ca apelam F '(2 3 4 5 6), va da eroare, deoarece f nu contine o definitie de functie. Pentru a contine o definitie de functie, ar trebui sa facem invers. Setq H 'G -> Setq F H. Astfel, ii dam lui f valoarea din h, care este g. 

; totusi, cand apelam f '(2 3 4 5 6), ne va spune ca nu exista o astfel de functie. Noi trebuie sa ne uitam la valoarea lui f si sa apelam valoarea lui f, care este g. Pentru asta vom folosi Funcall.

; deci pentru a redenumi cu succes, va trebui sa facem:
; SETQ H 'G
; SETQ F H
; (Funcall f '(2 3 4 5 6)), si in urma acestui apel va rezulta (g '(2 3 4 5 6)) -> 5