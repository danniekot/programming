print('Введите число.')
a = 1
b = 0
n = int(input())
for i in range(n):
if i + 1 == a:
  b += 1
  a *= 2
print('Степеней двойки: ', b)