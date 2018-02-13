Día 4: La biblioteca estándar
=================

Ahora que ya conocemos en profundidad qué es una clase y cómo funciona, podemos empezar a explorar algunas de las clases que vienen incluidas en la biblioteca estándar de C++ (STL, por sus siglas en inglés). 

Estas son una serie de clases que vienen incluidas con el lenguaje, y que nos ayudan a realizar tareas que no están incluidas en el lenguaje C++ pero son muy comunes: por ejemplo, una clase para trabajar con memoria dinámica a alto nivel, o una clase de números complejos.  Aquí vamos a revisar algunas de las clases que nos son de mayor utilidad para realizar simulaciones en Física.

## Versiones de C++

Una cosa que hay que tener en cuenta es que existen diferentes versiones de C++. En ellas han ido añadiendo nuevos elementos al lenguaje, así como a la biblioteca estándar. El salto más importante se encuentra en el estándar C++11. Este ahora mismo es el estándar más utilizado (incluso por encima de C++14)  e incluye todos los elementos que necesitamos.

Para poder utilizarlo, en Code::Blocks, vamos a *Settings > Compiler...* y en las opciones del compilador buscamos la correspondiente a C+11.
Si nos gusta compilar desde la consola, es tan sencillo como añadir un flag al compilador,

`g++ mifichero.cpp -o mifichero -std=c++11`

En algunos compiladores antiguos C++11 podría no estar disponible. Podemos probar en este a caso a compilar para C++0x, una versión previa, que sin embargo tiene ya prácticamente todas las funcionalidades de C++11.

## Complejos: clase `complex` 

C++ tiene una clase ya preparada para trabajar con números complejos de forma sencilla. Si queremos utilizarla, solo debemos añadir el encabezado `#include<complex>`. Para crear números complejos, hacemos

``` c++
complex<double> cd(1.5, 2.0); //1.5 + 2.0i
complex<int> ci(1,-1); //1-i
```

Podemos especificar el tipo de los coeficientes usando una plantilla. Los números complejos tienen sobrecargadas las operaciones básicas, así como las funciones matemáticas:

``` c++
complex<double> c1, c2, c3, I;
c1 = complex<double>(-1.0, 0.0);
c2 = complex<double>(1.0, -1.0);
I = complex<double>(0.0, 1.0);
c3 = 2.0*(c1 - c2) * I; //*
cout << c3 << endl;

//Identidad de Euler
cout << 1+exp(3.14159*I) << endl; 
//Definido como (exp(iw)-exp(-iw))/2i
cout << sin(c2) << endl;
//Funciones multivariadas en la primera superficie de Riemann: log(-1) = Pi
cout << log(c1) << endl;
```

De estas operaciones, es interesante la línea marcada `//*` , ya que en ella podemos ver una operación que involucra un `double`  (el número `2.0`) con un complejo. Esto no da error y puede hacerse. Sin embargo, un entero sí daría error. Es posible multiplicar complejos de un tipo por números de su mismo tipo, pero sin mezclar. Del resto, lo que más llama la atención es el hecho de que C++ pueda trabajar con funciones como senos o logaritmos empleando los números complejos.

