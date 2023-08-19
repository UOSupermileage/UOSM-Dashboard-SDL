//
// Created by Jeremy Cote on 2023-08-18.
//

#include "Identifiable.hpp"
#include <gtest/gtest.h>

// Test Identifiable's getId function
TEST(IdentifiableTests, GetId) {
    Identifiable object1;
    Identifiable object2;

    uint32_t id1 = object1.getId();
    uint32_t id2 = object2.getId();

    EXPECT_EQ(id1 + 1, id2); // The id should be incremented for construction
}

// Test Identifiable's equality operator
TEST(IdentifiableTests, EqualityOperator) {
    Identifiable object1;
    Identifiable object2;

    EXPECT_TRUE(object1 == object1); // An object should be equal to itself
    EXPECT_FALSE(object1 == object2); // Different objects should not be equal
}