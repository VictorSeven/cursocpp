Día 6: la biblioteca Eigen
===============

Saber hacer clases para los módulos de código que podamos necesitar es muy útil.  Además, nos permite entender cómo funcionan los objetos de la STL, así como otras bibliotecas de C++.  En esta última lección trabajaremos sobre una biblioteca existente.

A menudo, lo que necesitamos es operar de forma eficiente con álgebra lineal: operaciones con matrices, diagonalización, resolución de sistemas lineales, etc. Aunque tenemos herramientas para hacer esto nosotros mismos, existen ya bibliotecas que se ocupan de esto y que han sido trabajadas por muchos años: BLAS/LAPACK y ARPACK son unos ejemplos. Las primeras están pensadas para el trabajo con matrices y vectores de forma eficiente, mientras que ARPACK está especializada en el cálculo de autovectores y autovalores para matrices de gran tamaño.  Están escritas en Fortran, aprovechando que este lenguaje se diseñó teniendo en cuenta esta aplicación.

La mayor parte de las bibliotecas actuales que hacen álgebra lineal,  en realidad, son *wrappers* a estas. Las rutinas de `numpy.linalg`, por ejemplo, son llamadas a estas funciones. **Eigen** , aunque no depende directamente de estas bibliotecas,  sí es compatible con ellas y puede ser configurada para realizar los cálculos vía BLAS/LAPACK. 

## Instalar la biblioteca

