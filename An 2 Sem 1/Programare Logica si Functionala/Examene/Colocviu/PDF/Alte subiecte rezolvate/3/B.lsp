(defun sum-cif(n)
    (cond
        ((= 0 n) 0)
        (t (+ (mod n 10) (sum-cif (floor n 10))))
    )
)

(defun inloc-aux(L nivel)
    (mapcar #'(lambda (x)
                (cond
                    ((listp x) (inloc-aux x (+ nivel 1)))
                    ((and (numberp x) (evenp x) (oddp nivel)) (sum-cif x))
                    (t x)
                )
              ) L
              
    )
)

(defun inloc(L)
    (inloc-aux L 1)
)