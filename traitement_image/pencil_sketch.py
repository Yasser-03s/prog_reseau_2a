import matplotlib.pyplot as plt
import numpy as np
import skimage.color
import skimage.transform

from matplotlib import cm
from matplotlib.colors import ListedColormap

img= plt.imread("./img(1)/home.jpg")

ycbcr= skimage.color.rgb2ycbcr(img)

def sketch(alpha,beta):
    