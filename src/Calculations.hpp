#ifndef CALCULATIONS_H_
#define CALCULATIONS_H_

#include <vector>
#include "GroundHog.hpp"

class Calculations {
    public:
        static float        get_standard_deviation(std::vector<float>, int);
        static std::string  get_increase_average(GroundHog*);
        static std::string  get_temperature_evolution(GroundHog*);
        static std::string  get_deviation(GroundHog*);
        static bool         contains_char(std::string, int);
};

#endif