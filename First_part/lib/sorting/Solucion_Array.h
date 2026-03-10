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

#ifndef SOLUCION_ARRAY_H
#define SOLUCION_ARRAY_H

#include "base/Solucion.h"
#include <vector>

class SolucionArray : public Solucion {
  public:
    SolucionArray(const std::vector<int>& solucion) : solucion_(solucion) {}
    const std::vector<int>& get_solution() const { return solucion_; }
    friend std::ostream& operator<<(std::ostream& os, const SolucionArray& solucion);

  private:
    std::vector<int> solucion_;
};

#endif  // SOLUCION_ARRAY_H