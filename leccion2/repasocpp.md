# Día 2: Recordatorio de C++

## Variables y estructura básica

###Hola Mundo

Un programa de C++ tiene una estructura como la siguiente:

```c++
#include<iostream>
#include<cstdlib>

using namespace std;

int main(void)
{
    cout << "Hola Mundo" << endl;
    return 0;
}
```
Al principio, lo que hacemos es incluir las bibliotecas necesarias para nuestro programa. Después, decimos que queremos usar el espacio de nombres estándar (eso evitará, por ejemplo, tener que escribir `std::cout` todo el rato). Por último, viene la función principal. El programa siempre empezará a ejecutarse por esta función. Todo lo que va entre las llaves forma parte de la función principal. Al final, esta debe devolver 0, cuando acabe el programa. Esto indicará al ordenador que nuestro programa funcionó correctamente y sin incidencias. La instrucción `cout` se ha utilizado para mostrar un mensaje por pantalla al usuario. Observa que cada instrucción en C++ termina por un punto y coma. 

Para compilarlo con Code::Blocks, podemos pulsar la tecla F9 o el icono de "play" con engranajes en el menú. Una cosa que llama la atención de CB, si has usado otros entornos, es que detiene la ejecución al acabar el programa, de modo que la ventanita de la terminal generada no se cierra incluso sin ponerle una instrucción al final que pida una tecla por el usuario. Además, da el tiempo de ejecución del programa, lo cual es muy útil.

Si hay errores, aparecerán en el log de errores abajo. Si has escogido quitar todo lo que molestaba en la pantalla, puedes traer de vuelta el log de errores con la tecla F2. Cada error tiene una descripción e indica qué línea lo produjo. Hacer click sobre él lleva automáticamente a la línea problemática.

Dado que cada programa de C++ que escribamos queremos que tenga esta estructura básica, es posible añadirla como plantilla a Code::Blocks, escribiendo el código en *Settings > Editor...*, en el icono *Default Code*.

### Variables
Las variables son sitios de memoria reservados en el ordenador donde podemos guardar datos. Recordar cuál es cada dirección de memoria es muy complicado, así que a cada dirección le podemos dar un nombre, para recordarla mejor, así como un tipo, para indicar al ordenador cuánta memoria ha de reservar. Una variable es declarada como `tipo_variable nombre;`. En C++ hay muchos tipos, pero a nosotros lo que nos interesan son:

```c++
int entero; //Un número entero, positivo o negativo
float flotante; //Un número decimal, precisión simple
double doble; //Número decimal, precisión doble
bool booleano; //Verdadero o falso
char caracter; //Caracter
```
La única diferencia entre `float` y `double` es la precisión. Ambos son números *en coma flotante*, es decir, pueden tener decimales, pero `double` es más preciso que `float` (a costa, por supuesto, de ocupar el doble de bytes en memoria).  Ahora, puede que queramos asignar un valor a las variables. Esto ha de hacerse con el operador `=` , de la siguiente manera:

``` c++
 int entero; //Declarar el entero
 entero = 6; //Ahora entero tiene el valor 6
 entero = -3; //Ahora entero tiene el valor -3
```
 
 C++ admite notación cientiica en los números decimales:


``` c++
 double decimal; //Declarar la variable
 decimal = 1.2345; 
 decimal = 1.2e-4; //Ahora decimal es 0.00012
```
 
Las variables booleanas solo pueden valer verdadero o falso:

``` c++
bool b = true; //Se puede declarar y asignar a la vez
b = false;
```
Y es posible declarar varias variables del mismo tipo, al mismo tiempo:
    
``` c++
double d1, d2;
d1 = 1.2;
d2 = -1.2;
```
A la hora de elegir nombres para variables, hay que recordar las siguientes reglas:

1. No pueden empezar por un número.
2. Son sensibles a mayúsculas: variable y vaRiable son diferentes.
3. No pueden contener caracteres especiales, como ñ, á, ö.
4. No pueden contener espacios (pero sí guiones bajos, `_`).

