/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Diseño y Análisis de Algoritmos 2025-2026
  * Curso: 3º
  * 
  * @author Pablo García de los Reyes
  * @author César Navarro Santos
  * @description: Programa principal
  * @date 07 Mar 2026
  * @version 1.0
  */

#include "app/AppFunctions.h"
#include <fstream>
#include <iostream>

int main() {
    // Obtener lista de instancias disponibles
    auto instance_files = GetInstanceFiles();

    // Mostrar menú y obtener selección del usuario
    auto selected_instances = DisplayInstanceMenu(instance_files);

    // Obtener opción de salida (consola o fichero)
    int output_option = GetOutputOption();

    // Configurar redirección de salida si es necesario
    std::ofstream output_file;
    std::streambuf* old_cout = nullptr;
    std::streambuf* old_cerr = nullptr;

    if (!SetupOutputRedirection(output_option, output_file, old_cout, old_cerr)) {
        return 1;
    }

    // Procesar todas las instancias seleccionadas
    ProcessInstances(selected_instances);

    // Restaurar redirección de salida
    RestoreOutputRedirection(output_option, output_file, old_cout, old_cerr);

    return 0;
}