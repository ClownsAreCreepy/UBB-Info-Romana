;; inordine(arbore: Lista neliniara de TElem)
;; arbore - arborele in tip 2 -> R (subarbore stang) (subarbore drept)
(defun inordine(arbore)
    (cond
        ((null arbore) nil)
        (T (append 
            (inordine (car (cdr arbore)))         ;; sau cadr
            (list (car arbore))
            (inordine (car (cdr (cdr arbore)))))) ;; sau caddr
    )
)