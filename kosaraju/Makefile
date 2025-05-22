CXX = g++
CXXFLAGS = -Wall -std=c++11

# Nome do executável
TARGET = kosaraju

all: $(TARGET)

# Como compilar o executável
$(TARGET): kosaraju.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) kosaraju.o

# Como compilar o .cpp em .o
kruskal.o: kosaraju.cpp
	$(CXX) $(CXXFLAGS) -c kosaraju.cpp

clean:
	rm -f *.o $(TARGET)