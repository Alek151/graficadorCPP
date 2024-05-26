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
    int direccion;
    string color;
    string caracter_escritura;
};

struct Circulo {
    int x;
    int y;
    int radio;
    string color;
    string caracter_escritura;
};

struct Triangulo {
    int x;
    int y;
    int base;
    int direccion;
    string color;
    string caracter_escritura;
};

struct Rectangulo {
    int x;
    int y;
    int base;
    int altura;
    string color;
    string caracter_escritura;
};


struct Linea {
    int x;
    int y;
    int longitud;
    int direccion;
    string color;
    string caracter_escritura;
};

struct Rombo {
    int x;
    int y;
    int dMayor; // Diagonal mayor
    int dMenor; // Diagonal menor
    string color;
    string caracter_escritura;
};


struct Hexagono {
    int x;
    int y;
    int lado;
    string color;
    string caracter_escritura;
};




// se fija un color inicial
string color_fijo = WHITE;
string caracter_fijado = "*";

// se inicializan los vectores
vector<Cuadrado> cuadrados;
vector<Circulo> circulos;
vector<Triangulo> triangulos;
vector<Rectangulo> rectangulos;
vector<Linea> lineas;
vector<Rombo> rombos;
vector<Hexagono> hexagonos;



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

    int tx = 13;
    int ty = 0;
    gotoxy(tx, ty);
    cout << YELLOW << "  Arriba (^), Abajo (v), Izquierda (<), Derecha (>) | ctrl + A: Abrir | ctrl + G: Guardar";
    tx = 0;
    ty = height -1;
    gotoxy(tx, ty);
    cout << GREEN << "F1:Triangulo"<< RED << "|" <<  GREEN <<"F2:Cuadrado"<< RED << "|" <<  GREEN  <<"F3:Rectangulo"<< RED << "|" <<  GREEN  <<"F4:Circulo"<< RED << "|" <<  GREEN  <<"F5:Linea"<< RED << "|" <<  GREEN  <<"F6:Rombo"<< RED << "|" <<  GREEN  <<"F7:Hexa"<< RED << "|" <<  GREEN  <<"F8:Nuevo Caracter"<< RED << "|" <<  GREEN  <<"F9:limpiar"<< RED << "|" <<  GREEN <<"F10:Cambiocolor";
}

// funcion para vlidar valores incorrectos
bool validarValor(int valor) {
    if (cin.fail() || valor <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Por favor, ingrese un numero entero positivo valido." << endl;
        Sleep(2000);
            system("cls");
        return false;
    }
    return true;
}


void dibujarHexagono(int x, int y, int lado, const string& color, const string& caracter_escritura) {
    int h = lado;
    int i, j;

    // Parte superior del hexágono
    for (i = 0; i < h; i++) {
        for (j = 0; j < h - 1 - i; j++) {
            cout << " ";
        }
        cout << color << caracter_escritura;
        for (j = 0; j < (i * 2 - 1); j++) {
            cout << " ";
        }
        if (i != 0) {
            cout << color << caracter_escritura;
        }
        cout << endl;
    }

    // Parte media del hexágono
    for (i = 0; i < h - 2; i++) {
        cout << color << caracter_escritura;
        for (j = 0; j < (h * 2 - 3); j++) {
            cout << " ";
        }
        cout << color << caracter_escritura << endl;
    }

    // Parte inferior del hexágono
    for (i = h - 1; i >= 0; i--) {
        for (j = 0; j < h - 1 - i; j++) {
            cout << " ";
        }
        cout << color << caracter_escritura;
        for (j = 0; j < (i * 2 - 1); j++) {
            cout << " ";
        }
        if (i != 0) {
            cout << color << caracter_escritura;
        }
        cout << endl;
    }
}



