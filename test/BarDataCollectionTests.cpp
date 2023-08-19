//
// Created by Jeremy Cote on 2023-08-18.
//

#include <gtest/gtest.h>

#include "BarDataCollection.h"

// Test the constructor with valid and invalid sizes
TEST(BarDataCollectionTests, Constructor) {
    EXPECT_NO_THROW(BarDataCollection<int> collection(5));
    EXPECT_THROW(BarDataCollection<int> collection(0), std::invalid_argument);
}

// Test adding values to the collection
TEST(BarDataCollectionTests, AddValue) {
    BarDataCollection<int> collection(3);

    collection.add(10);
    collection.add(20);
    collection.add(30);

    EXPECT_EQ(collection.getNumberOfElements(), 3);
}

// Test adding more values than the collection size
TEST(BarDataCollectionTests, AddExceedingSize) {
    BarDataCollection<int> collection(2);

    collection.add(10);
    collection.add(20);
    collection.add(30);

    EXPECT_EQ(collection.getNumberOfElements(), 2);
    EXPECT_EQ(*collection.getValues()[0], 20); // Oldest value replaced
    EXPECT_EQ(*collection.getValues()[1], 30); // Newest value
}

// Test updating a value
TEST(BarDataCollectionTests, UpdateValue) {
    BarDataCollection<int> collection(2);

    collection.add(10);
    collection.add(20);

    collection.update(30);

    EXPECT_EQ(collection.getNumberOfElements(), 2);
    EXPECT_EQ(*collection.getValues()[0], 10);
    EXPECT_EQ(*collection.getValues()[1], 30); // Updated value
}

// Test updating without any values added
TEST(BarDataCollectionTests, UpdateWithoutAdd) {
    BarDataCollection<int> collection(2);

    collection.update(30);

    EXPECT_EQ(collection.getNumberOfElements(), 1);
    EXPECT_EQ(*collection.getValues()[0], 30); // New value
}

// Test getting the number of elements
TEST(BarDataCollectionTests, GetNumberOfElements) {
    BarDataCollection<int> collection(3);

    collection.add(10);
    collection.add(20);

    EXPECT_EQ(collection.getNumberOfElements(), 2);
}

// Test getting the size of the collection
TEST(BarDataCollectionTests, GetSize) {
    BarDataCollection<int> collection(5);

    EXPECT_EQ(collection.getSize(), 5);
}