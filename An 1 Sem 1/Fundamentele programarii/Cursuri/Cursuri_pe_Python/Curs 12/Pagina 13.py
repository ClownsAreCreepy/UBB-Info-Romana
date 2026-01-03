def generate(x,DIM):
    if len(x)==DIM:
        print(x)
    return
    x.append(0)
    for i in range(0,DIM):
        x[-1] = i
        generate(x,DIM) 
    x.pop()

generate([],3)