void dibujarRombo(int x, int y, int dMayor, int dMenor, const string& color, const string& caracter_escritura) {
  int h = dMayor / 2; // Mitad de la diagonal mayor (altura máxima del rombo)
  int w = dMenor / 2; // Mitad de la diagonal menor (ancho máximo del rombo)

  // Parte superior del rombo
  for (int i = 0; i <= h; ++i) {
    int dx = abs(h - i) * w / h;
    gotoxy((x - dx + width) % width, (y - i + height) % height);
    cout << color << caracter_escritura;
    gotoxy((x + dx + width) % width, (y - i + height) % height);
    cout << color << caracter_escritura;
  }

  // Parte inferior del rombo
  for (int i = 1; i <= h; ++i) {
    int dx = abs(h - i) * w / h;
    gotoxy((x - dx + width) % width, (y + i + height) % height);
    cout << color << caracter_escritura;
    gotoxy((x + dx + width) % width, (y + i + height) % height);
    cout << color << caracter_escritura;
  }
}
//almacenado y cargar un archivo
void dibujarLinea(int x, int y, int longitud, int direccion, const string& color, const string& caracter_escritura) {

    // Dibujar la línea según la dirección
    for (int i = 0; i < longitud; ++i) {
        gotoxy(x, y);
        cout << color << caracter_escritura;
        if (direccion == 1) {
            y--; // Arriba
        } else if (direccion == 2) {
            y++; // Abajo
        } else if (direccion == 3) {
            x--; // Izquierda
        } else if (direccion == 4) {
            x++; // Derecha
        } else if (direccion == 5) {
            x++;
            y++; // Diagonal abajo derecha
        } else if (direccion == 6) {
            x--;
            y--; // Diagonal arriba izquierda
        } else if (direccion == 7) {
            x++;
            y--; // Diagonal arriba derecha
        } else if (direccion == 8) {
            x--;
            y++; // Diagonal abajo izquierda
        }
    }
}





// se inicializan funciones para dibujar las figuras
void dibujarCuadrado(int x, int y, int lado, int direccion, const string& color, const string& caracter_escritura) {
    int px = x;
    int py = y;
    // Ajustar la posición de acuerdo a la dirección
    switch (direccion) {
        case 1: // Arriba
            py -= lado - 1;
            break;
        case 2: // Abajo
            break; // No se necesita ajuste
        case 3: // Izquierda
            px -= (lado * 2 - 2);
            py -= lado - 1;
            break;
        case 4: // Derecha
            break; // No se necesita ajuste
    }

    // Dibujar el cuadrado
    for (int i = 0; i < lado; i++) {
        for (int j = 0; j < lado; j++) {
            if (i == 0 || i == lado - 1 || j == 0 || j == lado - 1){
                int cx = (px + j * 2) % width;
                int cy = (py + i) % height;
                gotoxy(cx, cy);
                cout << color << caracter_escritura;
            }
        }
        cout << endl;
    }
}

void dibujarCirculo(int x, int y, int radio, const string& color, const string& caracter_escritura) {
    for (int i = 0; i <= radio * 2; ++i) {
        for (int j = 0; j <= radio * 2; ++j) {
            int dx = j - radio;
            int dy = i - radio;
            float distance = sqrt(dx * dx + dy * dy);
            if (abs(distance - radio) < 0.5) {
                int px = (x + j * 2) % width;
                int py = (y + i) % height;

                gotoxy(px, py);
                cout << color << caracter_escritura;
            }
        }
    }
}

