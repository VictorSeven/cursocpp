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

    polinomio operator+(const polinomio &other);
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


polinomio polinomio::operator+(const polinomio &other)
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

double& polinomio::operator[](const int j)
{
    return coeficientes[j];
}


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





int main(void)
{
    double c1[3] = {1.0, 3.0, 1.0};
    double c2[3] = {1.0, 3.0, -1.0};
    polinomio p(3, c1);
    polinomio q(3, c2);
    polinomio w = p;
    w += q;

    w[1] = -3.0;

    cout << w.get_grado() << " (" << w.get_coef(0) << ", " << w.get_coef(1) << ", " << w.get_coef(2) << ")" << endl;


    return 0;
}
