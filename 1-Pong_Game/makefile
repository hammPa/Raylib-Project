# # Compiler
# CXX = g++

# # Linker flags for raylib
# LDFLAGS = -lraylib

# # Target executable
# TARGET = main

# # Source file
# SOURCES = main.cpp

# # Default rule
# all: $(TARGET) run

# # Rule to build the target
# $(TARGET): $(SOURCES)
# 	$(CXX) $(SOURCES) -o $(TARGET) $(LDFLAGS)

# # Rule to run the executable
# run: $(TARGET)
# 	./$(TARGET)

# # Clean rule to remove the generated executable
# clean:
# 	rm -f $(TARGET)

# # Declare phony targets
# .PHONY: all clean run



# Compiler
CXX = g++

# Linker flags for raylib
LDFLAGS = -lraylib

# Target executable
TARGET = main

# Source files
SOURCES = main.cpp Ball.cpp Entity.cpp Player.cpp Enemy.cpp

# Object files (sama dengan SOURCES, tapi dengan ekstensi .o)
OBJECTS = $(SOURCES:.cpp=.o)

# Default rule
all: $(TARGET) run

# Rule to build the target
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Rule to run the executable
run: $(TARGET)
	./$(TARGET)

# Clean rule to remove the generated executable and object files
clean:
	rm -f $(TARGET) $(OBJECTS)

# Declare phony targets
.PHONY: all clean run
