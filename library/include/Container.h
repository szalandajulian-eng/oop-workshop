//
// Created by Julian Szałanda-Ośniecki on 23/10/2026.
//

#ifndef OOPPROJECT_CONTAINER_H
#define OOPPROJECT_CONTAINER_H

class Container {
private:
    int number;
    double tareWeight;
    double maxWeight;
    double cargo;

public:
    Container();
    Container(int number);

    int getNumber() const;

    double getTare() const;
    void setTare(double tareWeight);

    double getMaxWeight() const;
    void setMaxWeight(double maxWeight);

    double getGrossWeight() const;
    double getMaxCargo() const;
    double getNetWeight() const;

    void loadCargo(double amount);
};

#endif //OOPPROJECT_CONTAINER_H
