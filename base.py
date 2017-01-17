import numpy as np

class Base:

    gen = None

    def __init__(self, generator):
        print("Importing base...")
        self.gen = generator
        self.gen.functionList.append("addall [r] [g] [b] [a]")
        self.gen.functionList.append("setall [r] [g] [b] [a]")
        self.gen.commands["addall"] = self.addall
        self.gen.commands["setall"] = self.setall
    
    def addall(self, r, g, b, a):
        colorVector = np.fromstring(r + " " + g + " " + b + " " + a, dtype=int, sep=' ')
        
        print("adding " + str(colorVector) + " to all pixels...") # DEBUG

        self.gen.imgArray = self.gen.imgArray + colorVector
        self.gen.imgArray = np.clip(self.gen.imgArray, 0, 255)

    def setall(self, r, g, b, a):
        colorVector = np.fromstring(r + " " + g + " " + b + " " + a, dtype=int, sep=' ')
        
        print("setting all pixels to " + str(colorVector) + "...") # DEBUG
        
        for x in range(0, self.gen.imgHeight):
            for y in range(0, self.gen.imgWidth):
                self.gen.imgArray[x][y] = colorVector