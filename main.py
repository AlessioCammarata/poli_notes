# Disegno del ponte tibetano

import matplotlib.pyplot as plt
from matplotlib import style
import numpy as np

L = 9
N = 1000
x = np.zeros(N)
y = np.zeros(N)
z = np.zeros(N)
a = 0.386

dx = L/(N-1)

x[0] = 0
y[0] = 0
z[0] = 0

for i in range(N-1):
    x[i+1] = x[i] + dx
    y[i+1] = y[i] + dx*z[i]
    z[i+1] = z[i] + dx*a*np.sqrt(1+z[i]*z[i])


# print(x)
# print(y)
# print(z)
# La soluzione della catena è y = 1/a * cosh ax
# y'  = sinh ax
# y'' = acosh ax
# y =  acosh ax


plt.style.use("classic")
plt.plot(x,y)
plt.plot(-x,y)

plt.plot(x,1/a*np.cosh(a*x)-1/a,color="red")
plt.show()