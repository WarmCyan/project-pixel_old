#import png
#png.from_array([[255,0,0,255],[0,255,255,0]], 'L').save("small_smiley.png")

import scipy.misc
import numpy as np


#imgarray = np.array([[255,0,0,255],[0,255,255,0]], dtype=np.uint8)
#scipy.misc.imsave("test.png", imgarray)

def determineValue(row, col):
    highest = 2500

    val = (row*col)/highest
    return val*255


imgarray = np.zeros((50,50), dtype=np.uint8)

for row in range(0, len(imgarray)):
    for col in range(0, len(imgarray[0])):
        #print(str(col))
        imgarray[row][col] = determineValue(row, col)
        print(imgarray[row][col])
    
scipy.misc.imsave("image.png", imgarray)
