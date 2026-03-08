CXX = g++
TARGET = p03_dyv
CXXFLAGS = -std=c++17

SRCS = src/Algoritmo.cc src/Solucion.cc src/Divide_y_Venceras.cc src/Instancia.cc src/Instancia_Planificacion.cc src/Solucion_Planificacion.cc src/DyV_Planificacion.cc src/Printer.cc src/ProgramMain.cc
OBJS = $(patsubst src/%.cc, build/%.o, $(SRCS))

all: $(TARGET)

# Compilar ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar objetos
build/%.o: src/%.cc | build
	$(CXX) $(CXXFLAGS) -Ilib -c $< -o $@

# Crear carpeta build si no existe
build:
	mkdir -p build

# Limpiar
clean:
	rm -rf build $(TARGET)

# Ejecutar
run: $(TARGET)
	./$(TARGET)