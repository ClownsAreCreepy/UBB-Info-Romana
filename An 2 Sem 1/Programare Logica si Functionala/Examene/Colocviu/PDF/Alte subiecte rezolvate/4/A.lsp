(defun f(l1 l2)
    (append (f (car l1) l2)
        (cond 
            ((null l1) (cdr l2))
            (t (list (f (car l1) l2) (car l2)))
        )
    )
)


(defun f(l1 l2)
    (let ((val (f (car l1) l2)))
        (append val
            (cond
                ((null l1) (cdr l2))
                (t (list val (car l2))
            )
        )
    )
)