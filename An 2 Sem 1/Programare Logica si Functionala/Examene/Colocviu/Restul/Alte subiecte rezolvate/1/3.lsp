(defun f(l)
    (cond
        ((null l) 0)
        
        (t 
            (let ((val (f (car l))))
                (cond
                    ((> val 2) (+ (car l) (f (cdr l))))
                    (t val)
                )
            )
        )
    )
)