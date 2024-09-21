#include <iostream>
#include <cmath>
#include <array>

using namespace std;

const double k = 8.99e9; //Constante de Coulomb, la 'e' indica notación cientifica.

std::array<double, 3> coulombLaw(double q1, double q2, double distanceX, double distanceY, double r) {
    double force = (q1*q2*k)/(r*r);

    double forceX = force * (distanceX/r);
    double forceY = force * (distanceY/r);

    return {force, forceX, forceY};
}

std::array<double, 3> findDistance(double qX1, double qY1, double qX2, double qY2) {
    double distanceX = qX2-qX1;
    double distanceY = qY2-qY1;

    double distanceBetweenCharges = sqrt(distanceX*distanceX + distanceY*distanceY);

    return {distanceX, distanceY, distanceBetweenCharges};
}

int main() {
    //Fuerza en nC (nano coulombs). Si quieres usar otra notación como 10*-3, pones pr ej: -3e-3

    double q1 = -5e-9;
    double q2 = 4e-9;

    std::array<double, 3> force12_d = findDistance(2, 6, -3, 0);

    std::array<double, 3> force13_d = findDistance(2, 6, 5, 1);

    //Encontramos F12 en nN y sus componentes.
    std::array<double, 3> force12_data = coulombLaw(q1, q2, force12_d[0], force12_d[1], force12_d[2]);

    double force12_x = force12_data[1];
    double force12_y = force12_data[2];

    //Encontramos cuanto vale q3. Se obtiene simplemente descomponiendo la ley de Coulomb en un papel y aislando q3 sabiendo que f12x+f13x = 0.

    double q3 = (-force12_x*pow(force13_d[2], 3)) / (k * force13_d[0] * q1);

    std::array<double, 3> force13_data = coulombLaw(q1, q3, force13_d[0], force13_d[1], force13_d[2]);

    double force13_y = force13_data[2];

    double tension = fabs(force13_y + force12_y);

    cout << "q3: " << q3 <<endl;
    cout << "tension: " << tension <<endl;
}