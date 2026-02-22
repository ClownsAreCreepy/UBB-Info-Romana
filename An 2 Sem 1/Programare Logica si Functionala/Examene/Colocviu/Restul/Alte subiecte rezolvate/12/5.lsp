; Functia selecteaza toate numerele dintr-o lista
; get-nums(l:list)
; l - lista de unde selectam
;
; model recursiv:
; get-nums(l) = | (l), daca l e numar
;               | nil, daca l e atom
;               | U(get-nums(li)), unde i = 1..n, altfel
(defun get-nums (l)
    (cond
        ((numberp l) (list l))
        ((atom l) nil)
        (t (mapcan #'get-nums l))
    )
)

; Functia selecteaza ultimul atom dintr-o lista liniara
; last-el(l:list)
; l - lista de unde selectam
; 
; model recursiv:
; last-el(l1..ln) = | l1, daca n = 1
;                   | last-el(l2..ln), altfel 
(defun last-el (l)
    (cond
        ((null (cdr l)) (car l))
        (t (last-el (cdr l)))
    )
)

; Functia returneaza nr de subliste care au ca ultim numar unul impar
; nr-last-odd(l:list)
; l - lista unde ne uitam
;
; model recursiv:
; nr-last-odd(l) = | 0, daca l e atom
;                  | 1 + E(nr-last-odd(li)), daca nums nu e gol si last-el(nums) impar
;                                          , unde nums = get-nums(li)
;                  | E(nr-last-odd(li)), altfel

(defun nr-last-odd (l)
    (cond
        ((atom l) 0)
        (t 
            (+
                ((lambda (nums)
                    (if (and nums (oddp (last-el nums))) 1 0)
                 ) (get-nums l)
                )
                
                (apply #'+ (mapcar #'nr-last-odd l))
            )
        )
    )
)