Y las convenciones de C++:

1. Lo mejor es que el nombre dé información sobre para qué sirve la variable.
2. Las variables se escriben empezando en minúscula.

### Operando con variables

En C++ podemos operar de forma parecida a una calculadora, usando los operadores `+,-,*,/`:

``` c++
double d1, d2, d3;
d1 = 1.5;
d2 = 3.0;
d3 = d1 + d2; //d3 vale 4.5
d3 = 2.0 * d1; //d3 vale 3.0
d3 = d1 / d2; //d3 vale 0.5
```

Poseemos además los operadores `+=,-=,*=,/=` para modificar el valor de una variable:

``` c++
int numero = 0;
numero += 2; //numero vale 2 
numero *= 3; //numero vale 6
```
Para las variables de tipo entero tenemos los operador `++` y `--` , que aumentan o disminuyen el valor de la variable en uno:


``` c++
int numero = 0;
numero++; //Ahora numero vale 1
```


Para trabajar con variables booleanas, están los operadores lógicos `and, or, not`, que habitualmente se suelen escribir como `&&, ||, !`. Por ejemplo,

``` c++
bool b1, b2, b3;;
b1 = true;
b2 = false;
b3 = b1 and b2; //b3 es falso
b3 = b1 && b2; //Equivalente a la de arriba
b3 = !b1; //b3 es falso
b3 = !(b1 && !b2) //b3 es falso
```

Para realizar comparaciones, podemos emplear `>,>=,<,<=,==,!=`.  Observa que la comprobación se hace con dos iguales (puesto que uno solo es una asignación), y el operador `!=` significa "distinto de".

``` c++
double d1,d2;
bool comparacion;
d1 = 2.0;
d2 = 3.0;
comparacion = d1 < d2; //comparacion es verdadero
comparacion = d1 >= d2; //comparacion es falso
comparacion = d1 != d2; //comparacion es verdadero
comparacion = d1 == 2.0; //comparacion es verdadero
comparacion = d1 == 2.0 && d2 >= 3.0; //comparacion es verdadero
```

## Mostrar y recibir variables

### Uso básico de `cout`

Interesa, en este punto, ser capaces de mostrar valores de variables por pantalla, así como permitir al usuario recibirlas. Para mostrar algo por pantalla, usamos la instrucción `cout`. Si queremos mostrar el valor de una variable,

``` c++
int v = 5;
cout << v;
```

Mientras que las cadenas de texto las ponemos entre comillas,

``` c++
cout << "Hola";
```

Podemos concatenar cosas:

``` c++
int v = 5;
cout << "v vale " << v;
```
Observa que en el texto hemos dejado un espacio entre "vale" y la variable `var`. Esto es algo que tenemos que hacer manualmente. Si queremos meter un salto de línea (como una tecla "Intro" en un procesador de textos) usamos la palabra clave `endl`:

``` c++
int v = 5;
cout << "v vale " << endl << v << endl;
``` 

Esto dejará un reglón entre "Var vale" y el valor de la variable, y dejará un salto de línea para la próxima orden `cout` .

### Uso básico de `cin` 
Para permitir al usuario introducir valores a las variables de nuestro programa, tenemos la instrucción `cin`. Su sintaxis es muy parecida a la de `cout `,

``` c++
int v;
cin >> varv;
cout << "Var vale " << endl << v << endl;
``` 

En este caso, al ejecutar el programa aparecerá la terminal, y quedará esperando a que el usuario escriba un número y pulse la tecla Intro. Es posible también leer varias variables con una sola instrucción `cin`:

``` c++
int v;
double d;
cout << "Escriba un entero y un decimal, separados por un espacio" << endl;
cin >> v >> d;
``` 
Como hemos especificado, el `cin` en este caso recibe las dos variables. Vale cualquier separador, y no solo un espacio. Es importante, como hemos hecho en este último ejemplo, especificar al usuario qué se espera que haga.


## Tomando decisiones
Podemos elegir si hacer una u otra cosa en función del valor que tengan nuestras variables mediante la instrucción `if`. Esta tiene la siguiente sintaxis: 

