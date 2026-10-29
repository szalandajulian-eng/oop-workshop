//
// Created by Julian Szałanda-Ośniecki on 23/10/2026.
//

#include "Container.h"

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

void Container::setTare(double tareWeight) {
    if (cargo == 0) {
        this->tareWeight = tareWeight;
    }
}

void Container::setMaxWeight(double maxWeight) {
    if (cargo == 0) {
        this->maxWeight = maxWeight;
    }
}

void Container::setStrength(double strength) {
    this->strength = strength;
}

//ZAŁADUNEK I ROZŁADUNEK

void Container::loadCargo(double amount) {
    if (amount > 0 && cargo + amount <= getMaxCargo()) {
        cargo = cargo + amount;
    }
}

void Container::unloadCargo(double amount) {
    if (amount > 0 && amount <= cargo) {
        cargo = cargo - amount;
    }
}