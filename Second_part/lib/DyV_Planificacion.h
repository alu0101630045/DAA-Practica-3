/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Diseño y Análisis de Algoritmos 2025-2026
  * Curso: 3º
  * 
  * @author Pablo García de los Reyes
  * @author César Navarro Santos
  * @description: Algoritmo Divide y Vencerás para el problema de planificación
  * @date 07 Mar 2026
  * @version 1.0
  */

#ifndef DYV_PLANIFICACION_H
#define DYV_PLANIFICACION_H

#include "Divide_y_Venceras.h"
#include "Instancia_Planificación.h"
#include "Solucion_Planificacion.h"

/**
 * @class DyVPlanificacion
 * @brief Implementa un algoritmo Divide y Vencerás para resolver el problema de planificación
 * 
 * El algoritmo divide el horizonte de planificación binariamente por días,
 * resuelve subproblemas pequeños con un algoritmo voraz,
 * y combina las soluciones considerando restricciones globales.
 */
class DyVPlanificacion : public DivideYVenceras {
  public:
    DyVPlanificacion() = default;
    ~DyVPlanificacion() override = default;

    /**
     * @brief Resuelve el problema completo y post-procesa la solución
     */
    Solucion* Solve(const Instancia& instancia) override;

    /**
     * @brief Determina si una instancia es "pequeña" (1 día)
     */
    bool Small(const Instancia& instancia) const override;

    /**
     * @brief Resuelve una instancia pequeña usando algoritmo voraz
     */
    Solucion* SolveSmall(const Instancia& instancia) const override;

    /**
     * @brief Divide una instancia en dos subproblemas binarios por días
     */
    std::pair<Instancia*, Instancia*> Divide(const Instancia& instancia) const override;

    /**
     * @brief Combina dos soluciones de subproblemas
     */
    Solucion* Combine(const Solucion& solucion1, const Solucion& solucion2) const override;

  private:
    /**
     * @brief Algoritmo voraz para resolver un día
     * Asigna turnos a los empleados maximizando satisfacción mientras respeta requisitos
     */
    SolucionPlanificacion* GreedyResolveDayRange(const InstanciaPlanificacion& instancia,
                                                  int dia_inicio, int dia_fin) const;

    /**
     * @brief Obtiene el mejor turno para un empleado en un día (algoritmo voraz)
     */
    int GetBestTurno(const InstanciaPlanificacion& instancia,
                     const SolucionPlanificacion& solucion_parcial,
                     int empleado, int dia) const;

    /**
     * @brief Verifica si un turno puede ser asignado a un empleado
     */
    bool CanAssignTurno(const InstanciaPlanificacion& instancia,
                        const SolucionPlanificacion& solucion,
                        int empleado, int dia, int turno,
                        const std::vector<int>& turnos_asignados = std::vector<int>(),
                        const std::vector<int>& max_turnos = std::vector<int>()) const;

    /**
     * @brief Ajusta una solución para satisfacer restricciones de días de descanso
     */
    void AdjustRestDays(const InstanciaPlanificacion& instancia,
                        SolucionPlanificacion& solucion) const;

    /**
     * @brief Intenta cubrir turnos faltantes sin violar días de descanso
     */
    void CoverMissingShifts(const InstanciaPlanificacion& instancia,
                            SolucionPlanificacion& solucion) const;

    /**
     * @brief Heurística para mejorar una solución
     */
    void ImproveGreedySolution(const InstanciaPlanificacion& instancia,
                               SolucionPlanificacion& solucion) const;
};

#endif  // DYV_PLANIFICACION_H
