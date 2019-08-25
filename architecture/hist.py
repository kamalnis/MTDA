f = open('output3.txt')
val=[0,0,0,0,0,0,0,0,0,0,0,0]
for line in iter(f):
    str=line.split(" ")
    val[int(str[0])]=val[int(str[0])]+1

for i in range(0,12):
	print val[i]
f.close()

