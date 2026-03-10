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

#include "sorting/Merge_Sort.h"
#include <algorithm>

bool MergeSort::Small(const Instancia& instancia) const {
    const InstanciaArray& instancia_array = dynamic_cast<const InstanciaArray&>(instancia);
    return instancia_array.get_instance().size() <= 1;
}

Solucion* MergeSort::SolveSmall(const Instancia& instancia) const {
    const InstanciaArray& instancia_array = dynamic_cast<const InstanciaArray&>(instancia);
    std::vector<int> sorted = instancia_array.get_instance();
    std::sort(sorted.begin(), sorted.end());
    return new SolucionArray(sorted);
}

std::pair<Instancia*, Instancia*> MergeSort::Divide(const Instancia& instancia) const {
    const InstanciaArray& instancia_array = dynamic_cast<const InstanciaArray&>(instancia);
    const std::vector<int>& secuencia = instancia_array.get_instance();
    size_t mid = secuencia.size() / 2;
    std::vector<int> left(secuencia.begin(), secuencia.begin() + mid);
    std::vector<int> right(secuencia.begin() + mid, secuencia.end());
    return {new InstanciaArray(left), new InstanciaArray(right)};
}

Solucion* MergeSort::Combine(const Solucion& solucion1, const Solucion& solucion2) const {
    const SolucionArray& sol1 = dynamic_cast<const SolucionArray&>(solucion1);
    const SolucionArray& sol2 = dynamic_cast<const SolucionArray&>(solucion2);
    const std::vector<int>& left = sol1.get_solution();
    const std::vector<int>& right = sol2.get_solution();
    std::vector<int> merged;
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            merged.push_back(left[i++]);
        } else {
            merged.push_back(right[j++]);
        }
    }
    while (i < left.size()) {
        merged.push_back(left[i++]);
    }
    while (j < right.size()) {
        merged.push_back(right[j++]);
    }
    return new SolucionArray(merged);
}

