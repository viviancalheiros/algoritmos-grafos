CXX = g++
CXXFLAGS = -Wall -std=c++11

# Nome do executável
TARGET = kruskal

all: $(TARGET)

# Como compilar o executável
$(TARGET): kruskal.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) kruskal.o

# Como compilar o .cpp em .o
kruskal.o: kruskal.cpp
	$(CXX) $(CXXFLAGS) -c kruskal.cpp

clean:
	rm -f *.o $(TARGET)