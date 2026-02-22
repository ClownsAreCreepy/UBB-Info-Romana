(defun f(n)
    (cond
        ((= n 0) 0)
    
        (t 
            (let ((val (f (- n 1))))
                (cond
         
                    ((> val 1) (- n 2))
         
                    (t (+ val 1))
                )
            )
        )
    )
)

;; f(n) =
;;      1. 0, daca n = 0
;;      2. n - 2, daca f(n-1) > 1
;;      3. f(n-1) + 1, altfel