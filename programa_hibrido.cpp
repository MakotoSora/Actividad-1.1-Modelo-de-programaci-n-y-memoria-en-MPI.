#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <mpi.h>
#include <omp.h>

class GestorArreglo {
private:
    int* datos;
    long long tamano;
    int rank;
    int totalProcesos;
    std::string nombreEquipo;

public:
    // Constructor: Reserva estricta mediante arreglo dinámico tradicional
    GestorArreglo(long long n, int r, int totalP, const std::string& equipo)
        : tamano(n), rank(r), totalProcesos(totalP), nombreEquipo(equipo) {
        datos = new int[tamano];
    }

    // Destructor
    ~GestorArreglo() {
        delete[] datos;
    }

    // Llenado en paralelo con OpenMP
    void llenarArregloYMostrarAvance() {
        srand(static_cast<unsigned int>(time(NULL)) + rank * 1000);

        long long bloque = tamano / 10;
        if (bloque == 0) bloque = 1;

        for (int paso = 1; paso <= 10; ++paso) {
            long long inicio = (paso - 1) * bloque;
            long long fin = (paso == 10) ? tamano : paso * bloque;

#pragma omp parallel
            {
                int tid = omp_get_thread_num();

#pragma omp for schedule(static)
                for (long long i = inicio; i < fin; ++i) {
                    datos[i] = (rand() % 1000) + 1;
                }

#pragma omp single
                {
                    int porcentaje = paso * 10;
                    std::cout << "Avance: " << porcentaje << "% | "
                        << "Proceso/Nodo: " << rank << " | "
                        << "Equipo: " << nombreEquipo << " | "
                        << "Hilo OpenMP: " << tid << "\n";
                    std::cout.flush();
                }
            }
        }
    }

    // Impresión del contenido
    void mostrarContenido() {
        MPI_Barrier(MPI_COMM_WORLD);

        std::cout << "\n========================================\n";
        std::cout << "Equipo: " << nombreEquipo
            << " | Proceso/Nodo MPI: " << rank << "\n";
        std::cout << "Tamaño del arreglo dinámico: " << tamano << " elementos\n";
        std::cout << "========================================\n";

        if (tamano <= 100) {
            std::cout << "Contenido completo:\n[ ";
            for (long long i = 0; i < tamano; ++i) {
                std::cout << datos[i] << " ";
            }
            std::cout << "]\n";
        }
        else {
            std::cout << "Muestra de contenido (Primeros 10 y últimos 10 elementos):\n[ ";
            for (long long i = 0; i < 10; ++i) {
                std::cout << datos[i] << " ";
            }
            std::cout << "... ";
            for (long long i = tamano - 10; i < tamano; ++i) {
                std::cout << datos[i] << " ";
            }
            std::cout << "]\n";
        }
        std::cout.flush();
    }
};

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, totalProcesos;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &totalProcesos);

    // Ojehupyty computadora (host) réra
    char nombreHost[MPI_MAX_PROCESSOR_NAME];
    int longitudNombre;
    MPI_Get_processor_name(nombreHost, &longitudNombre);

    std::string nombreEquipo = "Equipo 11";
    // Oñembojuaju ato réra ha computadora réra
    std::string infoCompletaEquipo = nombreEquipo + " [Host: " + std::string(nombreHost) + "]";

    std::string integrantes[] = {
        "Hermosillo Prado Carlos",
        "Montes de Oca del Risco Rafael Alejandro",
        "Ramirez Andrade Uriel Ismael Guadalupe"
    };

    if (rank == 0) {
        std::cout << "=========================================================\n";
        std::cout << " ACTIVIDAD 1.1: MODELO DE PROGRAMACIÓN Y MEMORIA EN MPI  \n";
        std::cout << " " << nombreEquipo << "\n";
        std::cout << " Integrantes:\n";
        for (const auto& integrante : integrantes) {
            std::cout << "  - " << integrante << "\n";
        }
        std::cout << "=========================================================\n\n";
        std::cout.flush();
    }

    MPI_Barrier(MPI_COMM_WORLD);

    long long tamanoArreglo = 0;

    if (argc > 1) {
        tamanoArreglo = std::atoll(argv[1]);
    }
    else {
        srand(static_cast<unsigned int>(time(NULL)) + rank);
        tamanoArreglo = 20 + (rand() % 31);
    }

    GestorArreglo gestor(tamanoArreglo, rank, totalProcesos, infoCompletaEquipo);
    gestor.llenarArregloYMostrarAvance();
    gestor.mostrarContenido();

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0) {
        std::cout << "\n=========================================================\n";
        std::cout << "   EJECUCIÓN FINALIZADA CORRECTAMENTE                    \n";
        std::cout << " " << nombreEquipo << "\n";
        std::cout << " Integrantes:\n";
        for (const auto& integrante : integrantes) {
            std::cout << "  - " << integrante << "\n";
        }
        std::cout << "=========================================================\n";
        std::cout.flush();
    }

    MPI_Finalize();
    return 0;
}