import matplotlib.pyplot as plt
import numpy as np
import skimage.color
import skimage.transform

from matplotlib import cm
from matplotlib.colors import ListedColormap


img= plt.imread("./img(1)/pool.tif")



def resultat(r)  :
    ycbcr= skimage.color.rgb2ycbcr(img)
    h,w,channels = ycbcr.shape
    y= ycbcr[:,:, 0]
    cb= ycbcr[:,:, 1]
    cr= ycbcr[:,:, 2]
    
    #reduction puis retablition de la taille initiale de cb
    cb1= skimage.transform.resize(cb, (h*r, w*r))
    cb1_resize= skimage.transform.resize(cb1, (h, w),order=0)
    
    #reduction puis retablition de la taille initiale de cr
    cr1= skimage.transform.resize(cr, (h*r, w*r))
    cr1_resize= skimage.transform.resize(cr1, (h, w),order=0)
    
    #regroupement de l'image
    I= np.stack((y,cb1_resize,cr1_resize), axis=2).astype('double')
    ycbcr1= skimage.color.ycbcr2rgb(I)
    
    # plt.Figure()
    # plt.subplot(1,3,1)
    # plt.imshow(cb)
    # plt.subplot(1,3,2)
    # plt.imshow(cb1)
    # plt.subplot(1,3,3)
    # plt.imshow(cb1_resize)
    
    plt.figure()
    plt.title('le resultat pour r= '+ str(r))
    plt.imshow(ycbcr1)
    
    plt.show()
    
    
resultat(0.75)
resultat(0.5)
resultat(0.25)