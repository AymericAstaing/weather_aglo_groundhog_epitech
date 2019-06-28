#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>
#include <numeric>
#include <algorithm>
#include "Calculations.hpp"
#include "GroundHog.hpp"


GroundHog::GroundHog(int period) : period(period) {
    
}

GroundHog::~GroundHog() {

}

std::vector<float> GroundHog::get_temp_array() const {
    return (this->temp_array);
}

std::vector<float> GroundHog::get_deviation_array() const {
    return (this->deviation_array);
}

int GroundHog::get_period() const {
    return (this->period);
}

int GroundHog::get_index() const {
    return (this->index);
}

int GroundHog::get_sign() const {
    return (sign);
}
void GroundHog::set_sign(int sign) {
    this->sign = sign;
}

void GroundHog::set_last_percent(float last) {
    this->last_percent = last;
}

float GroundHog::get_last_percent() const {
    return (this->last_percent);
}

int GroundHog::get_switch_nbr() {
    return (this->switch_nbr);
}

void GroundHog::increase_switch_nbr() {
    this->switch_nbr++;
}

std::vector<float> GroundHog::find_weirdest_values() const {
    int limit = 0;
    std::vector<float> deviation_array_sorted = get_deviation_array();
    std::vector<float> deviation_array = get_deviation_array();
    std::vector<float> result;

    if (deviation_array.size() >= 5)
        limit = 5;
    else
        limit = deviation_array.size();
    std::sort(deviation_array_sorted.begin(), deviation_array_sorted.end(), std::greater<float>());
    for (int i = 0; i < limit; i++) {
        auto it = std::find(deviation_array.begin(), deviation_array.end(), deviation_array_sorted[i]);
        int index  = std::distance(deviation_array.begin(), it);
        result.push_back(temp_array[index + period]);
    }
    return (result);
}

void GroundHog::store_deviation_gap() {
    if (index < period + 1)
        return;
    float current_value = temp_array[index - 1];
    float average = std::accumulate(temp_array.end() - period, temp_array.end(), 0.0) / period;
    float standard_deviation = Calculations::get_standard_deviation(temp_array, period);
    float result = floor((fabs(current_value - average) / standard_deviation) * 100) / 100;
    add_array_value(deviation_array, result);
}

void GroundHog::store_temp(std::string temp) {
    float value = std::stof(temp.c_str());
    index++;
    add_array_value(temp_array, value);
}

void GroundHog::add_array_value(std::vector<float>&array, float value) {
    array.push_back(value);
}