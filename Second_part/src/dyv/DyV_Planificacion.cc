/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Diseño y Análisis de Algoritmos 2025-2026
  * Curso: 3º
  * 
  * @author Pablo García de los Reyes
  * @author César Navarro Santos
  * @description: Implementación del algoritmo Divide y Vencerás para planificación
  * @date 07 Mar 2026
  * @version 1.0
  */

#include "dyv/DyV_Planificacion.h"
#include <algorithm>
#include <climits>

bool DyVPlanificacion::Small(const Instancia& instancia) const {
    const auto* inst_plan = dynamic_cast<const InstanciaPlanificacion*>(&instancia);
    if (!inst_plan) return true;
    return inst_plan->get_numero_dias() <= 1;
}

Solucion* DyVPlanificacion::SolveSmall(const Instancia& instancia) const {
    const auto* inst_plan = dynamic_cast<const InstanciaPlanificacion*>(&instancia);
    if (!inst_plan) return nullptr;

    int num_empleados = inst_plan->get_numero_empleados();
    int num_dias = inst_plan->get_numero_dias();

    // Por si llega una instancia de 0 días
    if (num_dias <= 0) {
        return new SolucionPlanificacion(num_empleados, 0);
    }

    // Como Small() garantiza que num_dias es 1, creamos la solución para 1 día
    SolucionPlanificacion* solucion = new SolucionPlanificacion(num_empleados, 1);
    
    // Solo tenemos que resolver el día 0 de esta subinstancia
    int dia_relativo = 0; 
    int num_turnos = inst_plan->get_turnos().size();

    // Iteramos por los turnos de ese día
    for (int turno = 0; turno < num_turnos; ++turno) {
        int requeridos = inst_plan->get_empleados_necesarios_dia_turno(dia_relativo, turno);
        
        std::vector<std::pair<int, int>> candidatos;  // {satisfacción, empleado}
        
        // Recolectar candidatos disponibles
        for (int emp = 0; emp < num_empleados; ++emp) {
            // Un empleado es candidato solo si no tiene ya un turno asignado en este día
            if (solucion->get_turno_empleado_dia(emp, dia_relativo) == -1) {
                int satisfaccion = inst_plan->get_satisfaccion_empleado_dia(emp, dia_relativo, turno);
                candidatos.push_back({satisfaccion, emp});
            }
        }
        
        // Ordenar candidatos por satisfacción de mayor a menor
        std::sort(candidatos.rbegin(), candidatos.rend());
        
        // Asignar el turno a los n mejores candidatos hasta cubrir la demanda
        for (int i = 0; i < std::min(requeridos, (int)candidatos.size()); ++i) {
            int emp = candidatos[i].second;
            solucion->set_turno_empleado_dia(emp, dia_relativo, turno);
        }
    }

    return solucion;
}

std::pair<Instancia*, Instancia*> DyVPlanificacion::Divide(const Instancia& instancia) const {
    const auto* inst_plan = dynamic_cast<const InstanciaPlanificacion*>(&instancia);
    if (!inst_plan) return {nullptr, nullptr};

    int total_dias = inst_plan->get_numero_dias();
    int medio = total_dias / 2;

    // Crear subinstancias (solo cambia el rango de días)
    auto* inst1 = new InstanciaPlanificacion(0, medio, inst_plan->get_numero_empleados(), *inst_plan);
    auto* inst2 = new InstanciaPlanificacion(medio, total_dias - medio, inst_plan->get_numero_empleados(), *inst_plan);

    return {inst1, inst2};
}

