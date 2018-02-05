#include "suma_proxy.h"


int main(void)
{
    vector<double> v1 = {1,2,3,4,5};
    vector<double> v2 = {2,3,-4,5,6};
    vector<double> v3 = {1,2};

    lista lista1(5, v1);
    lista lista2(5, v2);
    lista mala(2, v3);

    suma_proxy<lista, lista> sp(lista1, lista2);


    lista lista3(5,v1);

    lista3 = lista1 + lista1 + lista2 + lista2; //Obtener una lista a partir de una suma

    lista3.mostrar_lista();

    //Calcular solo UNO de los terminos de la lista, sin tocar los demás:
    cout << (lista1 + lista1 + lista2 + lista2).get_coef(2) << endl;

    //Detiene el programa con un error de ejecución
    lista3 = lista1 + mala;

    return 0;

}
