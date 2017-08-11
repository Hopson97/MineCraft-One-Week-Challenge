CFILES=$(shell find Source -name '*.cpp')
OFILES=$(patsubst %.cpp,%.o,$(CFILES))
TARGET=MinecraftWeek

FLAGS=-lGL -lpthread -lsfml-system -lsfml-window -lsfml-graphics -lGLEW

$(TARGET): $(OFILES)
	g++ -o $(TARGET) $(OFILES) $(FLAGS)

%.o: %.cpp
	g++ -o $@ -c $<

clean:
	rm -rf $(TARGET) $(OFILES)
