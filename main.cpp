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