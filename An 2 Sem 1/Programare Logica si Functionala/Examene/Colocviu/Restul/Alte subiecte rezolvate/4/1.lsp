(defun INC(X) (+ 1 X))

; (setq A 1) - A ia valoarea 1
; (inc A) - va returna valoarea 2
; Va returna valoarea 2 pentru ca (inc A) e echivalent cu (inc 1)
; Valoarea lui A nu se modifica insa. >A va returna 1, deoarece functiile 
;din lisp sunt pure, si nu modifica variabilele care se dau. Ele folosesc
;transmiterea prin valoare, adica, cand facem (inc A), lisp evalueaza argumentul
;A la 1, si atunci X primeste valoarea 1 si continua executia, iar cu A nu se mai
;intampla nimic
; Daca am vrea sa modificam A, ar trebui sa facem urmatoarea manevra:
; (setf A (inc A)), deoarece setf are efect destructiv asupra simbolurilor din lisp.