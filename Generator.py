import numpy as np
import scipy.misc
import traceback

from base import Base

class Generator:

    imgArray = None
    imgHeight = 0
    imgWidth = 0

    functionList = ["help", "exit", "printvalues", "create [width] [height]", "save [name]"]
    #commands = []
    commands = {}

    replRunning = True

    base = None

    def __init__(self):
        #self.commands.append(self.create)
        #self.commands.append(self.save)
        self.commands["create"] = self.create
        self.commands["save"] = self.save
        self.commands["help"] = self.help
        self.commands["printvalues"] = self.printvalues
        self.base = Base(self)
        replRunning = True

        self.runCommand("help")
        self.runCommand("create 500 500")

    def create(self, width, height):
        self.imgHeight = int(height)
        self.imgWidth = int(width)

        self.imgArray = np.zeros((self.imgWidth, self.imgHeight, 4), dtype=np.uint8)
        print("Image of size " + str(width) + "x" + str(height) + " initialized...")

    def printvalues(self):
        print(str(self.imgArray))

    def save(self, name):
        scipy.misc.imsave(name + ".png", self.imgArray)
        print("Image saved successfully!")

    def help(self):
        print("")
        for function in self.functionList: print(function)

    def runCommand(self, cmdString):
        cmdArray = str(cmdString).split(" ")
        
        cmd = cmdArray[0]
        args = cmdArray[1:]

        #print("cmd: " + str(cmd)) # DEBUG
        #print("args: " + str(args)) # DEBUG

        if cmd == "exit":
            print("Exiting...")
            self.replRunning = False
            return

        try:
            self.commands[cmd](*args)
        except Exception as e:
            print("ERROR: " + str(e))
            traceback.print_exc()

    def repl(self):
        while self.replRunning:
            print("")
            cmdInput = input("Pixel> ")
            self.runCommand(cmdInput)
