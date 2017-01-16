import numpy as np

class Base:

    gen = None

    def __init__(self, generator):
        print("Importing base...")
        self.gen = generator
        self.gen.functionList.append("add [r] [g] [b] [a]")
        self.gen.commands["add"] = self.add
    
    def add(self, r, g, b, a):
        #self.gen
        #print(colorVector)
        colorVector = np.fromstring(r + " " + g + " " + b + " " + a, dtype=int, sep=' ')
        
        print(colorVector) # DEBUG

        self.gen.imgArray = self.gen.imgArray + colorVector

        #for thing in colorVector:
            #print(str(thing))
        #for x in range(0, len(self.gen.imgArray)):
            #for y in range(0, len(self.gen.imgArray))
