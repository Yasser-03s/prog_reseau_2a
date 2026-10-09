
import matplotlib.pyplot as plt
import numpy as np
import scipy.signal


img= plt.imread('./img(1)/cameraman.tif')



Sx= np.array([[1,0,-1],[2,0,-2],[1,0,-1]])/8
Sy= Sx.T

imgx= scipy.signal.convolve2d(img,Sx, mode='same')
imgy= scipy.signal.convolve2d(img,Sy, mode='same')

plt.subplot(1,2,1)
plt.imshow(imgx)
plt.title('derivee x')

plt.subplot(1,2,2)
plt.imshow(imgy)
plt.title('derivee y')



norme= np.sqrt(imgx**2 + imgy**2)
#normaliser entre 0 et 1
norme /= np.max(norme)

plt.figure()
plt.imshow(norme)
plt.show()
 #seuillage ..
seuil= norme>0.25
plt.figure()
plt.imshow(seuil)
plt.show()