/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Diseño y Análisis de Algoritmos 2025-2026
  * Curso: 3º
  * 
  * @author Pablo García de los Reyes
  * @author César Navarro Santos
  * @description: Implementación de funciones auxiliares para la aplicación
  * @date 10 Mar 2026
  * @version 1.0
  */

#include "app/AppFunctions.h"
#include "planificacion/Instancia_Planificación.h"
#include "io/Printer.h"
#include "dyv/DyV_Planificacion.h"
#include <chrono>
#include <iostream>
#include <limits>

std::vector<std::string> GetInstanceFiles() {
    return {
        "instance/instance_horizon7_employees5_shifts3_000.json",
        "instance/instance_horizon7_employees5_shifts3_001.json",
        "instance/instance_horizon7_employees10_shifts6_000.json",
        "instance/instance_horizon7_employees10_shifts6_001.json",
        "instance/instance_horizon14_employees10_shifts6_000.json",
        "instance/instance_horizon14_employees10_shifts6_001.json",
        "instance/instance_horizon14_employees20_shifts10_000.json",
        "instance/instance_horizon14_employees20_shifts10_001.json",
        "instance/instance_horizon30_employees20_shifts10_000.json",
        "instance/instance_horizon30_employees20_shifts10_001.json",
        "instance/instance_horizon30_employees30_shifts20_000.json",
        "instance/instance_horizon30_employees30_shifts20_001.json"
    };
}

std::vector<std::string> DisplayInstanceMenu(const std::vector<std::string>& instance_files) {
    std::cout << "=== Menu de ejecucion ===" << std::endl;
    std::cout << "Instancias disponibles:" << std::endl;
    for (size_t i = 0; i < instance_files.size(); ++i) {
        std::cout << "  [" << i << "] " << instance_files[i] << std::endl;
    }
    std::cout << "  [A] Ejecutar todas" << std::endl;

    std::vector<std::string> selected_instances;
    while (true) {
        std::cout << "\nSelecciona un indice (0-" << instance_files.size() - 1
                  << ") o 'A': ";
        std::string seleccion;
        std::cin >> seleccion;

        if (seleccion == "A" || seleccion == "a") {
            selected_instances = instance_files;
            break;
        }

        try {
            size_t pos = 0;
            int indice = std::stoi(seleccion, &pos);
            if (pos == seleccion.size() &&
                indice >= 0 &&
                indice < static_cast<int>(instance_files.size())) {
                selected_instances.push_back(instance_files[indice]);
                break;
            }
        } catch (const std::exception&) {
            std::cerr << "Entrada no valida. Intentalo de nuevo." << std::endl;
        }
    }

    return selected_instances;
}

int GetOutputOption() {
    std::cout << "\nDestino de salida:" << std::endl;
    std::cout << "  [1] Consola" << std::endl;
    std::cout << "  [2] Fichero" << std::endl;

    int output_option = 1;
    while (true) {
        std::cout << "Elige opcion (1-2): ";
        if ((std::cin >> output_option) && (output_option == 1 || output_option == 2)) {
            break;
        }
        std::cerr << "Entrada no valida. Intentalo de nuevo." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return output_option;
}

bool SetupOutputRedirection(int output_option,
                            std::ofstream& output_file,
                            std::streambuf*& old_cout,
                            std::streambuf*& old_cerr) {
    if (output_option == 2) {
        std::string output_path;
        std::cout << "Nombre del fichero de salida [output.txt]: ";
        std::cin >> std::ws;
        std::getline(std::cin, output_path);
        if (output_path.empty()) {
            output_path = "output.txt";
        }

        output_file.open(output_path);
        if (!output_file.is_open()) {
            std::cerr << "No se pudo abrir el fichero de salida: " << output_path << std::endl;
            return false;
        }

        old_cout = std::cout.rdbuf(output_file.rdbuf());
        old_cerr = std::cerr.rdbuf(output_file.rdbuf());
    }

    return true;
}

void RestoreOutputRedirection(int output_option,
                              std::ofstream& output_file,
                              std::streambuf* old_cout,
                              std::streambuf* old_cerr) {
    if (output_option == 2) {
        std::cout.rdbuf(old_cout);
        std::cerr.rdbuf(old_cerr);
        output_file.close();
        std::cout << "Resultados guardados en fichero." << std::endl;
    }
}

void ProcessInstances(const std::vector<std::string>& selected_instances) {
    DyVPlanificacion algoritmo;

    for (const auto& file : selected_instances) {
        try {
            std::cout << std::string(80, '=') << std::endl;
            std::cout << "Procesando: " << file << std::endl;
            std::cout << std::string(80, '=') << std::endl << std::endl;

            InstanciaPlanificacion instancia(file);
            
            // Resolver con DyV
            auto inicio = std::chrono::high_resolution_clock::now();
            Solucion* solucion = algoritmo.Solve(instancia);
            auto fin = std::chrono::high_resolution_clock::now();
            auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);

            auto* sol_plan = dynamic_cast<SolucionPlanificacion*>(solucion);
            if (sol_plan) {
                Printer::printSolucion(instancia, *sol_plan);
                std::cout << "Tiempo de ejecución: " << duracion.count() << " ms" << std::endl;
            } else {
                std::cerr << "Error: No se pudo resolver la instancia" << std::endl;
            }

            delete solucion;
            std::cout << std::endl << std::endl;

        } catch (const std::exception& e) {
            std::cerr << "Error al procesar " << file << ": " << e.what() << std::endl;
        }
    }
}
