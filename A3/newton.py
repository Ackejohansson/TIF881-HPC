def fprimofx(x):
  return 2*x

def fofx(x):
  return x**2 - 1

def newton(x):
  return x - fofx(x)/fprimofx(x)



x = -1.005376 + 0.000068j
for i in range(1):
  x = newton(x)
  print(x)