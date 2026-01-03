#open file for write (overwrite if exists, create if not)
f = open("test.txt","w")
f.write("Test data\n")
f.close()


# open file for write (append if exist, create if not)
f = open("test.txt", "a")
f.write("Test data line 2\n")
f.close()


# open for read
f = open("test.txt", "r")
# read a line from the file
line = f.readline()
#Mine: print line
f.close()


# open for read
f = open("test.txt", "r")
# read a line from the file
line = f.readline().strip()
while line != "":
    #Mine: print line
    line = f.readline().strip()
f.close()


# open for read
f = open("test.txt", "r")
# read the entire content from the file
line = f.read()
#Mine: print line
f.close()
# use a for loop
f = open("etc/test.txt")
#Mine: for line in f:
    #Mine: print line
f.close()