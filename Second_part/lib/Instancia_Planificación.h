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

#ifndef INSTANCIA_PLANIFICACIÓN_H
#define INSTANCIA_PLANIFICACIÓN_H

#include "Instancia.h"
#include <vector>
#include "json.hpp"

class InstanciaPlanificacion : public Instancia {
  public:
    InstanciaPlanificacion(const std::string json_path);
    InstanciaPlanificacion(const int dia_comienzo, const int numero_dias, const int numero_empleados, const InstanciaPlanificacion& instancia);
    friend std::ostream& operator<<(std::ostream& os, const InstanciaPlanificacion& instancia);
    int get_numero_empleados() const;
    int get_numero_dias() const;
    int get_dia_comienzo() const;
    std::vector<std::string> get_turnos() const;
    std::vector<std::string> get_empleados() const;
    std::vector<int> get_dias_libres() const;
    std::vector<std::vector<std::vector<int>>> get_matriz_satisfaccion() const;
    std::vector<std::vector<int>> get_matriz_turnos() const;
    int get_satisfaccion_empleado_dia(int empleado, int dia, int turno) const;
    int get_empleados_necesarios_dia_turno(int dia, int turno) const;
    int get_dias_libres_necesarios(int empleado) const;
    std::string get_nombre_empleado(int empleado) const;
    std::string get_nombre_turno(int turno) const;

  private:
    std::vector<std::string>* turnos_;
    std::vector<std::string>* empleados_;
    std::vector<int>* dias_libres_;
    std::vector<std::vector<std::vector<int>>>* matriz_satisfaccion_;
    std::vector<std::vector<int>>* matriz_turnos_;
    int dia_comienzo_;
    int numero_dias_;
    int numero_empleados_;
    nlohmann::json json_data_;
};

#endif // INSTANCIA_PLANIFICACIÓN_H