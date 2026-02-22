(defun inloc(L e k)
    (mapcar #'(lambda (x)
                (cond 
                    ((listp x) (inloc x e (- k 1)))
                    ((= k 0) e)
                    (t x)
                )
               ) L
    )
)