void dibujarTriangulo(int x, int y, int direccion, int base, const string& color, const string& caracter_escritura) {
    int altura = int(0.866 * base);

    switch (direccion) {
        case 1: // Arriba
            for (int i = 0; i < altura; ++i) {
                gotoxy(x - i, y + i);
                cout << color << caracter_escritura;
                gotoxy(x + i, y + i);
                cout << color << caracter_escritura;
            }
            for (int i = -altura; i <= altura; ++i) {
                gotoxy(x + i, y + altura);
                cout << color << caracter_escritura;
            }
            break;

        case 2: // Abajo
            for (int i = 0; i < altura; ++i) {
                gotoxy(x - i, y - i);
                cout << color << caracter_escritura;
                gotoxy(x + i, y - i);
                cout << color << caracter_escritura;
            }
            for (int i = -altura; i <= altura; ++i) {
                gotoxy(x + i, y - altura);
                cout << color << caracter_escritura;
            }
            break;

        case 3: // Izquierda
            for (int i = 0; i < altura; ++i) {
                gotoxy(x + i, y - i);
                cout << color << caracter_escritura;
                gotoxy(x + i, y + i);
                cout << color << caracter_escritura;
            }
            for (int i = 0; i < base; ++i) {
                gotoxy(x + altura, y - altura + i);
                cout << color << caracter_escritura;
            }
            break;

        case 4: // Derecha
            for (int i = 0; i < altura; ++i) {
                gotoxy(x - i, y - i);
                cout << color << caracter_escritura;
                gotoxy(x - i, y + i);
                cout << color << caracter_escritura;
            }
            for (int i = 0; i < base; ++i) {
                gotoxy(x - altura, y - altura + i);
                cout << color << caracter_escritura;
            }
            break;
    }
}

void dibujarContornoRectangulo(int x, int y, int base, int altura, const string& color, const string& caracter_escritura) {
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < base; ++j) {
            // Dibuja solo el contorno: superior, inferior, izquierdo, derecho
            if (i == 0 || i == altura - 1 || j == 0 || j == base - 1) {
                gotoxy(x + j, y + i);
                std::cout << color << caracter_escritura;
            }
        }
    }
}



void dibujarFiguras() {
    for (const auto& figura : cuadrados) {
        dibujarCuadrado(figura.x, figura.y, figura.lado, figura.direccion, figura.color, figura.caracter_escritura);
    }

    for (const auto& figura : circulos) {
        dibujarCirculo(figura.x, figura.y, figura.radio, figura.color, figura.caracter_escritura);
    }

    for (const auto& figura : triangulos) {
        dibujarTriangulo(figura.x, figura.y, figura.direccion, figura.base, figura.color, figura.caracter_escritura);
    }

    for (const auto& figura : rectangulos) {
        dibujarContornoRectangulo(figura.x, figura.y, figura.base, figura.altura, figura.color, figura.caracter_escritura);
    }

    for (const auto& figura : lineas) {
        dibujarLinea(figura.x, figura.y, figura.longitud, figura.direccion, figura.color, figura.caracter_escritura);
    }

     for (const auto& figura : rombos) {
        dibujarRombo(figura.x, figura.y, figura.dMayor, figura.dMenor, figura.color, figura.caracter_escritura);
    }

        for (const auto& figura : hexagonos) {
        dibujarHexagono(figura.x, figura.y, figura.lado, figura.color, figura.caracter_escritura);
    }
        mostrarMenu();
}

void cambioColor(int x, int y){
    int color_elegido;
x:
    gotoxy(x, y);
    cout << "Selecciona el color: " << endl << "1. Amarillo"<< endl << "2. Rojo" << endl << "3. Verde" << endl << "4. Blanco";
    cin>>color_elegido;
    if(color_elegido == 0 || color_elegido>=5){
     cout << RED << "EL COLOR INGRESADO ES INVALIDO";
     system("cls");
     cout << "Intente nuevamente" << endl;
     Sleep(1500);
     goto x;
    }
    switch(color_elegido){
       case 1:
           color_fijo = YELLOW;
        break;
       case 2:
           color_fijo = RED;
        break;
       case 3:
           color_fijo = GREEN;
        break;
       case 4:
           color_fijo = WHITE;
        break;

    }

    system("cls");
    cout <<"color nuevo selecccionado"<<endl;
    system("cls");
    dibujarFiguras();
    return;


}


