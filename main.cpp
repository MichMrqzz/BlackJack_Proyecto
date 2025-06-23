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