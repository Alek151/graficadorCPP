# Manual Técnico

## Estructura del Código

El código está organizado en varias secciones principales:

1. **Librerías Incluidas**: El programa incluye varias librerías estándar de C++ para manejar entrada y salida, manipulación de archivos y funciones específicas de la consola de Windows.

2. **Definición de Colores y Estructuras de Datos**: Se definen los colores utilizados para dibujar las figuras y se declaran las estructuras de datos para representar las diferentes figuras geométricas, como cuadrados, círculos, triángulos, etc.

3. **Funciones de Dibujo de Figuras**: Se implementan funciones para dibujar cada tipo de figura geométrica en la consola de Windows. Estas funciones utilizan la función `gotoxy` para posicionar el cursor en la consola y escribir los caracteres correspondientes.

4. **Funciones de Manejo de Archivos**: Se implementan funciones para guardar y cargar el estado actual de las figuras desde un archivo. Estas funciones utilizan la biblioteca `fstream` de C++ para manipular archivos de texto.

5. **Funciones de Interfaz de Usuario**: Se implementan funciones para interactuar con el usuario, como mostrar el menú, limpiar la pantalla y manejar las teclas de función.

6. **Función Principal (main)**: La función principal del programa controla el flujo de ejecución, maneja la entrada del usuario y llama a las funciones correspondientes según la acción seleccionada.

## Descripción de Funciones Importantes

- **dibujarCuadrado(int x, int y, int lado, const string& color, const string& caracter_escritura)**: Esta función dibuja un cuadrado en la posición `(x, y)` con el tamaño especificado por el parámetro `lado`. Utiliza los colores y el carácter de escritura proporcionados.

- **guardarDatos(string nombreArchivo)**: Esta función guarda el estado actual de todas las figuras en un archivo de texto con el nombre especificado por el parámetro `nombreArchivo`.

- **cargarArchivoAvectores(string nombreArchivo)**: Esta función carga las figuras almacenadas en un archivo de texto con el nombre especificado por el parámetro `nombreArchivo` y las almacena en los vectores correspondientes.

- **insertarPosFigura(int x, int y, string tipoFigura)**: Esta función inserta una nueva figura en la posición `(x, y)` del tipo especificado por el parámetro `tipoFigura`.

- **handleFunctionKey(int key, int x, int y)**: Esta función maneja las teclas de función presionadas por el usuario y realiza las acciones correspondientes, como dibujar una figura, guardar o cargar figuras, etc.

## Conclusiones

El programa está diseñado de manera modular y estructurada, lo que facilita la comprensión y el mantenimiento del código. La separación de las funciones según su funcionalidad permite una mayor flexibilidad y escalabilidad del sistema.
