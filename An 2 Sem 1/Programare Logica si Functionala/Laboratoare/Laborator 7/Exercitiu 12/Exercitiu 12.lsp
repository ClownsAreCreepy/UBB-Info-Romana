;; Functia inlocuieste un nod cu altul intr-un arbore
;; inloc(l:list, nu_vrem:atom, vrem:atom)
;; l - arborele reprezentat (rad sub1 sub2)
;; nu_vrem - nodul pe care il inlocuim
;; vrem - nodul cu care inlocuim
;;
;; model recursiv
;; inloc(l1..ln, nu_vrem, vrem) = f(l1) U inloc(l2..ln, nu_vrem, vrem)
;;          ,unde f(x) functioneaza astfel:
;;          f(x) = 
;;              1. inloc(x), daca x e lista
;;              2. vrem, daca l1 = nu_vrem
;;              3. l1, altfel

(defun inloc(l nu_vrem vrem)
    (mapcar #'(lambda(x) 
                    (cond
                        ((listp x) (inloc x nu_vrem vrem))
                        ((equal x nu_vrem) vrem)
                        (t x)
                    )
               ) l
    )
)