import random
import math
import numpy as np

class Function:


    # F(x,y) = sum_j(ax+by+c, dx+ey+f)

    #matrixCoefficients = {"a":0., "b":0., "c":0., "d":0., "e":0., "f":0.}
    # matrix coefficients 

    #variations = []
    #v = [] # variation coefficients

    def __init__(self):

        self.variations = []
        self.v = []

        self.a = 0.
        self.b = 0.
        self.c = 0.
        self.d = 0.
        self.e = 0.
        self.f = 0.
        
        self.variations.append(self.linear)
        self.variations.append(self.sinusoidal)
        self.variations.append(self.spherical)
        self.variations.append(self.swirl)
        
        self.v.append(0.)
        self.v.append(0.)
        self.v.append(0.)
        self.v.append(0.)
        pass
    
    def run(self, x, y):
        resultx = 0
        resulty = 0
        for i in range(0, len(self.variations)):
            #print("Running variation " + str(i)) # DEBUG
            tempx, tempy = self.variations[i](self.a*x + self.b*y + self.c, self.d*x + self.e*y + self.f)
            #print("Variation outputs: (" + str(tempx) + "," + str(tempy) + ")") # DEBUG
            tempx *= self.v[i]
            tempy *= self.v[i]
            #print("Coeff applied: (" + str(tempx) + "," + str(tempy) + ")") # DEBUG
            
            resultx += tempx
            resulty += tempy

        #print("Function result: (" + str(resultx) + "," + str(resulty) + ")") # DEBUG
        return resultx, resulty
            

    def calc_r(self, x, y):
        return math.sqrt(x**2 + y**2)

    # VARIATIONS
    
    def linear(self, x, y):
        return x, y

    def sinusoidal(self, x, y):
        return math.sin(x), math.sin(y)

    def spherical(self, x, y):
        r = self.calc_r(x, y)
        coef = 1/(r**2)
        return x*coef, y*coef

    def swirl(self, x, y):
        r = self.calc_r(x, y)
        return x*math.sin(r**2) - y*math.cos(r**2), x*math.sin(r**2) + y*math.cos(r**2)
    

class FlameFractal:

    gen = None

    functions = []

    # NOTE: use ff. prefix to all functions added to generator commands (for
    # flame fractal) since there will probably be a lot with all the variations
    # and stuff

    def __init__(self, generator):
        print("Importing flame fractal...")
        self.gen = generator
        self.gen.functionList.append("ff.solve")
        self.gen.commands["ff.solve"] = self.solve
        self.gen.functionList.append("ff.gasket")
        self.gen.commands["ff.gasket"] = self.setGasketFunctions

        self.createTestingFunction()

    def setGasketFunctions(self):
        self.functions = []
        
        f = Function()
        f.a = .5
        f.e = .5

        f.v[0] = 1.
        
        self.functions.append(f)

        f2 = Function()
        f2.a = .5
        f2.c = .5
        f2.e = .5
        f2.v[0] = 1.

        f3 = Function()
        f3.a = .5
        f3.e = .5
        f3.f = .5
        f3.v[0] = 1.

        self.functions.append(f2)
        self.functions.append(f3)
        print("Flame fractal functions set to Sierpinski's Gaskget")


    def createTestingFunction(self):
        f = Function()
        f.a = .9
        f.e = .9

        f.v[0] = .1
        f.v[2] = 1.
        #f.v[3] = 1.
        
        self.functions.append(f)

        f2 = Function()
        f2.a = .5
        f2.c = .5
        f2.e = .5
        f2.v[1] = .6
        f.v[3] = .3

        f3 = Function()
        f3.a = .5
        f3.e = .5
        f3.f = .5
        f3.v[1] = .5
        f3.v[2] = .3
        f3.v[3] = .1

        self.functions.append(f2)
        self.functions.append(f3)

        #f2 = Function()
        #f2.a = .1
        #f2.e = .1

        #f2.v[3] = .1
        #f2.v[4] = 1.

        #self.functions.append(f2)

    def finalTransform(self, x, y):
        return x*500, y*500

    def solve(self, iterations):
        # choose random starting point within our coordinate system's range of [-1,1]
        x = random.random() * 2 - 1
        y = random.random() * 2 - 1

        for index in range(0, int(iterations) + 1):
            #print("On iteration " + str(index)) # DEBUG
            #print("x: " + str(x) + " y: " + str(y)) # DEBUG

            # get a random function and apply it TODO: add weighting
            i = random.randint(0, len(self.functions) - 1)
            #print("Running function " + str(i)) # DEBUG
            x, y = self.functions[i].run(x, y)
            xf, yf = self.finalTransform(x, y)
            
            # ignore the first 20 iterations to allow it time to converge to below size of a pixel
            if index > 20: 
                pixels = self.determinePixel(xf, yf)
                #print("Plotting (" + str(pixels[0]) + "," + str(pixels[1]) + ")...") # DEBUG
                if pixels[0] < 0 or pixels[0] > self.gen.imgWidth - 1 or pixels[1] < 0 or pixels[1] > self.gen.imgHeight - 1:
                    continue
                self.gen.imgArray[pixels[1]][pixels[0]] = np.array([255,255,255,255])

        print("Flame fractal set solution plotted!")
    
    def determinePixel(self, x, y):
        #xpixel = int(x*(self.gen.imgWidth/2)) + (self.gen.imgWidth/2)
        #ypixel = int(y*(self.gen.imgHeight/2)) + (self.gen.imgHeight/2)
        #xpixel = int(x*(self.gen.imgWidth - 1))
        #ypixel = int(y*(self.gen.imgHeight - 1))
        xpixel = int(x)
        ypixel = int(y)
        return xpixel, ypixel
