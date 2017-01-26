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

        self.color = 0.

        self.weight = 1.

        self.isSymmetry = False

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
            if self.v[i] == 0: continue
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
    #functionColors = [[0,120,255],[0, 255, 120], [255,120,0]]

    points = []

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
        self.gen.functionList.append("ff.render")
        self.gen.commands["ff.render"] = self.render

        self.createTestingFunction()
        
    def preparePlot(self):
        print("Preparing plot...")
        for y in range(0, self.gen.imgHeight):
            self.points.append([])
            for x in range(0, self.gen.imgWidth):
                self.points[y].append([0,0,0,0])
        print("Plot prepared")

    def colorMap(self, value):
        #r = 1 - value
        #if value < .5:
            #g = value * 2
        #else:
            #g = (1 - value*2)
        #b = value

        #r = 0
        #g = 1 - value
        #b = value

        # AWESOME BLUE MAP
        r = 1. - value
        g = 1. - (value/2)
        b = 1.
        
        
        #r = 1. - value
        #r = 0.
        #g = value
        #b = 1. - value

        #return r*255, g*255, b*255
        return r, g, b

    def plot(self, x, y, c):
        # check if already exists
        #for point in self.points:
            #if x == point[0] and y == point[1]:
                #point[2] += 1
                #return
        # if not already in the points array
        #self.points.append([x, y, 1])
        color = self.colorMap(c)
        #print(str(color)) # DEBUG
        self.points[y][x][0] += color[0]
        self.points[y][x][1] += color[1]
        self.points[y][x][2] += color[2]
        self.points[y][x][3] += 1

    def render(self, gamma=1.0, brightness=1.0):
        print("Rendering... (gamma = " + str(gamma) + ")") 
        #for point in self.points:
            #value = int(math.log(point[2])*200)
            #self.gen.imgArray[point[1]][point[0]] = np.array([255,255,255,255])
            #self.gen.imgArray[point[1]][point[0]] = np.array([value,value,value,255])
        print("First pass...")
        totalPoints = 0
        avgSpots = 0
        
        for y in range(0, len(self.points)):
            for x in range(0, len(self.points[y])):
                count = self.points[y][x][3]
                if count > 1:
                    totalPoints += count
                    avgSpots += 1
                    
        averageDensity = float(totalPoints / avgSpots)
        print("Average point density: " + str(averageDensity))
        
        brightnessScalar = float(255 / averageDensity)*float(brightness)
        print("Brightness scalar: " + str(brightnessScalar))

        print("Second pass...")
        
        for y in range(0, len(self.points)):
            for x in range(0, len(self.points[y])):
                count = self.points[y][x][3]
                r = self.points[y][x][0]
                g = self.points[y][x][1]
                b = self.points[y][x][2]

                
                #print(str(x) + "," + str(y) + " - " + str(count))
                if count > 1: 
                    #totalPoints += count
                    #avgSpots += 1

                    scalar = math.log(count) / count

                    # gamma correction
                    scalar_c = scalar**(1/float(gamma))
                    #print(str(scalar_c))

                    
                    #r *= scalar_c*75
                    #g *= scalar_c*75
                    #b *= scalar_c*75
                    r *= scalar_c*brightnessScalar
                    g *= scalar_c*brightnessScalar
                    b *= scalar_c*brightnessScalar
                    #alpha = int(math.log(count) * 75)

                    # cap it, cause it does weird things if you don't....(I
                    # assume it was overflowing)
                    r = int(min(255, r))
                    g = int(min(255, g))
                    b = int(min(255, b))
                    
                    # this is what's known as an ERROR. This shouldn't occur....
                    #if r > g or g > b or r > b or r > 255 or g > 255 or b > 255:
                    #    print("WARNING - " + str(r) + " " + str(g) + " " + str(b))
                    
                    #print(str(count))
                    #value = int(math.log(count)*75)
                    #value = 255
                    self.gen.imgArray[y][x] = np.array([r, g, b, 255])
                #value = int(math.log(self.points[x][y] * 
        
                
        print("Render complete!")

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
        f.v[2] = .7
        f.v[3] = .1
        f.v[1] = .1

        f.color = 1
        f.weight = 1
        
        self.functions.append(f)

        f2 = Function()
        f2.a = .5
        f2.c = .5
        f2.e = .5
        f2.v[1] = .6
        f2.v[0] = .4
        f.v[3] = .2
        f2.color = .5
        f2.weight = 1

        f3 = Function()
        f3.a = .5
        f3.e = .5
        f3.f = .5
        f3.v[1] = .5
        f3.v[2] = .3
        f3.v[3] = .1
        f3.color = 0
        f3.weight = 1

        self.functions.append(f2)
        self.functions.append(f3)

        # NOTE: THIS is how you make symmetry work!!! Only include the linear
        # variation in it with a weight of 1!!!
        f4 = Function()
        f4.a = -1 # cos 180
        f4.b = 0 # sin 180
        f4.d = 0 # - sin 180
        f4.e = 1 # cos 180
        
        f4.v[0] = 1.
        f4.color = .7
        f4.weight = 3
        f4.isSymmetry = True

        #self.functions.append(f4)

        # 3-way symmetry
        f5 = Function()
        f5.a = -.5 # cos 120
        f5.b = .866025 # sin 120
        f5.d = -.866025 # - sin 120
        f5.e = -.5 # cos 120
        
        f5.v[0] = 1.
        f5.color = .7
        f5.weight = 3
        f5.isSymmetry = True
        self.functions.append(f5)
        
        f6 = Function()
        f6.a = -.5 # cos 240
        f6.b = .866025 # sin 240
        f6.d = -.866025 # - sin 240
        f6.e = -.5 # cos 240
        
        f6.v[0] = 1.
        f6.color = .7
        f6.weight = 3
        f6.isSymmetry = True
        self.functions.append(f6)

        #f2 = Function()
        #f2.a = .1
        #f2.e = .1

        #f2.v[3] = .1
        #f2.v[4] = 1.

        #self.functions.append(f2)

    def finalTransform(self, x, y):
        #return x*500, y*500
        
        return x*200 + 250, y*200 + 250
    
        #return (x*500)+350, y*500
        #return x*3200, y*3200
        #return (x*3200)+2240, y*3200
        #return (x*1800)+1260, y*1800

        #return x*400 + 500, y*400 + 500

    def finalColorTransform(self, c):
        return c

    def solve(self, iterations):
        self.preparePlot()
        
        print("Solving...")
        # choose random starting point within our coordinate system's range of [-1,1]
        x = random.random() * 2 - 1
        y = random.random() * 2 - 1

        c = random.random()
        cf = c # just to avoid bugs with symmetric functions?

        displaystep = int(int(iterations) / float(100))

        functionWeights = []
        functionWeightsTotal = 0.0

        functionCounts = []

        # first pass for total weight
        for i in range(0, len(self.functions)):
            functionWeightsTotal += self.functions[i].weight

        # second pass for finding each individual adjusted weight
        sumSoFar = 0
        for i in range(0, len(self.functions)):
            thisWeight = float(self.functions[i].weight / functionWeightsTotal)
            sumSoFar += thisWeight
            functionWeights.append(sumSoFar)
            functionCounts.append(0)

        print("Function weights: " + str(functionWeights)) # DEBUG

        for index in range(0, int(iterations) + 1):
            #print("On iteration " + str(index)) # DEBUG
            #print("x: " + str(x) + " y: " + str(y)) # DEBUG

            # get a random function and apply it TODO: add weighting
            #i = random.randint(0, len(self.functions) - 1)
            roll = random.random()

            # randomly choose function, based on weights
            i = 0
            while roll > functionWeights[i]: i += 1
            functionCounts[i] += 1
            
            #print("Running function " + str(i)) # DEBUG
            x, y = self.functions[i].run(x, y)
            xf, yf = self.finalTransform(x, y)
            
            if not self.functions[i].isSymmetry:
                c = (c + self.functions[i].color) / 2
                cf = (c + self.finalColorTransform(c)) / 2
            
            
            # ignore the first 20 iterations to allow it time to converge to below size of a pixel
            if index > 20: 
                pixels = self.determinePixel(xf, yf)
                #print("Plotting (" + str(pixels[0]) + "," + str(pixels[1]) + ")...") # DEBUG
                if pixels[0] < 0 or pixels[0] > self.gen.imgWidth - 1 or pixels[1] < 0 or pixels[1] > self.gen.imgHeight - 1:
                    continue
                #self.gen.imgArray[pixels[1]][pixels[0]] = np.array([255,255,255,255])
                self.plot(pixels[0], pixels[1], cf)

            if index % displaystep == 0: print("Completed iteration " + str(index))

        print("Flame fractal set solution plotted!")

        for c in range(0, len(functionCounts)):
            print(str(c) + " - " + str(functionCounts[c]))
        
        #self.render(2.2)
        self.render()
    
    def determinePixel(self, x, y):
        #xpixel = int(x*(self.gen.imgWidth/2)) + (self.gen.imgWidth/2)
        #ypixel = int(y*(self.gen.imgHeight/2)) + (self.gen.imgHeight/2)
        #xpixel = int(x*(self.gen.imgWidth - 1))
        #ypixel = int(y*(self.gen.imgHeight - 1))
        xpixel = int(x)
        ypixel = int(y)
        return xpixel, ypixel
