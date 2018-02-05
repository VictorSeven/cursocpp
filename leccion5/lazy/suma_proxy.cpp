#include "suma_proxy.h"


//Ahora la suma de dos listas no realiza la suma, sino que crea un suma_proxy. Como este captura por referencia, no hay copias aquí.
suma_proxy<lista, lista> operator+(const lista &p, const lista &q)
{
    if (p.get_nelem() != q.get_nelem() ) throw invalid_argument("Suma de dos listas de tamaño distinto");
    else return suma_proxy<lista, lista>(p, q);
}
