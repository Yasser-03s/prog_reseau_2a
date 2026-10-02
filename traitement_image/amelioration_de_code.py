import matplotlib.pyplot as plt
import numpy as np




#solution longue (7 lignes)
x = range(-34,35) #dernier element no pris
y = range(-32,33)
img1 = np.zeros((len(y), len(x)))
for i in range(0, len(y)):
    for j in range(0, len(x)):
        r = np.sqrt(x[j]**2+y[i]**2)
        img1[i,j] = 1000*np.sin(r/2)/r
plt.figure(1)
plt.imshow(img1)


#solution courte (3 lignes) 1000* plus puissant
X, Y = np.meshgrid(range(-34, 35), range(-32,33)) #stocker dans un matrice toutes les 
R = (X**2 + Y**2)**0.5; #operations directe sur les matrices
img2 = 1000*np.sin(R/2)/R;
plt.figure(2)
plt.imshow(img2)