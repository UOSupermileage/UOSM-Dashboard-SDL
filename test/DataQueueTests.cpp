//
// Created by Jeremy Cote on 2023-08-18.
//

#include <gtest/gtest.h>

#include "DataQueue.hpp"

// Test the constructor with valid and invalid sizes
TEST(DataQueueTests, Constructor) {
    EXPECT_NO_THROW(DataQueue<int> collection(5));
    EXPECT_THROW(DataQueue<int> collection(0), std::invalid_argument);
}

// Test adding values to the collection
TEST(DataQueueTests, AddValue) {
    DataQueue<int> collection(3);

    collection.add(10);
    collection.add(20);
    collection.add(30);

    EXPECT_EQ(collection.getNumberOfElements(), 3);
}

// Test adding more values than the collection size
TEST(DataQueueTests, AddExceedingSize) {
    DataQueue<int> collection(2);

    collection.add(10);
    collection.add(20);
    collection.add(30);

    EXPECT_EQ(collection.getNumberOfElements(), 2);
    EXPECT_EQ(collection.getValues()[0], 20); // Oldest value replaced
    EXPECT_EQ(collection.getValues()[1], 30); // Newest value
}

// Test updating a value
TEST(DataQueueTests, UpdateValue) {
    DataQueue<int> collection(2);

    collection.add(10);
    collection.add(20);

    collection.update(30);

    EXPECT_EQ(collection.getNumberOfElements(), 2);
    EXPECT_EQ(collection.getValues()[0], 10);
    EXPECT_EQ(collection.getValues()[1], 30); // Updated value
}

// Test updating without any values added
TEST(DataQueueTests, UpdateWithoutAdd) {
    DataQueue<int> collection(2);

    collection.update(30);

    EXPECT_EQ(collection.getNumberOfElements(), 1);
    EXPECT_EQ(collection.getValues()[0], 30); // New value
}

// Test getting the number of elements
TEST(DataQueueTests, GetNumberOfElements) {
    DataQueue<int> collection(3);

    collection.add(10);
    collection.add(20);

    EXPECT_EQ(collection.getNumberOfElements(), 2);
}

// Test getting the size of the collection
TEST(DataQueueTests, GetSize) {
    DataQueue<int> collection(5);

    EXPECT_EQ(collection.getSize(), 5);
}

// Test for getLargestValue when the DataQueue is empty
TEST(DataQueueTests, GetLargestValueEmptyQueue) {
    DataQueue<int> dataQueue(5);
    EXPECT_THROW(dataQueue.getLargestValue(), std::out_of_range);
}

// Test for getLargestValue when the DataQueue has one element
TEST(DataQueueTests, GetLargestValueSingleElement) {
    DataQueue<int> dataQueue(5);
    dataQueue.add(10);
    EXPECT_EQ(dataQueue.getLargestValue(), 10);
}

// Test for getLargestValue after adding elements
TEST(DataQueueTests, GetLargestValueAfterAdding) {
    DataQueue<int> dataQueue(5);
    dataQueue.add(5);
    dataQueue.add(10);
    dataQueue.add(7);
    EXPECT_EQ(dataQueue.getLargestValue(), 10);

    dataQueue.add(15);
    EXPECT_EQ(dataQueue.getLargestValue(), 15);

    dataQueue.add(12);
    EXPECT_EQ(dataQueue.getLargestValue(), 15);
}

// Test for getLargestValue after updating elements
TEST(DataQueueTests, GetLargestValueAfterUpdating) {
    DataQueue<int> dataQueue(5);
    dataQueue.add(5);

    EXPECT_EQ(dataQueue.getLargestValue(), 5);

    dataQueue.add(10);

    EXPECT_EQ(dataQueue.getLargestValue(), 10);

    dataQueue.add(7);

    EXPECT_EQ(dataQueue.getLargestValue(), 10);

    dataQueue.update(12);
    EXPECT_EQ(dataQueue.getLargestValue(), 12);

    dataQueue.update(8);
    EXPECT_EQ(dataQueue.getLargestValue(), 10);
}

// Test for getLargestValue after updating with a larger value
TEST(DataQueueTests, GetLargestValueUpdateWithLargerValue) {
    DataQueue<int> dataQueue(5);
    dataQueue.add(5);
    dataQueue.add(10);
    dataQueue.add(7);
    dataQueue.update(15);
    EXPECT_EQ(dataQueue.getLargestValue(), 15);
}

// Test for getLargestValue after updating with a smaller value
TEST(DataQueueTests, GetLargestValueUpdateWithSmallerValue) {
    DataQueue<int> dataQueue(5);
    dataQueue.add(15);
    dataQueue.add(10);
    dataQueue.add(12);
    dataQueue.update(7);
    EXPECT_EQ(dataQueue.getLargestValue(), 15);
}