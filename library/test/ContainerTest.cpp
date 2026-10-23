//
// Created by Julian Szałanda-Ośniecki on 23/10/2026.
//

#include <boost/test/unit_test.hpp>
#include "Container.h"

BOOST_AUTO_TEST_SUITE(ContainerSuite)

BOOST_AUTO_TEST_CASE(CreateEmptyContainer) {
    Container c;
    BOOST_REQUIRE_EQUAL(2 + 2, 4);
}

BOOST_AUTO_TEST_SUITE_END()