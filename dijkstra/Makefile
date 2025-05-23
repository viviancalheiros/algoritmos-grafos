# Variáveis
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Nome do executável
TARGET = dijkstra

# Regra principal
all: $(TARGET)

# Como compilar o executável
$(TARGET): dijkstra.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) dijkstra.o

# Como compilar o .cpp em .o
dijkstra.o: dijkstra.cpp
	$(CXX) $(CXXFLAGS) -c dijkstra.cpp

# Limpa os arquivos compilados
clean:
	rm -f *.o $(TARGET)
