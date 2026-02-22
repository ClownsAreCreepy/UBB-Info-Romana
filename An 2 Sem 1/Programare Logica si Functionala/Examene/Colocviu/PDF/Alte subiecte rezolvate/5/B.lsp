;; Calculeaza cel mai mare divizor comun a 2 numere
;; my-gcd(a:integer, b:integer)
;; a, b - numerele la care calculam cmmdc
;;
;; model recursiv:
;; my-gcd(a, b) = 
;;      1. a, daca b = 0 
;;      2. my-gcd(b, a%b), altfel
(defun my-gcd(a b)
    (cond
        ((equal b 0) a)
        (t (my-gcd b (mod a b)))
    )
)


;; Calculeaza lcm pe o lista intreaga
;; list-lcm(l: list)
;; l - lista pe care calculam cmmdc al elementelor ei
;;
;; model recursiv:
;; list-lcm(l1..ln) = 
;;      1. l1, daca n = 1
;;      2. my-gcd(l1, list-gcd(l2..ln))
(defun list-gcd(l)
    (cond
        ((null (cdr l)) (car l))
        (t (my-gcd (car l) (list-gcd (cdr l))))
    )
)


;; Eliminam nivelele non-superficiale din lista
;; flatten(l: lista)
;; l - lista unde eliminam nivelele superficiale
;;
;; model recursiv:
;; flatten(l1..ln) =
;;      1. nil, daca n = 0
;;      2. (l1), daca l1 e atom
;;      3. flatten(l1) U (flatten(l2..ln), altfel
(defun flatten(l)
    (cond
        ((null l) nil)
        ((atom l) (list l))
        (t (append (flatten (car l)) (flatten (cdr l))))
    )
)


;; Gasim numerele intre doi atomi nenumerici
;; filter-nums(l:list, prev:atom)
;; l - lista in care cautam
;; prev - elementul inaintea celui actual
;;
;; model recursiv:
;; 
(defun filter-nums (l prev)
    (cond
        ((null (cdr l)) nil)
        (t
            (let (
                    (curent (car l)) 
                    (next (cadr l))
                 )
                 (cond
                    ((and 
                          (numberp curent) 
                          prev (not (numberp prev)) 
                          next (not (numberp next))
                     )
                     (cons curent (filter-nums (cdr l) curent))
                    )
                    (t (filter-nums (cdr l) curent))
                 )
            )
        )
    )
)


;; Functia principala
;; solve (l:list)
;; l - lista unde calculam
;;
;; model recursiv e ca la functie
(defun solve (l)
    (let* (
            (FlatList (flatten l))
            (ValidNums (filter-nums FlatList nil))
         )
         (list-gcd ValidNums)
    )
)
    