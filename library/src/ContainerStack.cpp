//
// Created by Julian Szałanda-Ośniecki on 12/11/2026.
//

#include "ContainerStack.h"

ContainerStack::ContainerStack() {
}

ContainerStack::~ContainerStack() {
}

int ContainerStack::getCapacity() const {
    return MAX_HEIGHT;
}

int ContainerStack::getSize() const {
    return static_cast<int>(containers.size());
}

Container& ContainerStack::at(int height) {
    if (height < 0 || height >= getSize()) {
        static Container empty;     // numer 0 = brak kontenera
        return empty;
    }
    return containers[height];
}

// Kładzie kontener na wierzch stosu.
void ContainerStack::take(Container container) {
    if (getSize() < getCapacity()) {
        containers.push_back(container);
    }
}

// Zdejmuje kontener z wierzchu i zwraca go.
Container ContainerStack::give() {
    if (getSize() == 0) {
        return Container();         // numer 0 = brak kontenera
    }
    Container top = containers.back();
    containers.pop_back();
    return top;
}