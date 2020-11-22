//
// Created by Jeongho Han on 11/22/2020.
//

#include "UI_genetic_algorithm.hpp"
#include "master_list.hpp"


UI_genetic_algorithm::UI_genetic_algorithm() {

    vector<tour> crossover_tour{POPULATION_SIZE - NUMBER_OF_ELITES};

    // Generate master list
    master_list::get_instance().setup_master_lists(CITIES_IN_TOUR, LOWER_LIMIT, UPPER_LIMIT);

    for (int i = 0; i < POPULATION_SIZE; ++i) {
        for (int j = 0; j < CITIES_IN_TOUR; ++j)
            pop.population[i].cities[j] = master_list::get_instance().getCities()[j];
        pop.population[i].shuffle_cities();
        pop.population[i].fitness_rate = 0.0;
    }

    // Find first best fittest tour
    int bestIdx = fittest_tour(pop.population);
    base_dis = STANDARD / pop.population[bestIdx].fitness_rate;

    // Store base route
    baseRoute = pop.population[bestIdx];

    // Variable to save the number of iterations
    int iter = 0;
    while (iter++ < TOTAL_ITERATION && base_dis / shortest_dist > IMPROVEMENT) {
        if (bestIdx != 0) {
            const tour temp_tour = pop.population[0];
            pop.population[0] = pop.population[bestIdx];
            pop.population[bestIdx] = temp_tour;
        }

        for (int i = 0; i < (POPULATION_SIZE - NUMBER_OF_ELITES); ++i) {
            parent = select_parents(pop.population);
            crossover_tour[i] = crossover(parent);
        }

        for (int i = NUMBER_OF_ELITES; i < POPULATION_SIZE; ++i) {
            pop.population[i] = crossover_tour[i - NUMBER_OF_ELITES];
            pop.population[i].fitness_rate = 0.0;
        }

        mutate(pop.population);

        bestIdx = fittest_tour(pop.population);
        shortest_dist = pop.population[bestIdx].get_tour_distance();

        if (shortest_dist < base_dis) {
            base_dis = shortest_dist;
        }

        cout << "# of iterations: " << iter << endl;
        cout << "Best Distance: " << base_dis << endl;
        cout << "Improvement from Base: " << baseRoute.get_tour_distance() - shortest_dist << endl;
        cout << "=============================================================" << endl;

    }

    // Final Report
    final_report(bestIdx, iter);
}

void UI_genetic_algorithm::final_report(int bestIdx, int iteration) {
    cout << "=============================================================" << endl;
    cout << "========================== REPORT ===========================" << endl;
    cout << "Number of iterations: " << iteration << endl;
    cout << "Base Distance: " << baseRoute.get_tour_distance() << endl;
    cout << "Best Distance: " << shortest_dist << endl;
    cout << "Improvement: " << ((baseRoute.get_tour_distance() > shortest_dist) ? "True" : "False") << endl;
    cout << "Base Route: ";
    print_tour(baseRoute);
    cout << endl;
    cout << "Best Route: ";
    print_tour(pop.population[bestIdx]);
    cout << endl;
}


void UI_genetic_algorithm::mutate(vector<tour> &population) {
    for (int i = 0 + NUMBER_OF_ELITES; i < POPULATION_SIZE; ++i) {
        for (int j = 0; j < CITIES_IN_TOUR; ++j) {
            if ((double) rand() / (double) RAND_MAX <= MUTATION_RATE) {
                population[i].swap_cities(j, rand() % CITIES_IN_TOUR);
            }
        }
    }
}


int UI_genetic_algorithm::fittest_tour(vector<tour> &population) {
    int fittest_idx = 0;
    auto fittest_tour_in_population = (double) RAND_MAX;
    double current_dist = 0.0;

    for (int i = 0; i < population.size(); ++i) {
        current_dist = population[i].get_tour_distance();
        population[i].fitness_rate = STANDARD / current_dist;

        if (current_dist <= fittest_tour_in_population) {
            fittest_idx = i;
            fittest_tour_in_population = current_dist;
        }
    }
    return fittest_idx;
}

vector<tour> UI_genetic_algorithm::select_parents(vector<tour> &population) {
    vector<tour> parents_tour{NUMBER_OF_PARENTS};
    vector<tour> parent_tour_pool{PARENT_POOL_SIZE};

    for (int i = 0; i < NUMBER_OF_PARENTS; ++i) {
        for (int j = 0; j < PARENT_POOL_SIZE; ++j) {
            parent_tour_pool[j] = population[static_cast<int>(rand() % POPULATION_SIZE)];
        }

        parents_tour[i] = parent_tour_pool[fittest_tour(parent_tour_pool)];
    }
    return parents_tour;
}

tour UI_genetic_algorithm::crossover(vector<tour> &parents) {
    tour child;

    int randomIdx = rand() % CITIES_IN_TOUR;

    for (int i = 0; i < randomIdx; ++i) {
        child.cities[i] = parents[0].cities[i];
    }

    while (randomIdx < CITIES_IN_TOUR) {
        for (int i = 0; i < CITIES_IN_TOUR; ++i) {
            if (!child.contains_city(parents[1].cities[i])) {
                child.cities[randomIdx] = parents[1].cities[i];
                randomIdx++;
            }
        }
    }
    return child;
}

void UI_genetic_algorithm::print_tour(tour t) {
    t.print_cities();
}