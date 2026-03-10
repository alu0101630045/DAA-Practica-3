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

#include "sorting/Instancia_Array.h"

std::ostream& operator<<(std::ostream& os, const InstanciaArray& instancia) {
    os << "InstanciaArray: [";
    for (size_t i = 0; i < instancia.array_instancia_.size(); ++i) {
        os << instancia.array_instancia_[i] << (i < instancia.array_instancia_.size() - 1 ? ", " : "");
    }
    os << "]";
    return os;
}

