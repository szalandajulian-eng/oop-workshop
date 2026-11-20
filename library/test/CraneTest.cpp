//
// Created by Julian Szałanda-Ośniecki on 20/11/2026.
//

#include <boost/test/unit_test.hpp>
#include "Crane.h"
#include <stdexcept>

BOOST_AUTO_TEST_SUITE(CraneTestSuite)

BOOST_AUTO_TEST_CASE(Crane_NewCrane_IsParkedAndEmpty) {
    Crane crane;
    BOOST_CHECK(crane.isParked());
    BOOST_CHECK(!crane.isLoaded());
    BOOST_CHECK(!crane.isUnloaded());
    BOOST_CHECK(!crane.isWaitingEmpty());
    BOOST_CHECK(!crane.isWaitingFull());
    BOOST_CHECK_EQUAL(crane.getPosition(), PARKED);
    BOOST_CHECK_EQUAL(crane.getContainer().getNumber(), 0);
}

BOOST_AUTO_TEST_CASE(Crane_BackwardFromParked_IsOverTrailerAndUnloaded) {
    Crane crane;
    crane.backward(1);
    BOOST_CHECK_EQUAL(crane.getPosition(), OVER_TRAILER);
    BOOST_CHECK(crane.isUnloaded());
    BOOST_CHECK(!crane.isParked());
}

BOOST_AUTO_TEST_CASE(Crane_ForwardFromParked_IsWaitingEmptyOverFirstStack) {
    Crane crane;
    crane.forward(1);
    BOOST_CHECK_EQUAL(crane.getPosition(), 0);
    BOOST_CHECK(crane.isWaitingEmpty());
}

BOOST_AUTO_TEST_CASE(Crane_ForwardToLastStack_PositionIsLastStack) {
    Crane crane;
    crane.forward(static_cast<int>(MAX_STACKS));   // -1 + 5 = 4
    BOOST_CHECK_EQUAL(crane.getPosition(), static_cast<int>(MAX_STACKS) - 1);
}

BOOST_AUTO_TEST_CASE(Crane_ForwardBeyondLastStack_ExceptionThrown) {
    Crane crane;
    BOOST_CHECK_THROW(crane.forward(static_cast<int>(MAX_STACKS) + 1), std::out_of_range);
    BOOST_CHECK_EQUAL(crane.getPosition(), PARKED);   // pozycja bez zmian
}

BOOST_AUTO_TEST_CASE(Crane_BackwardBeyondTrailer_ExceptionThrown) {
    Crane crane;
    BOOST_CHECK_THROW(crane.backward(2), std::out_of_range);   // -1 - 2 = -3
    BOOST_CHECK_EQUAL(crane.getPosition(), PARKED);
}

BOOST_AUTO_TEST_CASE(Crane_ForwardThenPark_IsParked) {
    Crane crane;
    crane.forward(2);
    crane.park();
    BOOST_CHECK(crane.isParked());
}

BOOST_AUTO_TEST_CASE(Crane_LoadOverTrailer_IsLoadedAndHoldsContainer) {
    Crane crane;
    crane.backward(1);
    crane.load(Container(7));
    BOOST_CHECK(crane.isLoaded());
    BOOST_CHECK_EQUAL(crane.getContainer().getNumber(), 7);
}

BOOST_AUTO_TEST_CASE(Crane_LoadWhileParked_ExceptionThrown) {
    Crane crane;
    BOOST_CHECK_THROW(crane.load(Container(7)), std::logic_error);
}

BOOST_AUTO_TEST_CASE(Crane_LoadWhenAlreadyLoaded_ExceptionThrown) {
    Crane crane;
    crane.backward(1);
    crane.load(Container(7));
    BOOST_CHECK_THROW(crane.load(Container(8)), std::logic_error);
    BOOST_CHECK_EQUAL(crane.getContainer().getNumber(), 7);   // stary kontener został
}

BOOST_AUTO_TEST_CASE(Crane_ParkWhileLoaded_ExceptionThrown) {
    Crane crane;
    crane.backward(1);
    crane.load(Container(7));
    BOOST_CHECK_THROW(crane.park(), std::logic_error);
    BOOST_CHECK(crane.isLoaded());                            // nadal nad naczepą
}

