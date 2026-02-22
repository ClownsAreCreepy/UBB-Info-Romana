(defun f(l)
    (cond
        ((null l) nil)
        ((listp (car l)) (append (f (car l)) (f (cdr l)) (car (f (car l)))))
        (t (list (car l)))
    )
)

; -> Folosim lambda

(defun f(l)
    (cond
        ((null l) nil)
        ((listp (car l))
            ((lambda (x)
                (append x (f (cdr l)) (car x))
             ) (f (car l))
            )
        )
        (t (list (car l)))
    )
)