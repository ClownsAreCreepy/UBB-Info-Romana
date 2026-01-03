#Vers1
calc = reset()
add_to(calc, 1, 3)
print(get_total(calc))
undo(calc)
print(get_total(calc))
calc = reset ()
add_to(calc, 1, 3)
add_to(calc, 1, 3)
add_to(calc, 1, 3)
print(get_total(calc))


#Vers Bad
ca = [[0,1],[]]
ca[1].append(ca[0])
ca[0] = add(ca[0][0],ca[0][1],1,3)
print(ca[0])
ca[0] = ca[1].pop()
print(ca[0])
ca[1].clear()
ca[0] =[0,1]
ca[0] = add(ca[0][0],ca[0][1],1,3)
ca[0] = add(ca[0][0],ca[0][1],1,3)
ca[0] = add(ca[0][0],ca[0][1],1,3)
print(calc[0])