(defun maxim-impare(l lvl)
    (cond
        ((numberp l) (if (oddp lvl) l most-negative-fixnum))
        ((atom l) most-negative-fixnum)
        (t (apply #'max (mapcar #'(lambda (a)
                                        (maxim-impare a (+ 1 lvl))
                                  ) l
                        )
           )
        )
    )
)

(defun nr-solutii(l)
    (cond
        ((atom l) 0)
        (t
            (+
                ((lambda (m)
                    (if (and (> m most-negative-fixnum) (evenp m)) 1 0)
                 ) (maxim-impare l 1))
                 
                (apply #'+ (mapcar #'nr-solutii l))
            )
        )   
    )             
)