``` c++
if (variable_booleana)
{
    //Codigo si variable_booleana es verdadera
}
```
C++ ejecutará el código que se encuentre dentro de las llaves solamente si el valor de la variable entre paréntesis es verdadero. Por ejemplo,
``` c++
double d1 = 1.5;
if (d1 < 3.0)
{
    d1 += 1.0;
}
```
Al final de este código `d1` tendrá el valor 2.5, ya que la condición entre paréntesis devuelve "verdadero".  

Podemos incluir también la instrucción `else`, que puede usarse para complementar al `if`:
``` c++
if (variable_booleana)
{
    //Codigo si variable_booleana es verdadera
}
else
{
    //Codigo si variable_booleana es falsa
}
```

Con esta estructura es posible realizar todas las comparaciones que queramos. Es interesante comentar también el hecho de que tanto `if` como `else`  funcionan también sin las llaves, siempre y cuando la instrucción a ejecutar sea de una sola línea:

``` c++
double d1;
cin >> d1;

if (d1 > 0) cout << "d1 es positivo" << endl;
else cout << "d1 no es positivo" << endl;

if (d1 == 0) cout << "d1 es cero" << endl;
cout << "Esto se ejecuta siempre" << endl;
```

Esto permite escribir un código mucho más legible, y, además, nos permite *anidar* varias estructuras `if`:

``` c++
double d1;
cin >> d1;

if (d1 > 0) 
{
    cout << "d1 es positivo" << endl;
}
else if (d1 == 0)
{
    cout << "d1 es cero" << endl;
}
else 
{
    cout << "d1 no es positivo" << endl;
}

// O bien la versión corta:
if (d1 > 0) cout << "d1 es positivo" << endl;
else if (d1 == 0) cout << "d1 es cero" << endl;
else cout << "d1 no es positivo" << endl;
```
Podemos encadenar tantos `else if` como sean necesarios, permitiendo estructuras relativamente complicadas.

## Bucles

Muy frecuentemente queremos ejecutar una instrucción muchas veces seguidas, especialmente, en combinación con los *arrays*, como veremos enseguida.  Para ello, tenemos los bucles. 

### Bucle `while`

Este bucle tiene la siguiente sintaxis:
``` c++
while(variable_booleana)
{
    //Repetir
}
```
Repetirá todo lo que esté en el cuerpo de la función, mientras la condición que le demos devuelva verdadero.  Por ejemplo, para mostrar los números del 0 al 99,

``` c++
int i = 0;
while(i < 100)
{
    cout << i << " "; //Deja un espacio entre número y número
    i++; //Aumenta el contador
}
```

Observa que el bucle tiene tres partes importantes: iniciar el valor de la variable `i`, la condición que va dentro del `while`, y actualizar la variable `i` al final de cada vuelta. Sin la actualización, la condición siempre será verdadera y no podremos salir del bucle
Esto es común a todos los bucles.

### Bucle `for` 

La sintaxis del bucle `for` es muy similar a la del `while` :

``` c++
for(inicialización; condición; actualización)
{
    //Repetir
}
```

En este caso, el procedimiento que hacíamos manualmente en el `while` , de iniciar, ver la condición y actualizar al final, es requerido en la sintaxis del `for` , lo que lo hace habitualmente más cómodo para programar (aunque tiene otras desventajas, como veremos más adelante). 

El mismo ejemplo de antes se puede escribir como:

``` c++
int i;
for (i=0; i<100; i++)
{
    cout << i << " ";
}
```

### Arrays 
Llegamos ahora a las estructuradas conocidas como *arrays* en C++. Un array no es más que una tabla que es capaz de almacenar una serie de valores del mismo tipo. A menudo se le suele llamar vector, pero nosotros evitaremos esa palabra para no confundirlo con la clase `vector` de la biblioteca estándar de C++ más adelante.

Un array se declara de la siguiente forma:

	tipo nombre_variable[tamaño];

