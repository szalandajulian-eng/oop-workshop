//
// Created by Julian Szałanda-Ośniecki on 23/10/2026.
//

#include <boost/test/unit_test.hpp>
#include "Container.h"
#include <stdexcept>

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

// 3. Ładowanie i wyładowanie towaru
BOOST_AUTO_TEST_CASE(testContainer_loadAndUnloadCargo_netWeightShouldDecrease) {
    Container container(234);
    container.setMaxWeight(100.0);

    container.loadCargo(50.0);
    BOOST_REQUIRE_CLOSE_FRACTION(container.getNetWeight(), 50.0, 0.00001);

    container.unloadCargo(20.0);
    BOOST_REQUIRE_CLOSE_FRACTION(container.getNetWeight(), 30.0, 0.00001);
}

// 4. Waga brutto = tara + ładunek
BOOST_AUTO_TEST_CASE(testContainer_grossWeight_shouldBeSumOfTareAndNet) {
    Container container(234);
    container.setTare(1500.0);
    container.setMaxWeight(5000.0);
    container.loadCargo(2000.0);

    // Brutto = 1500 (tara) + 2000 (ładunek) = 3500
    BOOST_REQUIRE_CLOSE_FRACTION(container.getGrossWeight(), 3500.0, 0.00001);
}

// 5. Przeładowanie ponad maxWeight rzuca wyjątek, ładunek bez zmian
BOOST_AUTO_TEST_CASE(testContainer_loadCargoOverMaxWeight_exceptionThrown) {
    Container container(234);
    container.setMaxWeight(100.0);

    BOOST_CHECK_THROW(container.loadCargo(150.0), std::out_of_range);
    BOOST_CHECK_EQUAL(container.getNetWeight(), 0.0);
}

// 6. Wyładowanie więcej, niż jest w środku, rzuca wyjątek
BOOST_AUTO_TEST_CASE(testContainer_unloadTooMuch_exceptionThrown) {
    Container container(4);
    container.setTare(1.0);
    container.setMaxWeight(9.0);
    container.loadCargo(3.0);

    BOOST_CHECK_THROW(container.unloadCargo(5.0), std::out_of_range);
    BOOST_CHECK_EQUAL(container.getNetWeight(), 3.0);
}

// 7. Ujemna ilość towaru to błędny argument
BOOST_AUTO_TEST_CASE(testContainer_negativeAmount_exceptionThrown) {
    Container container(4);
    container.setTare(1.0);
    container.setMaxWeight(9.0);

    BOOST_CHECK_THROW(container.loadCargo(-1.0), std::invalid_argument);
    BOOST_CHECK_THROW(container.unloadCargo(-1.0), std::invalid_argument);
}

// 8. Obniżenie maxWeight poniżej wagi brutto rzuca wyjątek
BOOST_AUTO_TEST_CASE(testContainer_setMaxWeightBelowGross_exceptionThrown) {
    Container container(4);
    container.setTare(1.0);
    container.setMaxWeight(9.0);
    container.loadCargo(5.0);                 // brutto 6

    BOOST_CHECK_THROW(container.setMaxWeight(5.0), std::out_of_range);
    BOOST_CHECK_EQUAL(container.getMaxWeight(), 9.0);
}

// 9. Zwiększenie tary ponad limit rzuca wyjątek
BOOST_AUTO_TEST_CASE(testContainer_setTareAboveLimit_exceptionThrown) {
    Container container(4);
    container.setTare(1.0);
    container.setMaxWeight(9.0);
    container.loadCargo(8.0);                 // brutto 9

    BOOST_CHECK_THROW(container.setTare(2.0), std::out_of_range);
    BOOST_CHECK_EQUAL(container.getTare(), 1.0);
}

// 10. Zmiana tary przy załadowanym kontenerze działa,
//     jeśli limit nadal jest zachowany
BOOST_AUTO_TEST_CASE(testContainer_setTareWhenStillFits_works) {
    Container container(4);
    container.setTare(1.0);
    container.setMaxWeight(10.0);
    container.loadCargo(5.0);                 // brutto 6
    container.setTare(2.0);                   // brutto 7, nadal ok

    BOOST_CHECK_EQUAL(container.getTare(), 2.0);
}

BOOST_AUTO_TEST_SUITE_END()