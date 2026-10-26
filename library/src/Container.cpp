//
// Created by Julian Szałanda-Ośniecki on 23/10/2026.
//

#include "Container.h"

Container::Container() {
    number = 0;
    tareWeight = 0.0;
    maxWeight = 0.0;
    cargo = 0.0;
}

Container::Container(int number) {
    this->number = number;
    tareWeight = 0.0;
    maxWeight = 0.0;
    cargo = 0.0;
}

int Container::getNumber() const { return number; }
double Container::getTare() const { return tareWeight; }
double Container::getNetWeight() const { return cargo; }
double Container::getMaxWeight() const { return maxWeight; }

void Container::setTare(double tareWeight) {
    this->tareWeight = tareWeight;
}

void Container::setMaxWeight(double maxWeight) {
    this->maxWeight = maxWeight;
}


double Container::getGrossWeight() const {
    return tareWeight + cargo;
}

double Container::getMaxCargo() const {
    if (maxWeight > tareWeight) {
        return maxWeight - tareWeight;
    }
    return 0.0;
}

void Container::loadCargo(double amount) {
    if (amount > 0) {
        cargo += amount;
    }
}

