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

#include "dyv/Divide_y_Venceras.h"
#include "planificacion/Instancia_Planificación.h"
#include "planificacion/Solucion_Planificacion.h"

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

    bool Small(const Instancia& instancia) const override;
    Solucion* SolveSmall(const Instancia& instancia) const override;
    std::pair<Instancia*, Instancia*> Divide(const Instancia& instancia) const override;
    Solucion* Combine(const Instancia& instancia, const Solucion& solucion1, const Solucion& solucion2) const override;

  private:
    SolucionPlanificacion* GreedyResolveDayRange(const InstanciaPlanificacion& instancia,
                                                  int dia_inicio, int dia_fin) const;
    int GetBestTurno(const InstanciaPlanificacion& instancia,
                     const SolucionPlanificacion& solucion_parcial,
                     int empleado, int dia) const;

    bool CanAssignTurno(const InstanciaPlanificacion& instancia,
                        const SolucionPlanificacion& solucion,
                        int empleado, int dia, int turno,
                        const std::vector<int>& turnos_asignados = std::vector<int>(),
                        const std::vector<int>& max_turnos = std::vector<int>()) const;

    void AdjustRestDays(const InstanciaPlanificacion& instancia,
                        SolucionPlanificacion& solucion) const;

    void CoverMissingShifts(const InstanciaPlanificacion& instancia,
                            SolucionPlanificacion& solucion) const;

    void ImproveGreedySolution(const InstanciaPlanificacion& instancia,
                               SolucionPlanificacion& solucion) const;
};

#endif  // DYV_PLANIFICACION_H
