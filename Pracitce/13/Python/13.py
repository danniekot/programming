print('Введите натуральное число.')
n = int(input())
b = 0
for i in range(2, n):
  if n % i == 0:
    b = 1
if n <= 1:
  print('Число', n, '- ни простое, ни составное')
elif b == 1:
  print('Число', n, '- составное')
else:
  print('Число', n, '- простое')