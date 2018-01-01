# Día 5: Optimizar código

Ya tenemos todos los elementos que podemos necesitar para mejorar nuestro código. Podemos usar complejos, vectores, o incluso hacer nosotros nuestras propias clases. El objetivo de hoy es conseguir que el código se ejecute tan rápido como sea posible... y sin errores.

## Optimización desde el compilador

Buena parte del trabajo de optimización la puede hacer el compilador por nosotros. Veamos, para empezar, cómo compilar un programa desde la consola. Esto se hace de la siguiente manera:

```c++
g++ nombre_programa.cpp -o nombre_ejecutable
```

Como hemos comentado en tutoriales anteriores, conviene poder utilizar el estándar C++11. Para ello, 

```
g++ nombre_programa.cpp -o nombre_ejecutable -std=c++11
```

El compilador tiene muchísimas más opciones o *flags* . Una de ellas es la de optimización para velocidad: 

```
g++ -O3 nombre_programa.cpp -o nombre_ejecutable -std=c++11
```

Esta opción permite al compilador hacer algunos atajos, como desenrrollado de bucles, vectorización de funciones, o evitar llamadas a funciones, que pueden aumentar muchísimo la velocidad del código. Sin embargo, a cambio, el código puede volverse inestable si hay algún error. Aunque esto no va a producir ningún problema en nuestro ordenador, sí hace más difícil localizar los errores (por ejemplo: códigos que dan un fallo de segmento, y si escribimos `cout << "hola" << endl`  de repente llegan hasta el final). 

Code::Blocks tiene disponibles todos los *flags* del compilador. Solamente tenemos que ir a *Settings > Compiler...* y seleccionar aquellos que nos interesen por algún motivo. 

> En general, -O3 acelera el código sin ninguna consecuencia. Ahora bien, en algunos casos, las optimizaciones pueden llegar a romper el código. Si un código no funciona, es necesario comprobar si se debe a las optimizaciones.

## Depurar y encontrar errores

Una forma chapucera de depurar un programa, cuando da un error de ejecución, es ir escribiendo `cout`  para ver hasta dónde llega o cuánto valen las variables. Para andar por casa está bien, pero lo mejor es usar un depurador. GNU tiene el depurador `gdb` .

Code::Blocks puede usar `gdb` directamente en el entorno para localizar problemas, pero solo en proyectos grandes. En ficheros separados (que son los que habitualmente usamos para simular) no está disponible. Por tanto, lo mejor es usar `gdb`  desde la consola. 

`gdb`  debe actuar sobre un ejecutable que recuerde el código C++. Esto se puede hacer ejecutando:

```
g++ -g codigo.cpp -std=c++11
```

Observa que en este caso es mejor no utilizar las optimizaciones. Esto nos generará un fichero `a.out` , al que llamaremos con 

```
gdb a.out
```

La consola cambia para decirnos que estamos en `gdb`.  Para comenzar una depuración desde el principio, tecleamos `start`. Esto ejecuta la primera orden del `main` . Depurar estrictamente desde la consola es complicado, así que tenemos dos opciones:

1. Si mantenemos pulsado `Ctrl+x` y luego la tecla `a` , `gdb`  cambia para mostrar nuestro código, señalando en qué línea está. Este modo es el más cómodo. Sin embargo, a veces tiene algunos errores.
2.  El más seguro, ir avanzando con `gdb` en la consola mirando nuestro código en el editor. Debemos tener cuidado, eso sí, de que estar donde pensamos que estamos. El comando `frame`  nos dice qué línea está ejecutando el depurador.

Para movernos con el depurador, escribimos `next` para avanzar a la siguiente instrucción. Ten en cuenta que si nuestra instrucción es la llamada a una función, `gdb`  ejecutará toda la función sin entrar en ella, saltando a lo siguiente. Si queremos entrar, debemos usar `step` . Cuidado con `step` , para no entrar dentro del código de bibliotecas que estemos usando. No hay ningún problema, pero nos hará perder el tiempo.

Puede que el sitio al que queramos llegar en el código esté muy lejos. Por ejemplo, si tenemos delante un bucle de 10000 iteraciones, no queremos ir comprobado iteración a iteración. Para eso, podemos decirle a `gdb`  el sitio donde queremos que pare:

```
break numero_linea
```

Esto añade un *punto de interrupción*. Cuando utilicemos la orden `run` , el programa avanzará hasta encontrar el próximo punto de interrupción.

Avanzando de esta forma, podemos ver exactamente dónde está el error de nuestro programa. Pero es más, podemos ver qué valor tienen las variables, a cada momento. Para ver el valor de una variable concreta, escribimos

```
display nombre_variable
```

Si la variable en realidad es un objeto, `gdb` nos muestra el valor que tiene cada uno de sus miembros. Podemos pedirle también que nos muestre el valor de todas las variables locales (es decir, definidas dentro de la función actual), con
```
info locals
```

Una vez hayamos encontrado el error de nuestro código, bastará con escribir `quit`  para salir del depurador. Nos preguntará si queremos cerrar el proceso, a lo cual decimos que sí.


## Algunos trucos para optimizar

