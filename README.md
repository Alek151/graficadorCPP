Proyecto: Consola de Dibujo Interactiva
Este proyecto es una consola de dibujo interactiva simple desarrollada en C++ que permite al usuario dibujar formas geométricas básicas en la pantalla de la consola, cambiar colores y gestionar los elementos de manera interactiva utilizando entradas del teclado. La aplicación admite el dibujo de cuadrados, círculos, triángulos y rectángulos. Los usuarios pueden controlar la posición y las características de estas formas utilizando teclas de función y comandos.

Característicasferentes figuras geométricas: cuadrado, círculo, triángulo y rectángulo.
Capacid
Dibujar diad para limpiar la pantalla y comenzar de nuevo.
Cambiar los colores de las figuras dinámicamente.
Mover el cursor para posicionar nuevas figuras.
Menú de línea de comandos interactivo para un control más fácil.
Requisitos
Este proyecto requiere lo siguiente:

Sistema operativo Windows
Compilador de C++
API de Windows para el manejo de la consola
Configuración y Compilación


Ejecuta la aplicación compilada, la encuentras en el direcotorio del proyecto, graficador.exe, el código se encuentra en graficador.cpp, donde podrás compilar desde la aplicación Codeblocks 


Cómo Usar

Controles:

F1: Comienza a dibujar un cuadrado. Se te pedirá que ingreses la longitud del lado.
F2: Comienza a dibujar un círculo. Se te pedirá que ingreses el radio.
F3: Comienza a dibujar un triángulo. Se te pedirá que ingreses la longitud de la base.
F4: Comienza a dibujar un rectángulo. Se te pedirá que ingreses la base y la altura.
ESC: Limpia la pantalla de todas las formas.
F5: Cambiar el color a Rojo.
F6: Cambiar el color a Verde.
F7: Cambiar el color a Amarillo.
F8: Cambiar el color a Blanco.
Teclas de flecha (W, A, S, D o w, a, s, d): Mueve el cursor por la pantalla.

Dibujando una Figura:
Presiona la tecla de función correspondiente a la figura que deseas dibujar (por ejemplo, F1 para cuadrado).
Ingresa las dimensiones según se te solicite.
La forma aparecerá en la pantalla en la ubicación del cursor.
Cambiando Colores:
Presiona F5, F6, F7 o F8 para cambiar entre Rojo, Verde, Amarillo y Blanco, respectivamente.
Cualquier figura nueva que dibujes usará el color seleccionado.
Limpiando la Pantalla:
Presiona ESC para borrar todos los dibujos de la consola.
Notas Adicionales
El tamaño de la ventana de la consola determinará el área máxima dibujable. Asegúrate de que tu ventana de consola tenga un tamaño adecuado para una mejor visibilidad.
La aplicación utiliza caracteres ASCII simples para el dibujo y podría no escalar bien en diferentes resoluciones de pantalla o configuraciones de fuente de la consola.
