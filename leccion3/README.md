Día 3: Clases 
========

Hasta este punto, hemos instalado y configurado un entorno orientado a trabajar con C++, y hemos repasado los conceptos básicos del lenguaje. El próximo paso es repasar la sintaxis básica de clases, y extenderla para poder sacar partido de las aplicaciones que C++ nos ofrece en programación orientada a objetos.

Como ejemplo, vamos a crear una clase que trabaje con polinomios de grado arbitrario. Para ello, comenzaremos en esta lección con una clase que utiliza polinomios de grado menor o igual que `n`, y la ampliaremos posteriormente usando vectores de la biblioteca estándar para soportar cualquier tamaño.

## Comenzando

Lo primero es tener claro cuál es el concepto de clase y por qué la necesitamos en C++. De forma abstracta, una clase es un conjunto de variables y métodos agrupados dentro de una sola estructura. Llamamos *objeto* a una instancia de la clase. 

En la práctica, podemos entender una clase como un nuevo tipo más de variable, parecido a `int` o `double` , pero que nosotros podemos definir a nuestro antojo. Los objetos serían cada una de las veces que hemos "declarado" esta variable. Algunos ejemplos:

- Una clase "Rectangle" formada por un punto `x,y` en el espacio, ancho y alto define un rectángulo. Podríamos además equiparla con funciones para detectar si un punto está dentro del rectángulo, o si otro rectángulo está superpuesto.
- Una clase "Graph", que contenga un grafo o red compleja, que podría almacenar conexiones entre usuarios en redes sociales. Podría tener funciones para detectar comunidades en las redes o algunos otros parámetros del grafo.
- Una clase "Solver" que contenga información abstracta para resolver mediante el algoritmo de Runge-Kutta cualquier ecuación diferencial introducida por el usuario.

Es claro que las clases pueden ser de gran utilidad a la hora de encapsular código para reutilizarlo. Además, pueden hacerlo de una forma realmente versátil. Por ejemplo, podríamos querer que nuestro rectángulo estuviera definido a veces para números enteros y a veces para números en coma decimal. O nuestro *Solver* podría actuar de forma diferente en variable compleja. Todo esto se puede hacer con plantillas.

### Sintaxis de una clase

En C++, una clase tiene la siguiente sintaxis:

``` c++
class nombre_clase
{
    public:
    //Miembros publicos
    double miembro_publico;
    private:
    //Miembros privados
    double miembro_privado;
};
```  

Observa el `; `  después de la llave. Los miembros de una clase, que son bien variables o bien declaraciones de funciones, pueden ser públicos o privados. Los miembros privados solo pueden ser accedidos desde dentro de la clase y nunca desde fuera.  Es decir,

``` c++
int main(void)
{
    nombre_clase nombre_objeto(); //Crear nuevo objeto
    nombre_objeto.miembro_publico = 5;
    nombre_objeto.miembro_privado = 4; //Erroooor!
}
```  

En el código anterior, la línea `nombre_clase nombre_objeto()` es equivalente a lo que sería un `double nombre_variable`, y es la instancia de un objeto de la clase. Las dos líneas siguientes muestran cómo podemos acceder a los miembros de la clase, mediante un punto. Observa que si intentamos acceder a un miembro privado tendremos un error.

Vamos a comenzar nuestra clase de polinomios.  Si nuestro polinomio tiene grado `n`, entonces se puede escribir como  `p(x)=a_0 + a_1 x + a_2 x^2 + ... + a_n x^n`. Para almacenarlo, solamente hemos de guardar los coeficientes en un array, de modo que `coeficientes[j]` representa el coeficiente `a_j`.  Además, vamos a definir un tamaño máximo para los polinomios, de modo que el usuario no pueda elegir un número demasiado grande. Nuestra clase necesita almacenar, por tanto, un array cuyo tamaño límite `MAX_P_SIZE`, y el grado del polinomio que estamos usando, `n`. El resultado es este: 

``` c++
#define MAX_P_SIZE 100
class polinomio
{
public:
    double coeficientes[MAX_P_SIZE]; 
private:
    int n;
};

```  

### El constructor

Lo siguiente es ser capaces de crear nuevos polinomios. Toda clase ha de tener un constructor, que es una función especial que da información al compilador sobre cómo ha de iniciar nuevos objetos. El constructor debe ser un miembro público, y puede recibir tantos argumentos como queramos.  En nuestro ejemplo, necesitará un array de coeficientes y el grado del polinomio:

