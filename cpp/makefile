# compiler 
CC=gcc

# output name
TARGET=FlameFractalEngine

# directories
BINDIR=.
OBJDIR=obj
SRCDIR=src
LIBDIR=lib

INC=-I$(LIB_DIR)/cpp -I./

SOURCES := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(LIBDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.cpp=.o)) $(patsubst $(LIBDIR)/%,$(OBJDIR)/%,$(SOURCES:.cpp=.o)) 

all: $(TARGET)
	
run: all
	$(BINDIR)/$(TARGET)

re: clean all

rerun: clean run

# link
$(TARGET): $(OBJECTS)
	echo $(SOURCES)
	echo $(OBJECTS)
	$(CC) -o $(BINDIR)/$(TARGET) $^

# compile
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(LIBDIR)/%.cpp
	$(CC) $(INC) -c -o $@ $<

clean:
	-rm $(OBJDIR)/*.o
	-rm $(BINDIR)/$(TARGET)

.PHONY: clean all run re rerun
