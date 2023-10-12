def fprimofx(x):
  return 2*x

def fofx(x):
  return x**2 -1

def newton(x):
  return x - fofx(x)/fprimofx(x)


x = -1.8 + 2j
for i in range(10):
  x = newton(x)
  print(x)