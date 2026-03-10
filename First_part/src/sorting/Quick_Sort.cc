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

#include "sorting/Quick_Sort.h"
#include <algorithm>

bool QuickSort::Small(const Instancia& instancia) const {
    const InstanciaArray& instancia_array = dynamic_cast<const InstanciaArray&>(instancia);
    return instancia_array.get_instance().size() <= 2;
}

Solucion* QuickSort::SolveSmall(const Instancia& instancia) const {
    const InstanciaArray& instancia_array = dynamic_cast<const InstanciaArray&>(instancia);
    std::vector<int> sorted = instancia_array.get_instance();
    std::sort(sorted.begin(), sorted.end());
    return new SolucionArray(sorted);
}

std::pair<Instancia*, Instancia*> QuickSort::Divide(const Instancia& instancia) const {
    const InstanciaArray& instancia_array = dynamic_cast<const InstanciaArray&>(instancia);
    const std::vector<int>& secuencia = instancia_array.get_instance();
    int pivot = secuencia[0];
    std::vector<int> left, right;
    for (size_t i = 0; i < secuencia.size(); ++i) {
        if (i == 0) continue; 
        int num = secuencia[i];
        if (num <= pivot) {
            left.push_back(num);
        } else {
            right.push_back(num);
        }
    }

    // Colocar el pivote en la derecha evita particiones de tamaño n en casos extremos.
    right.push_back(pivot);
    return {new InstanciaArray(left), new InstanciaArray(right)};
}

Solucion* QuickSort::Combine(const Solucion& solucion1, const Solucion& solucion2) const {
    const SolucionArray& sol1 = dynamic_cast<const SolucionArray&>(solucion1);
    const SolucionArray& sol2 = dynamic_cast<const SolucionArray&>(solucion2);
    const std::vector<int>& left = sol1.get_solution();
    const std::vector<int>& right = sol2.get_solution();
    std::vector<int> combined;
    combined.reserve(left.size() + right.size());
    combined.insert(combined.end(), left.begin(), left.end());
    combined.insert(combined.end(), right.begin(), right.end());
    return new SolucionArray(combined);
}