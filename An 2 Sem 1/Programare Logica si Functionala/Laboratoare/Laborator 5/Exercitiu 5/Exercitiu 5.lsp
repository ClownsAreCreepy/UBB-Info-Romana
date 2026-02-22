;; a)
;; interclasare(l1: Lista de Intreg, l2: Lista de Intreg)
;; model de flux: interclasare(i, i)
;; l1 - Prima lista pe care o interclasam
;; l2 - A doua lista pe care o interclasam
(defun interclasare(l1 l2)
    (cond
        ((null l1) l2)
        
        ((null l2) l1)
        
        ((<= (car l1) (car l2)) (cons (car l1) (interclasare (cdr l1) l2)))
        
        (T (cons (car l2) (interclasare l1 (cdr l2))))
    )
)


;; b)
;; substituie(L: Lista de Atomi, E: Atom, L1: Lista de Atomi)
;; model de flux: substituie(i, i, i)
;; L - Lista in care substituim
;; E - Elementul pe care il substituim
;; L1 - Lista de atomi cu care substituim elementul
(defun substituie(L E L1)
    (cond
        ((null L) nil)
        
        ((listp (car L)) (cons (substituie (car L) E L1) (substituie (cdr L) E L1)))
        
        ((equal (car L) E) (append L1 (substituie (cdr L) E L1)))
        
        (T (cons (car L) (substituie (cdr L) E L1 )))
    )
)


;; c)
;; list-to-number(L: Lista de Intreg, S: Intreg)
;; model de flux: list-to-number(i, i)
;; L - lista pe care o transformam in numar
;; S - inceputul numarului
(defun list-to-number (L S)
    (cond
        ((null L) S)
        
        (T (list-to-number (cdr L) (+ (car L) (* S 10))))
    )
)

;; list_sum(L1: Lista de Intreg, L2: Lista de Intreg, C: Intreg)
;; model de flux: list_sum(i, i, i)
;; L1 - Prima lista din suma. TREBUIE INVERSATA INAINTE
;; L2 - A doua lista din suma. TREBUIE INVERSATA INAINTE
;; C - Imprumutul de la suma
(defun list_sum (L1 L2 C)
    (cond
        ((and (null L1) (null L2) (= C 0)) nil)
        
        ((and (null L1) (null L2)) (list C))
        
        (T (cons 
                (mod (+ (if (null L1) 0 (car L1)) (if (null L2) 0 (car L2)) C) 10)
                (list_sum (cdr L1) (cdr L2) (floor (+ (if (null L1) 0 (car L1)) (if (null L2) 0 (car L2)) C) 10))))
    )
)

;; rev(L: Lista de Intreg)
;; model de flux: rev(i)
;; L - lista pe care o inversam
(defun rev(L)
    (cond
        ((null L) nil)
        
        (T (append (rev (cdr L)) (list (car L))))
    )
)
 
;; sum(L1: Lista de Intreg, L2: Lista de Intreg)
;; model de flux: sum(i, i)
;; L1 - Prima lista din suma
;; L2 - A doua lista din suma
(defun sum_main(L1 L2)
    (list-to-number (rev (list_sum (rev L1) (rev L2) 0)) 0)
)


;; d)
;; cmmdc(A: Intreg, B: Intreg)
;; model de flux: cmmdc(i, i)
;; A - Primul numar si rezultatul 
;; B - Al doilea numar
(defun cmmdc(A B)
    (cond
        ((= B 0) A)
        (T (cmmdc B (mod A B)))
    )
)

;; div_list(L: Lista de Intreg, D: Intreg)
;; model de flux: div_list(i, i)
;; L - Lista unde facem cmmdc
;; D - Cel mai mare divizor comun al numerelor
(defun div_list(L D)
    (cond
        ((null L) D)
        (T (div_list (cdr L) (cmmdc D (car L))))
    )
)

;; cmmdc_list(L: Lista de Intreg)
;; model de flux: cmmdc_list(i, i)
;; L _ Lista unde facem cmmdc
(defun cmmdc_list(L)
    (div_list L 0)
)