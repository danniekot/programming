n = int(input())
k = int(input())
mini = 1.1
mini = n + 1
cmax = 0
ink = 0
a = []
b = []
c = []
for i in range (k):
  a.append(input())
  b.append(int(input()))
  c.append(int(input()))
  if b[i]/c[i]<=mini and c[i] > cmax:
    mini=b[i]
    ink=1
if min == n + 1: print(-1)
else: print(a[ink],' ', n/b[ink], '\n', n/b[ink]*c[i], '\n', n-n/b[ink]*b[ink],'\n',sep='')