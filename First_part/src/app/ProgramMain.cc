/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Diseño y Análisis de Algoritmos 2025-2026
  * Curso: 3º
  * 
  * @author Pablo García de los Reyes
  * @author César Navarro Santos
  * @description: Programa principal
  * @date 07 Mar 2026
  * @version 1.0
  */

#include "utils/Functions.h"

int main() {
    int mode = chooseMode();
    if (mode == 1) {
        runNormalMode();
    } else if (mode == 2) {
        runDebugMode();
    } else {
        std::cout << "Modo inválido." << std::endl;
    }
    return 0;
}