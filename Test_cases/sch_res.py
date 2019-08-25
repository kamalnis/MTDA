target = open("./result2.txt")
a=0
b=0
c=0
d=0
e=0
for lines in target
    arr=lines.split(" ")
    a=a+arr[0]
    b=b+arr[1]
    c=c+arr[2]
    d=d+arr[3]
    e=e+arr[4]

print "%d %d %d %d %d" %(a,b,c,d,e)


