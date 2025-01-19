CC=g++
CFLAGS=-g -Wall
SRC_DIR=src
INCLUDE_DIR=include
OBJ_DIR=obj
BIN_DIR=bin
EXECUTABLE=$(BIN_DIR)/tp2.out

SRC_FILES:=$(wildcard $(SRC_DIR)/*.cpp)

OBJ_FILES:=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

all:$(EXECUTABLE)

run:$(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -I$(INCLUDE_DIR) -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE)