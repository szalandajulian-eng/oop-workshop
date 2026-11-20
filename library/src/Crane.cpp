#include "Crane.h"
#include <stdexcept>

// Nowy dźwig jest zaparkowany.
Crane::Crane() : position(PARKED) {
}

// ----- Stan dźwigu -----
// Numer kontenera 0 oznacza "brak kontenera".

// Zaparkowany.
bool Crane::isParked() const {
    return position == PARKED;
}

// Nad naczepą, pusty.
bool Crane::isUnloaded() const {
    return position <= OVER_TRAILER
           && container.getNumber() == 0;
}

// Nad naczepą, z kontenerem.
bool Crane::isLoaded() const {
    return position <= OVER_TRAILER
           && container.getNumber() != 0;
}

// Nad stosem, pusty.
bool Crane::isWaitingEmpty() const {
    return position >= 0
           && position < static_cast<int>(MAX_STACKS)
           && container.getNumber() == 0;
}

// Nad stosem, z kontenerem.
bool Crane::isWaitingFull() const {
    return position >= 0
           && position < static_cast<int>(MAX_STACKS)
           && container.getNumber() != 0;
}

// ----- Parkowanie, załadunek, rozładunek -----

// Nie można parkować z kontenerem.
void Crane::park() {
    if (isLoaded() || isWaitingFull()) {
        throw std::logic_error(
            "Crane cannot park while carrying a container");
    }
    position = PARKED;
}

// Załadunek tylko nad naczepą i gdy dźwig jest pusty.
void Crane::load(Container c) {
    if (!isUnloaded()) {
        throw std::logic_error(
            "Crane can only be loaded over the trailer when empty");
    }
    container = c;
}

// Rozładunek tylko nad naczepą i gdy dźwig coś trzyma.
Container Crane::unload() {
    if (!isLoaded()) {
        throw std::logic_error(
            "Crane can only be unloaded over the trailer when loaded");
    }
    Container unloaded = container;  // zapamiętaj kontener
    container = Container();         // opróżnij dźwig
    return unloaded;                 // oddaj kontener
}

// ----- Ruch -----
// Najpierw liczymy nową pozycję i sprawdzamy ją,
// dopiero potem zmieniamy dźwig.

void Crane::forward(int steps) {
    int newPosition = position + steps;
    int lastStack = static_cast<int>(MAX_STACKS) - 1;

    if (newPosition > lastStack || newPosition < OVER_TRAILER) {
        throw std::out_of_range("Crane move out of range");
    }
    position = newPosition;
}

void Crane::backward(int steps) {
    int newPosition = position - steps;
    int lastStack = static_cast<int>(MAX_STACKS) - 1;

    if (newPosition > lastStack || newPosition < OVER_TRAILER) {
        throw std::out_of_range("Crane move out of range");
    }
    position = newPosition;
}

// ----- Praca ze stosami -----

// Zdejmij kontener ze stosu pod dźwigiem.
void Crane::pickUp() {
    if (!canPickUp()) {
        throw std::logic_error("Cannot pick up a container here");
    }
    container = stackAt(position).give();
}

// Połóż kontener na stosie pod dźwigiem.
void Crane::putDown() {
    if (!canPutDown()) {
        throw std::logic_error("Cannot put down a container here");
    }
    stackAt(position).take(container);  // najpierw połóż
    container = Container();            // potem opróżnij dźwig
}

// ----- Odczyt -----

int Crane::getPosition() const {
    return position;
}

// Referencja, żeby nie kopiować.
Container& Crane::getContainer() {
    return container;
}

// Stos o danym numerze. Zły numer to błąd.
ContainerStack& Crane::stackAt(int index) {
    if (index < 0 || index >= static_cast<int>(MAX_STACKS)) {
        throw std::out_of_range("Stack index out of range");
    }
    return storage[index];
}

// ----- Czy można? -----

// Dźwig czeka pusty, a stos ma kontenery.
// Zaparkowany dźwig zatrzyma się na isWaitingEmpty(),
// więc stackAt() się nie wykona.
bool Crane::canPickUp() {
    return isWaitingEmpty()
           && stackAt(position).getSize() > 0;
}

// Dźwig czeka pełny, a stos nie jest pełny.
bool Crane::canPutDown() {
    return isWaitingFull()
           && stackAt(position).getSize()
              < stackAt(position).getCapacity();
}