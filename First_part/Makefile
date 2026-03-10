CXX = g++
TARGET = p03_dyv
CXXFLAGS = -std=c++17 -Ilib -Ilib/base -Ilib/dyv -Ilib/sorting -Ilib/utils

SRCS = $(shell find src -name '*.cc' | sort)
OBJS = $(patsubst src/%.cc, build/%.o, $(SRCS))

all: $(TARGET)

# Compilar ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar objetos
build/%.o: src/%.cc | build
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear carpeta build si no existe
build:
	mkdir -p build

# Limpiar
clean:
	rm -rf build $(TARGET)

# Ejecutar
run: $(TARGET)
	./$(TARGET)