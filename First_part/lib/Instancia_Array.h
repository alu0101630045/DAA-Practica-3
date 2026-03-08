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

#ifndef INSTANCIA_ARRAY_H
#define INSTANCIA_ARRAY_H

#include "Instancia.h"
#include <vector>
#include <iostream>
#include <string>

class InstanciaArray : public Instancia {
  public:
    InstanciaArray(const std::vector<int>& array_instancia) : array_instancia_(array_instancia) {}
    const std::vector<int>& get_instance() const { return array_instancia_; }
    friend std::ostream& operator<<(std::ostream& os, const InstanciaArray& instancia);

  private:
    std::vector<int> array_instancia_;
};

#endif  // INSTANCIA_ARRAY_H