``` c++
#define MAX_P_SIZE 100
class polinomio
{
public:
    double coeficientes[MAX_P_SIZE];
    
    polinomio(int grado, double coefs[MAX_P_SIZE])
	{
	    int j;
	    n = grado;
	    for (j=0; j < n; j++)
	    {
	        coeficientes[j]=coefs[j];
	    }
	    for (j=n; j < MAX_P_SIZE; j++)
	    {
	        coeficientes[j] = 0.0;
	    }
	}

private:
    int n;
    
};
```  
En esta función hemos rellenado los coeficientes hasta donde llega el grado del polinomio, y el resto lo iniciamos a cero.

Ahora, cuando instanciemos el objeto tal y como hemos indicado antes, lo haremos siguiendo las instrucciones del constructor:

``` c++
double coefs[3] = {1.0, -1.0, 1.0};
polinomio mi_polinomio(3, coefs);
```  

Con esto ya hemos creado un polinomio, y el constructor se ha ocupado de darle valores a las variables `n`  y `coeficientes` . 

Antes de añadir más cosas a la clase, es importante comentar que las definiciones de las funciones no tienen por qué estar dentro de la clase. Pueden estar simplemente declaradas, y después definidas en cualquier otro lugar del código. 
De esta forma, tenemos por un lado nuestra clase:

``` c++
#define MAX_P_SIZE 100
class polinomio()
{
public:
    double coeficientes[MAX_P_SIZE];
    polinomio(int grado, double coefs[MAX_P_SIZE]);
private:
    int n;
    
};
```  
Y debajo, la definición del constructor. Hay que indicar que pertenece a la clase, lo cual se realiza poniendo `nombre_clase::nombre_funcion` en lugar de simplemente el nombre de la función:

``` c++

polinomio::polinomio(int grado, double coefs[MAX_P_SIZE])
{
    int j;
    n = grado;
    for (j=0; j < n; j++)
    {
        coeficientes[j]=coefs[j];
    }
    for (j=n; j < MAX_P_SIZE; j++)
    {
        coeficientes[j] = 0.0;
    }
}

```  




### Algunas funciones comunes

Antes de pasar a explicar más cosas, vamos a implementar algunas funciones más para nuestra clase de polinomios. Por un lado, en algunos lenguajes de programación se considera mala práctica que las variables de la clase sean accesibles para el usuario (en nuestro caso, `coeficientes` ), y en su lugar, deberíamos dar funciones que permitan su modificación. Vamos a suponer que una vez escogido el grado del polinomio, este no puede cambiar, pero los coeficientes sí.

Vamos a mover la variable `coeficientes`  a los campos privados, y a crear dos nuevas funciones públicas, con el objetivo de modificar `coeficientes` :

```c++
class polinomio
{
public:
    polinomio(int grado, double coefs[MAX_P_SIZE]);
    
    void set_coef(int j, double value);
    double get_coef(int j) const;
    int get_grado() const;
    
    
private:
    int n;
    double coeficientes[MAX_P_SIZE];
};
```

Observa el uso de la palabra clave `const`  después del nombre de la función. Esto indica al compilador que las funciones `get_coef`  y `get_grado`  no modifican las variables de la clase, es decir, son funciones de "solo lectura". Esto es muy importante porque si queremos declarar un polinomio constante `const polinomio inmutable(grado, coefs)`, solo podremos llamar a aquellas funciones que C++ sepa que no modifican a `polinomio` . Gracias al uso de `const` , podremos usar `inmutable.get_grado()`. Si no estuviera declarado como constante, esto nos daría un error. Las funciones están especificadas de la siguiente manera:

```c++
void polinomio::set_coef(int j, double value)
{
    coeficientes[j] = value;
    return;
}

double polinomio::get_coef(int j) const
{
    return coeficientes[j];
}

int polinomio::get_grado() const
{
    return n;
}

```

Al igual que antes, vemos que hemos cambiado el nombre de la función por `nombre_clase::nombre_funcion` , pero la estructura para declarar una función sigue siendo exactamente igual. Estas funciones simplemente permiten leer los datos de `coeficientes` , e incluso modificarlos, pero el usuario ya no tiene acceso directo a la variable.  

