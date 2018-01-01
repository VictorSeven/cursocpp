#include<iostream>
#include<cstdlib>

#include "Eigen/Eigen/Dense"

using Eigen::MatrixXd;
using Eigen::VectorXd;

using namespace std;


int main(void)
{
    MatrixXd m1(2,2);
    MatrixXd m2(2,3);
    VectorXd v(2);

    //Elementos de m1
    m1(0,0) = 1.0;
    m1(1,0) = 0.0;
    m1(0,1) = -1.0;
    m1(1,1) = m1(0,0);

    m1.resize(3,3); // Esto borra todos los contenidos de m1

    int i,j;
    //Rellenar m2
    for (i=0; i < m2.rows(); i++)
    {
        for (j=0; j < m2.cols(); j++)
        {
            m2(i,j) = 1.0*i*j;
        }
    }

    m1 = m2; //Tienen distintos tamaños, pero copia por completo la matriz

    cout << m1 << endl; //Mostrar

    m1.resize(2,2);

    //Es posible escribir matrices de forma rápida con <<:
    m1 << 1.0, 2.0,
          3.0, -1.0;
    v << 1.0, -1.0;

    cout << m1.transpose() + m1 << endl;
    cout << m1 * v << endl;
    cout << 2.0 * m1 + (m1 * m1) << endl;

    cout << m1.mean() << endl;
    cout << m1.minCoeff() << endl;
    cout << m1.trace() << endl;


    return 0;
}
