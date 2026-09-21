# Práctica 1: Programa Híbrido MPI + OpenMP

Este repositorio contiene la implementación de un programa híbrido en C++ utilizando **MPI (Message Passing Interface)** para la comunicación en memoria distribuida y **OpenMP** para el procesamiento paralelo por hilos en memoria compartida.

---

## 👥 Datos del Equipo

**Equipo 11**

* **Hermosillo Prado Carlos**
* **Montes de Oca del Risco Rafael Alejandro**
* **Ramirez Andrade Uriel Ismael Guadalupe**

---

## Requisitos Previos

Para compilar y ejecutar este proyecto se requiere el siguiente entorno en Windows:

1. **Microsoft MPI v10.1.2** o superior (Runtime y SDK).
2. **Compilador C++** con soporte para OpenMP (incluido en MSVC / Visual Studio Build Tools).
3. Entorno de línea de comandos **x64 Native Tools Command Prompt for VS**.

---

## Archivos del Repositorio

* `programa_hibrido.cpp`: Código fuente principal del programa híbrido.
* `.gitignore`: Filtro para excluir archivos binarios y temporales (`.exe`, `.obj`, `.pdb`).
* `README.md`: Documentación e instrucciones del proyecto.

---

## Compilación

Abre la consola **x64 Native Tools Command Prompt for VS** como Administrador, dirígete a la carpeta del proyecto y ejecuta:

```cmd
cl /EHsc /openmp programa_hibrido.cpp /I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" /Fe:programa_hibrido.exe /link /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" msmpi.lib
