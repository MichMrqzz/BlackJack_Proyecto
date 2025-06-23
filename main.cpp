#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;


// Struct para representar una carta
struct Carta{
    string nombre; // Nombre de la carta
    int valor; // Valor numérico de la carta 2–11
};


// Struct para representar un jugador o la banca
struct Jugador{
    string nombre; // Nombre del jugador
    Carta* mano; // Arreglo dinamico de cartas
    int numCartas; // Numero de cartas que tiene
    int puntos; // Puntos acumulados
};


// Struct para guardar una partida
struct Partida{
    string nombreJugador;
    string resultado;
    string fecha;
};

// Funcion que genera una carta aleatoria con su valor
Carta generarCarta(){
    string nombres[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    int valores[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    int i = rand()% 13; // Número aleatorio del 0 al 12
    return{nombres[i], valores[i]};
}


// Funcion para agregar una carta a la mano del jugador
void agregarCarta(Jugador &jugador){
    Carta nueva = generarCarta();
    Carta* nuevaMano = new Carta[jugador.numCartas + 1];  // Crear un nuevo arreglo con una carta adicional

    for(int i = 0; i < jugador.numCartas; i++) // Copiar las cartas existentes
        nuevaMano[i] = jugador.mano[i];

    nuevaMano[jugador.numCartas] = nueva;
    delete[] jugador.mano;
    jugador.mano = nuevaMano; // Actualizar la mano
    jugador.numCartas++;

    jugador.puntos += nueva.valor; // Sumar el valor de la carta

    // Ajustar si hay un As y el jugador se pasa de 21
    if(jugador.puntos > 21){
        for (int i = 0; i < jugador.numCartas; i++){
            if(jugador.mano[i].nombre == "A" && jugador.mano[i].valor == 11){
                jugador.mano[i].valor = 1;
                jugador.puntos -= 10;
                break;
            }
        }
    }
}


// Función para mostrar la mano actual de un jugador
void mostrarMano(const Jugador &jugador){
    cout << jugador.nombre << " tiene: ";
    for (int i = 0; i < jugador.numCartas; i++)
        cout << jugador.mano[i].nombre << " ";
    cout << "  Puntos: " << jugador.puntos << endl;
}

// Función para obtener la fecha actual
string obtenerFecha(){
    time_t t = time(0);
    tm* now = localtime(&t);
    char buffer[20];
    strftime(buffer, 20, "%Y-%m-%d", now);
    return buffer;
}


// Función para guardar el resultado de la partida
void guardarPartida(Partida partida){
    ofstream archivo("historial.txt", ios::app);
    archivo << left << setw(15) << partida.nombreJugador
            << setw(10) << partida.resultado
            << setw(12) << partida.fecha << endl;
    archivo.close();
}


// Función principal para ejecutar una partida completa
void jugar(){
    srand(time(0));
    Jugador jugador = {"Jugador", nullptr, 0, 0};
    Jugador banca = {"Banca", nullptr, 0, 0};

   string nombre; // Obtener nombre del jugador
    cout << "Ingresa tu nombre: ";
    getline(cin, nombre);
    jugador.nombre = nombre;

    // Repartir cartas iniciales
    agregarCarta(jugador);
    agregarCarta(jugador);
    agregarCarta(banca);
    agregarCarta(banca);

    // Turno del jugador
    char opcion;
    do{
        mostrarMano(jugador);
        if(jugador.puntos > 21){
            cout << "Te pasaste de 21. Pierdes." << endl;
            guardarPartida({jugador.nombre, "Perdiste", obtenerFecha()});
            return;
        }
        cout << "Deseas otra carta? (h = Hit / s = Stand): ";
        cin >> opcion;
        if(opcion == 'h'){
            agregarCarta(jugador);
        }
    }while(opcion == 'h');

    // Turno de la banca
    while(banca.puntos < 17){
        agregarCarta(banca);
    }

    mostrarMano(jugador);
    mostrarMano(banca);

    // Resultados
    string resultado;
    if(banca.puntos > 21 || jugador.puntos > banca.puntos){
        cout << "Ganaste!!!" << endl;
        resultado = "Ganaste";
    } else if(jugador.puntos < banca.puntos){
        cout << "La banca gana." << endl;
        resultado = "Perdiste";
    } else{
        cout << "Empate. Gana la banca." << endl;
        resultado = "Perdiste";
    }

    // Guardar resultado en el historial
    guardarPartida({jugador.nombre, resultado, obtenerFecha()});
    delete[] jugador.mano;
    delete[] banca.mano;
}