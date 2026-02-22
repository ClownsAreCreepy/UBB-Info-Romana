(defun inloc(L k nivel)
    (mapcar #'(lambda (x)
                   (cond
                        ((listp x) (inloc x k (+ nivel 1)))
                        ((= k nivel) 0)
                        (t x)
                   )
              ) L
    )
)

(defun inlocNivel(L k)
    (inloc L k 1)
)