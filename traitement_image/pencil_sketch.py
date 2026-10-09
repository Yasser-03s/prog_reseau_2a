#implementation de fct sketch a faire 


import matplotlib.pyplot as plt
import numpy as np
import skimage.color
import skimage.feature

img= plt.imread('./img(1)/home.jpg')
C= skimage.feature.canny(skimage.color.rgb2gray(img))
ycbcr= skimage.color.rgb2ycbcr(img)

def sketch(alpha,beta):
    newY= (255-alpha)*(1-C) + beta
    newycbcr= np.stack((newY,ycbcr[:,:, 1],ycbcr[:,:, 2]), axis= 2).astype('double')
    newimg= skimage.color.ycbcr2rgb(newycbcr)
    plt.figure()
    plt.imshow(newimg)
    plt.show()
    
    
    
    
sketch(20,50)