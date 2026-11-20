//
// Created by Julian Szałanda-Ośniecki on 12/11/2026.
//

#include <boost/test/unit_test.hpp>
#include "ContainerStack.h"
#include <stdexcept>

BOOST_AUTO_TEST_SUITE(ContainerStackTestSuite)

// Test 1: pojemność stosu jest równa stałej MAX_HEIGHT
BOOST_AUTO_TEST_CASE(testStack_getCapacity_shouldEqualMaxHeight) {
    ContainerStack stack;
    BOOST_REQUIRE_EQUAL(stack.getCapacity(), static_cast<int>(MAX_HEIGHT));
}

// Test 2: nowy stos jest pusty
BOOST_AUTO_TEST_CASE(testStack_newStack_shouldBeEmpty) {
    ContainerStack stack;
    BOOST_REQUIRE_EQUAL(stack.getSize(), 0);
}

// Test 3: po położeniu jednego kontenera rozmiar stosu to 1
BOOST_AUTO_TEST_CASE(testStack_takeOneContainer_sizeShouldBeOne) {
    ContainerStack stack;
    stack.take(Container(1));
    BOOST_REQUIRE_EQUAL(stack.getSize(), 1);
}

// Test 4: po położeniu trzech kontenerów rozmiar stosu to 3
BOOST_AUTO_TEST_CASE(testStack_takeThreeContainers_sizeShouldBeThree) {
    ContainerStack stack;
    stack.take(Container(1));
    stack.take(Container(2));
    stack.take(Container(3));
    BOOST_REQUIRE_EQUAL(stack.getSize(), 3);
}

// Test 5: położenie kontenera na pełny stos rzuca wyjątek
BOOST_AUTO_TEST_CASE(testStack_takeMoreThanCapacity_exceptionThrown) {
    ContainerStack stack;
    for (int i = 1; i <= stack.getCapacity(); i++) {
        stack.take(Container(i));
    }
    BOOST_CHECK_THROW(stack.take(Container(99)), std::out_of_range);
    BOOST_CHECK_EQUAL(stack.getSize(), stack.getCapacity());
}

// Test 6: zdjęcie ze stosu jednoelementowego
BOOST_AUTO_TEST_CASE(testStack_giveFromOneItemStack_stackEmptyAndCorrectNumber) {
    ContainerStack stack;
    stack.take(Container(7));
    Container c = stack.give();
    BOOST_REQUIRE_EQUAL(c.getNumber(), 7);
    BOOST_REQUIRE_EQUAL(stack.getSize(), 0);
}

// Test 7: zdjęty jest ostatni położony (LIFO), zostają dwa
BOOST_AUTO_TEST_CASE(testStack_giveFromThreeItemStack_shouldReturnLastTaken) {
    ContainerStack stack;
    stack.take(Container(1));
    stack.take(Container(2));
    stack.take(Container(3));
    Container c = stack.give();
    BOOST_REQUIRE_EQUAL(c.getNumber(), 3);
    BOOST_REQUIRE_EQUAL(stack.getSize(), 2);
}

// Test 8: at() zwraca kontenery w kolejności kładzenia (0 = dół stosu)
BOOST_AUTO_TEST_CASE(testStack_at_shouldMatchOrderOfLoading) {
    ContainerStack stack;
    stack.take(Container(1));
    stack.take(Container(2));
    stack.take(Container(3));
    BOOST_REQUIRE_EQUAL(stack.at(0).getNumber(), 1);
    BOOST_REQUIRE_EQUAL(stack.at(1).getNumber(), 2);
    BOOST_REQUIRE_EQUAL(stack.at(2).getNumber(), 3);
}

// Test 9: zdjęcie z pustego stosu rzuca wyjątek
BOOST_AUTO_TEST_CASE(testStack_giveFromEmptyStack_exceptionThrown) {
    ContainerStack stack;
    BOOST_CHECK_THROW(stack.give(), std::out_of_range);
    BOOST_CHECK_EQUAL(stack.getSize(), 0);
}

// Test 10: at() poza zakresem rzuca wyjątek
BOOST_AUTO_TEST_CASE(testStack_atOutOfRange_exceptionThrown) {
    ContainerStack stack;
    stack.take(Container(1));
    stack.take(Container(2));
    BOOST_CHECK_THROW(stack.at(2), std::out_of_range);
    BOOST_CHECK_THROW(stack.at(5), std::out_of_range);
    BOOST_CHECK_THROW(stack.at(-1), std::out_of_range);
}

// Test 11: załadowanie dokładnie tylu kontenerów, ile wynosi pojemność
BOOST_AUTO_TEST_CASE(testStack_takeExactlyCapacity_sizeShouldEqualCapacity) {
    ContainerStack stack;
    for (int i = 1; i <= stack.getCapacity(); i++) {
        stack.take(Container(i));
    }
    BOOST_REQUIRE_EQUAL(stack.getSize(), stack.getCapacity());
}

BOOST_AUTO_TEST_SUITE_END()