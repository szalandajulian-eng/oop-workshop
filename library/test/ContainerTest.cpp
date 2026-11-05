//
// Created by Julian Szałanda-Ośniecki on 23/10/2026.
//

#include <boost/test/unit_test.hpp>
#include "Container.h"

BOOST_AUTO_TEST_SUITE(ContainerTestSuite)

// 1. Konstruktor domyślny
BOOST_AUTO_TEST_CASE(testContainer_defaultConstructor_numberShouldBeZero) {
    Container container;
    BOOST_REQUIRE_EQUAL(container.getNumber(), 0);
}

// 2. Konstruktor z numerem i wagi początkowe
BOOST_AUTO_TEST_CASE(testContainer_onlyRegistrationNumber_allWeightsShouldBeZero) {
    Container container(234);
    BOOST_REQUIRE_EQUAL(container.getNumber(), 234);
    BOOST_REQUIRE_EQUAL(container.getTare(), 0.0);
    BOOST_REQUIRE_EQUAL(container.getMaxWeight(), 0.0);
    BOOST_REQUIRE_EQUAL(container.getNetWeight(), 0.0);
    BOOST_REQUIRE_CLOSE_FRACTION(container.getGrossWeight(), 0.0, 0.00001);
}

// 3. Ładowanie i wyładowanie towaru (unloadCargo)
BOOST_AUTO_TEST_CASE(testContainer_loadAndUnloadCargo_netWeightShouldDecrease) {
    Container container(234);
    container.setMaxWeight(100.0);

    container.loadCargo(50.0);
    BOOST_REQUIRE_CLOSE_FRACTION(container.getNetWeight(), 50.0, 0.00001);

    container.unloadCargo(20.0);
    BOOST_REQUIRE_CLOSE_FRACTION(container.getNetWeight(), 30.0, 0.00001);
}

// 4. Wyliczanie wagi brutto (Gross Weight = Tare + Net Weight)
BOOST_AUTO_TEST_CASE(testContainer_grossWeight_shouldBeSumOfTareAndNet) {
    Container container(234);
    container.setTare(1500.0);
    container.setMaxWeight(5000.0);
    container.loadCargo(2000.0);

    // Brutto = 1500 (tara) + 2000 (ładunek) = 3500
    BOOST_REQUIRE_CLOSE_FRACTION(container.getGrossWeight(), 3500.0, 0.00001);
}

// 5. Przypadek brzegowy: próba przeładowania kontenera ponad maxWeight
BOOST_AUTO_TEST_CASE(testContainer_loadCargoOverMaxWeight_shouldNotExceedLimit) {
    Container container(234);
    container.setMaxWeight(100.0);

    // Próba załadowania więcej niż wynosi limit maxWeight
    container.loadCargo(150.0);

    // Ładunek nie powinien przekroczyć maxWeight (powinien wynieść max 100.0 lub nie zostać przyjęty)
    BOOST_REQUIRE_LE(container.getNetWeight(), container.getMaxWeight());
}

BOOST_AUTO_TEST_SUITE_END()