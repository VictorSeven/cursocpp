Día 1: Configurar y comenzar
=================

## El entorno Code::Blocks

Lo primero que necesitamos para programar es escoger bien con qué vamos a hacerlo. Por supuesto, podemos abrir el bloc de notas y compilar con la línea de comandos. Sin embargo, los entornos de desarrollo integrado (IDEs) modernos proporcionan unas funcionalidades bastante cómodas. A menudo un buen IDE ayuda a ahorrar tiempo y facilita la corrección de errores.

Para C++ hay varias opciones. La que nunca deberíamos utilizar (y por desgracia se emplea muy a menudo) es Dev-Cpp. Este entorno lleva sin actualizar desde hace muchísimo tiempo. El compilador que trae está completamente desfasado, y no se va a corregir más. 

A mucha gente le gusta utilizar un único editor con soporte multilenguaje (algunas opciones son Atom, Sublime Text o las aplicaciones Emacs y Vim) y compilar desde la consola. Desde mi punto de vista, es mejor usar un IDE especialmente diseñado para nuestro lenguaje. Para C++, una buena opción es Code::Blocks, pensado para escribir C++ y/o Fortran.

Code::Blocks es un programa libre y de código abierto, que podemos descargar gratuitamente.

### Instalación en Windows
Vamos a [la página oficial de Code::Blocks](http://www.codeblocks.org/),  y en la sección *Downloads*, pinchamos sobre *Download the binary release*. Aquí aparecen diferentes opciones de descarga. Hay que tener en mente que Code::Blocks es un entorno, y no un compilador. Si descargamos *codeblocks-16.01mingw-setup.exe*, tendremos incluida una versión para Windows del compilador GCC.

Sin embargo, la versión de GCC ofrecida es bastante antigua, y resulta más conveniente tener una más actualizada.  En [nuwen.net](https://nuwen.net/mingw.html) tenemos a nuestra disposición las últimas versiones de GCC listas para utilizar. Descargamos *mingw-15.3-without-git.exe*. El siguiente paso es configurar Code::Blocks a nuestro antojo.

### Instalación en Linux

En Linux, muchas distros tienen Code::Blocks en los repositorios oficiales, de modo que podemos instalarlo con cualquier gestor de paquetes. Sin embargo, es conveniente prestar atención a la versión de los repositorios para asegurarnos de que tenemos una versión actualizada.

>**Nota**: en Ubuntu 16.04 el paquete de los repositorios está desactualizado y no funciona muy bien en mi experiencia, así que es mejor instalarlo como indico más abajo.

Vamos a [la página oficial de Code::Blocks](http://www.codeblocks.org/),  y en la sección *Downloads*, pinchamos sobre *Download the binary release*. Para la mayor parte de distros, hay binarios que podemos descargar e instalar. 

> En el caso de Ubuntu, nos recomiendan ir a una PPA. Tan sencillo como [ir a la PPA](https://launchpad.net/~damien-moore/+archive/ubuntu/codeblocks-stable), y escribir en nuestra consola los comandos indicados.  

## Configurar Code::Blocks 
El siguiente paso es configurar Code::Blocks. Básicamente nos interesa configurar dos cosas: el aspecto del editor, para que sea agradable, y el compilador a utilizar.

### Poniendo bonito el entorno
Vamos a la barra de herramientas y pinchamos en *Settings > Editor...*. Esto nos abre una ventana con muchas opciones. Para nosotros, la más interesante (de momento) está en el icono *Syntax Highlighting*. Al seleccionarlo, muestra un ejemplo de código, y una lista con secciones de C++: palabras clave, preprocesador, números... En este icono básicamente podemos personalizar el estilo de letra y color que debe tener cada cosa.

Sin embargo, editarlo a mano es un poco largo. Code::Blocks contiene ya algunas configuraciones de color predeterminadas,  que debemos incluir por separado. Estas están definidas en un archivo texto (el archivo `colour_themes.conf` que está en este mismo repositorio). Para añadirlas a Code::Blocks:

> **Windows:** 
1. Abrir la carpeta de instalación de Code::Blocks. **Cerrar Code::Blocks, si está abierto.**
2. Ejecutar *cb_share_config.exe*. Cargar a la derecha el archivo *default.conf* que se encuentra en *C:\Documents and Settings\[your_user_name]\Application Data\codeblocks*, y a la izquierda el archivo color_themes que hemos descargado. 
3. Seleccionar todos los colores, y darle a *Transfer>>>* y luego a *Save*

> **Linux:** 
1. **Cerrar Code::Blocks, si está abierto.**
2. Abrir una consola y escribir el comando *sudo cb_share_config*. Cargar a la derecha el archivo *default.conf* que se encuentra en */home/nombre_usuario/.config/codeblocks* (la carpeta *.config* está oculta por defecto), y a la izquierda el archivo color_themes que hemos descargado. 
3. Seleccionar todos los colores, y darle a *Transfer>>>* y luego a *Save*

Con esto, tenemos ya instalados todos los esquemas de color, y podemos elegir el que más nos guste, e incluso modificarlo. Si ponemos un fondo con el color oscuro, probablemente queramos modificar el color del cursor. Para ello vamos a *Settings > Editor...*, pinchamos en el icono *Margins & Caret*, y en el campo *Caret* podemos modificar el cursor.

Dejo al usuario explorar las opciones que hay para personalizar el entorno. Permite configurar indentados, auto-completado, y una gran cantidad de posibilidades. Otra cosa que puede que queramos hacer es quitar gran parte de las ventanas y menús que hay en la pantalla, para tener más espacio para programar. Esto se puede hacer en *View > Perspectives*, escogiendo la opción *Minimal*.

## Configurar el compilador
Puede que queramos instalar un compilador distinto de GCC, como Clang o Intel, o simplemente tener dos versiones de GCC distintas. En todo caso, hay que indicarle al entorno dónde se encuentra el compilador y cómo debe hacer su trabajo. 

Para ello, vamos a *Settings > Compiler...*. En este caso estamos interesados solo en el icono de *Compiler Settings* que aparece por defecto. Si vamos a la pestaña de *Toolchain executables*, podemos decirle a Code::Blocks en qué carpeta está nuestro compilador. Además, debemos indicar cuál es el ejecutable de los compiladores. En el caso de C++, basta indicar el compilador de C++. En el caso de GCC es `g++`. 

En Windows, si hemos descargado la opción que traía MinGW por defecto, está todo configurado. En Linux, Code::Blocks habrá detectado nuestro compilador automáticamente. Si queremos usar otro, basta poner la carpeta y elegir los ejecutables.

Al acabar, haz click en *Set as default* para guardar los cambios. Observa que podemos tener varios compiladares instalados y configurados simultáneamente en la lista. Para ir cambiando de uno a otro, basta elegir otro y hacer click en *Set as default*. Ten en cuenta que aunque Code::Blocks tenga una lista muy grande, no funcionará a no ser que instalemos y configuremos correctamente los ejecutables.

> Nota: los usuarios de Linux/Mac pueden tener problemas con el output de Code::Blocks, que está configurado por defecto para sacar los resultados en una terminal tipo XTerm. Si esta terminal no está instalada, no se puede ejecutar ningún código. Para solucionarlo, vamos a *Settings > Environment..* y del *Terminal to launch console programs* elegimos una adecuada a nuestra distro.


## Apéndice: ¿Por qué C++ en física?

El primer elemento a discutir en un curso de C++ para físicos es "¿por qué hacer un curso de un lenguaje de C++?". Por un lado, en física tenemos el sector Fortran, que parece que nunca abandonará Fortran 77, y por otro, el sector Python, que vende que tardamos la mitad en realizar un programa. Por tanto, creo que es necesario justificar por qué C++ y no otro lenguaje.

### C++ vs Fortran
Esta comparativa es ya un clásico en el cálculo numérico. Los defensores de Fortran argumentan que Fortran es más rápido, ya que se diseñó con el propósito de hacer cálculo numérico, que hay un montón de código ya escrito, los complejos están implementados en el lenguaje, y que es más fácil de escribir que C++. 

Según los test de los últimos años, Fortran no es más rápido que C++. De hecho, en general, C++ obtiene mejores resultados. Solamente es superado por Fortran cuando hay un volumen de operaciones con matrices muy importante. En cualquier otro caso, C++ gana.

Ahora bien, para que C++ gane hay que escribir correctamente. El primer código simple y directo que escribamos probablemente será  más lento que el que hagamos con Fortran. La principal diferencia, en mi opinión, es que Fortran es técnicamente más fácil de optimizar: el mismo algoritmo escrito en ambos lenguajes, si queremos que C++ realmente sea rápido, tenemos que prestar atención a algunos detalles de gestión de la memoria.

La sintaxis de Fortran, por otro lado, suele resultar mucho más cómoda que la sintaxis de C++, especialmente las operaciones vectorizadas. Este es uno de los puntos que a mí personalmente me gusta de Fortran.

A favor de Fortran, y en contra de sus críticos, hay que decir que no es un "lenguaje muerto" o desactualizado. El último estándar es Fortran 2015, que añade nuevas características al lenguaje, como una nueva implementación de arrays preparada de entrada para la paralelización.

Sin embargo, su principal desventaja es que Fortran no tiene clases. Se pueden hacer módulos que imitan el funcionamiento de las clases, pero al final la sintaxis es complicada. Las clases son una herramienta muy versátil y útil en programación, y (en mi opinión) minusvalorada a la hora de hacer cálculo numérico. Un código que se emplea muy a menudo es susceptible de ser incluido en una clase, y su reutilización es directa. Si bien usar una biblioteca de C estándar o llamar a módulos Fortran escritos por otra persona puede dar algunos dolores de cabeza de vez en cuando, una clase de C++ generalmente está autocontenida y se puede usar de una forma bastante sencilla y portable.

Por esto, y por todas las opciones extra que contienen las clases (sobrecarga de operadores y plantillas, principalmente), C++ es un lenguaje muy atractivo en este sentido. Y además, la nueva biblioteca estándar (llamada STL) contiene una gran cantidad de funcionalidades listas para usarse: números complejos, funciones especiales, generación de números aleatorios...

### C++ vs Python
En el otro extremo de las comparativas entre lenguajes, tenemos a Python. Python es un lenguaje interpretado, con un ecosistema de librerías muy amplio. Es un lenguaje perfecto para el prototipado de código, trabajar con cadenas de caracteres, como lenguaje auxiliar de scripts, diseño de aplicaciones de escritorio y muchas más tareas propias de un lenguaje de muy alto nivel. En el cálculo numérico, sus librerías (numpy, scipy, pandas y matplotlib) ofrecen una gran cantidad de herramientas avanzadas que permiten trabajar muy cómodamente en análisis de datos, representar gráficas, hacer estadística...

La principal ventaja del código Python es que es muy fácil de escribir. El mismo programa que tardamos una semana en tener funcionando en C++, en una tarde puede estar funcionando con Python. Si a esto le añadimos las funcionalidades extra de las librerías, tenemos también otra opción bastante atractiva.  Python también tiene clases y objetos, e importar y reutilizar sus librerías es incluso más sencillo que en C++. ¿Por qué elegir entonces C++ en lugar de Python?

La diferencia principal en este caso es la velocidad de ejecución. Python es aproximadamente 10 veces más lento que C++, en el sentido de que un bucle que use Python estándar irá mucho más lento que C++. Por supuesto, librerías como numpy ayudan a aliviar este problema, ya que están escritas en Fortran/C++, y trabajan más rápido que los arrays comunes. Sin embargo, en un código de simulación seria, es imposible evitar los bucles nativos, y acabaremos teniendo un código visiblemente más lento que su contrapartida en C++.

Para un código que tarda 10 segundos en ejecutarse, esperar 1 minuto es razonable. Sin embargo, para simulaciones serias, los programas (en C++/Fortran) pueden tardar del orden de muchas horas o varios días en ejecutarse. En Python, esto significa código ejecutándose durante semanas, lo cual es inadmisible. Por tanto, nuestra mejor baza es un lenguaje de bajo nivel. 

Existen algunos trucos para acelerar Python casi hasta la velocidad de C++, pero de momento son algo engorrosos, y hacen perder un poco la legibilidad del código. Sin embargo, pueden ser una herramienta excelente en algunas ocasiones. 

### Disclaimer
En esta discusión se han invertido muchas líneas ya en foros de internet. El principal problema es que la gente cree que tiene que escoger un único lenguaje para hacer todas las cosas, y esto no es verdad.
**No hay un lenguaje mejor que otro. La elección del lenguaje depende de la tarea a realizar.** 
Por ejemplo, *para mí*, dadas las características de las simulaciones que suelo hacer, lo mejor es realizar las simulaciones en C++, y después analizar los datos de la simulación con Python. Alguien de fluidos, que requiere resolver ecuaciones en derivadas parciales con método de los elementos finitos, probablemente obtenga mejor resultado con Fortran que con C++. Lo importante es estar más o menos actualizado y saber cuál es la mejor herramienta para una tarea en concreto. 



