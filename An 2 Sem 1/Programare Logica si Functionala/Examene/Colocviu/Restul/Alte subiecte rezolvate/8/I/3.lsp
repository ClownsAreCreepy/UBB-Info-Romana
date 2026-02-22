(defun g(l)
    (list (car l) (car l))
)

; (SETQ Q 'G), initializeaza Q la simbolul G
; (SETQ P Q), se evalueaza Q (rezultand G), iar variabila p este initializata la acest rezultat
; (Funcall P '(A B C)), funcall isi evalueaza primul argument (P), si returneaza valoarea G, iar deoarece functia G are o definitie de functie globala, funcall executa functia G pe lista (A B C), si va rezulta (A A)