Solucion* DyVPlanificacion::Combine(const Instancia& instancia, const Solucion& solucion1, const Solucion& solucion2) const {
    const auto* inst_plan = dynamic_cast<const InstanciaPlanificacion*>(&instancia);
    const auto* sol1 = dynamic_cast<const SolucionPlanificacion*>(&solucion1);
    const auto* sol2 = dynamic_cast<const SolucionPlanificacion*>(&solucion2);
    
    if (!inst_plan || !sol1 || !sol2) return nullptr;

    // Creamos una solución de tamaño sol1 + sol2
    SolucionPlanificacion* solucion_combinada = new SolucionPlanificacion(sol1->get_numero_empleados(), sol1->get_numero_dias() + sol2->get_numero_dias());

    // Copiar primera mitad
    for (int e = 0; e < sol1->get_numero_empleados(); ++e) {
        for (int d = 0; d < sol1->get_numero_dias(); ++d) {
            solucion_combinada->set_turno_empleado_dia(e, d, sol1->get_turno_empleado_dia(e, d));
        }
    }

    // Copiar segunda mitad
    for (int e = 0; e < sol2->get_numero_empleados(); ++e) {
        for (int d = 0; d < sol2->get_numero_dias(); ++d) {
            int turno = sol2->get_turno_empleado_dia(e, d);
            solucion_combinada->set_turno_empleado_dia(e, sol1->get_numero_dias() + d, turno);
        }
    }

    // Ajuste global en cada combinación
    AdjustRestDays(*inst_plan, *solucion_combinada);
    CoverMissingShifts(*inst_plan, *solucion_combinada);

    return solucion_combinada;
}

void DyVPlanificacion::AdjustRestDays(const InstanciaPlanificacion& instancia, SolucionPlanificacion& solucion) const {
    int num_empleados = instancia.get_numero_empleados();
    int num_dias = solucion.get_numero_dias();

    for (int emp = 0; emp < num_empleados; ++emp) {
        int dias_necesarios = instancia.get_dias_libres_necesarios(emp);
        int dias_descanso = solucion.contar_dias_descanso(emp);

        // Si tiene más descanso del necesario, no hay problema
        if (dias_descanso >= dias_necesarios) {
            continue;
        }

        // Si tiene menos, quitar turnos hasta tener suficientes días de descanso
        int deficit = dias_necesarios - dias_descanso;
        int removidos = 0;


        // Si aún falta, quitar turnos incluso si deja turnos sin cubrir (prioridad a días de descanso)
        for (int dia = 0; dia < num_dias && removidos < deficit; ++dia) {
            if (solucion.get_turno_empleado_dia(emp, dia) != -1) {
                solucion.set_turno_empleado_dia(emp, dia, -1);
                removidos++;
            }
        }
    }
}

void DyVPlanificacion::CoverMissingShifts(const InstanciaPlanificacion& instancia, SolucionPlanificacion& solucion) const {
    int num_empleados = instancia.get_numero_empleados();
    int num_dias = solucion.get_numero_dias();
    int num_turnos = instancia.get_turnos().size();

    // Para cada día y turno, verificar si falta cobertura
    for (int d = 0; d < num_dias; ++d) {
        for (int t = 0; t < num_turnos; ++t) {
            int requeridos = instancia.get_empleados_necesarios_dia_turno(d, t);
            int asignados = 0;
            for (int e = 0; e < num_empleados; ++e) {
                if (solucion.get_turno_empleado_dia(e, d) == t) {
                    asignados++;
                }
            }

            int faltan = requeridos - asignados;
            if (faltan <= 0) continue;

            // Encontrar empleados disponibles para este turno
            std::vector<std::pair<int, int>> candidatos;  // {satisfacción, empleado}
            for (int e = 0; e < num_empleados; ++e) {
                if (solucion.get_turno_empleado_dia(e, d) == -1) {  // Día libre
                    // Verificar que asignar no viole días de descanso
                    int dias_descanso_actual = solucion.contar_dias_descanso(e);
                    int dias_requeridos = instancia.get_dias_libres_necesarios(e);
                    if (dias_descanso_actual > dias_requeridos) {  // Tiene días extra
                        int satisfaccion = instancia.get_satisfaccion_empleado_dia(e, d, t);
                        candidatos.push_back({satisfaccion, e});
                    }
                }
            }

            // Ordenar por satisfacción descendente
            std::sort(candidatos.rbegin(), candidatos.rend());

            // Asignar los mejores candidatos
            for (int i = 0; i < std::min(faltan, (int)candidatos.size()); ++i) {
                int e = candidatos[i].second;
                solucion.set_turno_empleado_dia(e, d, t);
            }
        }
    }
}