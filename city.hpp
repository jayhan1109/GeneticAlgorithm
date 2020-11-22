//
// Created by Jeongho Han on 11/22/2020.
//

#pragma once

class city {
public:
    char name; // city name
    int x; // longitude
    int y; // latitude

    // Constructor
    city(char name, int x, int y) : name(name), x(x), y(y) {};
};
