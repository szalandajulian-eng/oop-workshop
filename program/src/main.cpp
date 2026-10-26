#include <iostream>
#include "Container.h"

using namespace std;

int main() {
    Container c(999);

    c.setTare(2000.0);
    c.setMaxWeight(5000.0);

    cout << "--- DANE KONTENERA ---" << endl;
    cout << "Maksymalny ladunek do zaladowania: " << c.getMaxCargo() << " kg" << endl;

    c.loadCargo(1500.0);

    cout << "Aktualny ladunek (netto): " << c.getNetWeight() << " kg" << endl;
    cout << "Calkowita waga (brutto): " << c.getGrossWeight() << " kg" << endl;

    return 0;
}