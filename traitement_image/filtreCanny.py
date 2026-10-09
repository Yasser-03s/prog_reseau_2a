
import matplotlib.pyplot as plt
import numpy as np
import scipy.signal


img= plt.imread('./img(1)/cameraman.tif')

P = range(-10,10+1)
X, Y = np.meshgrid(P,P)

sig = 1
Gx = -X/(2*np.pi*sig**4)*np.exp(-(X**2+Y**2)/(2*sig**2))
Gy = -Y/(2*np.pi*sig**4)*np.exp(-(X**2+Y**2)/(2*sig**2))


img_x= scipy.signal.convolve2d(img, Gx, mode='same')
img_y= scipy.signal.convolve2d(img, Gy, mode='same')


norme= np.sqrt(img_x ** 2 + img_y**2)
#normaliser entre 0 et 1
norme/= np.max(norme)

plt.subplot(1,2,1)
plt.imshow(img_x)
plt.subplot(1,2,2)
plt.imshow(img_y)


plt.figure()
plt.imshow(norme)
plt.show()


