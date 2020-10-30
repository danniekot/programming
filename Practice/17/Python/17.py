yes = []
no = []
r,b = 0, 0
for i in range(37):
  no.append(1)
  yes.append(0)
while 1:
  n = int(input())
  if n < 0: break
  if n == 1 or n == 3 or n == 5 or n == 7 or n == 9 or n == 12 or n == 14 or n == 16 or n == 18 or n == 19 or n == 21 or n == 23 or n == 25 or n == 27 or n == 30 or n == 32 or n == 34 or n == 36:
    r+=1
  elif n!=0:
    b+=1
  yes[n]+=1
  no[n] = 0
  maxi = yes[0]
  for i in range (37):
    if yes[i] > maxi: maxi = yes[i]
  for i in range (37):
    if yes[i] == maxi: print(i, end = ' ')
  print('\n')
  for i in range (37):
    if no[i] == 1:
      print(i, end = ' ')
  print('\n', r,' ', b,'\n\n', sep='')
  no[n] = 0