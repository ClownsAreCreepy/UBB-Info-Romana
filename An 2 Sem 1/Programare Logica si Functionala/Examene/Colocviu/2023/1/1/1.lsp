(defun Fct (F L)
    (cond
        ((null L) nil)
        (t 
            ((lambda (rez)
                (cond
                    (rez (cons rez (Fct F (cdr L))))
                    (t nil)
                )
             ) (funcall F (car l))
            )
        )
    )
)