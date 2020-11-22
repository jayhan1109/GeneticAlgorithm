//
// Created by Jeongho Han on 11/22/2020.
//

#include <random>
#include <algorithm>
#include <iostream>
#include "tour.hpp"

using namespace std;

tour::tour() : fitness_rate(0.0) {
    city temp{'a', 0, 0};
    for (int i = 0; i < CITIES_IN_TOUR; ++i) {
        cities.push_back(temp);
    }
}

tour &tour::operator=(tour t) {
    mySwap(*this, t);
    return *this;
}

void tour::mySwap(tour& left, tour& right) {
    swap(left.cities, right.cities);
}

void tour::shuffle_cities() {
    shuffle(begin(cities), end(cities), std::mt19937(std::random_device()()));
}

double tour::get_distance_between_cities(city c1, city c2) {
    return sqrt(pow((double) (c1.x - c2.y), 2.0) + pow((double) (c1.y - c2.y), 2.0));
}

double tour::get_tour_distance() {
    double distance = 0.0;
    for (int i = 0; i < CITIES_IN_TOUR; ++i)
        distance += get_distance_between_cities(cities[i], cities[(i + 1) % CITIES_IN_TOUR]);
    return distance;
}

void tour::print_cities() {
    for (auto city : cities) {
        std::cout << city.name << " ";
    }
}

void tour::swap_cities(int left, int right) {
    city temp = cities[left];
    cities[left] = cities[right];
    cities[right] = temp;
}

bool tour::contains_city(city &city) {
    for (auto c : cities) {
        if (c.name == city.name && c.x == city.x && c.y == city.y)
            return true;
    }
    return false;
}
