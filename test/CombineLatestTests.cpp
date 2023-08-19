//
// Created by Jeremy Cote on 2023-08-18.
//

#include "CombineLatest.hpp"
#include <gtest/gtest.h>

// Test callback invocation when different observed objects are set
TEST(CombineLatestTest, CallbackInvokedWithValue) {
    int sum = 0;

    ObservedObject<int> obj1(1);
    ObservedObject<int> obj2(2);

    auto callback = [&](const int& value1, const int& value2) {
        sum = value1 + value2;
    };

    CombineLatest<int, int> combiner(callback, obj1, obj2);

    obj1.set(5);
    EXPECT_EQ(sum, 7);

    obj2.set(10);
    EXPECT_EQ(sum, 15);
}