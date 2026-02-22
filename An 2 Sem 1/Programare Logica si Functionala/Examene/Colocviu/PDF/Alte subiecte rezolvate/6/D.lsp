(defun my-max (a b)
    (cond
        ((> a b) a)
        (t b)
    )
)

(defun list-max (l)
    (cond
        ((null l) -1)
        ((null (cdr l)) (car l))
        (t (my-max (car l) (list-max (cdr l))))
    )
)


(defun tree-height (L)
    (cond
        ((null (cdr L)) 0)
        (t (+ 1 (list-max (mapcar #'tree-height (cdr L)))))
    )
)

(defun find-height (tree elem)
    (cond
        ((equal (car tree) elem) (tree-height tree))
        ((null (cdr tree)) -1)
        (t 
            (list-max (mapcar #'(lambda (sub-arbore)
                                            (find-height sub-arbore elem))
                                       (cdr tree)
                             )
            )
        )
    )
)