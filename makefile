CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iincludes
LDFLAGS = -lsqlite3

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = bin/helicopter_transport

all: $(EXEC)

$(EXEC): $(OBJ)
  $(CXX) $(CXXFLAGS) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
  $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
  rm -f $(OBJ) $(EXEC)

run: $(EXEC)
    ./$(EXEC)