### 1. Cada operación importa

Siempre se trata de tratar de reducir al máximo el número de operaciones que hacemos. Esta clase de optimización, habitualmente, no va a influir muchísimo en el código, pero debemos tener cuidado con ella.  Por ejemplo,

```c++
double sum = 0.0;
double c = 1.23456;
int n = 1000;
for (i=0; i < n; i++)
{
    sum += 3.14159 * sqrt(c + 2.0) * exp(-3.0 + i) / n;
}
```

Muchas de las operaciones estamos haciéndolas muchas veces, pero dan siempre el mismo número.  ¿Por qué las hacemos? Bastaría guardarlas en una variable una única vez.

```c++
double sum = 0.0;
double c = 1.23456;
double aux = 3.14159 * sqrt(c + 2.0) * exp(-3.0)/n;
int n = 1000;
for (i=0; i < n; i++)
{
    sum +=  aux * exp(i);
}
```

Aunque esto no se va a notar mucho con las operaciones aritméticas, sí hay una diferencia si incluye funciones como senos, exponenciales, o raíces cuadradas. Por ejemplo, la función `sqrt` , cada vez que es llamada, ejecuta una variante del algoritmo de Newton-Rapshon. Es decir, hay un **bucle** por cada llamada. Otras funciones simplemente están representadas por una serie de Taylor, o una más eficiente. En todo caso, al final es un bucle dentro de otro. Estas funciones debemos tratar de evitarlas lo máximo posible. 

En concreto, a la hora de calcular distancias, es buena práctica trabajar con las distancias al cuadrado siempre y cuando sea posible, por ejemplo, en el siguiente código que comprueba si un punto está dentro de un círculo centrado en cero:

```c++
double r = 10.0;
double r2 = r*r; //Calcular el cuadrado
double x,y;
cout << "Introducir un punto" << endl;
cin >> x >> y;

if (x*x+y*y <= r2) cout << "dentro" << endl;
```

### 2. Usa siempre las referencias

Esto es algo en lo que he insistido bastante en el tutorial de clases, pero merece la pena decirlo una vez más: evita las copias. Pueden acabar (mucho antes de lo que te imaginas) con la RAM de tu ordenador, y, encima, hacen el código mucho más lento. **Pasa siempre los objetos por referencia.**

### 3. ¡Constantes!

Si algo es constante, házselo saber al compilador. Si una función de la clase no cambia, escríbelo con `tipo nocambia(args) const`. Esto evita, por un lado, errores de compilación. Por otro, ayuda enormemente al compilador en la tarea de optimizar, ya que puede hacer algunas asunciones en los bucles y similares.

Otro consejo es tener cuidado con el comando `#define`. Para una constante numérica está bien, pero ten en cuenta que lo que hace es directamente **sustituir texto**, es decir,

```c++
#define h1 42
#define h2 int(sqrt(h1))

//Código:
for (i=0; i < h2; i++) s += h1;

//Lo que piensas que hace:
for (i=0; i < 6; i++) s += 42;

//Lo que en realidad hace:
for (i=0; i < int(sqrt(42)); i++) s+=42;
```

De hecho, se puede llegar al culmen de la maldad con este comando:

```c++
#define true false
#define 42 true

int answer_to_everything = 42
```

Sí, efectivamente, `anwer_to_everything` vale ahora `true` , que se ha sustituido por `false` , que en realidad tiene una equivalencia entera a 0. Cada 42 será sustituido por 0. Y no quieres utilizar la palabra clave `true`  en este código. 

### 4. Evita los cambios de tamaño innecesarios

La operación más lenta de los vectores es cambiar el tamaño. Intenta evitarlo siempre que sea posible, por ejemplo, inicializando los vectores con su tamaño en lugar de trabajar con `push_back` :

```c++
//Esto es lento...
vector<int> v = vector<double>();
for (i=0; i < 10000000; i++) v.push_back(i);

//...esto más es rápido:
vector<int> v = vector<double>(10000000);
for (i=0; i < 10000000; i++) v[i] = i;
```
 
