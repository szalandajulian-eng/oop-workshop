//
// Created by Julian Szałanda-Ośniecki on 23/10/2026.
//

#ifndef CONTAINER_H
#define CONTAINER_H

class Container {
private:
    int number;         // numer rejestracyjny kontenera (0 oznacza: brak kontenera)
    double tareWeight;  // waga pustego kontenera
    double maxWeight;   // maksymalna waga kontenera razem z ładunkiem
    double strength;    // maksymalny ciężar innych kontenerów, które można na nim postawić
    double cargo;       // waga ładunku w środku (to samo co netWeight)

public:
    Container();
    Container(int number);

    int getNumber() const;
    double getTare() const;
    void setTare(double tareWeight);
    double getMaxWeight() const;
    void setMaxWeight(double maxWeight);
    double getStrength() const;
    void setStrength(double strength);
    double getGrossWeight() const;   // oblicza i zwraca wagę brutto (tara + ładunek)
    double getNetWeight() const;     // zwraca wagę ładunku (cargo)
    double getMaxCargo() const;      // oblicza i zwraca maksymalną wagę ładunku (maxWeight - tareWeight)

    void loadCargo(double amount);
    void unloadCargo(double amount);
};

#endif