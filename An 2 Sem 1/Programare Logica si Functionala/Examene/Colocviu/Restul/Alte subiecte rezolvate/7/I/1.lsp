(defun f(l1 l2)
    (append (f (car l1) l2)
        (cond
            ((null l1) (cdr l2))
            (t (list (f (car l1) l2) (car l2)))
        )
    )
)

; -> (Folosim lambda)

(defun f(l1 l2)
    ((lambda (r)
        (append r
            (cond
                ((null l1) (cdr l2))
                (t (list r (car l2)))
            )
        )
     ) (f (car l1) l2)
    )
)

; Asta e motamo dar e gresit -> va mere infinit pentru ca nu ajunge la cazul de baza
; Varianta corecta

(defun f(l1 l2)
    (cond
        ((null l1) (cdr l2))
        (t
            ((lambda (r)
                (append r (list r (car l2)))
             ) (f (car l1) l2)
            )
        )
    )
)