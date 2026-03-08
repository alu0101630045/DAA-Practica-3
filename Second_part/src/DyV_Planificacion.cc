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

#include "../lib/DyV_Planificacion.h"
#include <algorithm>
#include <climits>

Solucion* DyVPlanificacion::Solve(const Instancia& instancia) {
    // Llamar al algoritmo DyV base
    Solucion* solucion_dyv = DivideYVenceras::Solve(instancia);
    
    // Post-procesar la solución para mejorar restricciones
    auto* sol_plan = dynamic_cast<SolucionPlanificacion*>(solucion_dyv);
    const auto* inst_plan = dynamic_cast<const InstanciaPlanificacion*>(&instancia);
    
    if (sol_plan && inst_plan) {
        // Aplicar ajustes de días libres y mejoras
        AdjustRestDays(*inst_plan, *sol_plan);
        ImproveGreedySolution(*inst_plan, *sol_plan);
    }
    
    return solucion_dyv;
}

bool DyVPlanificacion::Small(const Instancia& instancia) const {
    const auto* inst_plan = dynamic_cast<const InstanciaPlanificacion*>(&instancia);
    if (!inst_plan) return true;
    return inst_plan->get_numero_dias() <= 1;
}

Solucion* DyVPlanificacion::SolveSmall(const Instancia& instancia) const {
    const auto* inst_plan = dynamic_cast<const InstanciaPlanificacion*>(&instancia);
    if (!inst_plan) return nullptr;

    // Para una instancia pequeña (1 día), simplemente asignar turnos sin considerar días libres globales
    // Los días libres se resolverán cuando se combinen las soluciones
    SolucionPlanificacion* solucion = GreedyResolveDayRange(*inst_plan, 0, inst_plan->get_numero_dias() - 1);
    // No aplicamos AdjustRestDays aquí porque para subproblemas de 1 día es demasiado restrictivo
    
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

Solucion* DyVPlanificacion::Combine(const Solucion& solucion1, const Solucion& solucion2) const {
    const auto* sol1 = dynamic_cast<const SolucionPlanificacion*>(&solucion1);
    const auto* sol2 = dynamic_cast<const SolucionPlanificacion*>(&solucion2);
    
    if (!sol1 || !sol2) return nullptr;

    // La combinación es simple: concatenar las asignaciones
    SolucionPlanificacion* solucion_combinada = new SolucionPlanificacion(sol1->get_numero_empleados(),
                                                                            sol1->get_numero_dias() + sol2->get_numero_dias());

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

    return solucion_combinada;
}

SolucionPlanificacion* DyVPlanificacion::GreedyResolveDayRange(const InstanciaPlanificacion& instancia,
                                                                 int dia_inicio, int dia_fin) const {
    int num_empleados = instancia.get_numero_empleados();
    int num_dias = dia_fin - dia_inicio + 1;
    
    SolucionPlanificacion* solucion = new SolucionPlanificacion(num_empleados, num_dias);

    // Calcular máximo turnos por empleado para respetar días libres aproximadamente
    std::vector<int> max_turnos(num_empleados);
    std::vector<int> turnos_asignados(num_empleados, 0);
    int total_dias = instancia.get_numero_dias();
    
    for (int emp = 0; emp < num_empleados; ++emp) {
        int dias_libres_necesarios = instancia.get_dias_libres_necesarios(emp);
        int dias_libres_en_rango = (dias_libres_necesarios * num_dias + total_dias - 1) / total_dias;  // ceil
        max_turnos[emp] = num_dias - dias_libres_en_rango;
        if (max_turnos[emp] < 0) max_turnos[emp] = 0;
    }

    // Para cada día, asignar turnos de manera voraz
    for (int dia_relativo = 0; dia_relativo < num_dias; ++dia_relativo) {
        int num_turnos = instancia.get_turnos().size();
        
        // Para cada turno, asignar empleados de manera voraz maximizando satisfacción
        for (int turno = 0; turno < num_turnos; ++turno) {
            int requeridos = instancia.get_empleados_necesarios_dia_turno(dia_relativo, turno);
            
            // Encontrar los mejores empleados para este turno
            std::vector<std::pair<int, int>> candidatos;  // {satisfacción, empleado}
            
            for (int emp = 0; emp < num_empleados; ++emp) {
                if (CanAssignTurno(instancia, *solucion, emp, dia_relativo, turno, turnos_asignados, max_turnos)) {
                    int satisfaccion = instancia.get_satisfaccion_empleado_dia(emp, dia_relativo, turno);
                    candidatos.push_back({satisfaccion, emp});
                }
            }
            
            // Ordenar por satisfacción descendente
            std::sort(candidatos.rbegin(), candidatos.rend());
            
            // Asignar los mejores candidatos
            for (int i = 0; i < std::min(requeridos, (int)candidatos.size()); ++i) {
                int emp = candidatos[i].second;
                solucion->set_turno_empleado_dia(emp, dia_relativo, turno);
                turnos_asignados[emp]++;
            }
        }
    }

    return solucion;
}

bool DyVPlanificacion::CanAssignTurno(const InstanciaPlanificacion& instancia,
                                      const SolucionPlanificacion& solucion,
                                      int empleado, int dia, int turno,
                                      const std::vector<int>& turnos_asignados,
                                      const std::vector<int>& max_turnos) const {
    // Un empleado ya tiene turno asignado este día
    if (solucion.get_turno_empleado_dia(empleado, dia) != -1) {
        return false;
    }

    // Verificar límite de turnos para respetar días libres
    if (!max_turnos.empty() && !turnos_asignados.empty() && 
        turnos_asignados[empleado] >= max_turnos[empleado]) {
        return false;
    }

    return true;
}

void DyVPlanificacion::AdjustRestDays(const InstanciaPlanificacion& instancia,
                                       SolucionPlanificacion& solucion) const {
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

        // Primero intentar quitar turnos donde hay exceso de asignados
        for (int dia = 0; dia < num_dias && removidos < deficit; ++dia) {
            if (solucion.get_turno_empleado_dia(emp, dia) != -1) {
                int turno = solucion.get_turno_empleado_dia(emp, dia);
                
                int asignados = 0;
                for (int e = 0; e < num_empleados; ++e) {
                    if (solucion.get_turno_empleado_dia(e, dia) == turno) {
                        asignados++;
                    }
                }
                
                int requeridos = instancia.get_empleados_necesarios_dia_turno(dia, turno);
                if (asignados > requeridos) {
                    solucion.set_turno_empleado_dia(emp, dia, -1);
                    removidos++;
                }
            }
        }

        // Si aún falta, quitar turnos incluso si deja turnos sin cubrir (prioridad a días de descanso)
        for (int dia = 0; dia < num_dias && removidos < deficit; ++dia) {
            if (solucion.get_turno_empleado_dia(emp, dia) != -1) {
                solucion.set_turno_empleado_dia(emp, dia, -1);
                removidos++;
            }
        }
    }
}

