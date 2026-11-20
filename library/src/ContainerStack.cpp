//
// Created by Julian Szałanda-Ośniecki on 12/11/2026.
//

#include "ContainerStack.h"
#include <stdexcept>

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

// Kontener na danej wysokości (0 = dół stosu).
// Zła wysokość to błąd.
Container& ContainerStack::at(int height) {
    if (height < 0 || height >= getSize()) {
        throw std::out_of_range("No container at this height");
    }
    return containers[height];
}

// Kładzie kontener na wierzch stosu.
// Pełny stos to błąd.
void ContainerStack::take(Container container) {
    if (getSize() >= getCapacity()) {
        throw std::out_of_range("Stack is full");
    }
    containers.push_back(container);
}

// Zdejmuje kontener z wierzchu i zwraca go.
// Pusty stos to błąd.
Container ContainerStack::give() {
    if (getSize() == 0) {
        throw std::out_of_range("Stack is empty");
    }
    Container top = containers.back();
    containers.pop_back();
    return top;
}