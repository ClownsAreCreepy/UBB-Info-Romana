(defun cale (L nod)
    (cond
        ;; Caz baza: Radacina e nodul cautat -> Returnam lista cu nodul
        ((equal (car L) nod) (list nod))
        
        ;; Cautam
        (t
            ;; Mapcan aplica functia pe fiecare subarbore si lipeste rezultatele
            ;; Deoarece calea e unica, doar unul va returna o lista, restul NIL
            (let ((cale-copil (mapcan #'(lambda (sub) (cale sub nod)) (cdr arbore))))
                (cond
                    ;; Daca am primit ceva de la copii, lipim radacina curenta
                    (cale-copil (cons (car arbore) cale-copil))
                    
                    ;; Altfel, returnam nil
                    (t nil)
                )
            )
        )
    )
)