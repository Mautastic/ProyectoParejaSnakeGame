
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESC 27

int serpiente[200][2];
int longitud = 1;
int tamano = 14; // Tamaño inicial con los 10 cubos adicionales
int posX = 10, posY = 12;
int direccion = 3;
int posXComida = 30, posYComida = 15;
int velocidad = 100, incremento = 1; //velocidad mas bajo el numero = mas velocidad
int puntaje = 0;

char tecla;

void irA(int x, int y) {

    HANDLE hConsola;
    COORD dwPosicion;

    dwPosicion.X = x;
    dwPosicion.Y = y;
    hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsola, dwPosicion);

}

void pintarTablero() {
    //lineas horizontal
    for (int i = 2; i < 78; i++) {
        irA(i, 3); printf("%c", 205);
        irA(i, 23); printf("%c", 205);
    }
    //lineas vertical
    for (int i = 4; i < 23; i++) {
        irA(2, i); printf("%c", 186);
        irA(77, i); printf("%c", 186);
    }
    //Corners
    irA(2, 3); printf("%c", 201);
    irA(2, 23); printf("%c", 200);
    irA(77, 3); printf("%c", 187);
    irA(77, 23); printf("%c", 188);
}

void guardarPosicion() {

    serpiente[longitud][0] = posX;
    serpiente[longitud][1] = posY;
    longitud++;
    if (longitud == tamano) longitud = 1;
}

void dibujarSerpiente() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 3);

    for (int i = 1; i < tamano; i++) {
        irA(serpiente[i][0], serpiente[i][1]); printf("S");
    }
}

void borrarSerpiente() {
    irA(serpiente[longitud][0], serpiente[longitud][1]); printf(" ");
}

void leerTecla() {

    if (_kbhit()) {
        tecla = _getch();
        switch (tecla) {
        case ARRIBA:
            if (direccion != 2)
                direccion = 1;
            break;
        case ABAJO:
            if (direccion != 1)
                direccion = 2;
            break;
        case DERECHA:
            if (direccion != 4)
                direccion = 3;
            break;
        case IZQUIERDA:
            if (direccion != 3)
                direccion = 4;
            break;
        }
    }
}

void ajustarVelocidad() {
    if (puntaje == incremento * 20) {
        velocidad -= 10;
        incremento++;
    }
}

void generarComida() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);

    if (posX == posXComida && posY == posYComida) {
        posXComida = (rand() % 73) + 4;
        posYComida = (rand() % 19) + 4;

        tamano++;
        puntaje += 10;
        irA(posXComida, posYComida); printf("%c", 147);

        ajustarVelocidad();
    }
}

bool gameOver() {
    if (posY == 3 || posY == 23 || posX == 2 || posX == 77) return false; // la serpiente choca con un objeto y regresa falso
    for (int j = tamano - 1; j > 0; j--) {
        if (serpiente[j][0] == posX && serpiente[j][1] == posY)
            return false;
    }

    return true;
}

void mostrarPuntaje() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 6);

    irA(3, 1); printf("Puntuacion: %d", puntaje); //saber los puntos del jugador

}

int main() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 2);
    printf("SJUEGO DE LA SERPIENTE");

    pintarTablero();
    irA(posXComida, posYComida); printf("%c", 147);

    // Agregar 10 cubos aleatorios al inicio del juego
    for (int i = 0; i < 10; i++) {
        serpiente[i][0] = (rand() % 73) + 4;
        serpiente[i][1] = (rand() % 19) + 4;
    }

    while (tecla != ESC && gameOver()) {
        borrarSerpiente();
        guardarPosicion();
        dibujarSerpiente();

        generarComida();
        mostrarPuntaje();
        leerTecla();
        leerTecla();

        if (direccion == 1) posY--;
        if (direccion == 2) posY++;
        if (direccion == 3) posX++;
        if (direccion == 4) posX--;

        Sleep(velocidad);
    }

    system("pause>null");
    SetConsoleTextAttribute(hConsole, 12);
    printf(" \nGAME OVER");
    SetConsoleTextAttribute(hConsole, 7);
    return 0;
}