donde el tamaño es el número de elementos que va a contener nuestra lista de valores.
Por ejemplo:
``` c++
double lista[100];
```
Almacena 100 variables de tipo `double` .  Cada una de ellas está representada por un índice, que va del 0 al 99. Por ejemplo, podemos darle valores a algunas:

``` c++
double lista[100];
lista[0] = 1.2; //Primer elemento de la lista
lista[19] = -5.8; //Elemento número 20
lista[99] = 1e3; //Último elemento
```
Podemos darle un valor a cada una de ellas utilizando un bucle, por ejemplo:

``` c++
int i;
double lista[100];
for (i=0; i < 100; i++)
{
    lista[i] = 1.0;
}
```

Inicializa todos los elementos de la lista a 1.0. A la hora de trabajar con listas, es importante tener cuidado de que accedemos únicamente a índices que existen. Por ejemplo, si intentamos acceder a `lista[100]`, o `lista[-1]` , el programa dará un error y se detendrá sin previo aviso. En sistemas como Windows dejará la aplicación colgada, mientras que Linux se quejará de un `segmentation fault`. 

Hay que notar, además, que la cantidad de datos que podemos almacenar en un array está limitada por nuestra RAM. Debemos ser cautelosos a la hora de trabajar con arrays grandes. Por defecto, C++ evita que pongamos tamaños demasiado grandes a los arrays. Si lo intentamos, el programa simplemente se parará al ejecutarlo, sin hacer nada. En otros casos, debemos tener cuidado y ser conscientes de la memoria que almacenamos siempre.
Podemos ver qué tamaño tiene (en bytes) cualquier variable de C++ usando `sizeof`, de la siguiente manera:

``` c++
int i;
int lista[100];
cout << sizeof(i) << " " << sizeof(lista) << endl;
```

El resultado de este programa es `4 400`, indicando que un solo entero ocupa 4 bytes de memoria, mientras que nuestra lista tiene 400 bytes (cerca de 0.5kb).

Podemos hacer, además, arrays de arrays, que sería el equivalente a una tabla con filas y columnas, o arrays 3D, que tendrían otra dimensión. Por ejemplo, para crear una tabla y rellenar todas sus entradas, necesitamos ahora dos bucles,

``` c++
int i,j;
double tabla[10][5];
for (i=0; i < 10; i++)
{
    for (j=0; j < 5; j++)
    {
        tabla[10][5] = i*j;
    }
}
```

Es claro que trabajar con tablas más alla de 3D tiene unos requerimientos muy altos, tanto de memoria como de procesamiento (hay que hacer muchas operaciones para visitar todos los elementos de la tabla). **Hay que tratar de buscar siempre opciones mejores a partir de tener arrays 3D o superiores, a menos que tengan unos tamaños reducidos.** 

## Funciones

Finalmente, vamos a repasar la estructura de las funciones en C++.  Una función es un trozo de código que vive fuera de la función principal `main`, y que puede ser llamada cuantas veces queramos para ejecutar ese pequeño trozo de código, sin andar copiando, pegando y/o modificando. Por ejemplo, supongamos que yo le doy una variable a la función, y quiero calcular como resultado un polinomio de segundo grado, $q(x)=x^2-x+2$. Entonces, puedo definir

``` c++
double qx(double x)
{
    return x*x-x+2;
}
```

Como puedes ver, la sintaxis de una función es muy sencilla. Tengo que darle un tipo, un nombre y unos argumentos de entrada. La función, tras realizar su cometido, devolverá (usando `return`) el resultado. Puedo calcular valores del polinomio usando la función:

``` c++
double x;
for (x=-1; x<=1; x+=0.01)
{
   cout << qx(x) << endl;
}
```
Una función puede elegir no devolver ningún valor, usando el tipo `void`. Por ejemplo, la siguiente muestra la suma de dos números, sin devolver nada:

``` c++
void suma(double x, double y)
{
    cout << x+y << endl;
    return; //Esta línea es opcional
}
```

Y se le puede llamar sencillamente con `suma(4.0,1.0)`, por ejemplo. 

