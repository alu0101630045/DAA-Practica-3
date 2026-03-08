CXX = g++
TARGET = p03_dyv
CXXFLAGS = -std=c++17

SRCS = $(wildcard src/*.cc)
OBJS = $(patsubst src/%.cc, build/%.o, $(SRCS))

all: $(TARGET)

# Compilar ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar objetos
build/%.o: src/%.cc | build
	$(CXX) $(CXXFLAGS) -Iinclude -c $< -o $@

# Crear carpeta build si no existe
build:
	mkdir -p build

# Limpiar
clean:
	rm -rf build $(TARGET)

# Ejecutar
run: $(TARGET)
	./$(TARGET)