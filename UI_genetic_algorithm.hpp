//
// Created by Jeongho Han on 11/22/2020.
//

#pragma once

#include <random>
#include <iostream>
#include <iomanip>

#include <algorithm>
#include "city.hpp"
#include "tour.hpp"
#include "population.hpp"

using namespace std;

class UI_genetic_algorithm {
private:

    int CITIES_IN_TOUR = 15;

    unsigned long POPULATION_SIZE = 32;

    int LOWER_LIMIT = 0;

    int UPPER_LIMIT = 1000;

    int TOTAL_ITERATION = 1000;

    unsigned long PARENT_POOL_SIZE = 5;

    double MUTATION_RATE = 0.15;

    unsigned long NUMBER_OF_PARENTS = 2;

    int NUMBER_OF_ELITES = 1;

    double STANDARD = 10000.0;

    double IMPROVEMENT = 0.1;

public:
    double shortest_dist = 0.0; // best distance
    double base_dis = 0.0; // base distance

    population pop; // population
    tour baseRoute; // tour of base route
    vector<tour> parent; // parent

    // Constructor
    UI_genetic_algorithm();

    // Print cities in the tour
    void print_tour(tour t);

    // Find the fittest tour
    int fittest_tour(vector<tour> &population);

    // Select parent
    vector<tour> select_parents(vector<tour> &population);

    // Cross over from parents
    tour crossover(vector<tour> &parents);

    // Mutate with population
    void mutate(vector<tour> &population);

    // Final Report
    void final_report(int bestIdx, int iteration);
};

