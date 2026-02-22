(defun nextPar(L)
    (mapcar '#(lambda (x)
                (cond
                    ((listp x) (nextPar x))
                    ((and (numberp x) (evenp x) (> x 0)) (+ x 1))
                    ((and (numberp x) (evenp x) (< x 0)) 0)
                    (t x)
                )
              ) L
    )
)