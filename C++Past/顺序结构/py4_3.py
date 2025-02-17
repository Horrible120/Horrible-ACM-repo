from math import sqrt
a=int(input("a="))
b=int(input("b="))
c=int(input("c="))
x1=(-b+sqrt(b**2-4*a*c))/2*a
x2=(-b-sqrt(b**2-4*a*c))/2*a
print("x1=",x1,"x2=",x2,)
