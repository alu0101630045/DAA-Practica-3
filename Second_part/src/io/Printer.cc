/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Diseño y Análisis de Algoritmos 2025-2026
  * Curso: 3º
  * 
  * @author Pablo García de los Reyes
  * @author César Navarro Santos
  * @description: Implementación de la clase Printer
  * @date 07 Mar 2026
  * @version 1.0
  */

#include "io/Printer.h"
#include <iomanip>

void Printer::printInstancia(const InstanciaPlanificacion& instancia) {
    std::cout << "=== Instancia de Planificación ===" << std::endl;
    std::cout << "Número de empleados: " << instancia.get_numero_empleados() << std::endl;
    std::cout << "Número de días: " << instancia.get_numero_dias() << std::endl;
    std::cout << "Día de comienzo: " << instancia.get_dia_comienzo() << std::endl;
    std::cout << std::endl;

    std::cout << "Turnos:" << std::endl;
    auto turnos = instancia.get_turnos();
    for (size_t i = 0; i < turnos.size(); ++i) {
        std::cout << "  " << i << ": " << turnos[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Empleados:" << std::endl;
    auto empleados = instancia.get_empleados();
    auto dias_libres = instancia.get_dias_libres();
    for (size_t i = 0; i < empleados.size(); ++i) {
        std::cout << "  " << i << ": " << empleados[i] << " (Días libres: " << dias_libres[i] << ")" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Matriz de turnos requeridos (día x turno):" << std::endl;
    auto matriz_turnos = instancia.get_matriz_turnos();
    for (int dia = 0; dia < instancia.get_numero_dias(); ++dia) {
        std::cout << "  Día " << dia << ": ";
        for (int turno = 0; turno < (int)turnos.size(); ++turno) {
            std::cout << matriz_turnos[dia][turno] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Matriz de satisfacción (empleado x día x turno) - Muestra algunos valores:" << std::endl;
    auto matriz_sat = instancia.get_matriz_satisfaccion();
    for (int emp = 0; emp < std::min(5, instancia.get_numero_empleados()); ++emp) {
        std::cout << "  Empleado " << emp << ":" << std::endl;
        for (int dia = 0; dia < std::min(3, instancia.get_numero_dias()); ++dia) {
            std::cout << "    Día " << dia << ": ";
            for (int turno = 0; turno < (int)turnos.size(); ++turno) {
                std::cout << matriz_sat[emp][dia][turno] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

void Printer::printSolucion(const InstanciaPlanificacion& instancia, const SolucionPlanificacion& solucion) {
    std::cout << "=== Solución de Planificación ===" << std::endl;
    std::cout << "Empleados: " << solucion.get_numero_empleados() << ", Días: " << solucion.get_numero_dias() << std::endl;
    std::cout << std::endl;

    // Tabla de asignaciones
    std::cout << "Asignación de turnos por empleado y día:" << std::endl;
    std::cout << std::setw(15) << "Empleado";
    auto turnos = instancia.get_turnos();
    for (int d = 0; d < solucion.get_numero_dias(); ++d) {
        std::cout << std::setw(4) << "D" + std::to_string(d);
    }
    std::cout << std::endl;

    for (int e = 0; e < solucion.get_numero_empleados(); ++e) {
        std::cout << std::setw(15) << instancia.get_nombre_empleado(e);
        for (int d = 0; d < solucion.get_numero_dias(); ++d) {
            int turno = solucion.get_turno_empleado_dia(e, d);
            if (turno == -1) {
                std::cout << std::setw(4) << "R";  // R de Rest (descanso)
            } else {
                std::cout << std::setw(4) << "T" + std::to_string(turno);
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Verificación de restricciones
    std::cout << "Verificación de restricciones:" << std::endl;
    bool valida = solucion.es_valida(instancia);
    std::cout << "  Solución válida: " << (valida ? "SÍ" : "NO") << std::endl;

    // Días de descanso por empleado
    std::cout << "  Días de descanso por empleado:" << std::endl;
    for (int e = 0; e < solucion.get_numero_empleados(); ++e) {
        int dias_descanso = solucion.contar_dias_descanso(e);
        int dias_requeridos = instancia.get_dias_libres_necesarios(e);
        bool cumple = dias_descanso >= dias_requeridos;
        std::cout << "    " << instancia.get_nombre_empleado(e) << ": " << dias_descanso 
                  << " (requerido: " << dias_requeridos << ") " 
                  << (cumple ? "✓" : "✗") << std::endl;
    }
    std::cout << std::endl;

    // Cobertura de turnos
    std::cout << "  Cobertura de turnos por día:" << std::endl;
    auto matriz_turnos = instancia.get_matriz_turnos();
    for (int d = 0; d < solucion.get_numero_dias(); ++d) {
        std::cout << "    Día " << d << ": ";
        bool todos_cubiertos = true;
        for (int t = 0; t < (int)turnos.size(); ++t) {
            int requeridos = matriz_turnos[d][t];
            int asignados = 0;
            for (int e = 0; e < solucion.get_numero_empleados(); ++e) {
                if (solucion.get_turno_empleado_dia(e, d) == t) {
                    asignados++;
                }
            }
            bool cubierto = asignados >= requeridos;
            if (!cubierto) todos_cubiertos = false;
            std::cout << "T" << t << "(" << asignados << "/" << requeridos << ") ";
        }
        std::cout << (todos_cubiertos ? "✓" : "✗") << std::endl;
    }
    std::cout << std::endl;

    // Función objetivo
    std::cout << "Métricas de la solución:" << std::endl;
    int satisfaccion = solucion.calcular_satisfaccion_total(instancia);
    int turnos_cubiertos = solucion.contar_turnos_cubiertos(instancia);
    int objetivo = solucion.calcular_objetivo(instancia);
    
    std::cout << "  Satisfacción total: " << satisfaccion << std::endl;
    std::cout << "  Turnos cubiertos: " << turnos_cubiertos << " / " 
              << (solucion.get_numero_dias() * (int)turnos.size()) << std::endl;
    std::cout << "  Función objetivo: " << objetivo << std::endl;
    std::cout << "    (Cálculo: " << satisfaccion << " + " << turnos_cubiertos << " * 100 = " << objetivo << ")" << std::endl;
}