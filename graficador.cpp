#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <vector>
#include <limits>
//se agregan librerias necesarias para la realización del proyecto

using namespace std;

// se definen los colores a utilizar, no pude utilizar conio para esto
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define WHITE   "\033[37m"

string tipoFigura;

// se definen las clases de las figuras
struct Cuadrado {
    int x;
    int y;
    int lado;
    string color;
};

struct Circulo {
    int x;
    int y;
    int radio;
    string color;
};

struct Triangulo {
    int x;
    int y;
    int base;
    string color;
};

struct Rectangulo {
    int x;
    int y;
    int base;
    int altura;
    string color;
};

// se fija un color inicial
string color_fijo = WHITE;

// se inicializan los vectores
vector<Cuadrado> cuadrados;
vector<Circulo> circulos;
vector<Triangulo> triangulos;
vector<Rectangulo> rectangulos;


// se implementa funcion para dispositivos que tengan la tecla fn
bool fn_mode = false;

void toggleFnMode() {
    fn_mode = !fn_mode;
}


int width, height; // Declarar width y height como variables globales

// se marca el gotoxy y se ayuda de la funcion para mlover cursor con windows
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// funcion para mostrar un menú
void mostrarMenu(){
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    width = info.dwSize.X;
    height = info.dwSize.Y;

    int tx = 8;
    int ty = 0;
    gotoxy(tx, ty);
    cout << YELLOW << "W - w : Arriba  | S - s : Abajo | A - a : Izquierda | D - d : Derecha | G : GuardarDatos | Q : Abrir Archivo";
    tx = 5;
    ty = height -1;
    gotoxy(tx, ty);
    cout << GREEN << "F1:Cuadrado | F2:Circulo | F3:Triangulo | F4:Rectangulo | ESC:Borrar | F5:Rojo |F6:Verde| F7:Amarillo | F8:Blanco";
}

// funcion para vlidar valores incorrectos
bool validarValor(int valor) {
    if (cin.fail() || valor <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Por favor, ingrese un numero entero positivo v�lido." << endl;
        return false;
    }
    return true;
}


//almacenado y cargar un archivo


// se inicializan funciones para dibujar las figuras
void dibujarCuadrado(int x, int y, int lado, const string& color) {
    for (int i = 0; i < lado; i++) {
        for (int j = 0; j < lado; j++) {
            if (i == 0 || i == lado - 1 || j == 0 || j == lado - 1){
                int px = (x + j * 2) % width;
                int py = (y + i) % height;
                gotoxy(px, py);
                cout << color << "*";
            }
        }
        cout << endl;
    }
}

void dibujarCirculo(int x, int y, int radio, const string& color) {
    for (int i = 0; i <= radio * 2; ++i) {
        for (int j = 0; j <= radio * 2; ++j) {
            int dx = j - radio;
            int dy = i - radio;
            float distance = sqrt(dx * dx + dy * dy);
            if (abs(distance - radio) < 0.5) {
                int px = (x + j * 2) % width;
                int py = (y + i) % height;

                gotoxy(px, py);
                cout << color << "*";
            }
        }
    }
}

void dibujarTriangulo(int x, int y, int base, const string& color) {
    int altura = int(0.866 * base);

    for (int i = 0; i <= altura; ++i) {
        gotoxy(x - i, y + i);
        cout << color << "*";
        gotoxy(x + i, y + i);
        cout << color << "*";
    }

    for (int i = 0; i < base; ++i) {
        int validacion = base % 2;
        if(validacion == 1){ // Verificar si la base es impar
            gotoxy(x - altura + i * 2, y + altura);
            cout << color << "*";
        } else { // Si la base es par
            if (i % 2 == 0 || i == base + 1) { // Imprimir solo cada segundo asterisco y el último
                gotoxy(x - altura + i, y + altura);
                cout << color << "*";
            }
        }
    }
}

