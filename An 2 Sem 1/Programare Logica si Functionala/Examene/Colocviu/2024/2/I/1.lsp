(defun h()
    (function (lambda (x) 
                 (append x (mapcar #'(lambda (l)
                                        (car l)
                                     ) x
                           )
                 )
               )
    )
)

; funcall (H) '((2 3) (4 5))
; h returneaza o functie, care este preluata de funcall si dat parametrii '((2 3) (4 5))
; deci x-ul nostru va fi ((2 3) (4 5))
; append x pe mapcar #' car x va insemna ca noi vom lua primele elemente din subliste si vom pune x in fata lor, adica va rezulta ((2 3 ) (4 5) 2 4).
; In mod surprinzator, totul este corect gramatical