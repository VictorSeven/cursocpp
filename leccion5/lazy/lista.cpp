#include "lista.h"

lista::lista(int nelem, const vector<double> &coefs)
{
    int j;
    n = nelem;
    coeficientes = vector<double>(nelem); //Crear una lista con el número adecuado de coeficientes

    //Rellenar los coeficientes
    for (j=0; j < nelem; j++)
    {
        coeficientes[j]=coefs[j];
    }
}

int lista::get_nelem() const
{
    return n;
}


double&  lista::operator[](const int j)
{
    return coeficientes[j];
}


double lista::get_coef(int j) const
{
    return coeficientes[j];
}


void lista::mostrar_lista()
{
    int i;
    cout << "(";
    for (i=0; i < n; i++)
    {
        cout << coeficientes[i] << ", ";
    }
    cout << ")" << endl;
}



