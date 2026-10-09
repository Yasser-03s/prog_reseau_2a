#Filtrage moyenneur (linéaire)

import matplotlib.pyplot as plt
import numpy as np
import scipy.signal
import scipy.ndimage


img= plt.imread('./img(1)/barbara_awgn_noise.png')
img1= plt.imread('./img(1)/cameraman_sp_noise.png')

plt.subplot(1,3,1)
plt.imshow(img1, cmap= 'gray')



#filtre carré
l=5

H= np.array([[1,1,1],[1,1,1],[1,1,1]])
H=np.ones((l,l))/(l*l)

img_H= scipy.signal.convolve2d(img1,H, mode='same')



plt.subplot(1,3,2)
plt.imshow(img_H, cmap= 'gray')




#filtre gaussien

sigma=0.4

X,Y = np.meshgrid(range(-3,4), range(-3,4))
#pour centrer la gaussienne: range(-n, n+1) (pythong range +1)
G= 1/(2*np.pi*sigma*sigma) *np.exp(-(((X**2)/2*sigma**2)+((Y**2)/2*sigma**2)))


img_G= scipy.signal.convolve2d(img1,G, mode='same')


plt.subplot(1,3,3)
plt.imshow(img_G, cmap= 'gray')
plt.show()


#filtre median
img_med= np.zeros(img1.shape)
v=1
h,w = img1.shape
#Parcourir tous les pixels de l’image
for i in range(v, h-v):
    for j in range(v, w-v):
        #Déterminer un voisinage 2D (de taille (2v+1)*(2v+1))
        win= img1[i-v: i+v+1, j-v:j+v+1]
        #Calculer la médiane sur l’ensemble des pixels (np.median)
        img_med[i,j] = np.median(win)

plt.figure()
plt.imshow(img_med, cmap= 'gray')
plt.show()

