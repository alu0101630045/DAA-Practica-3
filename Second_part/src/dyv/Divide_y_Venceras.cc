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

#include "dyv/Divide_y_Venceras.h"

Solucion* DivideYVenceras::Solve(const Instancia& instancia) {
    if (Small(instancia)) {
        return SolveSmall(instancia);
    }
    auto [instancia1, instancia2] = Divide(instancia);
    Solucion* solucion1 = Solve(*instancia1);
    Solucion* solucion2 = Solve(*instancia2);
    Solucion* solucion_combinada = Combine(instancia, *solucion1, *solucion2);
    delete instancia1;
    delete instancia2;
    delete solucion1;
    delete solucion2;
    return solucion_combinada;
}