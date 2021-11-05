#include <iostream>

#include "functions.hpp"

using namespace std;

double Normal_distribution() {
    // Inspired from https://en.cppreference.com/w/cpp/numeric/random/normal_distribution
    random_device rd{};
    mt19937 gen{rd()};
 
    normal_distribution<float> d{0, 1};
 
    map<int, int> hist{};
    return round(d(gen));
}

// Calculate Euclidean Distance
long double euclidean_dis(vector<int> vec1, vector<int> vec2) {
    long double dist=0.0;

    auto itA = vec1.begin();
    auto itB = vec2.begin();
    ++itA;
    ++itB;

    while(itA != vec1.end() || itB != vec2.end())
    {
        dist = dist + (itA[0]-itB[0])*(itA[0]-itB[0]);
        if(itA != vec1.end()) {
            ++itA;
        }
        if(itB != vec2.end()) {
            ++itB;
        }
    }

	return sqrt(dist);
}

vector <double> Nearest_N_brute(vector<vector<int>> data, vector<int> query, int N) {
    long double d = (double) BIG; // Minimum distance

    vector <double> near_items;

    for (auto Item: data) {
        long double euc_dist = euclidean_dis(Item, query);

        if (euc_dist < d) {
            if (near_items.size() >= N) {
                near_items.pop_back();
            }
            near_items.push_back(euc_dist);
            sort(near_items.begin(), near_items.end());
            d = near_items.back();
        }
    }

    return near_items;
}