```c++
double coefs[3] = {1.0, 0.5, 1.0};
polinomio p(3, coefs);

p.set_coef(2, -6.0)
cout << p.get_coef(2) << endl; //Muestra -6.0
```

Más adelante veremos formas más intuitivas de modificar estos valores en la clase. 

Otro método que suele resultar interesante es uno que permita una representación de la clase en una cadena de texto. Es decir, a la hora de hacer `cout`  o escribir la clase en un fichero, que el usuario que lee el fichero pueda reconocer la clase. Hay dos formas de hacer esto:

1. Mediante una función que devuelva una cadena de caracteres, para poder hacer `cout << mi_objeto.to_string() << endl;`. 
2. Mediante la sobrecarga del operador `<<` en la clase (ver más abajo), que permite hacer `cout << mi_objeto << endl;`. 

La primera suele ser una opción más sencilla conceptualmente, Aquí, sin embargo, el objetivo es aprender la segunda. Con lo cual, vamos a nuestro siguiente objetivo.

## Sobrecarga de operadores

### Operador `+`

Conceptualmente, nos interesaría que nuestra clase fuera capaz de sumar, restar, multiplicar o dividir polinomios, unos entre otros. Esto se puede hacer implementando una función suma que reciba dos polinomios, y devuelva un tercero (o que lo escriba por referencia). Sin embargo, sería mucho más conveniente escribir cosas como `s=p+q`, o incluso operar de la forma `s=p1*(p2-p3)`. Para conseguir este objetivo, se emplea la llamada sobrecarga de operadores.

La sobrecarga de un operador se realiza de la siguiente manera:

```c++
class polinomio
{
public:
    polinomio(int grado, double coefs[MAX_P_SIZE]);

    void set_coef(int j, double value);
    double get_coef(int j) const;
    int get_grado() const;
    
    polinomio operator+(const polinomio &other) const;


private:
    int n;
    double coeficientes[MAX_P_SIZE];
};
```

Observa que la sobrecarga del operador es una función: tiene un tipo a devolver y unos argumentos. En este caso, es muy importante que los argumentos sean pasados por referencia constante. El motivo es que cada polinomio es una clase que contiene muchos datos: un array de coeficientes, funciones...  si no pasamos los datos por referencia, cada vez que escribamos `p+q`  habrá una copia de `p`  y `q`  a la memoria, lo cual es bastante lento. Pero además, al sumar ambas variables, ninguna de ellas es modificada, con lo cual las podemos pasar como constantes, lo que permite al compilador realizar optimizaciones.

Por otro lado, la suma solo ha recibido un argumento. Esto sucede porque C++, en el fondo, interpreta que `p+q`  es `p.operator+(q)`, y por tanto solo requiere un argumento: el otro sumando es el término que está a la izquierda.  La especificación de la función es:

```c++
polinomio polinomio::operator+(const polinomio &other) const
{
    int suma_grado = max(n, q.get_grado()); //Grado del nuevo polinomio
    double coefs[MAX_P_SIZE]; //Coeficientes
    int i; //Contador
    for (i=0; i < suma_grado; i++)
    {
        coefs[i] = p.get_coef(i) + q.get_coef(i); //Suma coeficientes
    }
    //¿Es el último coeficiente 0?
        while (coefs[suma_grado-1] == 0 && suma_grado > 0)
    {
        suma_grado--:
    }
    return polinomio(suma_grado, coefs); //Crea un nuevo polinomio
}

```

Observa que si un polinomio tiene grado mayor que otro, no pasa nada porque hemos hecho cero todos los coeficientes `a_j` tales que `j>n` , en el constructor. Lo que devuelve la suma es un nuevo polinomio, con grado el del polinomio de grado más alto (a menos que el último coeficiente sea 0).  Un detalle es que al ser pasada `other`  como constante, solo podremos usar las funciones `other.get_grado`  y `other.get_coef` , que son las que hemos declarado anteriormente como constantes.

Podemos comprobar que la implementación es correcta haciendo algunas sumas de polinomios, por ejemplo:

```c++
double c1[3] = {1.0, 3.0, 1.0};
double c2[3] = {1.0, 3.0, -1.0};
polinomio p(3, c1);
polinomio q(4, c2);
polinomio w = p + q;

cout << w.get_grado() << " (" << w.get_coef(0) << ", " << w.get_coef(1) << ", " << w.get_coef(2) << ")" << endl;
```

