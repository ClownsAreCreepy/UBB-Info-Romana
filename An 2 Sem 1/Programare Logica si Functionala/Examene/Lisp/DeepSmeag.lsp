;; Dandu-se o lista liniara, se cere sa se elimine elementele din N in N
;; ex: (elimin '(1 2 3 4 5 6 7 8 9 10) '2) -> (1 3 5)

;; Model matematic
;; elimin(list, n) = eliminAux(list, k, n)
;; n - din cat in cat stergem
;; k - elem curent din seria de n, stergem cand k = n
;; eliminAux(list, k, n) = { [], daca list = null
                        ;; { [list[1]] U eliminAx(list[2..], 1, n), daca list != null & k = n
                        ;; { eliminAux(list[2..], k+1,n), daca list!= null & k!=n (altfel)



(defun elimin (listy n)
    (eliminAux listy 1 n)
)
(defun eliminAux (listy k n)
    (cond
        ((null listy) nil)
        ((= k n) (eliminAux (cdr listy) 1 n))
        (t (append (list (car listy)) (eliminAux (cdr listy) (+ k 1) n)))
    )
)