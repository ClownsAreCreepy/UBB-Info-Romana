(defun my-max (a b)
    (cond
        ((null a) b)
        ((null b) a)
        ((> a b) a)
        (t b)
    )
)

(defun find-max (x)
    (cond
        ((numberp x) x)
        ((atom x) nil)
        (t (my-max (find-max (car x)) (find-max (cdr x))))
    )
)

(defun count (L)
    (cond
        ((atom L) 0)
            (t
                (+
                    ;; 1. Calculam maximul listei curente
                    (let ((m (find-max L)))
                        (cond
                            ((and m (evenp m)) 1)
                            (t 0)
                        )
                    )
                    
                    ;; 2. Mapcar returneaza lista de scoruri
                    (apply #'+ (mapcar #'count L))
                )
            )
   )
)