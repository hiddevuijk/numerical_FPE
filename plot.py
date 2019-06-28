import numpy as np
import matplotlib.pyplot as plt

rho = np.loadtxt("rho.dat")

plt.imshow(rho, interpolation="none")
plt.show()


