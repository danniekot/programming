print('Введите целое число, затем начальную и конечную точку первого и второго диапазона')
s, l1, r1, l2, r2= map(int,input().split())
x1 = min(l1, r1)
if x1 + l2 == s:
  print(x1, l2)
elif x1 + r2 == s:
  print(x1, r2)
else:
  if x1 + l2 == s:
    print(x1, l2)
  elif x1 + r2 == s:
    print(x1, r2)
  else:
    print(-1)