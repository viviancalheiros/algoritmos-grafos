# Variáveis
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Nome do executável
TARGET = prim

# Regra principal
all: $(TARGET)

# Como compilar o executável
$(TARGET): prim.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) prim.o

# Como compilar o .cpp em .o
prim.o: prim.cpp
	$(CXX) $(CXXFLAGS) -c prim.cpp

# Limpa os arquivos compilados
clean:
	rm -f *.o $(TARGET)
