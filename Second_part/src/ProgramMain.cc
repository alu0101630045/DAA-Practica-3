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

#include "../lib/Instancia_Planificación.h"
#include "../lib/Printer.h"
#include "../lib/DyV_Planificacion.h"
#include <iostream>
#include <chrono>

int main() {
    std::vector<std::string> instance_files = {
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

    DyVPlanificacion algoritmo;

    for (const auto& file : instance_files) {
        try {
            std::cout << std::string(80, '=') << std::endl;
            std::cout << "Procesando: " << file << std::endl;
            std::cout << std::string(80, '=') << std::endl << std::endl;

            InstanciaPlanificacion instancia(file);
            
            // Imprimir instancia
            // Printer::printInstancia(instancia);
            // std::cout << std::endl << std::string(80, '-') << std::endl << std::endl;

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

    return 0;
}