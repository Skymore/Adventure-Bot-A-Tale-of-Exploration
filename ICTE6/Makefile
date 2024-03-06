# Define the compiler
CXX = g++ -std=c++17

# Compiler flags
CXXFLAGS = -std=c++17 -Wall

# Define the target executable
TARGET = test

# Build the target executable
$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)

# Clean target to remove compiled objects and the executable
clean:
	rm -f $(TARGET)
