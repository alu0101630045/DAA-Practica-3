/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Diseño y Análisis de Algoritmos 2025-2026
  * Curso: 3º
  * 
  * @author Pablo García de los Reyes
  * @author César Navarro Santos
  * @description: Clase para imprimir instancias de planificación de forma legible
  * @date 07 Mar 2026
  * @version 1.0
  */

#ifndef PRINTER_H
#define PRINTER_H

#include "Instancia_Planificación.h"
#include "Solucion_Planificacion.h"
#include <iostream>

class Printer {
  public:
    static void printInstancia(const InstanciaPlanificacion& instancia);
    static void printSolucion(const InstanciaPlanificacion& instancia, const SolucionPlanificacion& solucion);
};

#endif // PRINTER_H