import numpy as np
import math
import random

class FlameTest:

    gen = None

    functions = []
    
    def __init__(self, generator):
        print("Importing flame test...")
        self.gen = generator
        self.gen.functionList.append("solve")
        self.gen.commands["solve"] = self.solve

        self.functions.append(self.f0)
        self.functions.append(self.f1)
        self.functions.append(self.f2)

    def f0(self, x, y):
        return x/2, y/2
    
    def f1(self, x, y):
        return (x+1)/2, y/2
    
    def f2(self, x, y):
        return x/2, (y+1)/2

    def solve(self, iterations):
        x = random.random() * 2 - 1
        y = random.random() * 2 - 1
        
        for index in range(0, int(iterations) + 1):
            print("On iteration " + str(index)) # DEBUG
            print("x: " + str(x) + " y: " + str(y)) # DEBUG
            i = random.randint(0, len(self.functions) - 1)
            x, y = self.functions[i](x, y)
            if index > 20: 
                pixels = self.determinePixel(x, y)
                print("Plotting (" + str(pixels[0]) + "," + str(pixels[1]) + ")...")
                self.gen.imgArray[pixels[1]][pixels[0]] = np.array([255,255,255,255])
        
    def determinePixel(self, x, y):
        #xpixel = int(x*(self.gen.imgWidth/2)) + (self.gen.imgWidth/2)
        #ypixel = int(y*(self.gen.imgHeight/2)) + (self.gen.imgHeight/2)
        xpixel = int(x*(self.gen.imgWidth))
        ypixel = int(y*(self.gen.imgHeight))
        return xpixel, ypixel
