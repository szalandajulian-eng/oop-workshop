//
// Created by Julian Szałanda-Ośniecki on 23/10/2026.
//

#include "Container.h"
#include <stdexcept>

Container::Container() {
    number = 0;               // numer 0 oznacza brak kontenera
    tareWeight = 0;
    maxWeight = 0;
    strength = 0;
    cargo = 0;
}

Container::Container(int number) {
    this->number = number;
    tareWeight = 0;
    maxWeight = 0;
    strength = 0;
    cargo = 0;
}

//GETTERY

int Container::getNumber() const { return number; }
double Container::getTare() const { return tareWeight; }
double Container::getMaxWeight() const { return maxWeight; }
double Container::getStrength() const { return strength; }
double Container::getNetWeight() const { return cargo; }

double Container::getGrossWeight() const {
    return tareWeight + cargo;
}

double Container::getMaxCargo() const {
    if (maxWeight > tareWeight) {
        return maxWeight - tareWeight;
    }
    return 0;
}

//SETTERY

// Gdy w kontenerze jest ładunek, zmiana nie może
// złamać limitu wagi. Wtedy rzucamy wyjątek.
void Container::setTare(double tareWeight) {
    if (cargo > 0 && tareWeight + cargo > maxWeight) {
        throw std::out_of_range("New tare weight exceeds max weight");
    }
    this->tareWeight = tareWeight;
}

void Container::setMaxWeight(double maxWeight) {
    if (cargo > 0 && tareWeight + cargo > maxWeight) {
        throw std::out_of_range("New max weight is below current gross weight");
    }
    this->maxWeight = maxWeight;
}

void Container::setStrength(double strength) {
    this->strength = strength;
}

//ZAŁADUNEK I ROZŁADUNEK

// Najpierw sprawdzamy błędy, dopiero potem zmieniamy stan.
void Container::loadCargo(double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Amount must not be negative");
    }
    if (cargo + amount > getMaxCargo()) {
        throw std::out_of_range("Too much cargo");
    }
    cargo = cargo + amount;
}

void Container::unloadCargo(double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Amount must not be negative");
    }
    if (amount > cargo) {
        throw std::out_of_range("Not enough cargo to unload");
    }
    cargo = cargo - amount;
}