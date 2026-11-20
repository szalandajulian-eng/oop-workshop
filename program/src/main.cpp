#include <iostream>
#include <stdexcept>
#include "Container.h"
#include "Crane.h"

using namespace std;

//1.przez WARTOŚĆ
void display(Container c) {
    cout << "Kontener nr " << c.getNumber()
         << ": tara=" << c.getTare()
         << ", max=" << c.getMaxWeight()
         << ", wytrzymalosc=" << c.getStrength()
         << ", ladunek=" << c.getNetWeight()
         << ", brutto=" << c.getGrossWeight()
         << ", max ladunek=" << c.getMaxCargo() << endl;
}

//6 przez WSKAŹNIK
void display(Container* p) {
    cout << "Kontener nr " << p->getNumber()
         << ": tara=" << p->getTare()
         << ", max=" << p->getMaxWeight()
         << ", wytrzymalosc=" << p->getStrength()
         << ", ladunek=" << p->getNetWeight()
         << ", brutto=" << p->getGrossWeight()
         << ", max ladunek=" << p->getMaxCargo() << endl;
}

//3. przez REFERENCJĘ
void displayCargo(Container& c) {
    cout << "  ladunek: " << c.getNetWeight() << " kg" << endl;
}

//4. Może rzucić wyjątek (przeładowanie).
void testLoadAndUnload(Container& c, double goods) {
    displayCargo(c);
    c.loadCargo(goods);
    displayCargo(c);
    c.unloadCargo(goods);
    displayCargo(c);
}

//2. obiekt na STOSIE
void testLocalObject() {
    Container c(101);
    c.setTare(2000);
    c.setMaxWeight(6000);
    c.setStrength(10000);
    display(c);

    testLoadAndUnload(c, 3000);        // mieści się

    // 9000 się nie zmieści, więc łapiemy wyjątek.
    try {
        testLoadAndUnload(c, 9000);
    } catch (const out_of_range& ex) {
        cerr << "Blad: " << ex.what() << endl;
    }
}

//5. obiekt na STERCIE
Container* prepare(int number, double goods) {
    Container* p = new Container(number);
    try {
        p->setTare(1000);
        p->setMaxWeight(5000);
        p->loadCargo(goods);
    } catch (...) {
        delete p;      // sprzątamy, żeby nie było wycieku pamięci
        throw;         // i przekazujemy błąd dalej
    }
    return p;
}

//7.
void testDynamicObject() {
    Container* p = prepare(202, 1500);
    display(p);
    delete p;
}

// Pełny cykl pracy dźwigu: naczepa -> stos -> naczepa.
void testCrane() {
    Crane crane;                    // zaparkowany

    crane.backward(1);              // nad naczepą
    crane.load(Container(1));       // kontener z naczepy na dźwig
    crane.forward(2);               // nad stosem 0
    crane.putDown();                // kontener na stos

    cout << "Kontenery na stosie 0: "
         << crane.stackAt(0).getSize() << endl;

    crane.pickUp();                 // kontener ze stosu na dźwig
    crane.backward(2);              // nad naczepą
    Container c = crane.unload();   // kontener na naczepę
    crane.park();                   // koniec pracy

    cout << "Rozladowano kontener numer "
         << c.getNumber() << endl;
}

// Błąd obsłużony przez try/catch.
void testCraneError() {
    Crane crane;                    // zaparkowany
    try {
        crane.pickUp();             // nie wolno
    } catch (const logic_error& ex) {
        cerr << "Blad: " << ex.what() << endl;
    }
}

int main() {
    try {
        testLocalObject();
        testDynamicObject();
        testCrane();
        testCraneError();
    } catch (const exception& ex) {
        cerr << "Nieobsluzony blad: " << ex.what() << endl;
        return 1;
    }
    return 0;
}