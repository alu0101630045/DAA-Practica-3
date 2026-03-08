/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Diseño y Análisis de Algoritmos 2025-2026
  * Curso: 3º
  * 
  * @author Pablo García de los Reyes
  * @author César Navarro Santos
  * @description: Clase para representar una solución del problema de planificación
  * @date 07 Mar 2026
  * @version 1.0
  */

#ifndef SOLUCION_PLANIFICACION_H
#define SOLUCION_PLANIFICACION_H

#include "Solucion.h"
#include "Instancia_Planificación.h"
#include <vector>
#include <iostream>

/**
 * @class SolucionPlanificacion
 * @brief Representa una asignación de turnos para los empleados en el horizonte de planificación
 * 
 * Almacena la asignación de turnos para cada empleado en cada día,
 * y proporciona métodos para evaluar la calidad de la solución.
 */
class SolucionPlanificacion : public Solucion {
  public:
    /**
     * @brief Constructor que crea una solución vacía
     * @param numero_empleados Número de empleados
     * @param numero_dias Número de días
     */
    SolucionPlanificacion(int numero_empleados, int numero_dias);

    /**
     * @brief Constructor de copia
     */
    SolucionPlanificacion(const SolucionPlanificacion& otra);

    /**
     * @brief Destructora
     */
    ~SolucionPlanificacion() override;

    /**
     * @brief Obtiene el turno asignado a un empleado en un día
     * @param empleado Índice del empleado
     * @param dia Índice del día
     * @return Índice del turno, o -1 si no tiene asignado
     */
    int get_turno_empleado_dia(int empleado, int dia) const;

    /**
     * @brief Asigna un turno a un empleado en un día
     * @param empleado Índice del empleado
     * @param dia Índice del día
     * @param turno Índice del turno (-1 para sin asignar)
     */
    void set_turno_empleado_dia(int empleado, int dia, int turno);

    /**
     * @brief Calcula la satisfacción total de la solución
     * @param instancia La instancia del problema
     * @return Suma de satisfacciones
     */
    int calcular_satisfaccion_total(const InstanciaPlanificacion& instancia) const;

    /**
     * @brief Cuenta cuántos turnos están cubiertos (cumplen requisito mínimo)
     * @param instancia La instancia del problema
     * @return Número de turnos cubiertos
     */
    int contar_turnos_cubiertos(const InstanciaPlanificacion& instancia) const;

    /**
     * @brief Calcula la función objetivo
     * f(x) = SUMA(satisfaccion) + SUMA(turnos_cubiertos) * 100
     * @param instancia La instancia del problema
     * @return Valor de la función objetivo
     */
    int calcular_objetivo(const InstanciaPlanificacion& instancia) const;

    /**
     * @brief Verifica si la solución es válida (cumple restricciones duras)
     * @param instancia La instancia del problema
     * @return true si es válida, false en caso contrario
     */
    bool es_valida(const InstanciaPlanificacion& instancia) const;

    /**
     * @brief Cuenta los días de descanso de un empleado
     * @param empleado Índice del empleado
     * @return Número de días sin turnos asignados
     */
    int contar_dias_descanso(int empleado) const;

    /**
     * @brief Obtiene la matriz de asignación (empleado x día -> turno)
     * @return Referencia const a la matriz
     */
    const std::vector<std::vector<int>>& get_asignacion() const;

    /**
     * @brief Obtiene el número de empleados
     */
    int get_numero_empleados() const;

    /**
     * @brief Obtiene el número de días
     */
    int get_numero_dias() const;

  private:
    std::vector<std::vector<int>> asignacion_;  // asignacion_[empleado][dia] = turno (-1 si no asignado)
    int numero_empleados_;
    int numero_dias_;
};

#endif  // SOLUCION_PLANIFICACION_H