Vamos a la [página oficial de Eigen](http://eigen.tuxfamily.org) y descargamos la última versión estable. Descomprimimos el archivo en una carpeta (digamos `eigen334` , ya que en mi caso he descargado la versión 3.3.4), y lo copiamos esta carpeta al lado de nuestro fichero fuente `.cpp` . Si vamos a usar la biblioteca mucho, es conveniente copiar la carpeta con el resto de ficheros de cabecera de la STL. 

Una de las ventajas de C++ respecto de C estándar es que es posible distribuir el código de una forma bastante sencilla. Cada clase tiene su propio fichero `.h`  y `.cpp` , y basta incluir las clases que queramos en nuestro fichero, con `#include` . Por ejemplo, una matriz normal y corriente se añade con:

```c++
#include "eigen334/Eigen/Dense" //Incluir la parte de la biblioteca que nos interesa -no cargarla toda.
//Para acortar el espacio de nombres
using namespace Eigen::MatrixXd;
```

Si hemos copiado la carpeta donde el resto de los ficheros de cabecera, haremos `#include <eigen334/Eigen/Dense>`. 

## Tipos básicos de Eigen

Eigen proporciona soporte para vectores y matrices, así como sobrecargas de operadores adecuadas. 

Todos los objetos de Eigen derivan de la clase `Matrix<tipo, filas, columnas>`.  Por ejemplo, para hacer una matrix 4x3 de enteros, puedo declarar: `Matrix<int, 4, 3> m43i;` Como los tamaños de matriz cuadrada 2, 3 y 4 son muy comunes, existen algunos tipos predefinidos para estos. Por ejemplo, `Matrix3d`  es una matriz 3x3 de `double`, y `Matrix4i`  una matriz 4x4 de enteros. Se pueden usar complejos con `Matrix3cd`  (para `complex<double>`), `Matrix2cf`   (para `complex<float>` ), etc. 

En lugar de especificar el tamaño de la matriz al principio, Eigen da la posibilidad de seleccionarlo de forma dinámica usando `Dynamic` . Por ejemplo, `Matrix<double, 3, Dynamic>`  es una matriz de números reales con 3 filas de la cual no conocemos (aún) el número de columnas. Tenemos también la definición de  `MatrixXd`, una matriz de números reales de la cual no conocemos el tamaño al principio.

El constructor de las matrices con tamaño variable sirve para especificar el tamaño de la matriz,

```c++
int n;
cout << "Tamaño de matriz: ";
cin >> n;
MatrixXd m(n,n); //Crea una matriz nxn
```

Es posible también declarar vectores en una sintaxis parecida a la de las matrices, como `Vector<tipo, elementos>`. Los vectores en realidad son matrices con una sola columna. También se pueden declarar como `Vector2i` , `Vector4d`  o `VectorXd` , al igual que las matrices.

En Eigen, para acceder a los elementos de las matrices o vectores, se usan los paréntesis y no los corchetes:


```c++
MatrixXd m(2,2); 
VectorXd v(2);

m(0,0) = 1.0;
m(1,0) = -1.0;
m(0,1) = m(0,0);
m(1,1) = 0.0;
cout << m << endl;

v(0) = 1.0;
v(1) = -1.0;
cout << v << endl;
```

Las dimensiones de una matriz dinámica se pueden variar en cualquier momento con `resize` . Esto, sin embargo, borra los contenidos de la matriz. El tamaño se puede ver en cualquier momento:

```c++
MatrixXd m(2,2); 

cout << m.rows() << " " << m.cols() << " " << m.size() << endl;

m.resize(3,5);

cout << m.rows() << " " << m.cols() << " " << m.size() << endl;

VectorXd v(4);

cout << v.rows() << " " << v.size() endl;
```

Se puede asignar una matriz a otra de distinto tamaño, si son de tipo dinámico. Esto copiará por completo el tamaño de la segunda en la primera.:

```c++
MatrixXd a(2,2);
MatrixXd b(3,4);
a = b;

//Shows 3 4 12:
cout << a.rows() << " " << a.cols() << " " << a.size() << endl;
```

## Operaciones:

Eigen permite operar con estos tipos básicos de una manera bastante natural. 

```c++
MatrixXd m(3,3);
VectorXd v(3);

//Rellenar cosas...
//Hacer algunas cuentas
cout << m.transpose() + m << endl;
cout << m * v << endl;
cout << 2.0 * m + (m * m) << endl;
cout << v.dot(v) << endl; //Producto escalar
cout << v.cross(v) << endl; //Producto vectorial
```

Observa que el el producto por escalares está sobrecargado también, de modo que `2.0*m`  es una operación válida.

> En Eigen,  todas las operaciones están optimizadas mediante técnicas  como evaluación perezosa, que permite evaluar cosas como `a+b+c` sin realizar ninguna copia. 
> En algunas ocaciones la evaluación perezosa no es una buena idea. Eigen escoge automáticamente el mejor procedimiento para realizar las operaciones, pero podemos exigirle que lo haga manualmente.  Para más detalles, consulta [la documentación de Eigen](https://eigen.tuxfamily.org/dox/TopicLazyEvaluation.html).

Además, Eigen permite calcular la suma y la media de los elementos de la matriz o vector, máximo, mínimo, o parámetros como la traza:

```c++
MatrixXd m(3,3);
VectorXd v(3);

//Rellenar cosas...

cout << m.mean() << endl;
cout << m.minCoeff() << endl;
cout << m.trace() << endl;
```

Finalmente, tenemos la posibilidad de calcular determinantes, inversas, o autovalores de la matriz, así como diversas descomposiciones y sistemas de ecuaciones.  La lista completa está en [la documentación de Eigen](https://eigen.tuxfamily.org/dox/group__DenseLinearSolvers__chapter.html).

Nosotros, como ejemplo, vamos a obtener autovalores. Eigen tiene diversas formas de trabajar dependiendo de nuestra matriz. Si es autoadjunta, lo mejor es usar `SelfAdjointEigenSolver`.  Es importante asegurarse de que nuestra matriz es autoadjunta para ello. Si no, tenemos otros métodos como `EigenSolver`  o `ComplexEigenSolver` .

```c++
Matrix3d selfadj(3);

//Rellenar de modo que selfadj es autoadjunta

//Crear el "solver" que realiza las operaciones con nuestra matriz
SelfAdjointEigenSolver<Matrix3d> solver(selfadj);

//Obtener autovalores y autovectores:
cout << "Eigenvalues: " << endl << solver.eigenvalues() << endl;
cout << "Eigenvectors: " << endl << solver.eigenvectors() << endl;
```

Entre otras opciones, Eigen permite operar con matrices dispersas, en las que la mayor parte de entradas son ceros. En estos casos, no merece la pena almacenar toda la matriz, sino solo las entradas no nulas. Eigen las guarda con un algoritmo que permite la máximo compresión de los datos (ya que estas matrices suelen tener un tamaño muy superior al habitual), y posee rutinas específicas para ellas, aunque son más complicadas de utilizar.

Por otro lado, Eigen tiene (aún como *en proceso*) módulos para hacer transformadas de Fourier discretas empleando el algoritmo FFT. Aunque nuestro código para hacer transformadas de Fourier es funcional, para una serie temporal con miles o millones de puntos  esto es muy lento. FFT permite hacerlo de una manera mucho más eficiente.

## Un comentario sobre el uso de Eigen en C++

Aunque Eigen puede ayudar mucho, algunas funciones (sobre todo las de matrices dispersas, los métodos para hacer mínimos cuadrados, etc) son algo incómodas de utilizar. Paquetes como Numpy (Python) emplean el mismo código base que Eigen (BLAS/LAPACK/ARPACK y similares), siendo comparables en velocidad (si no usamos bucles nativos de Python) y permiten trabajar de forma muchísimo más sencilla el trabajo con vectores y matrices debido a la notación con *slicing* de los vectores de Python.

Como dije al principio, cada lenguaje tiene su propósito. Si necesitas un código de simulación altamente eficiente, y tienes que hacer uso de álgebra lineal complicada, C++ es tu mejor opción y Eigen se ocupará de muchos cuellos de botella del código. Sin embargo, si has sacado datos de una simulación y estás usando Eigen para analizarlos, ajustando mínimos cuadrados, o haciendo Fourier, probablemente cambiar a Python para esta tarea sea más productivo: es más cómodo, y tiene más opciones para el análisis. 

Eigen, por el otro lado, es una librería ideal para resolver operaciones que necesiten cálculos con matrices o vectores, incluso si no empleamos ninguna de las funciones para calcular autovalores, inversas ni ninguna otra cosa. El hecho de que la clase ya esté hecha, tenga una sintaxis clara, sea sencilla de utilizar, y la sobrecarga de los operadores ariméticos esté optimizada probablemente mejore nuestro código, por el mero hecho de emplearla.


