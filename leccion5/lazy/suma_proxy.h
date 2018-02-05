#include "lista.h"
#include <stdexcept> //Para lanzar errores que detengan el programa si hacemos algo ilegal

template<class lhs, class rhs>
class suma_proxy
{
public:
    //Cosntructor usando listas de inicialización (obligatorio porque a y b son miembros constantes)
    suma_proxy(lhs const &_a, rhs const& _b) : a(_a), b(_b) {};

    //Declarar la función como amiga para poder acceder a sus miembros privados
    friend suma_proxy<lista, lista> operator+(const lista &p, const lista &q);
    template<class l, class r> friend suma_proxy<suma_proxy<l,r>, lista> operator+(const suma_proxy<l,r> &sp, const lista &p);
    template<class l, class r> friend suma_proxy<lista, suma_proxy<l,r>> operator+(const lista &p, const suma_proxy<l,r> &sp);

    lhs const& get_lhs() const {return a;} //Devuelve la referencia cuando se le pida.
    rhs const& get_rhs() const {return b;}

    double get_coef(int j) const; //Devuelve el coeficiente j de la lista que contiene

private:
    //Esta clase no almacena objetos, solo las referencias a ellos,
    lhs const &a;
    rhs const &b;
};


///NOTA: TODAS LAS FUNCIONES CON PLANTILLA DEBEN IMPLEMENTARSE EN EL .h PORQUE C++ CREA UNA CLASE POR CADA TIPO NECESARIO DE LA PLANTILLA
///LAS FUNCIONES QUE NO LLEVAN PLANTILLA DEBEN HACERSE FUERA, O AL RE-COPIAR CODIGO DE LA PLANTILLA SERAN RE-DEFINIDAS

//Funciones libres:
suma_proxy<lista, lista> operator+(const lista &p, const lista &q);

//Si hay un suma_proxy a la izquierda, creamos un nuevo suma_proxy. Este a su vez puede contener más suma_proxy en los lhs y rhs, creando una estructura recursiva
template<class lhs, class rhs>
suma_proxy<suma_proxy<lhs,rhs>, lista> operator+(const suma_proxy<lhs,rhs> &sp, const lista &p)
{
    return suma_proxy<suma_proxy<lhs,rhs>, lista>(sp, p);
}

//Lo mismo, con un suma_proxy a la derecha
template<class lhs, class rhs>
suma_proxy<lista, suma_proxy<lhs,rhs>> operator+(const lista &p, const suma_proxy<lhs,rhs> &sp)
{
    return suma_proxy<lista, suma_proxy<lhs,rhs> >(p, sp);
}

//Aquí es donde sucede la magia: esta es la suma que hemos estado deteniendo sin realizar:
//- Si lhs = rhs = lista, suma el valor de los dos coeficientes j
//- Si lhs ó rhs son suma_proxy, esto llama recursivamente al get_coef de ambos suma_proxy...hasta llegar al primer caso
//Nota: se ha hecho con get_coef por claridad, pero se podría haber sobrecargado el operador [] en su lugar
//Otra cosa interesante: ahora, p+q es un objeto suma_proxy, luego (p+q).get_coef(j) SOLO HACE LA CUENTA PARA EL COEFICIENTE J, sin tocar los demás.
template<class lhs, class rhs>
double suma_proxy<lhs, rhs>::get_coef(int j) const
{
    return a.get_coef(j) + b.get_coef(j);
}
