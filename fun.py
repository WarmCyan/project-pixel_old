import numpy as np
import math

class Fun:

    gen = None

    def __init__(self, generator):
        print("Importing fun...")
        self.gen = generator
        self.gen.functionList.append("fun1")
        self.gen.commands["fun1"] = self.fun1
        self.gen.functionList.append("fun2")
        self.gen.commands["fun2"] = self.fun2
        self.gen.functionList.append("fun3")
        self.gen.commands["fun3"] = self.fun3
        self.gen.functionList.append("fun4")
        self.gen.commands["fun4"] = self.fun4
        
    def fun1Calculator(self, x, y):
        value = math.sin(x) * math.cos(y)
        value = abs(value)
        value *= 255
        value = int(value)
        return np.array([value, value, value, 255], dtype=int)


    def fun1(self):
        print("Applying fun1...")
        for x in range(0, self.gen.imgHeight):
            for y in range(0, self.gen.imgWidth):
                self.gen.imgArray[x][y] = self.fun1Calculator(x, y)
            
    def fun2Calculator(self, x, y, xscalar, yscalar):
        value = math.sin((float(x/self.gen.imgHeight)*float(xscalar))*(float(y/self.gen.imgWidth)*float(yscalar)))
        value = abs(value)
        value *= 254
        value = int(value)
        return np.array([value, value, value, 255], dtype=int)

    def fun2(self, xscalar, yscalar):
        print("Applying fun2...")
        for x in range(0, self.gen.imgHeight):
            for y in range(0, self.gen.imgWidth):
                self.gen.imgArray[x][y] = self.fun2Calculator(x, y, xscalar, yscalar)
            
    def fun3Calculator(self, x, y):
        value = math.sin(x) * math.sin(y)
        value = abs(value)
        value *= 254
        value = int(value)
        return np.array([value, value, value, 255], dtype=int)

    def fun3(self):
        print("Applying fun3...")
        for x in range(0, self.gen.imgHeight):
            for y in range(0, self.gen.imgWidth):
                self.gen.imgArray[x][y] = self.fun3Calculator(x, y)
            
    def fun4Calculator(self, x, y, xscalar, yscalar):
        value = math.sin((x*float(xscalar))*math.sqrt(y*float(yscalar)))
        value = abs(value)
        #print(str(value))
        value *= 255
        #value *= 50
        value = int(value)
        return np.array([value, value, value, 255], dtype=int)

    def fun4(self, xscalar, yscalar):
        print("Applying fun4...")
        for x in range(0, self.gen.imgHeight):
            for y in range(0, self.gen.imgWidth):
                self.gen.imgArray[x][y] = self.fun4Calculator(x, y, xscalar, yscalar)
            
