#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <vector>
#include <limits>


using namespace std;

struct Cuadrado {
    int x;
    int y;
    int lado;
};

struct Circulo {
    int x;
    int y;
    int radio;
};

struct Triangulo {
    int x;
    int y;
    int base;
};

bool fn_mode = false;

vector<Cuadrado> cuadrados;
vector<Circulo> circulos;
vector<Triangulo> triangulos;


void toggleFnMode() {
    fn_mode = !fn_mode;
}

int width, height; // Declarar width y height como variables globales

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void dibujarCuadrado(int x, int y, int lado, char caracter) {
    for (int i = 0; i < lado; ++i) {
        for (int j = 0; j < lado; ++j) {
            if (i == 0 || i == lado - 1 || j == 0 || j == lado - 1) {
                int px = (x + j) % width;
                int py = (y + i) % height;

                gotoxy(px, py);
                cout << caracter;
            }
        }
    }
}

bool validarValor(int valor) {
    if (cin.fail() || valor <= 0) {
        cin.clear(); // Limpiar el estado de error
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada inválida del usuario
        cout << "Por favor, ingrese un número entero positivo válido." << endl;
        return false; // Retorna false para indicar que el valor es incorrecto
    }
    return true; // Retorna true si el valor es válido
}


void dibujarCirculo(int x, int y, int radio, char caracter) {
    for (int i = 0; i <= radio * 2; ++i) {
        for (int j = 0; j <= radio * 2; ++j) {
            int dx = j - radio;
            int dy = i - radio;
            float distance = sqrt(dx * dx + dy * dy);
            if (abs(distance - radio) < 0.5) {
                int px = (x + j) % width;
                int py = (y + i) % height;

                gotoxy(px, py);
                cout << caracter;
            }
        }
    }
}

void dibujarTriangulo(int x, int y, int base, char caracter) {
    // Calcular la altura del triángulo equilátero (aproximadamente sqrt(3)/2 * base)
    int altura = int(0.866 * base); // Aproximación de sqrt(3)/2 * base

    // Dibujar el lado izquierdo del triángulo
    for (int i = 0; i <= altura; ++i) {
        gotoxy(x - i, y + i);
        cout << "*";
    }

    // Dibujar el lado derecho del triángulo
    for (int i = 0; i <= altura; ++i) {
        gotoxy(x + i, y + i);
        cout << "*";
    }

    // Dibujar la base del triángulo
    for (int i = 0; i < base; ++i) {
        gotoxy(x - altura + i, y + altura);
        cout << caracter;
    }
}

void dibujarFiguras() {
    if (!cuadrados.empty()) {
        for (const auto& figura : cuadrados) {
            dibujarCuadrado(figura.x, figura.y, figura.lado, '*');
        }
    }

        if (!circulos.empty()) {
        for (const auto& figura : circulos) {
            dibujarCirculo(figura.x, figura.y, figura.radio, '*');
        }
    }

    if (!triangulos.empty()) {
        for (const auto& figura : triangulos) {
            dibujarTriangulo(figura.x, figura.y, figura.base, '*');
        }
    }
}


void insertarCirculo(int x, int y){
 int radio;
 x:
    cout << "R circulo: ";
    cin >> radio;
    if (!validarValor(radio)) {
           cout << "El valor ingresado es incorrecto";
           goto x;
    }

    Circulo nueva_figura = {x, y, radio};
    circulos.push_back(nueva_figura);
    system("cls");
    dibujarFiguras();
}

void insertarTriangulo(int x, int y){
 int base;
 y:
    cout << "B Triangulo: ";
    cin >> base;
    if (!validarValor(base)) {
           cout << "El valor ingresado es incorrecto";
           goto y;
    }

    Triangulo nueva_figura = {x, y, base};
    triangulos.push_back(nueva_figura);
    system("cls");
    dibujarFiguras();
}



void insertarCuadrado(int x, int y) {
    int lado;
    cout << "Tamaño del lado:";
    cin >> lado;
    Cuadrado nuevo_cuadrado = {x, y, lado};
    cuadrados.push_back(nuevo_cuadrado);
    system("cls");
    dibujarFiguras();
}

void handleFunctionKey(int key, int x, int y) {
    switch (key) {
        case 59: // F1
            insertarCuadrado(x, y);
            break;
        case 60: // F2
            insertarCirculo(x, y);
            break;
        case 61: // F3
            insertarTriangulo(x, y);
            break;
        case 27: // Escape
            system("cls");
            cuadrados.clear();
            circulos.clear();
            gotoxy(x, y);
            cout << "Limpiando Pantalla" << endl;
            Sleep(2000);
            system("cls");
            break;
    }
}

int main() {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    width = info.dwSize.X;
    height = info.dwSize.Y;

    int x = width / 2;
    int y = height / 2;
    char key;

    system("cls");
    gotoxy(x, y);
    cout << "";
        while (true) {
                if (_kbhit()) {
                    key = _getch();
                    if (key == 0) {
                        // Se recibió un código de tecla extendido (0)
                        toggleFnMode();
                    } else {
                        handleFunctionKey(key, x, y);
                        switch (key) {
                            case 'w':
                                y = (y - 1 + height) % height;
                                break;
                            case 's':
                                y = (y + 1) % height;
                                break;
                            case 'a':
                                x = (x - 1 + width) % width;
                                break;
                            case 'd':
                                x = (x + 1) % width;
                                break;
                        }
                        gotoxy(x, y);
                        cout << "";
                    }
                }
                Sleep(100);
            }
}
