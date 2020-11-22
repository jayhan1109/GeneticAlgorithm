//
// Created by Jeongho Han on 11/22/2020.
//

#pragma once

#include <vector>
#include <random>
#include "city.hpp"

class master_list {
private:
    // Master city lists
    std::vector<city> cities;

    master_list() = default;

public:
    // Singleton design
    static master_list &get_instance() {
        static master_list instance;
        return instance;
    }

    master_list(const master_list &) = delete;

    void operator=(master_list) = delete;

    // Set-up master city lists
    void setup_master_lists(int num_of_cities, int lower, int upper);

    // Get cities
    const std::vector<city> &getCities() const;
};
