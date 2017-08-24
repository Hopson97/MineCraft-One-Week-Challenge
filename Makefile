CFILES=$(shell find Source -name '*.cpp')
OFILES=$(patsubst %.cpp,%.o,$(CFILES))
TARGET=MinecraftWeek

OS := $(shell uname)
ifeq ($(OS),Darwin)
FLAGS=-lGL -lpthread -lsfml-system -lsfml-window -lsfml-graphics -lGLEW -L/opt/local/bin
CC_FLAGS=-std=c++1y -I/opt/local/include
else
FLAGS=-lGL -lpthread -lsfml-system -lsfml-window -lsfml-graphics -lGLEW
CC_FLAGS=-std=c++1y
endif

$(TARGET): $(OFILES)
	g++ -o $(TARGET) $(OFILES) $(FLAGS)

%.o: %.cpp
	g++ $(CC_FLAGS) -o $@ -c $<

clean:
	rm -rf $(TARGET) $(OFILES)
