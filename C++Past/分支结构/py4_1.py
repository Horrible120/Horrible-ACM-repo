a=int(input("请输入"))
if a//100==0:
    print("输入错误")
else:
    b=str(a%10*100)+str(a%100//10*10)+str(a//100)
    print(b)
