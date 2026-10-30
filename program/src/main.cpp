#include <iostream>
#include "Container.h"

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

//4.
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
    testLoadAndUnload(c, 3000);
    testLoadAndUnload(c, 9000);
}

//5. obiekt na STERCIE
Container* prepare(int number, double goods) {
    Container* p = new Container(number);
    p->setTare(1000);
    p->setMaxWeight(5000);
    p->loadCargo(goods);
    return p;
}

//7.
void testDynamicObject() {
    Container* p = prepare(202, 1500);
    display(p);
    delete p;
}

int main() {
    testLocalObject();
    testDynamicObject();
    return 0;
}
