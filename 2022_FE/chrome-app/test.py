n = int(input("차량의 개수를 입력하시 오 (n): "))
listV = []
listW = []
sum = 0
for i in range(n):
  v, w = map(int, input().split())
  listV.append(v)
  listW.append(w)
  
n = len(listV)
for i in range(n-1, -1, -1):
    for j in range(0,i):
        if listV[j] == listV[j+1]:
            if listW[j] > listW[j+1]:
                sum += j+1
            elif listW[j] <= listW[j+1]:
                sum += (j+2)
            
print(sum)
