import matplotlib.pyplot as plt
import numpy as np
from matplotlib import cm
from matplotlib.colors import ListedColormap

def disk(R, espacement, taille):
    
    d= espacement
    
    red= [1, 0, 0, 1]
    green= [0, 1, 0, 1]
    blue= [0, 0, 1, 1]
     
    h=range(0, taille-1)
    w=range(0, taille-1)
    alpha= 30 *np.pi / 180
    
    #dabord largeur puis hauteur.. inversement à la matrice
    X,Y=np.meshgrid(h,w)
    
    cr= [taille/2-d*np.sin(alpha), taille/2 + d*np.cos(alpha)]    
    cg= [taille/2-d*np.sin(alpha), taille/2 - d*np.cos(alpha)]
    cb= [taille/2 + d, taille/2]

    print(cr)
    print(cg)

    Red= (X- cr[1])**2 + (Y- cr[0])**2 < R**2
    Green= (X- cg[1])**2 + (Y- cg[0])**2 < R**2
    Blue= (X- cb[1])**2 + (Y- cb[0])**2 < R**2
    
    I=np.stack((Red,Green,Blue), axis=2).astype('double')
    
    plt.figure()
    plt.imshow(I)
    plt.colorbar()
    
    
    
    
    
disk(40,30,201)