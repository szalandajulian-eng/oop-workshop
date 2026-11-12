//
// Created by Julian Szałanda-Ośniecki on 12/11/2026.
//

#ifndef OOPPROJECT_CONTAINERSTACK_H
#define OOPPROJECT_CONTAINERSTACK_H

#include <vector>
#include "Container.h"

const unsigned MAX_HEIGHT = 10;

class ContainerStack {
private:
    std::vector<Container> containers;

public:
    ContainerStack();
    ~ContainerStack();

    int getCapacity() const;          // ile kontenerów maksymalnie zmieści się na stosie
    int getSize() const;              // ile kontenerów jest teraz na stosie
    Container& at(int height);        // dostęp do kontenera na danej wysokości (REFERENCJA, nie kopia)
    void take(Container container);   // kładzie kontener na wierzch stosu
    Container give();                 // zdejmuje kontener z wierzchu i oddaje go (KOPIA)
};

#endif //OOPPROJECT_CONTAINERSTACK_H