void dibujarContornoRectangulo(int x, int y, int base, int altura, const string& color) {
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < base; ++j) {
            // Dibuja solo el contorno: superior, inferior, izquierdo, derecho
            if (i == 0 || i == altura - 1 || j == 0 || j == base - 1) {
                gotoxy(x + j, y + i);
                std::cout << color << "*";
            }
        }
    }
}



void dibujarFiguras() {
    for (const auto& figura : cuadrados) {
        dibujarCuadrado(figura.x, figura.y, figura.lado, figura.color);
    }

    for (const auto& figura : circulos) {
        dibujarCirculo(figura.x, figura.y, figura.radio, figura.color);
    }

    for (const auto& figura : triangulos) {
        dibujarTriangulo(figura.x, figura.y, figura.base, figura.color);
    }

    for (const auto& figura : rectangulos) {
        dibujarContornoRectangulo(figura.x, figura.y, figura.base, figura.altura, figura.color);
    }
        mostrarMenu();
}


void guardarDatos(string nombreArchivo) {
    ofstream archivo(nombreArchivo);

    // Verifica si se pudo crear el archivo
    if (!archivo) {
        cerr << "Error al crear el archivo " << nombreArchivo << endl;
        return;
    }

    // Guarda los datos de los vectores en el archivo
    for (const auto& cuadrado : cuadrados) {
        archivo << "Cuadrado " << cuadrado.x << " " << cuadrado.y << " " << cuadrado.lado << " " << cuadrado.color << endl;
    }

    for (const auto& circulo : circulos) {
        archivo << "Circulo " << circulo.x << " " << circulo.y << " " << circulo.radio << " " << circulo.color << endl;
    }

    for (const auto& triangulo : triangulos) {
        archivo << "Triangulo " << triangulo.x << " " << triangulo.y << " " << triangulo.base << " " << triangulo.color << endl;
    }

    for (const auto& rectangulo : rectangulos) {
        archivo << "Rectangulo " << rectangulo.x << " " << rectangulo.y << " " << rectangulo.base << " " << rectangulo.altura << " " << rectangulo.color << endl;
    }

    // Cierra el archivo
    archivo.close();

    cout << "Datos guardados en el archivo " << nombreArchivo << endl;
            Sleep(2000);
            system("cls");
            dibujarFiguras();
}


// Función para abrir un archivo y obtener los datos
void cargarArchivoAvectores(string nombreArchivo) {
    ifstream archivo(nombreArchivo);

    // Verifica si se pudo abrir el archivo
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    // Variables temporales para almacenar los datos mientras se leen del archivo
    string tipo;
    int x, y, base, altura, lado, radio;
    string color;

    // Lee la información del archivo y almacena los datos en los vectores
    while (archivo >> tipo) {
        if (tipo == "Cuadrado") {
            archivo >> x >> y >> lado >> color;
            Cuadrado cuadrado = {x, y, lado, color};
            cuadrados.push_back(cuadrado);
        } else if (tipo == "Circulo") {
            archivo >> x >> y >> radio >> color;
            Circulo circulo = {x, y, radio, color};
            circulos.push_back(circulo);
        } else if (tipo == "Triangulo") {
            archivo >> x >> y >> base >> color;
            Triangulo triangulo = {x, y, base, color};
            triangulos.push_back(triangulo);
        } else if (tipo == "Rectangulo") {
            archivo >> x >> y >> base >> altura >> color;
            Rectangulo rectangulo = {x, y, base, altura, color};
            rectangulos.push_back(rectangulo);
        }
    }

    archivo.close();

    cout << "Obteniendo figuras y creandolas" << nombreArchivo << endl;
            Sleep(2000);
            system("cls");
    dibujarFiguras();
}


void guardarDatosName() {
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo: ";
    cin >> nombreArchivo;

    guardarDatos(nombreArchivo);
}

void abrirArchivo() {
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo: ";
    cin >> nombreArchivo;

    cargarArchivoAvectores(nombreArchivo);
}

// funcion para insertar figuras en los vectores

