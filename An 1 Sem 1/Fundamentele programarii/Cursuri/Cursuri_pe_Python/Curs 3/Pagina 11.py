#Unde incepem

def startUI():
    list = []
    print(list)
    # read user command
    menu = """ 
            Enter command: 
               1-add element 
               0-exit 
           """
    print(menu)
    cmd = input("")
    while cmd != 0:
        if cmd == 1:
            nr = input("Give element:")
            list.append(nr)
            print(list)
            list
        # read user command
        menu = """ 
            Enter command: 
               1-add element 
               0-exit 
           """
        print(menu)
        cmd = input("")
#Mine:startUI()



#Unde ajungem

def getUserCommand():
    """
     Print the application menu
     return the selected menu
    """
    menu = """ 
            Enter command: 
               1-add element 
               0-exit 
           """
    print(menu)
    cmd = input("")
    return cmd


def startUI():
    list = []
    print
    list
    cmd = getUserCommand()
    while cmd != 0:
        if cmd == 1:
            nr = input("Give element:")
            list.append(nr)
            print (list)
            list
        cmd = getUserCommand()
#Mine:startUI()