Una función no puede cambiar, por defecto, los valores de las variables que le damos como argumento. Por ejemplo, si modificamos la función suma de la siguiente manera:


``` c++
void suma2(double x, double y)
{
    x = 1.0;
    y = 0.0;
    cout << x+y << endl;
    return; 
}
```

La función siempre mostrará `1.0` independientemente del valor que le demos.  Pero no es capaz de cambiar el valor de sus argumentos fuera de la función, es decir, el programa

``` c++
double x = 5.0;
double y = -1.0;
suma2(x,y);
cout << x << " " << y << endl;
```
muestra la siguiente salida:

	1.0
	5.0  -1.0
Es decir, que `x` e `y`  no han cambiado su valor fuera de la función. Esto es porque al llamar a una función, lo que hace el compilador es copiar los valores de `x` e `y`  a unas variables auxiliares, y lo que nosotros estamos cambiando dentro de la función son esas variables auxiliares. 

Aunque esto puede ser deseable en muchas ocasiones, en otras queremos explícitamente que una función cambie el valor de nuestras variables. Esto se puede hacer dándole como argumento una referencia a la variable, en lugar de la variable en sí misma. Al hacerlo, le estaremos dando el lugar físico en el ordenador donde se encuentra la variable, y modificará ese valor directamente.

``` c++
void suma3(double &x, double &y)
{
    x = 1.0;
    y = 0.0;
    cout << x+y << endl;
    return; 
}
```
La diferencia es sutil (los  `&` en el argumento), pero cambia el comportamiento del ćodigo. Ahora, el output del programa anterior, si usamos `suma3` , será 

	1.0
	1.0  0.0

de modo que realmente ha cambiando el valor de `x` e `y` . Nótese que en este caso no podemos invocar una función tipo `suma3(4.0,3.0)`, puesto que realmente el número 4 no tiene una dirección de memoria en el ordenador que poder tocar. No se le puede asignar al número 4 el número 1. En este caso, la forma correcta de hacerlo es con `suma2(4.0, 3.0)`.

Por último, resaltar que los arrays siempre se pasan por referencia, es decir, como si tuvieran delante una `&` aunque esta no aparezca explícitamente. Esto es bueno, ya que **al pasar un array como argumento a una función, no estamos copiando el array completo, sino simplemente le decimos al ordenador dónde está en la memoria, que es mucho más rápido y consume menos RAM.**
Realicemos un ejemplo, una función que calcula la media de los elementos de un array, y después pone todos sus datos a cero:

``` c++
double promedio(lista[100])
{
    double suma = 0.0;
    int i;
    for (i=0; i < 100; i++)
    {
        suma += lista[i]; //Sumar
        lista[i] = 0.0; //Poner a 0
    }
    
    return suma/100.0; //Acabar media
}
```

Esta función se invoca de la siguiente manera:

``` c++
double lista[100];
//Rellenamos lista de alguna manera...
double media = promedio(lista);
//Ver la media:
cout << media << endl;
//Ver que los elementos han cambiado
cout << lista[0] << endl;
```

Observa que al llamarla no hace falta ponerle corchetes a `lista` , y que lo que pasamos es una referencia, de modo que al llamar a promedio, todos los elementos de `lista` pasan a ser cero.  

Una función no puede devolver un array, y la solución habitual es pasar el array resultado como argumento, para rellenarlo después. Por ejemplo, la siguiente función recibe un número y un array como argumentos. En `resultado` se guarda lo que queda de multiplicar cada elemento del array por el número:

``` c++
void marray(double a, double lista[100], double resultado[100])
{
    int i;
    for (i=0; i < 100; i++)
    {
        resultado[i] = lista[i] * a;
    }
    return;
}
```

Esta función se puede invocar de la siguiente manera:


``` c++
double x = 2.0;
double lista[100];
double resultado[100];
//Rellenar lista con algo...
marray(x,lista,resultado);
//Ver que lista*2 = resultado
cout << lista[43] << " " << resultado[43] << endl;

```
