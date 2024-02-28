// By: Gonçalo Leão

#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

bool valueSort(const pair<unsigned int, unsigned int> &a, const pair<unsigned int, unsigned int> &b) {
    return a.first/a.second > b.first/b.second;
}

double fractionalKnapsack(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, double usedItems[]) {
    double weight = 0.0;
    double value = 0.0;
    vector<pair<unsigned int,unsigned int>> items;

    for (int i = 0; i < n; i++) {
        items.push_back(make_pair(values[i],weights[i]));
    }
    sort(items.begin(), items.end(), valueSort);
    int selected = 0;
    int order = 0;
    while (weight < maxWeight) {
        unsigned int weightItem = items[selected].second;
        if (weightItem + weight <= maxWeight) {
            usedItems[order] = 1.0;
            weight += weightItem;
            value += items[selected].first;
            order++;
            selected++;
        }
        else {
            usedItems[order] = (maxWeight - weight)/weightItem;
            value += items[selected].first * usedItems[order];
            weight = maxWeight;
            order++;
            selected++;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << usedItems[i] << endl;
    }
    return value;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex4, testFractionalKnapsack_3items) {
    const unsigned int n = 3;
    {
        unsigned int values[n] = {60, 100, 120};
        unsigned int weights[n] = {10, 20, 30};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsack(values, weights, n, 50, usedItems), 240.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 2.0/3.0, 0.00001);
    }
}

TEST(TP2_Ex4, testFractionalKnapsack_7items) {
    const unsigned int n = 7;
    {
        unsigned int values[n] = {10, 5, 15, 7, 6, 18, 3};
        unsigned int weights[n] = {2, 3, 5, 7, 1, 4, 1};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsack(values, weights, n, 15, usedItems), 52.0 + 10.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 2.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[3], 0.0, 0.00001);
        EXPECT_NEAR(usedItems[4], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[5], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[6], 1.0, 0.00001);
    }
}