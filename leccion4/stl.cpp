#include<iostream>
#include<cstdlib>
#include<complex>
#include<vector>
#include<random>

using namespace std;


void calcular_primos(const int nmax)
{
    vector<int> v(1); //Vector de primos
    v[0] = 2; //Primer primo: el 2

    int i, j;
    bool divisible;

    cout << nmax << endl;
    for (i=3; i < nmax; i++)
    {
        j = 0;
        divisible = false; //Para que empiece el bucle
        //Ve dividiendo por cada primo.
        while(!divisible && j < v.size())
        {
            divisible = i % v[j] == 0; //Es divisible?
            j++;
        }

        //Si ningún primo ha conseguido dividirlo, es primo
        if (j == v.size()) v.push_back(i);
    }

    v.erase(v.end()-1);
    for (i=0; i < v.size(); i++) cout << v[i] << " ";
}

void ejemplo_complejos()
{
    complex<double> c1, c2, c3, I;
    c1 = complex<double>(-1.0, 0.0);
    c2 = complex<double>(1.0, -1.0);
    I = complex<double>(0.0, 1.0);
    c3 = 2.0 * (c1 - c2) * I;
    cout << c3 << endl;

    cout << 1.0+exp(I*3.14159) << endl;
    cout << sin(c2) << endl;
    cout << log(c1) << endl;
}

complex<double> xw(const double xn[100], const int w)
{
    complex<double> suma(0.0, 0.0);
    complex<double> c(0.0, 2.0 * 3.14159 / 100.0);

    int i;

    for (i=0; i < 100; i++)
    {
        suma += xn[i] * exp(-c * complex<double>(i*w, 0.0));
    }

    return suma;
}

void ejemplo_fourier()
{
    int i;
    double xn[100];
    double t, dt;

    t = 0;
    dt = 0.01;
    for (i=0; i < 100; i++)
    {
        xn[i] = sin(8.0 * 2.0 * 3.14159 * t);
        t += dt;
    }

    for (i=0; i < 100; i++)
    {
        cout << i << " " << abs(xw(xn, i)) << endl;
    }
}


void ejemplo_random()
{
    ranlux48 gen(958431198);
    uniform_real_distribution<double> r(0.0, 1.0);

    cout << r(gen) << " " << r(gen) << endl;
}

int main(void)
{
    //calcular_primos(100);
    //ejemplo_complejos();
    ejemplo_random();
    return 0;
}
