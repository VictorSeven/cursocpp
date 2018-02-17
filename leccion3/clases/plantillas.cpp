#include<iostream>
#include<cstdlib>
#include<typeinfo>

#define MAX_P_SIZE 100

using namespace std;

template<class T>
class polinomio
{
public:
    polinomio(int grado, const T coefs[MAX_P_SIZE]);

    void set_coef(int j, T value);
    T get_coef(int j) const;
    int get_grado() const;

    polinomio<T> operator+(const polinomio &other) const;
    polinomio<T>& operator+=(const polinomio &other);
    T& operator[](const int j);


private:
    int n;
    T coeficientes[MAX_P_SIZE];
};


template<class T>
polinomio<T>::polinomio(int grado, const T coefs[MAX_P_SIZE])
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

template<class T>
polinomio<T> polinomio<T>::operator+(const polinomio &other) const
{
    int suma_grado = max(n, other.get_grado()); //Grado del nuevo polinomio
    T coefs[MAX_P_SIZE]; //Coeficientes
    int i; //Contador
    for (i=0; i < suma_grado; i++)
    {
        coefs[i] = coeficientes[i] + other[i]; //Suma coeficientes
    }
    while (coefs[suma_grado-1] == 0 && suma_grado > 0)
    {
        suma_grado--;
    }
    return polinomio(suma_grado, coefs); //Crea un nuevo polinomio
}

template<class T>
polinomio<T>& polinomio<T>::operator+=(const polinomio &other)
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

template<class T>
T& polinomio<T>::operator[](const int j)
{
    return coeficientes[j];
}


template<class T>
void polinomio<T>::set_coef(int j, T value)
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

template<class T>
T polinomio<T>::get_coef(int j) const
{
    return coeficientes[j];
}

template<class T>
int polinomio<T>::get_grado() const
{
    return n;
}


int main(void)
{
    int c1[3] = {1, 3, 1};
    int c2[3] = {1, 3, -1};
    polinomio<int> p(3, c1);
    polinomio<int> q(3, c2);
    polinomio<int> w = p+q;

    cout << w.get_grado() << " (" << w[0] << ", " << w[1] << ", " << w[2] << ")" << endl;


    return 0;
}
