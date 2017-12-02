CFILES=$(shell find Source -name '*.cpp')
OFILES=$(patsubst %.cpp,%.o,$(CFILES))
TARGET=MinecraftWeek

OS := $(shell uname)
ifeq ($(OS),Darwin)
FLAGS=-framework OpenGL -lpthread -lsfml-system -lsfml-window -lsfml-graphics -lGLEW -L/usr/local/lib
CC_FLAGS=-std=c++1y -I/usr/local/include -O3 -march=native -mtune=native
else
FLAGS=-lGL -lpthread -lsfml-system -lsfml-window -lsfml-graphics -lGLEW
-CC_FLAGS=-std=c++1y -O3 -march=native -mtune=native
endif

$(TARGET): $(OFILES)
	g++ -g -o $(TARGET) $(OFILES) $(FLAGS)

%.o: %.cpp
	g++ $(CC_FLAGS) -o $@ -c $<

clean:
	rm -rf $(TARGET) $(OFILES)
