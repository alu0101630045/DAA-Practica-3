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

#include "sorting/Solucion_Array.h"

std::ostream& operator<<(std::ostream& os, const SolucionArray& solucion) {
    os << "SolucionArray: [";
    for (size_t i = 0; i < solucion.solucion_.size(); ++i) {
        os << solucion.solucion_[i] << (i < solucion.solucion_.size() - 1 ? ", " : "");
    }
    os << "]";
    return os;
}

