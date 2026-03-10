/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Diseño y Análisis de Algoritmos 2025-2026
  * Curso: 3º
  * 
  * @author Pablo García de los Reyes
  * @author César Navarro Santos
  * @description: Funciones para la práctica 3 de DAA
  * @date 07 Mar 2026
  * @version 1.0
  */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "sorting/Instancia_Array.h"
#include "sorting/Solucion_Array.h"
#include "sorting/Merge_Sort.h"
#include "sorting/Quick_Sort.h"
#include <vector>
#include <memory>
#include <iostream>

// Genera instancias aleatorias de los tamaños especificados
std::vector<InstanciaArray> generateRandomInstances(const std::vector<size_t>& sizes);

// Mide los tiempos de ejecución de un algoritmo para varias instancias
std::vector<double> measureTimes(Algoritmo& algo, const std::vector<InstanciaArray>& instances);

// Imprime la tabla de comparación de tiempos
void printComparisonTable(const std::vector<size_t>& sizes, const std::vector<double>& mergeTimes, const std::vector<double>& quickTimes);

// Ejecuta el modo normal: genera instancias, mide tiempos, muestra tabla
void runNormalMode();

// Ejecuta el modo debug: pide algoritmo y tamaño, muestra instancia y solución
void runDebugMode();

// Pide al usuario que elija el modo de ejecución
int chooseMode();

// Pide al usuario que elija el algoritmo
std::unique_ptr<Algoritmo> chooseAlgorithm();

// Pide al usuario el tamaño de la instancia para debug
size_t chooseSize();

#endif  // FUNCTIONS_H