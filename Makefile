CFILES=$(shell find Source -name '*.cpp')
OFILES=$(patsubst %.cpp,%.o,$(CFILES))
TARGET=MinecraftWeek

FLAGS=-lGL -lpthread -lsfml-system -lsfml-window -lsfml-graphics -lGLEW
CC_FLAGS=-std=c++17

$(TARGET): $(OFILES)
	g++ -o $(TARGET) $(OFILES) $(FLAGS)

%.o: %.cpp
	g++ $(CC_FLAGS) -o $@ -c $<

clean:
	rm -rf $(TARGET) $(OFILES)
