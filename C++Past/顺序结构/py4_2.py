from math import sqrt
a=int(input("a="))
b=int(input("b="))
c=int(input("c="))
p=(a+b+c)/2
s=sqrt(p*(p-a)*(p-b)*(p-c))
print("面积=",s)