Con esto, hemos ganado la posibilidad de operar de forma natural con los polinomios. Como contra, la función suma devuelve el polinomio por valor, con lo cual se realiza una copia del polinomio a devolver. Lo que hemos ganado en legibilidad, en este caso, se ha perdido en eficiencia. Piensa en un ejemplo como:

```c++
polinomio q1, q2,q3,q4,q5;
//Rellenar los polinomios
q5 = q1 + q2 + q3 + q4 + q5;
```

En este caso, lo que hace C++ es calcular `q1+q2`, devolver una copia al resultado, y esto sumarlo con `q3`. Después, la copia obtenida la suma con `q4` , y así sucesivamente. Esto quiere decir que esta suma realiza `4n` iteraciones. Si la hiciéramos con un solo bucle sobre los coeficientes, solo gastaríamos `n` iteraciones.  Una solución es la implementación de la llamada **evaluación perezosa**, que evita que se devuelvan copias hasta que no se ha llegado al final de la operación. La implementación de la evaluación perezosa puede llegar a ser complicada. Un ejemplo claro de implementación [se puede consultar aquí](https://stackoverflow.com/a/414418/1600778).

> **Ejercicio:** implementar los operadores `-` y `*`  para un polinomio. La multiplicación debe poder aceptar un escalar también.

### Operador `+=`

Un detalle importante es que a la hora de sobrecargar operadores, si sobrecargamos `+`, deberíamos sobrecargar también `+=` , ya que el usuario espera que si puede sumar, también puede añadir.   Otro motivo por el cual este operador es interesante es porque `p+=q`  es más eficiente que `p+q` . Este último realiza la suma, y después devuelve una copia del resultado. Esto es necesario ya que si hacemos `p+q+w`, entonces C++ primero hace `p+q` , guarda la copia, y después suma `w`  con la copia. En `p+=q` , el valor de `p`  aumenta, y podemos ahorrarnos la copia. Para objetos grandes, esto aumenta mucho la eficiencia.

La implementación es muy parecida a la del operador `+` , con la diferencia de que ahora queremos editar la clase:

```c++
polinomio& polinomio::operator+=(const polinomio &other)
{
    n = max(n, other.get_grado()); //Grado del nuevo polinomio

    int i; //Contador
    for (i=0; i < n; i++)
    {
        coeficientes[i] += other.get_coef(i); //Suma coeficientes
    }

    while (coeficientes[n-1] == 0 && n > 0)
    {
        n--;
    }
    return *this; //Crea un nuevo polinomio
}
```

Ahora modificamos `n`  y `coeficientes`, que son las variables de nuestra clase. Observa que el tipo del operador `+=`  es `polinomio&`, es decir, **devuelve una referencia a un polinomio existente**.  Lo que queremos es que coja como referencia nuestro polinomio original, lo que hacemos con la palabra clave `this` . Esta es una referencia a nuestro objeto. Para devolver el objeto en sí, tenemos que ponerle delante el asterisco para hacer un puntero: `*this` es realmente nuestro objeto.  **Lo que hace el operador, en realidad, es `p.operator+=(q)`. El resultado de la función devuelve una referencia a `p`, que es lo que hemos editado.**  

**En muchos manuales de C++ se recomienda que el operador `+` no pertenezca a la clase,** sino que vaya por libre, declarándose como `polinomio operator+(const polinomio lhs, const polinomio& rhs);`.  En este caso, el operador `+`  se puede definir fácilmente en función del `+=` , como:

```c++
polinomio operator+(const polinomio lhs, const polinomio& rhs)
{
    lhs+=rhs; //Sumar el lado izquierdo al derecho
    return lhs; //Devolver el izquierdo tras la suma
}
```

La decisión de incluir un operador dentro o fuera de una clase es, más que nada, conceptual, y depende de varios factores (para qué se usará la clase, qué tipo de cosas vamos a hacer con referencias/punteros después, qué es más normal conceptualmente...). 

> Desde mi punto de vista, es más normal tener el operador `+=` dentro de la clase, y el operador `+`  fuera. Sin embargo, hay que pagar un precio: el miembro izquierdo, `lhs`  ha de ser pasado por copia, ya que es modificado. Esto es más lento si el objeto que usamos es grande. En un código orientado a ser eficiente, es mejor tener `+` dentro de la clase. Igualmente, podríamos escribir `+`  en función de`+=` , usando `lhs=*this;`. Sin embargo, esto implica, al final, hacer una copia. Por tanto, para tener un código rápido, en este caso, es mejor "duplicar" el código de los operadores `+`  y `+=`, y que ambos pertenezcan a la clase, aunque rompa algunas normas de estilo.

### Operador `=` 

C++ nos ofrece, por defecto, un operador `=`  para objetos, de modo que si escribimos `p=q`  hace una réplica completa de `q`  en `p`  mediante un volcado de memoria. En ocasiones, sin embargo, es conveniente definir un operador `=`  personalizado. Esto se hace con la siguiente sintaxis: `polinomio& operator=(const polinomio& other)`. En este caso la referencia es muy importante, porque sin ella C++ hará una copia del objeto antes de asignarlo. 


### Operadores `[]` y `()`

Antes hemos dicho que queríamos tener una forma de editar las variables `coeficientes`  de nuestra clase, y creamos dos funciones para ello. Una forma mucho más natural es sobrecargar los corchetes, de modo que al definir `polinomio p(n, coefs)`  podamos obtener los coeficientes simplemente como `p[j]`. 

Un ejemplo de implementación de este operador es:

```c++
double& polinomio::operator[](const int j)
{
    return coeficientes[j];
}
```

Observa que al devolver una referencia, no solo es posible recibir el valor de `coeficientes[j]` , sino también editarlo. Es decir, con esto, podemos escribir

``` c++
double c1[3] = {1.0, 3.0, 1.0};
polinomio p(3, c1);
p[1] = -4.0;
cout << p[1] << endl;
```

y editar directamente los valores de los coeficientes del polinomio. 

Al igual que se puede sobrecargar el operador `[]` , podemos sobrecargar `()`. Este operador es mucho más versátil, ya que puede admitir un número arbitrario de argumentos. Si tuviéramos, por ejemplo, una matriz, es posible sobrecargar los paréntesis para poder acceder al elemento como `matriz(i,j)` , en una sintaxis parecida a Python/Numpy o Fortran.

### Operador  `<<` 

Este es el operador que utilizamos para sacar nuestro objeto a un fichero, habitualmente la pantalla. A diferencia de los operadores anteriores, dado que se ejecutará como `output << miobjeto`,  no puede ir dentro de la clase: C++ lo entiende como `output.operator<<(miobjeto)` , de modo que el primer argumento debe ser obligatoriamente `output`. Si fuera dentro de la clase recibiría el propio objeto como argumento  (como pasa con `+` , por ejemplo). 

Por tanto, debe ir fuera de la clase. Podemos, a pesar de ello, acceder a los miembros privados de la clase. Solo hay que declarar esta función como *amiga de la clase*. Para ello la declaramos como otra función cualquiera de la clase, y añadimos la palabra clave *friend*, de la siguiente manera:

```c++
#include<fstream> 

class foo
{
	public:
	friend ostream& operator<<(std::ostream& os, const foo& f)
	private:
	double priv;
}
```

De esta manera, nuestra clase recibe el `ostream` como primer argumento por referencia, y la clase (que ahora debe ser incluido explícitamente) como el segundo. Después, podemos proceder a implementarlo:

```c++
ostream& operator<<(std::ostream& os, const foo& f)
{
	os << f.priv;
	return os;
}
```

Como detalles interesantes, observa que no hay que poner `foo:operator<<` precisamente porque este método no pertenece a la clase, solamente es amigo suyo. Y como amigo, puede acceder a ciertas cosas privadas, como la variable `priv`.  Además, el `ostream` debe devolverse para que siga encadenando salidas. 

> Ojo con hacer cosas del tipo `os << f.priv << " "`  o bien `os << f.priv << endl` , que pueden ser muy incómodas a la hora de organizar la salida en ficheros. 


## Plantillas

### Plantillas de funciones

Hasta el momento, hemos visto cómo crear una clase que contenga variables, funciones, e incluso con el que podamos operar de forma intuitiva sobrecargando operadores.

Sin embargo, queremos ahora añadir una nueva funcionalidad: supongamos que deseamos que los coeficientes de mi clase sean enteros únicamente, reales únicamente -o incluso booleanos. En principio, es posible declarar la clase como `double` y usar solo valores enteros, o incluso 0 ó 1, pero esto tiene dos problemas importantes:

1. La posibilidad de que se cometa algún error es muy alta, ya que en los cálculos intermedios que se producen dentro de la clase no redondeamos a enteros (ni mucho menos con los booleanos).
2. Estamos gastando mucha memoria (16 bytes para un `double` en lugar de los 2 bytes para un `bool` ) de manera inútil.

Para solucionar esto tenemos las plantillas. Una *plantilla* es una función o clase que funciona de forma diferente según el tipo indicado. Por ejemplo, 

```c++
//Declaración
template<class T>
T suma(const T& x, const T& y);

//Especificación
template<class T>
T suma(const T& x, const T& y)
{
    return x+y;
}
```

En esta expresión, `template<class T>` indica que la función que está debajo es una plantilla, y `T`  es un tipo que no especificamos. Podría ser `int`, `double` , o cualquier otra cosa que tenga sobrecargado el operador `+`, como `polinomio` .   Para llamar a esta función, utilizamos:

```c++
double x1, x2, x3;
int n1, n2, n3;
polinomio p1, p2, p3;

//Iniciar todas las variables con algún valor

x3 = suma<double>(x1, x2);
n3 = suma<int>(n1, n2);
p3 = suma<polinomio>(p1, p2);
```

De esta forma la misma función puede ser reutilizada para diferentes tipos. Por otro lado, es posible que queramos realizar operaciones diferentes según el tipo de dato. Para ello, si incluimos en nuestra cabecera `#include<typeinfo>` podemos hacer uso de la instrucción `typeid` , que nos permite comprobar el tipo de dato introducido:


```c++
//Cabecera:
#include<typeinfo>

//...

template<class T>
T suma(const T& x, const T& y)
{
    if (typeid(T) == typeid(float)) return 0.0;
    else return x+y;
}
```

De modo que si la variable que hemos usado es `float`  la función `suma`  siempre devuelve el valor nulo.

> Un detalle: hemos pasado los argumentos como referencia constante, ya que para un `int`  realmente no hay mucho problema, pero si queremos pasar un objeto, lo mejor es usar siempre referencias. 
> Si la referencia no es constante, por ejemplo con `suma(T& x, T& y)`, no podemos llamar a la función como `suma<int>(2, 4)`, ya que podríamos estar modificando los números. Lo único que asegura al compilador que no haremos esto es pasar los argumentos como constantes. 

Hay veces que las plantillas se utilizan muy a menudo con cierto tipo en concreto. En tal caso, la notación `nombre<tipo>(args)`  se vuelve redundante, y conviene más llamar a la función por `nombre(args)` . C++ es capaz de deducir el tipo que debe aplicar en ocasiones. Por ejemplo, si ejecutamos

```c++
int a = 1;
int b = 2;
cout << suma<int>(a,b) << " " << suma<>(a,b) << suma(a,b) << endl;
```

veremos que el código siempre devuelve lo mismo, como un entero. Esto no funcionará en casos más complicados. Sin embargo, es posible decirle al compilador qué es lo que esperamos cuando llamamos a la función sin la etiqueta del tipo, cuando declaramos la función:

```c++
template<class T>
T suma(const T& x, const T& y);

template polinomio suma(const polinomio& x, const polinomio& y);

```

De modo que así al llamar  a la función sin ninguna etiqueta lo que tendremos será la aplicación de la suma a dos polinomios.

Una función puede tener, además, varios tipos diferentes en la plantilla. Por ejemplo, una suma que mezcle dos tipos y devuelva un tercero (esto se puede hacer siempre y cuando hayamos sobrecargado el operador `+`  correspondiente):

```c++
template<class T1, class T2, class T3>
T3 suma(const T1& x, const T2& y);

//Y si alguno lo usamos mucho, lo podemos atajar...
template double suma(const int&, const double&);
```

Observa que hemos definido también un atajo para las sumas de enteros con decimales, que devuelven decimales. Así, `suma(1, 3.0)` llama directamente al atajo, devolviendo un `double`.

### Plantillas de clases

Al igual que pasa con las funciones, podemos tener plantillas de clases. La sintaxis es prácticamente igual:

```c++
template<class T>
class nombre
{
//Cosas de la clase. Podemos usar el tipo T.
};
```

Por ejemplo, podemos cambiar nuestra clase de polinomios para admitir un tipo arbitrario de coeficiente, en lugar de un `double`:


```c++

template<class T>
class polinomio
{
public:
    polinomio(int grado, T coefs[MAX_P_SIZE]);

    void set_coef(int j, T value);
    T get_coef(int j) const;
    int get_grado() const;

    polinomio<T> operator+(const polinomio &other) const;
    polinomio<T>& operator+=(const polinomio &other);
    T& operator[](const int j);


private:
    int n;
    T coeficientes[MAX_P_SIZE];
};

```
El cambio no es realmente grande: solo hemos cambiado el `double` de la variable `coeficientes`  por una `T`  donde ha sido necesario. Este cambio sencillo, sin embargo, nos permite utilizar ahora polinomios con coeficientes de cualquier tipo. Todo aquello que devolvía un `polinomio`, ahora devuelve un `polinomio<T>`.

Hay que cambiar, consecuentemente, todas las especificaciones de las clases. Por ejemplo, para el constructor y el operador `+` , tenemos: 

```c++
template<class T>
polinomio<T>::polinomio(int grado, T coefs[MAX_P_SIZE])
{
    int j;
    n = grado;
    for (j=0; j < n; j++)
    {
        coeficientes[j]=coefs[j];
    }
    for (j=n; j < MAX_P_SIZE; j++)
    {
        coeficientes[j] = 0.0;
    }
}

template<class T>
polinomio<T> polinomio<T>::operator+(const polinomio &other) const
{
    int suma_grado = max(n, other.get_grado()); //Grado del nuevo polinomio
    T coefs[MAX_P_SIZE]; //Coeficientes
    int i; //Contador
    for (i=0; i < suma_grado; i++)
    {
        coefs[i] = coeficientes[i] + other.get_coef(i); //Suma coeficientes
    }
    while (coefs[suma_grado-1] == 0 && suma_grado > 0)
    {
        suma_grado--;
    }
    return polinomio(suma_grado, coefs); //Crea un nuevo polinomio
}

```

El resto de métodos se cambian de la misma manera. podemos utilizar la clase con plantillas indicando el tipo del polinomio:

```c++
int c1[3] = {1, 3, 1};
int c2[3] = {1, 3, -1};
polinomio<int> p(3, c1);
polinomio<int> q(3, c2);
polinomio<int> w = p+q;

    cout << w.get_grado() << " (" << w[0] << ", " << w[1]<< ", " << w[2] << ")" << endl;
```

Hay algunas veces, al igual que ocurre con las funciones, que vamos a emplear a menudo un tipo de polinomio. Supongamos que es el de coeficientes reales. Es posible escribir un atajo para el tipo `polinomio<double>`  usando la secuencia `typedef` :

```c++
typedef polinomio<double> polid 

//...y luego para trabajar con él,
polid polinomio_double(n, coefs);
```

En el fondo, `typedef`  "define" un nuevo tipo, permitiendo escribir atajos.  A partir del estándar de C++11 (ver la lección sobre compiladores más adelante) también es posible emplear la directiva `using` , que es completamente equivalente:

```c++
using polid = polinomio<double>

//...y luego para trabajar con él,
polid polinomio_double(n, coefs);
```

La diferencia es que `using`  también admite plantillas. Veamos un ejemplo práctico. Un uso curioso de las plantillas, es la posibilidad de poder añadir parámetros. Por ejemplo, nuestro polinomio ahora mismo recibe el grado en el constructor. Sin embargo, podríamos obtener el grado del polinomio a partir de una plantilla 

```c++
template<class T, int n>
class polinomio
{
//...
};
```

La diferencia principal es que ahora nuestro polinomio tendría un grado fijo y no podría cambiarlo bajo ningún concepto. La ventaja principal de este método es que el tamaño máximo del array `coeficientes`  puede  establecerse en `n` en lugar de `MAX_P_SIZE` (sin embargo, requiere cambiar el constructor, los métodos de suma...). 

Esta clase podría usarse de la siguiente manera:

```c++
polinomio<double, 3> grado3(coefs3);
polinomio<double, 40> grado40(coefs40);
```

Si decidiésemos utilizar esta arquitectura, y, por algún motivo, los polinomios de grado 3 fueran muy comunes en nuestro programa, podríamos hacer

```c++
//Tamaño fijo
template<class T>
using poliT3 = polinomio<T, 3>

//Tamaño fijo y double
using polid3 = polinomio<double, 3>


//Uso:
poliT3<double> grado3(d_coefs);
poliT3<int> grado3_int(i_coefs);
```
