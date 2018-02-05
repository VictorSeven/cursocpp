#include<iostream>
#include<cstdlib>
#include<typeinfo>
#include<vector>

using namespace std;


template<class lhs, class rhs> class suma_proxy; //Declaración adelantada, especificada en suma_proxy.h.

/// CLASE POLINOMIO SIMPLIFICADA, HECHA CON VECTORES

using namespace std;

class lista
{
public:

    lista(int nelem, const vector<double> &coefs);

    int get_nelem() const;

    //Para obtener el coeficiente j en este caso usaremos la función.
    double& operator[](const int j);
    double get_coef(int j) const;

    //Esta sobrecarga sirve para obtener una lista a partir de una suma_proxy cualquiera
    template<class lhs, class rhs> lista& operator=(suma_proxy<lhs, rhs> const& proxy);
    //Y esta, definir la conversión de un tipo a otro
    //template<class lhs, class rhs> lista& operator=(suma_proxy<lhs, rhs> const& proxy);


    void mostrar_lista();

private:
    int n;
    vector<double> coeficientes;
};


//Specify templated function here in order to work:

template<class lhs, class rhs>
lista& lista::operator=(suma_proxy<lhs, rhs> const& proxy)
{
    int i;
    //Obtener cada uno de los coeficientes a través del proxy
    for (i=0; i < n; i++)
    {
        coeficientes[i] = proxy.get_coef(i);
    }
    return (*this);
}
