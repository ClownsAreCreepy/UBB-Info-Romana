;; Parcurge arborele si inlocuieste nodurile de pe nivele impare cu variabila e
;; inlocuire(L:atom*, e:atom, nivel:integer)
;; L - arborele pe care il parcurgem
;; e - elementul cu care inlocuim
;; nivel - nivelul la care ne alfam
;;
;; model recursiv:
;; inlocuire(l1..ln, e, nivel) =
;;      1. [], daca n = 0
;;      2. inlocuire(l1, e, nivel + 1) (+) inlocuire(l2..ln, e, nivel), daca l1 e lista
;;      3. e (+) inlocuire(l2..ln, e, nivel), daca nivel % 2 = 1
;;      4. l1 (+) inlocuire(l2..ln, e, nivel), altfel
(defun inlocuire (L e nivel)
    (mapcar #'(lambda (x)
                   (cond
                        ((listp x) (inlocuire x e (+ 1 nivel)))
                        
                        ((oddp nivel) e)
                        
                        (t x)
                    )
              ) L
    )
)


;; Functie wrapper ca sa instantiem nivelul cu 0 - bad UX daca ar trebui user-ul sa faca asta
;; inlocuire-main(arbore:atom*, e:atom)
;; arbore - arborele pe care il parcurgem
;; e - elementul cu care inlocuim
;;
;; model recursiv:
;; inlocuire-main(arbore, e) = inlocuire(arbore, e, 0)
(defun inlocuire-main (arbore e)
    (inlocuire arbore e 0)
)