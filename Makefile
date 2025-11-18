CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

SRC = src/main.cpp src/Character.cpp src/Monster.cpp src/DungeonManager.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = ShadowRealms

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)
