CXX = g++
CXXFLAGS = -Wall -std=c++11

# Nome do executável
TARGET = exclusao_inversa

all: $(TARGET)

# Como compilar o executável
$(TARGET): exclusao_inversa.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) exclusao_inversa.o

# Como compilar o .cpp em .o
kruskal.o: exclusao_inversa.cpp
	$(CXX) $(CXXFLAGS) -c exclusao_inversa.cpp

clean:
	rm -f *.o $(TARGET)