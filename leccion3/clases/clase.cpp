#include<iostream>
#include<cstdlib>

#define MAX_P_SIZE 100

using namespace std;

class polinomio
{
public:
    polinomio();
    polinomio(int grado, double coefs[MAX_P_SIZE]);

    void set_coef(int j, double value);
    double get_coef(int j) const;
    int get_grado() const;

    polinomio operator+(const polinomio &other) const;
    polinomio& operator+=(const polinomio &other);
    double& operator[](const int j);


private:
    int n;
    double coeficientes[MAX_P_SIZE];
};

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


polinomio polinomio::operator+(const polinomio &other) const
{
    int suma_grado = max(n, other.get_grado()); //Grado del nuevo polinomio
    double coefs[MAX_P_SIZE]; //Coeficientes
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

//Modifica la propia clase y la devuelve a sí misma. Devuelve por referencia para evitar una copia
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

//Expone la referencia a coeficientes[j] para poder modificarla o leerla
//EN ESTE CASO ES INSEGURO YA QUE AL MODIFICAR ESTE VALOR HAY QUE TENER CUIDADO CON EL GRADO
double& polinomio::operator[](const int j)
{
    return coeficientes[j];
}

ostream& operator<<(ostream& os, const polinomio &p)
{
    int i;

    int n = p.get_grado(); //ostream no está detnro de la clase, así que tenemos que usar las funciones

    os << "(" << p.get_coef(0) << " + " << p.get_coef(1) << " x + ";
    for (i=1; i < n-1; i++)
    {
        os << p.get_coef(i) << " x^" << i+1 << " + ";
    }
    os << p.get_coef(n-1) << " x^" << n << ")";

    return os;

}

void polinomio::set_coef(int j, double value)
{
    coeficientes[j] = value; //Asignar el valor
    //Si nuestro indice es mayor que el grado, aumentar el grado
    if (j > n) n = j;

    //Si el que cambiamos es el último, y lo cambiamos a cero, reducir el grado
    //El bucle se asegura de que ir bajando hasta encontrar el primero no nulo
    if (j == n)
    {
        while (coeficientes[n] == 0 && n > 0)
        {
            n--;
        }
    }
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





int main(void)
{
    double c1[3] = {1.0, 3.0, 1.0};
    double c2[3] = {1.0, 3.0, -1.0};
    polinomio p(3, c1);
    polinomio q(3, c2);
    polinomio w = p;
    w += q;

    w[1] = -3.0;

    //cout << w.get_grado() << " (" << w.get_coef(0) << ", " << w.get_coef(1) << ", " << w.get_coef(2) << ")" << endl;

    cout << w << endl;

    return 0;
}