void DyVPlanificacion::CoverMissingShifts(const InstanciaPlanificacion& instancia,
                                         SolucionPlanificacion& solucion) const {
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

void DyVPlanificacion::ImproveGreedySolution(const InstanciaPlanificacion& instancia,
                                             SolucionPlanificacion& solucion) const {
    // Primero intentar cubrir turnos faltantes
    CoverMissingShifts(instancia, solucion);

    // Luego intenta mejorar la solución voraz mediante búsqueda local
    int num_empleados = instancia.get_numero_empleados();
    int num_dias = solucion.get_numero_dias();
    int num_turnos = instancia.get_turnos().size();
    bool mejora_encontrada = true;

    while (mejora_encontrada) {
        mejora_encontrada = false;

        // Intenta cambiar asignaciones para mejorar la satisfacción
        for (int e = 0; e < num_empleados && !mejora_encontrada; ++e) {
            for (int d = 0; d < num_dias && !mejora_encontrada; ++d) {
                int turno_actual = solucion.get_turno_empleado_dia(e, d);
                if (turno_actual == -1) continue;

                int satisfaccion_actual = instancia.get_satisfaccion_empleado_dia(e, d, turno_actual);

                // Intentar cambiar a otros turnos
                for (int nuevo_turno = 0; nuevo_turno < num_turnos; ++nuevo_turno) {
                    if (nuevo_turno == turno_actual) continue;

                    int satisfaccion_nueva = instancia.get_satisfaccion_empleado_dia(e, d, nuevo_turno);
                    
                    if (satisfaccion_nueva > satisfaccion_actual) {
                        // Verificar si podemos hacer el cambio
                        int asignados_nuevo = 0;
                        for (int emp = 0; emp < num_empleados; ++emp) {
                            if (solucion.get_turno_empleado_dia(emp, d) == nuevo_turno) {
                                asignados_nuevo++;
                            }
                        }
                        
                        int requeridos_nuevo = instancia.get_empleados_necesarios_dia_turno(d, nuevo_turno);
                        int requeridos_actual = instancia.get_empleados_necesarios_dia_turno(d, turno_actual);
                        
                        // Contar asignados al turno actual
                        int asignados_actual = 0;
                        for (int emp = 0; emp < num_empleados; ++emp) {
                            if (solucion.get_turno_empleado_dia(emp, d) == turno_actual) {
                                asignados_actual++;
                            }
                        }

                        // Verificar que cambio sea válido
                        if (asignados_nuevo < requeridos_nuevo && asignados_actual > requeridos_actual) {
                            solucion.set_turno_empleado_dia(e, d, nuevo_turno);
                            mejora_encontrada = true;
                        }
                    }
                }
            }
        }
    }
}
