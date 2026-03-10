CXX = g++
TARGET = p03_dyv
CXXFLAGS = -std=c++17 -Ilib -Ilib/base -Ilib/dyv -Ilib/planificacion -Ilib/io -Ilib/sorting -Ilib/third_party -Ilib/app

SRCS = src/base/Algoritmo.cc \
	src/base/Solucion.cc \
	src/base/Instancia.cc \
	src/dyv/Divide_y_Venceras.cc \
	src/dyv/DyV_Planificacion.cc \
	src/planificacion/Instancia_Planificacion.cc \
	src/planificacion/Solucion_Planificacion.cc \
	src/io/Printer.cc \
	src/app/AppFunctions.cc \
	src/app/ProgramMain.cc
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