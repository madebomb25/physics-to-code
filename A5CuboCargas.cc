#include <iostream>
#include <cmath>
#include <array>

using namespace std;

const double k = 8.99e9; //Constante de Coulomb, la 'e' indica notación cientifica.

double coulombLaw(double q1, double q2, double r, double vectorDirection=1) {
    // 8.99e9 es la constante de Coulomb en notación cientifica.
    return (q1*q2*8.99e9)/(r*r);
}

std::array<double, 4> find3DDistance(std::array<double, 3> q1coords, std::array<double, 3> q2coords) {
    double distanceX = q2coords[0] - q1coords[0];
    double distanceY = q2coords[1] - q1coords[1];
    double distanceZ = q2coords[2] - q1coords[2];

    double totalDistance = sqrt(distanceX*distanceX + distanceY*distanceY + distanceZ*distanceZ);

    return {distanceX, distanceY, distanceZ, totalDistance};
}

int main() {
    const double l = 0.03;

    double totalForce_x = 0;
    double totalForce_y = 0;
    double totalForce_z = 0;

    const int target = 7;

    const std::array<double, 8> charges = {
        4e-6,
        3e-6,
        2e-6,
        4e-6,
        4e-6,
        3e-6,
        2e-6,
        2e-6

    };

    const std::array<std::array<double, 3>, 8> chargeCoords = {{
        {0, 0, 0},
        {l, 0, 0},
        {l, l, 0},
        {0, l, 0},
        {0, 0, l},
        {l, 0, l},
        {l, l, l},
        {0, l, l}
    }};

    std::array<double, 3> targetChargeCoords = {chargeCoords[target-1][0], chargeCoords[target-1][1], chargeCoords[target-1][2]};

    for (int i=0; i<charges.size(); i++) {
            std::array<double, 4> distances = find3DDistance(chargeCoords[i], targetChargeCoords);

            if (distances[3] != 0) {
                double force = coulombLaw(charges[i], charges[target-1], distances[3]);

                totalForce_x += force * (distances[0] / distances[3]);
                totalForce_y += force * (distances[1] / distances[3]);
                totalForce_z += force * (distances[2] / distances[3]);
            }
    }

    cout << "Fx = " << totalForce_x <<endl;
    cout << "Fy = " << totalForce_y <<endl;
    cout << "Fz = " << totalForce_z <<endl;
}