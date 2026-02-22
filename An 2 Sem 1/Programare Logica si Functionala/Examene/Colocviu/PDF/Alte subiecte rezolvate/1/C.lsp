;; Functia foloseste mapcar pentru a parcurge lista neliniara si inlocuieste nr pare cu urmatorul nr impar
;; inlocuire(L)
;; L - lista pe care o parcurgem
;;
;; model recursiv:
;; inlocuire(l1..ln) =
;;      1. nil, daca n = 0
;;      2. inlocuire(l1) (+) inlocuire(l2..ln), daca l1 e lista
;;      4. l1 + 1 (+) inlocuire(l2..ln), daca l1 e numar par
;;      5. l1 (+) inlocuire(l2..ln), altfel

(defun inlocuire (L)
    (mapcar #'(lambda (x)
                    (cond
                        ;; Case 1: E sublista, merem recursiv in jos
                        ((listp x) (inlocuire x))
                        
                        ;; Case 2: E numar par. Inlocuim cu x + 1
                        ((and (numberp x) (evenp x)) (+ x 1))
                        
                        ;; Case 3: Altfel
                        (T x)
                    )
              )
        L
    )
)