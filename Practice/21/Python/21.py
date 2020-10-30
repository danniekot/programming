def BMI(weight: float, height: float):
  return weight/(height*height/10000)
def printBMI(bmi: float):
  if BMI < 18.5 print('Underweight')
  elif BMI < 25 print('Normal')
  elif BMI < 30 print('Overweight')
  else print('Obesity')
w,h=map(float,input().split())
printBMI(BMI(w,h))