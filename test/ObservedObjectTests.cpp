//
// Created by Jeremy Cote on 2023-08-18.
//

#include "ObservedObject.hpp"
#include <gtest/gtest.h>

// Test setting and getting values
TEST(ObservedObjectTests, SetValueAndGetValue) {
    ObservedObject<int> observedObject(5);

    EXPECT_EQ(observedObject.get(), 5);

    observedObject.set(10);
    EXPECT_EQ(observedObject.get(), 10);
}

// Test getMutable function
TEST(ObservedObjectTests, GetMutable) {
    ObservedObject<int> observedObject(5);

    // Get a mutable reference to the value
    int& mutableValue = observedObject.getMutable();

    EXPECT_EQ(mutableValue, 5);

    // Modify the mutable value and publish changes
    mutableValue = 10;

    // The value of the observed object should also change
    EXPECT_EQ(observedObject.get(), 10);
}

// Test adding listeners and notifying them
TEST(ObservedObjectTests, AddListenerAndNotify) {
    ObservedObject<int> observedObject(0);

    int sum = 0;

    // Add a listener that sums up the value
    ObserverToken token = observedObject.addListener([&sum](const int& value) {
        sum += value;
    });

    observedObject.set(5);
    observedObject.set(10);
    observedObject.set(15);

    // After 3 notifications, the sum should be 5 + 10 + 15 = 30
    EXPECT_EQ(sum, 30);

    // Cancel the listener and update the value
    token.cancel();
    observedObject.set(20);

    // The sum should remain 30 since the listener is canceled
    EXPECT_EQ(sum, 30);
}

// Test publishing changes to all listeners
TEST(ObservedObjectTests, PublishChanges) {
    ObservedObject<int> observedObject(0);

    int count = 0;

    // Add a listener that increments the count
    observedObject.addListener([&count](const int& value) {
        count++;
    });

    observedObject.set(5);
    observedObject.publish(); // Publish changes

    // The count should be incremented twice (once from set and once from publish)
    EXPECT_EQ(count, 2);
}

// Test ObserverToken's conformity to Identifiable
TEST(ObservedObjectTests, ObserverTokenConformsToIdentifiable) {
    ObserverToken token1([]() {});
    ObserverToken token2([]() {});

    EXPECT_NE(token1.getId(), token2.getId()); // Ensure that the IDs are unique
}
