;problema 1 -> sa se determine adancimea unei liste

(defun maxim (lista m)
	(cond
		((null lista) m)
		((> m (car lista)) (maxim (cdr lista) m))
		(t (maxim (cdr lista) (car lista)))
	)
)

(defun maxim_main (lista)
	(maxim lista 0)
)

(defun adancime (lista nivel)
	(cond
		((atom lista) nivel)
		(t (maxim_main (mapcar #'(lambda(x)
									(adancime x (+ nivel 1))
								 )
								 lista
						)
		    )
		)
	)
)

(defun adancime_main (lista)
	(adancime lista 0)
)


;problema 2 -> lista tuturor atomilor care apar pe orice nivel, in aceeasi ordine

(defun atomi (lista)
	(cond
		((atom lista) (list lista))
		(t (mapcan #'atomi lista))
	)
)


;problema 3 -> sa se verifice daca un atom se afla intr-o lista (nu neaparat liniara)

(defun membru (lista elem)
	(cond 
		((and (atom lista) (equal lista elem)) 1)
		( (atom lista) 0)
		( t (apply #'+ (mapcar #'(lambda (x)
									(membru x elem)
								  )
								  lista
					    )
			)
		)
	)
)

(defun exista (lista elem)
	(cond
		( (> (membru lista elem) 0) t)
		(t nil)
	)
)


;problema 4 -> suma atomilor numerici de la orice nivel

(defun suma(elem)
	(cond
		((and (atom elem) (numberp elem)) elem)
		((atom elem) 0)
		(t (apply #'+ (mapcar #'suma elem)))
	 )
)


;problema 7 -> suma elementelor pare - suma elementelor impare

(defun suma_s(elem)
	(cond
		((and (atom elem) (numberp elem) (evenp elem)) elem)
		((and (atom elem) (numberp elem) (* -1 elem)))
		((atom elem) 0)
		(t (apply #'+ (mapcar #'suma_s elem)))
	)
)


;problema 8 -> maximul unei liste
(defun maxim_lista(elem)
	(cond
		((and (atom elem) (numberp elem)) elem)
		((atom elem) most-negative-fixnum)
		(t (maxim_main (mapcar #'maxim_lista elem)))
	)
)
		
		

;problema 9 -> sa se inlocuiasca un element cu o lista de elemente data

(defun substituie (lista elem aux)
	(cond
		((and (atom lista) (equal lista elem)) (copy-list aux))
		((atom lista) lista)
		(t (mapcar #'(lambda(x)
						(substituie x elem aux)
					)
					lista
			)
		)
	)
)


;problema 10 -> sa se determine nr de noduri de pe nivelul k al unui arbore

(defun noduri (lista k nivel)
	(cond
		((and (atom lista) (equal nivel k)) 1)
		((atom lista) 0)
		(t (apply #'+ (mapcar #'(lambda(x)
									(noduri x k (+ 1 nivel))
								)
								lista
						)
			)
		)
	)
)

(defun noduri_main (lista k)
	(noduri lista k 0)
)


;problema 11 -> sterge toate aparitiile unui atom din lista
(defun sterge (lista elem)
	(cond
		((and (atom lista) (equal lista elem)) nil)
		((atom lista) (list lista))
		(t (list(apply #'append (mapcar #'(lambda(x)
									(sterge x elem)
								)
								lista
						)
			))
		)
	)
)


;problema 12 -> un nod este inlocuit de alt nod intr-un arbore
(defun inlocuire (arbore nod1 nod2)
	(cond 
		((and (atom arbore) (equal arbore nod1)) nod2)
		((atom arbore) arbore)
		(t (mapcar #'(lambda(x)
						(inlocuire x nod1 nod2)
					 )
					 arbore
			)
		)
	)
)


;problema 13 -> cam aceeasi ca 12

;problema 14 -> ca problema 1

;problema 15 -> nr atomilor dintr-o lista, de la orice nivel
(defun nr_atomi (lista)
	(cond
		((atom lista) 1)
		(t (apply #'+ (mapcar #'nr_atomi lista)))
	)
)


;problema 16 -> inverseaza o lista, impreuna cu toate sublistele sale de pe orie nivel
(defun invers(lista)
	(cond
		((null lista) nil)
		(t (append (invers (cdr lista)) (list (car lista))))
	)
)

(defun inverseaza (lista)
	(cond
		((atom lista) lista)
		(t (mapcar #'inverseaza (invers lista)))
	)
)


; test
(defun inlocuiree (lista elem nivel)
	(cond 
		((and (atom lista) (evenp nivel)) lista)
		((atom lista) elem)
		(t (mapcar #'(lambda (x)
						(inlocuiree x elem (+ nivel 1))
					 )
					lista
			)
		)
	)
)

(defun inlocuiree_main ( lista elem)
	(inlocuiree lista elem -1)
)

;(inlocuiree_main '(a (b (g)) (c (d (e)) (f))) 'h)
						