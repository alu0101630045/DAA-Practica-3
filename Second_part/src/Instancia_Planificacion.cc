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

#include "../lib/Instancia_Planificación.h"

#include <fstream>

InstanciaPlanificacion::InstanciaPlanificacion(const std::string json_path) {
    std::ifstream file(json_path);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo JSON: " + json_path);
    }
    json_data_ = nlohmann::json::parse(file);

    // Parse shifts
    turnos_ = new std::vector<std::string>();
    for (const auto& shift : json_data_["shifts"]) {
        turnos_->push_back(shift);
    }

    // Parse employees
    empleados_ = new std::vector<std::string>();
    dias_libres_ = new std::vector<int>();
    for (const auto& emp : json_data_["employees"]) {
        empleados_->push_back(emp["name"]);
        dias_libres_->push_back(emp["freeDays"]);
    }

    numero_empleados_ = empleados_->size();
    numero_dias_ = json_data_["planningHorizon"];
    dia_comienzo_ = 0; // Assuming starts from day 0

    int numero_turnos = turnos_->size();

    // Initialize matriz_satisfaccion_
    matriz_satisfaccion_ = new std::vector<std::vector<std::vector<int>>>(numero_empleados_, std::vector<std::vector<int>>(numero_dias_, std::vector<int>(numero_turnos, 0)));

    // Fill matriz_satisfaccion_
    for (const auto& sat : json_data_["satisfaction"]) {
        int emp = sat["employee"];
        int day = sat["day"];
        int shift = sat["shift"];
        int value = sat["value"];
        (*matriz_satisfaccion_)[emp][day][shift] = value;
    }

    // Initialize matriz_turnos_
    matriz_turnos_ = new std::vector<std::vector<int>>(numero_dias_, std::vector<int>(numero_turnos, 0));

    // Fill matriz_turnos_
    for (const auto& req : json_data_["requiredEmployees"]) {
        int day = req["day"];
        int shift = req["shift"];
        int value = req["value"];
        (*matriz_turnos_)[day][shift] = value;
    }
}

InstanciaPlanificacion::InstanciaPlanificacion(const int dia_comienzo, const int numero_dias, const int numero_empleados, const InstanciaPlanificacion& instancia) {
    // Constructor para crear una subinstancia de un rango de días
    numero_empleados_ = numero_empleados;
    numero_dias_ = numero_dias;
    dia_comienzo_ = dia_comienzo;

    // Copy shared data
    turnos_ = new std::vector<std::string>(*instancia.turnos_);
    empleados_ = new std::vector<std::string>(*instancia.empleados_);
    dias_libres_ = new std::vector<int>(*instancia.dias_libres_);

    int numero_turnos = turnos_->size();

    // Create submatrices for the range of days
    matriz_satisfaccion_ = new std::vector<std::vector<std::vector<int>>>(numero_empleados_, std::vector<std::vector<int>>(numero_dias_, std::vector<int>(numero_turnos, 0)));
    
    auto original_sat = instancia.get_matriz_satisfaccion();
    for (int e = 0; e < numero_empleados_; ++e) {
        for (int d = 0; d < numero_dias_; ++d) {
            for (int t = 0; t < numero_turnos; ++t) {
                (*matriz_satisfaccion_)[e][d][t] = original_sat[e][dia_comienzo + d][t];
            }
        }
    }

    matriz_turnos_ = new std::vector<std::vector<int>>(numero_dias_, std::vector<int>(numero_turnos, 0));
    auto original_turnos = instancia.get_matriz_turnos();
    for (int d = 0; d < numero_dias_; ++d) {
        for (int t = 0; t < numero_turnos; ++t) {
            (*matriz_turnos_)[d][t] = original_turnos[dia_comienzo + d][t];
        }
    }

    json_data_ = nlohmann::json();  // Empty JSON for subinstances
}

int InstanciaPlanificacion::get_numero_empleados() const {
    return numero_empleados_;
}

int InstanciaPlanificacion::get_numero_dias() const {
    return numero_dias_;
}

int InstanciaPlanificacion::get_dia_comienzo() const {
    return dia_comienzo_;
}

std::vector<std::string> InstanciaPlanificacion::get_turnos() const {
    return *turnos_;
}

std::vector<std::string> InstanciaPlanificacion::get_empleados() const {
    return *empleados_;
}

std::vector<int> InstanciaPlanificacion::get_dias_libres() const {
    return *dias_libres_;
}

std::vector<std::vector<std::vector<int>>> InstanciaPlanificacion::get_matriz_satisfaccion() const {
    return *matriz_satisfaccion_;
}

std::vector<std::vector<int>> InstanciaPlanificacion::get_matriz_turnos() const {
    return *matriz_turnos_;
}

int InstanciaPlanificacion::get_satisfaccion_empleado_dia(int empleado, int dia, int turno) const {
    return (*matriz_satisfaccion_)[empleado][dia][turno];
}

int InstanciaPlanificacion::get_empleados_necesarios_dia_turno(int dia, int turno) const {
    return (*matriz_turnos_)[dia][turno];
}

int InstanciaPlanificacion::get_dias_libres_necesarios(int empleado) const {
    return (*dias_libres_)[empleado];
}

std::string InstanciaPlanificacion::get_nombre_empleado(int empleado) const {
    return (*empleados_)[empleado];
}

std::string InstanciaPlanificacion::get_nombre_turno(int turno) const {
    return (*turnos_)[turno];
}