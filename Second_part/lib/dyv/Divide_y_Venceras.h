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

#ifndef DIVIDE_Y_VENCERAS_H
#define DIVIDE_Y_VENCERAS_H

#include "base/Algoritmo.h"

#include <iostream>
#include <vector>

class DivideYVenceras : public Algoritmo {
  public:
    DivideYVenceras() = default;
    ~DivideYVenceras() override = default;
    Solucion* Solve(const Instancia& instancia) override;
    virtual bool Small(const Instancia& instancia) const = 0;
    virtual Solucion* SolveSmall(const Instancia& instancia) const = 0;
    virtual std::pair<Instancia*, Instancia*> Divide(const Instancia& instancia) const = 0;
    virtual Solucion* Combine(const Instancia& instancia,
                              const Solucion& solucion1,
                              const Solucion& solucion2) const = 0;
};

#endif  // DIVIDE_Y_VENCERAS_H