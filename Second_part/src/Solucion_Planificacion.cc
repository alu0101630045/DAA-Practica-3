/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Diseño y Análisis de Algoritmos 2025-2026
  * Curso: 3º
  * 
  * @author Pablo García de los Reyes
  * @author César Navarro Santos
  * @description: Implementación de la clase SolucionPlanificacion
  * @date 07 Mar 2026
  * @version 1.0
  */

#include "../lib/Solucion_Planificacion.h"

SolucionPlanificacion::SolucionPlanificacion(int numero_empleados, int numero_dias)
    : numero_empleados_(numero_empleados), numero_dias_(numero_dias) {
    // Inicializar matriz con -1 (sin turno asignado)
    asignacion_.resize(numero_empleados, std::vector<int>(numero_dias, -1));
}

SolucionPlanificacion::SolucionPlanificacion(const SolucionPlanificacion& otra)
    : asignacion_(otra.asignacion_), numero_empleados_(otra.numero_empleados_),
      numero_dias_(otra.numero_dias_) {
}

SolucionPlanificacion::~SolucionPlanificacion() = default;

int SolucionPlanificacion::get_turno_empleado_dia(int empleado, int dia) const {
    return asignacion_[empleado][dia];
}

void SolucionPlanificacion::set_turno_empleado_dia(int empleado, int dia, int turno) {
    asignacion_[empleado][dia] = turno;
}

int SolucionPlanificacion::calcular_satisfaccion_total(const InstanciaPlanificacion& instancia) const {
    int satisfaccion_total = 0;
    for (int e = 0; e < numero_empleados_; ++e) {
        for (int d = 0; d < numero_dias_; ++d) {
            int turno = asignacion_[e][d];
            if (turno != -1) {  // Si el empleado tiene turno asignado
                satisfaccion_total += instancia.get_satisfaccion_empleado_dia(e, d, turno);
            }
        }
    }
    return satisfaccion_total;
}

int SolucionPlanificacion::contar_turnos_cubiertos(const InstanciaPlanificacion& instancia) const {
    int turnos_cubiertos = 0;
    auto matriz_turnos = instancia.get_matriz_turnos();
    int num_turnos = instancia.get_turnos().size();

    for (int d = 0; d < numero_dias_; ++d) {
        for (int t = 0; t < num_turnos; ++t) {
            int requeridos = matriz_turnos[d][t];
            // Contar cuántos empleados están asignados a este turno en este día
            int asignados = 0;
            for (int e = 0; e < numero_empleados_; ++e) {
                if (asignacion_[e][d] == t) {
                    asignados++;
                }
            }
            // Si está cubierto (al menos el mínimo requerido)
            if (asignados >= requeridos) {
                turnos_cubiertos++;
            }
        }
    }
    return turnos_cubiertos;
}

int SolucionPlanificacion::calcular_objetivo(const InstanciaPlanificacion& instancia) const {
    int satisfaccion = calcular_satisfaccion_total(instancia);
    int turnos_cubiertos = contar_turnos_cubiertos(instancia);
    return satisfaccion + turnos_cubiertos * 100;
}

bool SolucionPlanificacion::es_valida(const InstanciaPlanificacion& instancia) const {
    // Restricción 1: Cada empleado debe tener al menos el número de días de descanso requeridos
    for (int e = 0; e < numero_empleados_; ++e) {
        int dias_descanso = contar_dias_descanso(e);
        int dias_requeridos = instancia.get_dias_libres_necesarios(e);
        if (dias_descanso < dias_requeridos) {
            return false;  // No tiene suficientes días de descanso
        }
    }

    // Restricción 2: Cada turno debe estar cubierto por al menos el número mínimo de empleados
    auto matriz_turnos = instancia.get_matriz_turnos();
    int num_turnos = instancia.get_turnos().size();
    
    for (int d = 0; d < numero_dias_; ++d) {
        for (int t = 0; t < num_turnos; ++t) {
            int requeridos = matriz_turnos[d][t];
            int asignados = 0;
            for (int e = 0; e < numero_empleados_; ++e) {
                if (asignacion_[e][d] == t) {
                    asignados++;
                }
            }
            if (asignados < requeridos) {
                return false;  // Turno no cubierto
            }
        }
    }

    // Restricción 3: Un empleado no puede trabajar dos turnos en el mismo día
    for (int e = 0; e < numero_empleados_; ++e) {
        for (int d = 0; d < numero_dias_; ++d) {
            // Este es implícito en nuestra representación (un valor por célula)
        }
    }

    return true;
}

int SolucionPlanificacion::contar_dias_descanso(int empleado) const {
    int dias_descanso = 0;
    for (int d = 0; d < numero_dias_; ++d) {
        if (asignacion_[empleado][d] == -1) {  // -1 significa sin turno (descanso)
            dias_descanso++;
        }
    }
    return dias_descanso;
}

const std::vector<std::vector<int>>& SolucionPlanificacion::get_asignacion() const {
    return asignacion_;
}

int SolucionPlanificacion::get_numero_empleados() const {
    return numero_empleados_;
}

int SolucionPlanificacion::get_numero_dias() const {
    return numero_dias_;
}
