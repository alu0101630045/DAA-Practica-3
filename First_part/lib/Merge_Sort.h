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

#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "Divide_y_Venceras.h"

class MergeSort : public DivideYVenceras {
  public:
    MergeSort() = default;
    ~MergeSort() override = default;
    bool Small(const Instancia& instancia) const override;
    Solucion* SolveSmall(const Instancia& instancia) const override;
    std::pair<Instancia*, Instancia*> Divide(const Instancia& instancia) const override;
    Solucion* Combine(const Solucion& solucion1, const Solucion& solucion2) const override;
};

#endif  // MERGE_SORT_H