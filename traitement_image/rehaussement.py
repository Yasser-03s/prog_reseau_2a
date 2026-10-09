import matplotlib.pyplot as plt
import numpy as np
import scipy.signal


img1 = plt.imread('./img(1)/moon.png')
img2 = plt.imread('./img(1)/cat.jpg')


dI= np.array([[1,1,1],[1,-8,1],[1,1,1]])/2
beta= 15

dimg1= img1 - beta* scipy.signal.convolve2d(img1,dI,mode='same')
# dimg2= img2 - beta* scipy.signal.convolve2d(img2,dI,mode='same')



plt.subplot(1,2,1)
plt.imshow(img1, cmap= 'gray')

plt.subplot(1,2,2)
plt.imshow(dimg1, cmap= 'gray', vmin=0, vmax=1)


# plt.subplot(2,2,1)
# plt.imshow()

# plt.subplot(2,2,2)
# plt.imshow()