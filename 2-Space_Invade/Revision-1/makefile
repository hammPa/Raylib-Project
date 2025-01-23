# Compiler
CXX = g++

# Linker flags for raylib
LDFLAGS = -lraylib

# Target executable
TARGET = main

# Directories
SRC_DIR = .
BULLET_DIR = ./Bullet
ENTITY_DIR = ./Entity
ASSETS_DIR = ./Assets

# Source files
SOURCES = $(SRC_DIR)/main.cpp \
          $(BULLET_DIR)/Bullet.cpp \
          $(ENTITY_DIR)/Entity.cpp \
          $(ENTITY_DIR)/Enemy.cpp \
          $(ENTITY_DIR)/Player.cpp \
          $(ASSETS_DIR)/Assets.cpp

# Object files (replace .cpp with .o)
OBJECTS = $(SOURCES:.cpp=.o)

# Default rule
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Rule to compile source files to object files
%.o: %.cpp
	$(CXX) -c $< -o $@

# Clean rule to remove the generated executable and object files
clean:
	rm -f $(TARGET) $(OBJECTS)

# Rule to run the executable
run: $(TARGET)
	./$(TARGET)

# Declare phony targets
.PHONY: all clean run
