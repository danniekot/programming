print('Здравствуйте! Введите число.')
n = int(input())
a = 1
for i in range(n):
  a *= (i + 1)
print(n,'! = ', a, sep = '')