void insertarPosFigura(int x, int y, string tipoFigura){

    if(tipoFigura == "cuadrado") {
        string color = color_fijo;
        int lado;
        cout << "lado:";
        cin >> lado;
        if (!validarValor(lado)) {
            cout << "El valor ingresado es incorrecto";
            return;
        }
        Cuadrado nuevo_cuadrado = {x, y, lado, color};
        cuadrados.push_back(nuevo_cuadrado);
        system("cls");
        dibujarFiguras();

    }
    if(tipoFigura == "triangulo") {
        string color = color_fijo;
        int base;
        cout << "Base: ";
        cin >> base;
        if (!validarValor(base)) {
            cout << "El valor ingresado es incorrecto";
            return;
        }
        Triangulo nueva_figura = {x, y, base, color};
        triangulos.push_back(nueva_figura);
        system("cls");
        dibujarFiguras();

    }

    if(tipoFigura == "circulo") {
        string color = color_fijo;
        int radio;
        cout << "Diametro: ";
        cin >> radio;
        if (!validarValor(radio)) {
            cout << "El valor ingresado es incorrecto";
            return;
        }
        Circulo nueva_figura = {x, y, radio, color};
        circulos.push_back(nueva_figura);
        system("cls");
        dibujarFiguras();
    }

        if(tipoFigura == "rectangulo") {
        string color = color_fijo;
        int base;
        int altura;
        cout << "base: ";
        cin >> base;
        cout << "altura: ";
        cin >> altura;
        if (!validarValor(base) || !validarValor(altura) ) {
            cout << "El valor ingresado es incorrecto";
            return;
        }
        Rectangulo nueva_figura = {x, y, base, altura, color};
        rectangulos.push_back(nueva_figura);
        system("cls");
        dibujarFiguras();
    }

    }


// funcion para leer las teclas de funcion especiales
void handleFunctionKey(int key, int x, int y) {
    switch (key) {
        case 59: // F1 //cuadradp
            tipoFigura = "cuadrado";
            insertarPosFigura(x, y, tipoFigura);
            break;
        case 60: // F2
            tipoFigura = "circulo";
            insertarPosFigura(x, y, tipoFigura);
            break;
        case 61: // F3
            tipoFigura = "triangulo";
            insertarPosFigura(x, y, tipoFigura);
            break;
        case 62: // F4
            tipoFigura = "rectangulo";
            insertarPosFigura(x, y, tipoFigura);
            break;
        case 27: // Escape
            system("cls");
            cuadrados.clear();
            circulos.clear();
            triangulos.clear();
            gotoxy(x, y);
            cout << RED <<"Limpiando Pantalla" << endl;
            Sleep(2000);
            system("cls");
               mostrarMenu();
            break;
        case 63: // F5
            color_fijo = RED;
            break;
        case 64: // F6
            color_fijo = GREEN;
            break;
        case 65: // F7
            color_fijo = YELLOW;
            break;
        case 66: // F8
            color_fijo = WHITE;
            break;
        case 68: // F10
            mostrarMenu();
            break;
        case 103: // g
            guardarDatosName();
            break;
        case 71: // G
            guardarDatosName();
            break;
        case 113: // q
            abrirArchivo();
            break;
        case 81: // Q
            abrirArchivo();
            break;

    }
}


int main() {
// se utiliza una funcion de windows par aobtener el tamaño del cmd generado y asignar ese valor a widh y height
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    width = info.dwSize.X;
    height = info.dwSize.Y;
    int x = width / 2;
    int y = height / 2;
    char key;
    system("cls");
    mostrarMenu();
    gotoxy(x, y);
    cout << "";

    // se establece While para hacer el ciclo de escuchar las entradas del usuario
    while (true) {
  // khbit y getch funciones para escuchar y leer la tecla presionada
        if (_kbhit()) {
            key = _getch();
            if (key == 0 || key == 224) {
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
                      case 'W':
                        y = (y - 1 + height) % height;
                        break;
                    case 'S':
                        y = (y + 1) % height;
                        break;
                    case 'A':
                        x = (x - 1 + width) % width;
                        break;
                    case 'D':
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
