print('Введите основание и показатель степени.')
a = int(input())
b = int(input())
s = a
for i in range(b - 1):
  s *= a
print(a, 'в степени', b, 'даёт', s)