b = 1
if b == 1:
  for j in range(100000000000000):
    print('Здравствуйте! Загадано число от 1 до 100. Угадайте его с пяти попыток.')
    a = random.randint(0, 100)
    k = 0
    for i in range(5):
      c = int(input())
      if c == a:
        print('Поздравляю! Вы угадали!\nХотите начать сначала? (1 - ДА)')
        k = 1
        b = int(input())
        break
      elif(c > a):
        print('Загаданное число меньше\n')
      elif(c < a):
        print('Загаданное число больше\n')
    if k == 0;
      print('Вы проиграли. Было загадано:', a,'\nХотите начать сначала? (1 - ДА)')
      b = int(input())
    if b == 0:
      break