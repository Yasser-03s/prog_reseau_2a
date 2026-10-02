import matplotlib.pyplot as plt
import numpy as np
from matplotlib import cm
from matplotlib.colors import ListedColormap
map= cm.jet(range(256))


#img= plt.imread('./img(1)/cameraman.tif')


Mandrill= np.load('./img(1)/challengeA.npy')
#taille 512x512x3 donc 3 canaux
# fixMandrill= Mandrill.astype(np.uint8)

Radio= np.load('./img(1)/challengeB.npy')
Worldmap= np.load('./img(1)/challengeC.npy')

# plt.figure(1)
# plt.imshow(Mandrill/255)


#plt.imshow(img)
# plt.imshow(img, cmap= "gray")
# plt.figure(2)
# plt.imshow(img/5, cmap= "gray")
# plt.figure(3)
# plt.imshow(img,cmap="gray", vmin=0, vmax=1)


# plt.figure()
# plt.imshow(Radio, vmin= 100,vmax= 120, cmap='viridis')


map= map[::int(256/6),:]
map[2,:]= [1,0,1,1] 

#ou bien coder hard a la main map = [[,,],[,,]]

plt.figure()
plt.imshow(Worldmap, ListedColormap(map))
plt.colorbar()

plt.show()