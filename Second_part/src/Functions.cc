/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Diseño y Análisis de Algoritmos 2025-2026
  * Curso: 3º
  * 
  * @author Pablo García de los Reyes
  * @author César Navarro Santos
  * @description: Definiciones de funciones auxiliares
  * @date 07 Mar 2026
  * @version 1.0
  */

#include "../lib/Functions.h"
#include <random>
#include <chrono>
#include <iomanip>

std::vector<InstanciaArray> generateRandomInstances(const std::vector<size_t>& sizes) {
    std::vector<InstanciaArray> instances;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);  // Números aleatorios entre 1 y 100

    for (size_t size : sizes) {
        std::vector<int> data;
        for (size_t i = 0; i < size; ++i) {
            data.push_back(dis(gen));
        }
        instances.emplace_back(data);
    }
    return instances;
}

std::vector<double> measureTimes(Algoritmo& algo, const std::vector<InstanciaArray>& instances) {
    std::vector<double> times;
    for (const auto& instance : instances) {
        auto start = std::chrono::high_resolution_clock::now();
        Solucion* sol = algo.Solve(instance);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        times.push_back(duration.count());
        delete sol;
    }
    return times;
}

void printComparisonTable(const std::vector<size_t>& sizes, const std::vector<double>& mergeTimes, const std::vector<double>& quickTimes) {
    std::cout << std::left << std::setw(10) << "Tamaño" << std::setw(15) << "Merge Sort (ms)" << std::setw(15) << "Quick Sort (ms)" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    for (size_t i = 0; i < sizes.size(); ++i) {
        std::cout << std::left << std::setw(10) << sizes[i] 
                  << std::setw(15) << std::fixed << std::setprecision(2) << mergeTimes[i] 
                  << std::setw(15) << quickTimes[i] << std::endl;
    }
}

void runNormalMode() {
    std::vector<size_t> sizes = {10, 100, 1000, 10000};  // Tamaños de instancia
    auto instances = generateRandomInstances(sizes);

    MergeSort mergeSort;
    QuickSort quickSort;

    auto mergeTimes = measureTimes(mergeSort, instances);
    auto quickTimes = measureTimes(quickSort, instances);

    printComparisonTable(sizes, mergeTimes, quickTimes);
}

void runDebugMode() {
    auto algo = chooseAlgorithm();
    size_t size = chooseSize();

    std::vector<size_t> sizes = {size};
    auto instances = generateRandomInstances(sizes);
    const auto& instance = instances[0];

    std::cout << "Instancia: " << instance << std::endl;

    Solucion* sol = algo->Solve(instance);
    std::cout << "Solución: " << *dynamic_cast<SolucionArray*>(sol) << std::endl;

    delete sol;
}

int chooseMode() {
    int mode;
    std::cout << "Elija el modo de ejecución:" << std::endl;
    std::cout << "1. Modo normal (comparación de tiempos)" << std::endl;
    std::cout << "2. Modo debug (mostrar instancia y solución)" << std::endl;
    std::cout << "Opción: ";
    std::cin >> mode;
    return mode;
}

std::unique_ptr<Algoritmo> chooseAlgorithm() {
    int choice;
    std::cout << "Elija el algoritmo:" << std::endl;
    std::cout << "1. Merge Sort" << std::endl;
    std::cout << "2. Quick Sort" << std::endl;
    std::cout << "Opción: ";
    std::cin >> choice;

    if (choice == 1) {
        return std::make_unique<MergeSort>();
    } else if (choice == 2) {
        return std::make_unique<QuickSort>();
    } else {
        std::cout << "Opción inválida, usando Merge Sort por defecto." << std::endl;
        return std::make_unique<MergeSort>();
    }
}

size_t chooseSize() {
    size_t size;
    std::cout << "Ingrese el tamaño de la instancia: ";
    std::cin >> size;
    return size;
}