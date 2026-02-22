(defun f(l)
    (cond
        ((null l) 0)
        (t
            ((lambda (x)
                (cond
                    ((> x 2) (+ x (f (cdr l))))
                    (t x)
                )
             )
             (g l)
            )
        )
    )
)