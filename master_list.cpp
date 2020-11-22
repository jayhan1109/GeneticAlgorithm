//
// Created by Jeongho Han on 11/22/2020.
//

#include "master_list.hpp"

void master_list::setup_master_lists(int num_of_cities, int lower, int upper) {

    std::random_device rd;
    std::mt19937 mt(rd());

    for (int i = 0; i < num_of_cities; i++) {
        std::uniform_int_distribution<> dist(lower, upper);
        cities.push_back(city{(char)(i +65), dist(mt), dist(mt)});
    }
}

const std::vector<city> &master_list::getCities() const {
    return cities;
}