La biblioteca de compejos permite, por ejemplo, escribir fácilmente una versión chapucera (pero funcional) de [una transformada discreta de Fourier](https://en.wikipedia.org/wiki/Discrete_Fourier_transform#Definition):

```c++
//Calcula la transformada de Fourier de xn en la frecuencia w
complex<double> xw(const double xn[100], const int w)
{
    complex<double> suma(0.0, 0.0); //Almacenar suma
    //Constante 2piI/N
    complex<double> c(0.0, 2.0 * 3.14159 / 100.0);

    int i;//Contador

    for (i=0; i < 100; i++)
    {
        //int*complex<double> da un error, así que pasa los 
        //enteros a complex<double>
        suma += xn[i] * exp(-c * complex<double>(i*w, 0.0));
    }

    return suma;
}

```

A la hora de utilizar la función, se puede hacer de forma sencilla,

```c++
int i;
double xn[100];
double t, dt;

//Crea una función senoidal de frecuencia 8.0 Hz
t = 0;
dt = 0.01;
for (i=0; i < 100; i++)
{
    xn[i] = sin(8.0 * 2.0 * 3.14159 * t);
    t += dt;
}

//Transformada de Fourier
for (i=0; i < 100; i++)
{
    cout << i << " " << abs(xw(xn, i)) << endl;
}
```

Podemos observar que el resultado de este ejemplo es prácticamente 0.0, salvo para los valores con `k=8,92`, ya que `92=100-8= -8` (la transformada de Fourier es simétrica respecto de `k=0` y tiene picos en las frecuencias de la función senoidal). 

El comentario importante es la aparición de la función `abs`, que devuelve el módulo cuadrado de un número complejo (en los reales, recordemos, solo calcula el valor absoluto).  Se puede obtener la fase, en radianes, con `arg`. Otras funciones interesantes son:

- `norm(z)` : devuelve el módulo del número.
- `conj(z)` : complejo conjugado.
- `real(z)`  e `imag(z)`  devuelven la parte real e imaginaria.
- `polar(modulo, fase)`: devuelve un número complejo, conocidos su módulo y fase.



## Memoria dinámica: clase `vector` 

Hasta ahora hemos usado arrays estáticos. Aunque para empezar están bien, tiene una desventaja importante:  El tamaño del array debe conocerse al compilar el código. No podemos establecerlo a partir de una variable. En una clase, puede establecerse como un parámetro usando una plantilla, pero una vez declarado el objeto, es inmutable. Cuando sabemos que un array va a tener exactamente 100 elementos, no hay problema. Pero con tamaños variables, tenemos que empezar a hacer malabares.

Miremos el ejemplo de `polinomio` : debemos seleccionar un tamaño máximo para tener cuidado con el usuario. Además, tenemos un array con 100 elementos de los cuales estamos desaprovechando la mayor parte. Para empezar, esto ocupa muchísima más memoria. Y en términos de eficiencia es un problema: si un polinomio tiene grado 2, y lo sumamos con otro de grado 2, estamos sumando 98 ceros.  
Podemos arreglarlo usando un parámetro de plantilla, pero esto nos obliga a ser muy cuidadosos con los índices y añadir una buena cantidad de `if` . Operadores como `+=`  serían muy complicados de implementar, ya que estos pueden cambiar el grado del polinomio (que hemos seleccionado como inmutable).

Una buena solución sería poder decidir qué tamaño tiene el array en cualquier momento, y poner y quitar elementos a nuestro antojo. Para hacer esto, en C estándar se reservaba el tamaño de la memoria a mano, con punteros, y se iba seleccionando qué trocito de memoria asigno a qué variable. Aunque este procedimiento es posible aún en C++, desde mi punto de vista no es recomendable para el cálculo numérico (habitualmente): hay grandes posibilidades de equivocarse, y los errores son difíciles de detectar (como contrapartida, en ocasiones permite hacer optimizaciones que no son posibles de otra manera). Para hacer esto de forma sencilla, tenemos la clase `vector` . Esta nos permite declarar un vector con la siguiente sintaxis:

```c++
#include<vector> //añadir la cabecera correspondiente

//Declaraciones
vector<tipo> nombre(); //Crea un vector
vector<tipo> nombre2(n); //Vector con tamaño inicial n
vector<tipo> nombre3(n, valor_inicial); //Tamaño inicial, cada elemento iniciado a valor_inicial.
```

A la hora de iniciar vectores, si no sabemos el tamaño inicial, podemos emplear el primer constructor. **Si lo conocemos, por defecto, usaremos el segundo constructor. Nunca usaremos el tercero a menos que nuestra aplicación concreta requiera inicializar los valores.** Recuerda que aunque no lo veas, esa inicialización requiere un bucle sobre cada elemento.

Observa que `vector`  no es más que una plantilla de una clase, que tiene tres constructores definidos, según lo que queramos hacer.  `vector`  tiene además sobrecargado el operador corchete:

```c++
vector<double> v(100); //Crea un vector
v[0] = 1.0;
v[1] = 2.0 * v[0];
```

Una diferencia importante con los arrays es que los vectores no tienen tamaño límite. No importa cuántos elementos metamos, no darán nunca un fallo de segmento. El único límite, por tanto, es nuestra RAM. 

> Si recordamos, podemos ver el tamaño de una variable con la directiva  `sizeof` . Sin embargo, ojo, `vector`  es una clase, de modo que `sizeof`  solamente devuelve el tamaño del vector como contenedor en sí, y no como su contenido:
```c++
vector<double> v1(1); 
vector<double> v2(100); 
cout << sizeof(v1) << " " << sizeof(v2) << endl;
```
> Este código devuelve dos veces 12 bytes, que es el tamaño del contenedor. Si queremos el tamaño del vector, hemos de sumarle a este el tamaño del vector por el tamaño del tipo que contiene.

### Funciones de vector

Veamos ahora las funciones que tiene un vector. Las más importantes son:

- `size()`: devuelve el número de elementos del vector.
- `push_back(elemento)` : agrega un nuevo `elemento` al vector, por el final.
- `pop_back()` : elimina el último elemento del vector.
- `insert(iterador, elemento)` : inserta un nuevo elemento en la posicion `iterador` .
- `erase(iterador)` : elimina un elemento en la posición `iterador` .
- `clear()`: elimina todo lo que hay en el vector.
- `swap(vector)` : intercambia el contenido de ambos vectores de forma eficiente.

Veamos un ejemplo sencillo de cómo agregar nuevos elementos a un vector. Por ejemplo, este código que busca números primos (de una forma muy ineficiente):

```c++
void calcular_primos(const int nmax)
{
    vector<int> v(1); //Vector de primos
    v[0] = 2; //Primer primo: el 2

    int i, j;
    bool divisible;

    cout << nmax << endl;
    for (i=3; i < nmax; i++)
    {
        j = 0;
        divisible = false; //Para que empiece el bucle
        //Ve dividiendo por cada primo.
        while(!divisible && j < v.size())
        {
            divisible = i % v[j] == 0; //Es divisible?
            j++;
        }

        //Si ningún primo ha conseguido dividirlo, es primo
        if (j == v.size()) v.push_back(i);
    }

    for (i=0; i < v.size(); i++) cout << v[i] << " ";
}
```

Este código simplemente va guardando los números primos que vamos encontrando en un vector, y, al final, los muestra. Este código se podría hacer muy fácilmente con arrays, añadiendo otra variable más para contar cuántos primos llevamos. El problema es que hay que saber, con antelación, cuál es el número de primos al que vamos a llegar, y poner esta cota, que dejará algunos elementos vacíos (gastando más memoria).

La ventaja es que irá algo más rápido. **Cuando llamamos a un método que cambia el tamaño del vector, como `push_back`  o `erase` , hay que reservar más espacio para los datos. Esta operación es lenta. Debemos reducir siempre al máximo los cambios de tamaño de vector.** Conste decir que un vector al que nunca le cambiamos el tamaño es igual de rápido que un array.

Aunque cambiar todos los vectores por arrays sería más rápido, en algunos algoritmos se gana muchísimo más añadiendo y quitando que haciendo malabares con un array estático, y se hace todo mucho más fácil de programar. Además, ocupa menos memoria. Es decisión del programador qué utilizar. **En caso de duda, usa siempre un vector: si no le cambias el tamaño es igual de rápido, no tiene límite a la cantidad de elementos que le quieras meter, y si en algún momento cambias de opinión y necesitas memoria dinámica, será más fácil cambiarlo.** 

### Borrar o insertar

Los métodos `erase` e `insert`  esperan un objeto de tipo `iterator`  como argumento. Antes, habíamos dicho que en C había que referirse a la memoria manualmente. Los vectores, en el fondo, están haciendo esto, y hay que señalar el trocito de memoria correcto. Los iteradores son unos objetos que encargan de apuntar a la posición de memoria correcta sin tener que preocuparnos demasiado y de una forma segura.

El trozo de memoria donde empieza un vector se puede obtener con `vector.begin()` , y donde acaba, con `vector.end()` . Un iterador, además, tiene sobrecargada la suma con números enteros. Así, para borrar un elemento, podemos llamar a:

```c++
vector<double> v(100, 0.0);
v.erase(v.begin()); //Elimina el primer elemento
v.erase(v.begin() + 50); //Elimina el elemento 50
v.erase(v.end()-1); //Elimina el último elemento
```

> Observa que, si ejecutamos estas tres líneas en orden, el elemento 50 es en realidad el 51 ya que hemos borrado el 0 anteriormente.

Los iteradores son muy útiles, ya que permiten abstraer el concepto de ir a una dirección de memoria u otra en cualquier contenedor de datos de C++ (como los mapas o las tablas hash).

### El vector de vectores

Por último, notar que dentro del tipo del vector puede ir cualquier tipo. Esto incluye, por ejemplo, otro vector, lo cual permite hacer vectores 2D. Esto se hace de la siguiente forma:


```c++
vector< vector<double> > m(100, vector<double>(100) );
```

Los espacios entre los `>` son importante para no confundir al compilador con `>>` .  La declaración crea un vector de vectores, que tiene tamaño 100, y que inicializa cada elemento con un vector de tamaño 100: es decir, una matriz 100x100. Para añadir elementos, 

``` c++
m.push_back(vector<double>(100)); //Agrega una nueva columna
m[0].push_back(1.0); //Toma la primera columna y agregale un nuevo elemento
```

Observa que al hacer esto cada columna puede tener un número distinto de elementos.

### Vectores como argumento de funciones

Una diferencia importante con los arrays es que los vectores, al ser un objeto, se pasan por valor a no ser que lo indiquemos explícitamente con `& `. **Recuerda pasar los vectores por referencia siempre, puesto que pueden contener muchos datos**.  Otra diferencia interesante es que las funciones pueden devolver vectores:

```c++
vector<double> mifuncion()
{
    return vector<double>(100, 0.0);
}
```

Esto era imposible con los arrays. Sin embargo, esto devuelve una copia al vector, lo cual es poco eficiente. Una función como la siguiente sería mucho más rápida:

```c++
void mifuncion(vector<double>& v)
{
    v = vector<double>(100, 0.0);
    return;
}
```

Por tanto, en general, es mejor pasar los vectores por referencia siempre. 

> **Ejercicio:** reescribe el código para una transformada de Fourier usando la clase `vector`  en lugar de los arrays, para que admite cualquier tamaño de la señal a convertir.

## Pseudoaleatorios: clase `random`

A menudo, en nuestros programas necesitaremos generar números aleatorios. Como probablemente ya sabes, un ordenador no puede generar números realmente aleatorios, sino solamente *pseudoaleatorios*: es una serie determinista que es indiferenciable de una serie aleatoria... siempre y cuando no excedas su periodo. 

En C++, habitualment se usa `rand()`  para obtener estos números. Aunque para algunas aplicaciones está bien, `rand`  emplea un generador de aleatorios llamado lineal congruente. La serie tiene "solo" 2.147.483.647 números diferentes. Aunque dos mil millones (`~10^9`)  de aleatorios puedan parecer bastantes, para aplicaciones específicas se quedan muy cortos. Los métodos Monte Carlo, usados muy comúnmente en física estadística, física de partículas, o para integrales en muchas dimensiones, pueden exceder fácilmente esta cifra. Además, la calidad del generador no es precisamente la mejor: varias pruebas no demasiado complicadas muestras que el generador tiene bastantes correlaciones entre los números -lo cual no es una propiedad deseable.

Pero  no solo eso: un uso básico suele requerir obtener números a partir de una distribución uniforme (por ejemplo, simular un dado o una moneda), pero estos métodos precisamente requieren simular el resultado de hacer un proceso aleatorio según una distribución de probabilidad general `f(x)`, que podría ser una gaussiana, una distribución de Poisson, una lognormal, una distribución de Weibull o una distrubicón gamma de Euler. Aunque para las más raras tendremos que escribir nuestro código, generar una gaussiana es una operación muy común. A pesar de que [el algoritmo de Box-Muller](https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform) parece la solución a todos nuestros problemas en este caso, en general es bastante ineficiente. Escribir algo mejor requiere tiempo. Y no hablemos si queremos una distribución lognormal.

Por ello, C++ tiene una clase dedicada a generar números aleatorios de calidad, y soporte para las distribuciones más comunes, de forma eficiente. Para ello, primero hacemos `#include<random>`. Después, hacen falta dos cosas: elegir un generador de aleatorios, y una distribución. Para el generador tenemos varias opciones. 

- **El generador por defecto, `default_random_engine`.**  De una calidad más que dudosa, deberíamos evitarlo a toda costa.
- **El Mersenne Twister, `mt19937` :**  tiene un periodo muchísimo más largo (¡de `2^219937-1` dígitos!), y es mucho mejor en los test. Durante bastante tiempo ha sido uno de los estándares en simulación Monte Carlo. Nuevos test estadísticos parecen mostrar que no es *tan* bueno como se pensaba. 
- **El Ranlux, `ranlux48` :**  es el que actualmente utiliza el CERN. A pesar de que no tiene un período tan largo como Mersenne Twister, está basado en un proceso caótico que asegura una decorrelación completa en series largas. Eso sí, es más lento. 
- **El dispositivo de aleatorios, `random_device`:** este es la sorpresa de la comparativa. `random_device`  no genera pseudoaleatorios, **genera aleatorios de verdad**. Eso sí, depende del hardware de nuestro ordenador, y puede estar temporalmente no disponible. A menudo se usa para dar una semilla a cualquiera de los otros generadores.

Para los ejemplos siguientes usaré `mt19937`. Después de escoger nuestro generador, C++ tiene varias opciones para las distribuciones de probabilidad. Para nosotros, las más importantes son: 

- Reales en el intervalo `[a,b]`: `uniform_real_distribution<double> ran_u(a,b)` 
- Enteros en el intervalo `[n,m]`: `uniform_int_distribution<int> ran_i(n,m)` 
- Distribución gaussiana de media μ  y varianza σ^2:  `normal_distribution<double>(mu, sigma)`.

Hay muchas más (exponenciales, lognormales, Cauchy...), y están todas en las [páginas de referencia](http://www.cplusplus.com/reference/random/). 

Para emplear los números aleatorios, primero declaramos el generador, y luego la distribución:

```c++
int i;
mt19937 gen(1234567892);
uniform_real_distribution<double> ran_u(0.0,1.0);

cout << "Diez números aleatorios:" << endl;
for (i=0; i < 10; i++) cout << ran_u(gen) << " ";
```

donde el número `1234567892` es la semilla inicial de la serie. A menudo, se recomienda usar el tiempo del sistema como semilla. En cálculo cientifico, no es buena idea, ya que imposibilita reproducir exactamente un resultado. **Usar siempre la misma semilla permite que el resultado de un programa sea siempre el mismo, a pesar de la aleatoriedad. Eso hace más sencillo encontrar errores y reproducir resultados anteriores.**  

El generador de aleatorios debe declararse siempre en el `main`  y pasarse por referencia a los métodos (o emplearlo incluso como variable global), porque si no la serie de aleatorios empezará desde el principio cada vez que llamamemos a la función, creando correlaciones importantes.
