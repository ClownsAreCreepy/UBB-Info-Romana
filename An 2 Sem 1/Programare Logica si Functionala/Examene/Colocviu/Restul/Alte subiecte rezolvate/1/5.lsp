(defun first-num(x)
    (cond
        ((numberp x) x)     ; Am gasit numar, il returnam
        ((atom x) nil)      ; Am dat de simbol, ignoram
        (t (or (first-num (car x)) ; Am dat de lista, cautam in stanga
               (first-num (cdr x)) ;si in dreapta
           )
        )
    )
)
    
(defun count-sublists(L)
    (cond
        ;; Daca L e atom, nu e sublista. Deci contributia e 0
        ((atom L) 0)
        ;; Calculam scorul curent + scorul copiilor
        (t
            (let (
                    ;; 1. Calculam scorul curent (1 sau 0)
                    (current-score
                        (cond
                            ;; Verificam: avem un numar SI e impar?
                            ((let ((n (first-num L))) (and (numberp n) (oddp n))) 1)
                            (t 0)
                        )
                    )
                    ;; Calculam scorul copiilor (recursivitate prin MAP)
                    ;; mapcar returneaza o lista de scoruri ex: (0 1 0 2)
                    ;; apply #'+ le aduna: 0 + 1 + 0 + 2 = 3
                    (children-sum (apply #'+ (mapcar #'count-sublists L)))
                 )
                 ;; Rezultat final: Scorul meu + scorul copiilor
                 (+ current-score children-sum)
            )
        )
    )
)