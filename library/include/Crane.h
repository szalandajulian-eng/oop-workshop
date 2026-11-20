//
// Created by Julian Szałanda-Ośniecki on 20/11/2026.
//

#ifndef OOPPROJECT_CRANE_H
#define OOPPROJECT_CRANE_H

#endif //OOPPROJECT_CRANE_H

#include "Container.h"
#include "ContainerStack.h"

const unsigned MAX_STACKS = 5;   // ile stosów jest na placu

const int PARKED = -1;
const int OVER_TRAILER = -2;

class Crane {
private:
    int position;                       // gdzie jest dźwig
    ContainerStack storage[MAX_STACKS]; // plac składowy
    Container container;                // to, co dźwig trzyma

public:
    Crane();

    // pytania o stan
    bool isParked() const;
    bool isLoaded() const;
    bool isUnloaded() const;
    bool isWaitingEmpty() const;
    bool isWaitingFull() const;

    // operacje
    void park();
    void load(Container c);
    Container unload();
    void forward(int steps);
    void backward(int steps);
    void pickUp();
    void putDown();

    // odczyt
    int getPosition() const;
    Container& getContainer();
    ContainerStack& stackAt(int index);

    bool canPickUp();
    bool canPutDown();
};
