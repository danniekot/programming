print('Введите два числа')
a,b=map(int,input().split())
temp = a
a = b
b = temp
print('После замены первое число равно ', a ,', а второе ', b, sep='')
print('Введите два числа')
a,b=map(int,input().split())
b += a
a = b - a
b -= a
print('После замены первое число равно ', a ,', а второе ', b, sep='')