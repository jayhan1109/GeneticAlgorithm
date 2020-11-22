//
// Created by Jeongho Han on 11/22/2020.
//

#pragma once

#include <vector>
#include "city.hpp"

using namespace std;

class tour {
private:
    const int CITIES_IN_TOUR = 15;
public:
    vector<city> cities;
    double fitness_rate;

    // Constructor
    tour();

    // Assignment operator overloading
    tour &operator=(tour);

    // For assignment operator overloading
    void mySwap(tour &left, tour &right);

    // Shuffle cities
    void shuffle_cities();

    // Get distance between two cities
    double get_distance_between_cities(city, city);

    // Get tour's distance
    double get_tour_distance();

    // Print all cities
    void print_cities();

    // Swap two cities
    void swap_cities(int, int);

    // Check if this tour contains the city
    bool contains_city(city &);

};



