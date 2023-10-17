def fprimofx(x, d):
  fprimofx = d*(x**(d-1))
  print(fprimofx)
  return fprimofx

def fofx(x, d):
  fofx = x**d - 1
  print(fofx)
  return fofx

def newton(x, d):
  minus = fofx(x, d)/fprimofx(x, d)
  next = x - minus
  return next

def newton2(x, d):
  # minus = fofx(x, d)/fprimofx(x, d)
  # print(minus)
  discrim = 1/(d*x**(d-1))
  print(discrim)
  xoldtimesthing = x*(1-1/d)
  print(xoldtimesthing)
  next = xoldtimesthing + discrim
  return next




x_new = 1.138353 + -3.349038j
# Cabs fofx = 552.745533
# Discrim = 0.001643 + -0.006173i
# x_old *(1-1/b) = 1.138353 + -3.349038i
# x_new = 1.139996 + -3.355211i

for i in range(1):
  x = newton(x_new, d=5)
  print(x)
  x = newton2(x, d=5)
  print(x)

#Correct (0.9123237036461649-2.6853943492345627j)