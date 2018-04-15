CFILES=$(shell find Source -name '*.cpp')
OFILES=$(patsubst %.cpp,%.o,$(CFILES))
TARGET=MinecraftWeek

OS := $(shell uname)
ifeq ($(OS),Darwin)
FLAGS=-framework OpenGL -lpthread -lsfml-system -lsfml-window -lsfml-graphics -ldl -L/usr/local/lib
CC_FLAGS=-std=c++1y -O3 -pipe -ffast-math -fno-inline -mfpmath=sse -flto -fno-omit-frame-pointer -march=native -mtune=native -I/Users/19nbourgeois_68/homebrew/include
else
FLAGS=-lGL -lpthread -lsfml-system -lsfml-window -lsfml-graphics -ldl
CC_FLAGS=-std=c++1y -O3 -pipe -ffast-math -fno-inline -mfpmath=sse -flto -fno-omit-frame-pointer -march=native -mtune=native
endif

$(TARGET): $(OFILES)
	g++ -g -o $(TARGET) $(OFILES) $(FLAGS)

%.o: %.cpp
	g++ $(CC_FLAGS) -o $@ -c $<

clean:
	rm -rf $(TARGET) $(OFILES)

