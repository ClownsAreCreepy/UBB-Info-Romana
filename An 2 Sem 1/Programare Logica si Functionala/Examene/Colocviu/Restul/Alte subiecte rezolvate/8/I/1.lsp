(defun Fct(f l)
    (cond
        ((null l) nil)
        ((funcall f (car l)) (cons (funcall f (car l)) (Fct f (cdr l))))
        (t nil)
    )
)

; -> Folosim lambda

(defun Fct (f l)
    (cond
        ((null l) nil)
        (t
            ((lambda (x)
                (cond
                    (x (cons x (Fct F (cdr l))))
                    (t nil)
                ) 
             )(funcall f (car l))
            )
        )
    )
)