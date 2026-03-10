/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Diseño y Análisis de Algoritmos 2025-2026
  * Curso: 3º
  * 
  * @author Pablo García de los Reyes
  * @author César Navarro Santos
  * @description: Funciones auxiliares para la aplicación principal
  * @date 10 Mar 2026
  * @version 1.0
  */

#ifndef APP_FUNCTIONS_H
#define APP_FUNCTIONS_H

#include <vector>
#include <string>
#include <fstream>

/**
 * @brief Retorna la lista de ficheros de instancias disponibles
 * @return Vector de rutas de ficheros de instancias
 */
std::vector<std::string> GetInstanceFiles();

/**
 * @brief Muestra el menú de selección de instancias y retorna las seleccionadas
 * @param instance_files Vector con las rutas de instancias disponibles
 * @return Vector de instancias seleccionadas
 */
std::vector<std::string> DisplayInstanceMenu(const std::vector<std::string>& instance_files);

/**
 * @brief Obtiene la opción de salida del usuario (consola o fichero)
 * @return 1 para consola, 2 para fichero
 */
int GetOutputOption();

/**
 * @brief Configura la redirección de salida según la opción seleccionada
 * @param output_option Opción de salida (1=consola, 2=fichero)
 * @param output_file Referencia al fichero de salida
 * @param old_cout Puntero a old_cout para restaurar
 * @param old_cerr Puntero a old_cerr para restaurar
 * @return true si se configuró correctamente, false si hay error
 */
bool SetupOutputRedirection(int output_option,
                            std::ofstream& output_file,
                            std::streambuf*& old_cout,
                            std::streambuf*& old_cerr);

/**
 * @brief Restaura la redirección de salida a su estado original
 * @param output_option Opción de salida utilizada
 * @param output_file Referencia al fichero de salida
 * @param old_cout Puntero del buffer original de cout
 * @param old_cerr Puntero del buffer original de cerr
 */
void RestoreOutputRedirection(int output_option,
                              std::ofstream& output_file,
                              std::streambuf* old_cout,
                              std::streambuf* old_cerr);

/**
 * @brief Procesa y resuelve todas las instancias seleccionadas
 * @param selected_instances Vector de rutas de instancias a procesar
 */
void ProcessInstances(const std::vector<std::string>& selected_instances);

#endif  // APP_FUNCTIONS_H
