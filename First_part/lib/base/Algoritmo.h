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

#ifndef ALGORITMO_H
#define ALGORITMO_H

#include <iostream>

#include "base/Instancia.h"
#include "base/Solucion.h"
#include "sorting/Instancia_Array.h"
#include "sorting/Solucion_Array.h"

class Algoritmo {
  public:
    virtual ~Algoritmo() = 0;
    virtual Solucion* Solve(const Instancia& instancia) = 0;
};

#endif  // ALGORITMO_H