void guardarDatos(string nombreArchivo) {
    ofstream archivo(nombreArchivo);

    // Verifica si se pudo crear el archivo
    if (!archivo) {
        cerr << "Error al crear el archivo " << nombreArchivo << endl;
        Sleep(2000);
            system("cls");
        return;
    }

    // Guarda los datos de los vectores en el archivo
    for (const auto& cuadrado : cuadrados) {
        archivo << "Cuadrado " << cuadrado.x << " " << cuadrado.y << " " << cuadrado.lado << " " << cuadrado.direccion << " " << cuadrado.color << " " << cuadrado.caracter_escritura <<endl;
    }

    for (const auto& circulo : circulos) {
        archivo << "Circulo " << circulo.x << " " << circulo.y << " " << circulo.radio << " " << circulo.color << " " << circulo.caracter_escritura <<endl;
    }

    for (const auto& triangulo : triangulos) {
        archivo << "Triangulo " << triangulo.x << " " << triangulo.y << " " << triangulo.base << " " << triangulo.direccion << " " << triangulo.color << " " << triangulo.caracter_escritura <<endl;
    }

    for (const auto& rectangulo : rectangulos) {
        archivo << "Rectangulo " << rectangulo.x << " " << rectangulo.y << " " << rectangulo.base << " " << rectangulo.altura << " " << rectangulo.color <<" " << rectangulo.caracter_escritura << endl;
    }
        for (const auto& linea : lineas) {
        archivo << "Linea " << linea.x << " " << linea.y << " " << linea.longitud << " " << linea.direccion << " " << linea.color << " " << linea.caracter_escritura <<endl;
    }

     for (const auto& rombo : rombos) {
        archivo << "Rombo " << rombo.x << " " << rombo.y << " " << rombo.dMayor << " " << rombo.dMenor << " " << rombo.color << " " << rombo.caracter_escritura <<endl;
    }

         for (const auto& hexagono : hexagonos) {
        archivo << "Hexagono " << hexagono.x << " " << hexagono.y << " " << hexagono.lado << " " << hexagono.color << " " << hexagono.caracter_escritura <<endl;
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
                Sleep(2000);
            system("cls");
        return;
    }

    // Variables temporales para almacenar los datos mientras se leen del archivo
    string tipo;
    int x, y, base, altura, lado, radio, longitud, direccion, dMayor, dMenor;
    string color;
    string caracter_escritura;

    // Lee la información del archivo y almacena los datos en los vectores
    while (archivo >> tipo) {
        if (tipo == "Cuadrado") {
            archivo >> x >> y >> lado >> direccion >> color >> caracter_escritura;
            Cuadrado cuadrado = {x, y, lado, direccion, color, caracter_escritura};
            cuadrados.push_back(cuadrado);
        } else if (tipo == "Circulo") {
            archivo >> x >> y >> radio >> color;
            Circulo circulo = {x, y, radio, color, caracter_escritura};
            circulos.push_back(circulo);
        } else if (tipo == "Triangulo") {
            archivo >> x >> y >> base >> direccion >> color >> caracter_escritura;
            Triangulo triangulo = {x, y, base, direccion, color, caracter_escritura};
            triangulos.push_back(triangulo);
        } else if (tipo == "Rectangulo") {
            archivo >> x >> y >> base >> altura >> color >> caracter_escritura;
            Rectangulo rectangulo = {x, y, base, altura, color, caracter_escritura};
            rectangulos.push_back(rectangulo);
        }else if (tipo == "Linea") {
            archivo >> x >> y >> longitud >> direccion >> color >> caracter_escritura;
            Linea linea = {x, y, longitud, direccion, color, caracter_escritura};
            lineas.push_back(linea);
        }else if (tipo == "Rombo") {
            archivo >> x >> y >> dMayor >> dMenor >> color >> caracter_escritura;
            Rombo rombo = {x, y, dMayor, dMenor, color, caracter_escritura};
            rombos.push_back(rombo);
        } else if (tipo == "Hexagono") {
            archivo >> x >> y >> lado >> color >> caracter_escritura;
            Hexagono hexagono = {x, y, lado, color, caracter_escritura};
            hexagonos.push_back(hexagono);
        }
    }

    archivo.close();

    cout << "Obteniendo figuras y creandolas desde archivo: " << nombreArchivo << endl;
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

// Función para limpiar los vectores de figuras
void limpiarVectores() {
    cuadrados.clear();
    circulos.clear();
    triangulos.clear();
    rectangulos.clear();
    lineas.clear();
    cout << "Vectores limpiados." << endl;
}

void abrirArchivo() {
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo: ";
    cin >> nombreArchivo;

    if (!cuadrados.empty() || !circulos.empty() || !triangulos.empty() || !rectangulos.empty()) {
        char opcion;
        cout << "Si cargas el archivo, se perdera el contenido actual, quieres cancelar S/N";
        cin >> opcion;

        if (toupper(opcion) == 'N') {
            cout << "Operación cancelada." << endl;
            return;
        } else {
            limpiarVectores(); // Limpiar vectores si el usuario elige sobrescribir
        }
    }

    cargarArchivoAvectores(nombreArchivo);
}

// funcion para insertar figuras en los vectores

void insertarPosFigura(int x, int y, string tipoFigura){

    if(tipoFigura == "cuadrado") {
        string color = color_fijo;
        string caracter_escritura = caracter_fijado;
        int direccion;
        int lado;
        cout << "lado:";
        cin >> lado;
        if (!validarValor(lado)) {
            cout << "El valor ingresado es incorrecto";
            return;
        }
        cout << "direccion:" << endl << "1. Arriba" << endl << "2. abajo" << endl << "3. Izquierda" << endl << "4. Derecha" << endl;
        cin >> direccion;
        if(direccion == 0 || direccion >=5){
            cout << "El valor ingresado es incorrecto";
            Sleep(1500);
            system("cls");
            dibujarFiguras();
            return;
        }
        Cuadrado nuevo_cuadrado = {x, y, lado, direccion, color, caracter_escritura};
        cuadrados.push_back(nuevo_cuadrado);
        system("cls");
        dibujarFiguras();

    }

       if (tipoFigura == "triangulo") {
        string color = color_fijo;
        string caracter_escritura = caracter_fijado;
        int base;
        cout << "Base: ";
        cin >> base;
        if (!validarValor(base)) {
            cout << "El valor ingresado es incorrecto";
            dibujarFiguras();
            return;
        }
        int direccion;
        cout << "Direccion: " << endl << " 1. Arriba  " << endl << " 2. Abajo " << endl << " 3. Izquierda  " << endl << " 4. Derecha " << endl;
        cin >> direccion;
        if (direccion == 0 || direccion >= 5) {
            cout << "El valor ingresado es incorrecto";
            Sleep(1500);
            system("cls");
            dibujarFiguras();
            return;
        }
        Triangulo nueva_figura = {x, y, base, direccion, color, caracter_escritura};
        triangulos.push_back(nueva_figura);
        system("cls");
        dibujarFiguras();
    }

    if(tipoFigura == "circulo") {
        string color = color_fijo;
        string caracter_escritura = caracter_fijado;
        int radio;
        cout << "Diametro: ";
        cin >> radio;
        if (!validarValor(radio)) {
            cout << "El valor ingresado es incorrecto";
            return;
        }
        Circulo nueva_figura = {x, y, radio, color, caracter_escritura};
        circulos.push_back(nueva_figura);
        system("cls");
        dibujarFiguras();
    }

        if(tipoFigura == "rectangulo") {
        string color = color_fijo;
        string caracter_escritura = caracter_fijado;
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
        Rectangulo nueva_figura = {x, y, base, altura, color, caracter_escritura};
        rectangulos.push_back(nueva_figura);
        system("cls");
        dibujarFiguras();
    }
    if(tipoFigura == "linea"){
        string color = color_fijo;
        string caracter_escritura = caracter_fijado;

        int longitud;
        int direccion;

        cout << "Ingrese la longitud de la línea: ";
        cin >> longitud;
        if (!validarValor(longitud)) {
            cout << "Longitud inválida." << endl;
            Sleep(2000);
            system("cls");
            return;
        }

        cout << "Direccion: " << endl << " 1. arriba  "<< endl << "2. abajo "<< endl << " 3. izquierda  "<< endl << " 4. derecha. " << endl << " 5 diagonal abajo derecha"  << endl << " 6 diagonal arriba izquierda"  << endl << " 7 diagonal arriba derecha"  << endl << " 8 diagonal abajo izquierda"  << endl;
        cin >> direccion;
        if(direccion == 0 || direccion >=9){
            cout << "Dirección no válida.";
            Sleep(2000);
            system("cls");
            dibujarFiguras();
            return;
        }

        Linea nueva_linea = {x, y, longitud, direccion, color, caracter_escritura};
        lineas.push_back(nueva_linea);
        system("cls");
        dibujarFiguras();
        } else if (tipoFigura == "rombo") {
            int dMayor, dMenor;
            string color = color_fijo;
            string caracter_escritura = caracter_fijado;
            cout << "Ingrese la diagonal mayor del rombo: ";
            cin >> dMayor;
            validarValor(dMayor);
            cout << "Ingrese la diagonal menor del rombo: ";
            cin >> dMenor;
            validarValor(dMenor);
            Rombo rombo = {x, y, dMayor, dMenor, color, caracter_escritura};
            rombos.push_back(rombo);
            system("cls");
            dibujarFiguras();
        } else if (tipoFigura == "hexagono") {
        string color = color_fijo;
        string caracter_escritura = caracter_fijado;
        int lado;
        cout << "Lado del hexágono: ";
        cin >> lado;
        if (!validarValor(lado)) {
            cout << "El valor ingresado es incorrecto";
            return;
        }
        Hexagono nuevo_hexagono = {x, y, lado, color, caracter_escritura};
        hexagonos.push_back(nuevo_hexagono);
        system("cls");
        dibujarFiguras();
    }

    }


    void cambiarCarcterEscritura(){

        cout<< "Escribe el nuevo caracter:" << endl;
        cin>>caracter_fijado;
        cout<< "Se ha seteado el caracter: " << caracter_fijado << endl;
        Sleep(2000);
        system("cls");
        dibujarFiguras();
        return;

    }


// funcion para leer las teclas de funcion especiales
void handleFunctionKey(int key, int x, int y) {
    switch (key) {
        case 59: // F1 //cuadradp
            tipoFigura = "triangulo";
            insertarPosFigura(x, y, tipoFigura);
            break;
        case 60: // F2
            tipoFigura = "cuadrado";
            insertarPosFigura(x, y, tipoFigura);
            break;
        case 61: // F3
            tipoFigura = "rectangulo";
            insertarPosFigura(x, y, tipoFigura);
            break;
        case 62: // F4
            tipoFigura = "circulo";
            insertarPosFigura(x, y, tipoFigura);
            break;
        case 63: // F5
            tipoFigura = "linea";
            insertarPosFigura(x, y, tipoFigura);
            break;
        case 64: // F6
            tipoFigura = "rombo";
            insertarPosFigura(x, y, tipoFigura);
            break;
        case 65: // F7
            tipoFigura = "hexagono";
            insertarPosFigura(x, y, tipoFigura);
            break;
        case 66:
            cambiarCarcterEscritura();
            break;
        case 67:
            system("cls");
            cuadrados.clear();
            circulos.clear();
            triangulos.clear();
            lineas.clear();
            rombos.clear();
            rectangulos.clear();
            gotoxy(x, y);
            cout << RED <<"Limpiando Pantalla" << endl;
            Sleep(2000);
            system("cls");
            mostrarMenu();
            break;
        case 68: // F10
            cambioColor(x, y);
            break;
        case 69: // F10
            mostrarMenu();
            break;
        case 134: // ctrl + A
            guardarDatosName();
            break;
        case 7: // ctrl + A
            guardarDatosName();
            break;
        case 1: // ctrl
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
                    case 72: // Flecha hacia arriba
                        y = (y - 1 + height) % height;
                        break;
                    case 80: // Flecha hacia abajo
                        y = (y + 1) % height;
                        break;
                    case 75: // Flecha hacia la izquierda
                        x = (x - 1 + width) % width;
                        break;
                    case 77: // Flecha hacia la derecha
                        x = (x + 1) % width;
                        break;

                }
                gotoxy(x, y);
                cout << "";
            }
        }
        Sleep(10);

    }
}