BOOST_AUTO_TEST_CASE(Crane_Unload_ReturnsContainerAndCraneIsEmpty) {
    Crane crane;
    crane.backward(1);
    crane.load(Container(7));
    Container c = crane.unload();
    BOOST_CHECK_EQUAL(c.getNumber(), 7);
    BOOST_CHECK(crane.isUnloaded());
    BOOST_CHECK_EQUAL(crane.getContainer().getNumber(), 0);
}

BOOST_AUTO_TEST_CASE(Crane_UnloadWhenEmpty_ExceptionThrown) {
    Crane crane;
    crane.backward(1);
    BOOST_CHECK_THROW(crane.unload(), std::logic_error);
}

BOOST_AUTO_TEST_CASE(Crane_NegativeSteps_ExceptionThrown) {
    Crane crane;
    BOOST_CHECK_THROW(crane.forward(-5), std::out_of_range);
    BOOST_CHECK_THROW(crane.backward(-10), std::out_of_range);
    BOOST_CHECK_EQUAL(crane.getPosition(), PARKED);
}

BOOST_AUTO_TEST_CASE(Crane_StackAtInvalidIndex_ExceptionThrown) {
    Crane crane;
    BOOST_CHECK_THROW(crane.stackAt(-1), std::out_of_range);
    BOOST_CHECK_THROW(
        crane.stackAt(static_cast<int>(MAX_STACKS)),
        std::out_of_range);
    BOOST_CHECK_NO_THROW(crane.stackAt(0));
}

BOOST_AUTO_TEST_CASE(Crane_PickUp_TakesContainerFromStack) {
    Crane crane;
    crane.stackAt(0).take(Container(5));
    crane.forward(1);                  // nad stosem 0
    BOOST_CHECK(crane.canPickUp());
    crane.pickUp();
    BOOST_CHECK(crane.isWaitingFull());
    BOOST_CHECK_EQUAL(crane.getContainer().getNumber(), 5);
    BOOST_CHECK_EQUAL(crane.stackAt(0).getSize(), 0);
}

BOOST_AUTO_TEST_CASE(Crane_CanPickUp_FalseWhenParkedOrStackEmpty) {
    Crane crane;
    BOOST_CHECK(!crane.canPickUp());   // zaparkowany
    crane.forward(1);
    BOOST_CHECK(!crane.canPickUp());   // pusty stos
}

BOOST_AUTO_TEST_CASE(Crane_PickUpFromEmptyStack_ExceptionThrown) {
    Crane crane;
    crane.forward(1);
    BOOST_CHECK_THROW(crane.pickUp(), std::logic_error);
}

BOOST_AUTO_TEST_CASE(Crane_PutDown_PutsContainerOnStack) {
    Crane crane;
    crane.backward(1);                 // nad naczepą
    crane.load(Container(7));
    crane.forward(2);                  // nad stosem 0
    BOOST_CHECK(crane.canPutDown());
    crane.putDown();
    BOOST_CHECK(crane.isWaitingEmpty());
    BOOST_CHECK_EQUAL(crane.stackAt(0).getSize(), 1);
    BOOST_CHECK_EQUAL(crane.stackAt(0).at(0).getNumber(), 7);
}

BOOST_AUTO_TEST_CASE(Crane_PutDownWhenEmpty_ExceptionThrown) {
    Crane crane;
    crane.forward(1);
    BOOST_CHECK(!crane.canPutDown());
    BOOST_CHECK_THROW(crane.putDown(), std::logic_error);
}

BOOST_AUTO_TEST_CASE(Crane_PutDownOnFullStack_ExceptionThrown) {
    Crane crane;
    for (int i = 1; i <= static_cast<int>(MAX_HEIGHT); ++i) {
        crane.stackAt(0).take(Container(i));
    }
    crane.backward(1);
    crane.load(Container(99));
    crane.forward(2);
    BOOST_CHECK(!crane.canPutDown());
    BOOST_CHECK_THROW(crane.putDown(), std::logic_error);
    BOOST_CHECK_EQUAL(crane.getContainer().getNumber(), 99);
}

BOOST_AUTO_TEST_SUITE_END()