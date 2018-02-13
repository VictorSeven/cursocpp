#include<iostream>
#include<cstdlib>

#include "funciones.h"

int main(void)
{
    double d1, d2, d3;

    cout << "Introduzca dos números separados por un espacio:   ";
    cin >> d1 >> d2;

    d3 = suma(d1, d2);

    cout << d3 << endl;

    return 0;
}
