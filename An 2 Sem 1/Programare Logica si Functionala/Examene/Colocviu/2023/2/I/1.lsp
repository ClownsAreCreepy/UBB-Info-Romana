(defun f(l)
    (cond
        ((null l) 0)
        ((> (f (car l)) 2) (+ (car l) (f (cdr l))))
        (t (f (car l)))
    )
)

; -> Folosim lambda
(defun f(l)
    (cond
        ((null l) 0)
        (t
            ((lambda (x)
                (cond
                    ((> x 2) + (car l) (f (cdr l)))
                    (t x)
                )
             ) (f (car l))
            )
        )
    )
)