[Esta comparativa](https://lemire.me/blog/2012/06/20/do-not-waste-time-with-stl-vectors/) muestra que podemos estar haciendo un ahorro importante, si realizamos muchas veces esta operación.

### 5. Cuidado con `erase` .

Cuando queremos borrar un elemeto en una posición arbitraria, usualmente utilizamos `erase` sin echarle más cuentas. Sin embargo, esta función es muy lenta: elimina el elemento en la posición `j` , y luego coge el `j+1`  y lo pone en `j` , el `j+2`  lo pone en `j+1` , hasta que llega al final. En un vector de un millón elementos, en el que eliminamos los elementos 500.000, 500.001, y 500.002,  tenemos por debajo un millón y medio de iteraciones. Supongamos que esto va dentro de un bucle que se ejecuta miles de veces. 

La moraleja, igual que pasaba con `sqrt` , es que hay  para optimizar hay que saber más o menos cómo funciona la librería que estoy utilizando. `erase`  es buena opción para eliminar un elemento si no queremos alterar el orden del vector. Sin embargo,  a menudo el orden en el que están guardados los elementos en el vector me es indiferente. Con lo cual, podemos escribir:

```c++
template<class T>
void fast_erase(vector<T>& v, int index)
{
    v[index] = v[v.size() - 1];
    v.pop_back();
    return;
}
```

Este código simplemente coge el último elemento y lo cambia de sitio, sobreescribiendo el que queremos borrar. Después, eliminamos el último. Es absolutamente equivalente a intercambiar de sitio el que queremos borrar y el último, y eliminarlo con `pop_back`.  Esta función hace unas pocas operaciones, independientemente del tamaño del vector. Si queremos los elementos 500.000, 500.001, y 500.002, como antes, ahora nos cuesta menos de 30 operaciones. Puedes imaginar que 30 operaciones frente al millón y medio de antes suponen una diferencia.

Todo esto aplica también a `insert` . Si el orden da igual, ¡usa `push_back`!

### 6. Haz tablas

En cálculo numérico, a veces hay que calcular algunas funciones que son costosas numéricamente. Un ejemplo claro es el binomio de Newton.  Si intentamos calcularlo con factoriales,  el ordenador se quejará. Hay fórmulas iterativas para obtenerlo. Ahora bien, supongamos que tenemos `n`  fijo y necesitamos hacer cuentas con `binomio(n,j)` . Muchas cuentas, digamos dentro de un bucle.  Para `n ` grandes, este método es muy ineficiente, porque ya tengo que hacer `n`  iteraciones para calcular `binomio(n,j)` . Una solución es calcular todos los binomios posibles para `n`  dado y almacenarlos en una tabla. Esto puede llevar bastante tiempo, pero en muchos casos a la larga permite hacer más eficiente el código.

Otro ejemplo. Supongamos que tenemos una función, digamos `f(x)`, definida como una sumatoria de 20 integrales (que no se pueden resolver analíticamente). Un método adecuado puede resolver esta función en un tiempo razonable, digamos, por ejemplo, un segundo.

Ahora bien, podríamos querer, por ejemplo, integrar `log(f(x))dx`. Para ello podemos usar cualquier método numérico. Digamos que nos gusta [la regla del trapecio](https://en.wikipedia.org/wiki/Trapezoidal_rule).  Tanto este, como cualquier otro, al final reduce la integral a realizar una sumatoria. El problema es que el código quedará algo parecido a esto:

```c++
double N = 1000;
double dx = (b-a)/N;
double integral = 0.0;
for (x=a; x < b; x += dx)
{
    integral = (f(x) + f(x + dx)) / 2.0
}
```

El número de iteraciones que hagamos será igual a `N` . Si nuestra función tarda un segundo, y tenemos que calcularla dos veces por cada iteración, necesitamos `2N`  segundos, que media hora. Para `N=10000`, 5 horas. Una forma de mejorar el código es la siguiente:


```c++
double N = 1000;
double dx = (b-a)/N;
double integral = 0.0;
double fx, fxp;

fxp = f(a);
for (x=a; x < b; x += dx)
{
    fx = fxp;
    fxp = f(x + dx);
    integral = (fx + fxp) / 2.0
}
```

Como al paso siguiente `f(x)` es la `f(x+dx)` el anterior, podemos guardarla en memoria para el siguiente paso, y evitar calcularla dos veces. Esto reduce el tiempo efectivamente a la mitad, es decir, 15 minutos o dos horas y media, dependiendo de `N`. Esta es una optimización muy importante. En métodos de integración más avanzados, que llamen 3, 4, o 5 veces a `f(x)`, se vuelve cada vez más y más importante.

A veces, sin embargo, esto no es suficiente porque `N` es muy grande,  o porque hacemos muchas integraciones en diferentes intervalos `[a,b]`, o cualquier otro motivo. Entonces, puede ser interesante escribir la función en una tabla discreta. Así, el vector `tabla[j]`  contiene `f(x0 + h * j)` .  La pregunta es cómo obtener cualquier `f(x)` , que probablemente no estará en la tabla. Sin embargo, si hemos hecho suficientes divisiones, una interpolación lineal será una buena aproximación:

```c++
double aux_f(double x, double dx, vector<double>& tabla)
{
    //Encuentra el índice en la tabla
    int j = find_index(x, tabla);

    //Calcular posicion x de los puntos
    double x0 = j * dx;
    double x1 = x0 + dx;
    
    //Interpolación lineal
    return tabla[j] + (tabla[j+1]-tabla[j]) * (x-x0)/(x1-x0);
}
```

La función `find_index`  es la que devuelve el índice tal que `tabla[j+1]>x>tabla[j]`. Una forma muy eficiente (y fácil de implementar) de hacer esto es emplear un [algoritmo de búsqueda binaria](https://en.wikipedia.org/wiki/Binary_search_algorithm). Este calculará `j`  en solo `log2(n)+1` operaciones. Si hacemos un millón de divisiones, solamente necesitamos 20 iteraciones (como máximo) para encontrar `j`. Después, hacemos una interpolación lineal. Con esto, calcular cualquier función, por complicada que sea, acaba necesitando solo unas 20-30 operaciones, lo que puede acelerar mucho el código si la llamamos a menudo.