def compute(a,b):
    print ("compute :start ")
    aux = a/b
    print ("compute:after division")
    rez = aux*10
    print ("compute: return")
    return rez

def main():
    print ("main:start")
    a = 40
    b = 1
    c = compute(a, b)
    print ("main:after compute")
    print ("result:",c*c)
    print ("main:finish")

main()