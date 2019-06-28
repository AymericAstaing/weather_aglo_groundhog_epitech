#include <numeric>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "Calculations.hpp"

float Calculations::get_standard_deviation(std::vector<float> list, int population) {
    int start = list.size() - 1;
    int end = start - population;
    float total = 0;
    if (end > start)
        return (0);
    float average = std::accumulate(list.end() - population, list.end(), 0.0) / population;
    while (start != end) {
            total += pow((list[start] - average), 2);
            start--;
    }
    total /= population;
    total = sqrt(total);
    return (total);
}

std::string Calculations::get_deviation(GroundHog* hog) {
    if (hog->get_index() + 1 > hog->get_period()) {
        float total = Calculations::get_standard_deviation(hog->get_temp_array(), hog->get_period());
        std::ostringstream os;
        os << std::fixed << std::setprecision(2) << roundf(total * 100) / 100;
        return (os.str());
    }
    return (NO_INFORMATION);
}

bool Calculations::contains_char(std::string s, int flag) {
    for (unsigned int i = 0; i < s.length(); i++) {
        int e = s[i];
        if ((e < 48 || e > 57)) {
            if (flag == WITH_POINT && (e == 46 || e == 44 || e == 45))
                return (false);
            else
                return (true);
        }
    }
    return (false);
}

std::string Calculations::get_temperature_evolution(GroundHog *hog) {
    if (hog->get_index() > hog->get_period()) {
        std::vector<float> tmp = hog->get_temp_array();
        float current = tmp[tmp.size() - 1];
        float one_week_ago = tmp[(tmp.size() - 1) - hog->get_period()];
        float percent = (current - one_week_ago) / one_week_ago;
        percent = roundf(percent * 100) / 100;
        percent *= 100;
        hog->set_last_percent(percent);
        std::ostringstream os;
        os << percent;
        return (os.str());
    }
    return (NO_INFORMATION);
}

std::string Calculations::get_increase_average(GroundHog* hog) {
    if (hog->get_index() > hog->get_period()) {
        float total_increase = 0;
        std::vector<float> temp_array = hog->get_temp_array();
        for (unsigned int i = temp_array.size() - 1; i > (temp_array.size() - 1) - hog->get_period(); i--) { 
            total_increase += temp_array[i] - temp_array[i - 1];
        }
        total_increase = total_increase / hog->get_period();
        std::ostringstream os;
        os << std::fixed << std::setprecision(2) << roundf(total_increase * 100) / 100;
        return (os.str());
    }
    return (NO_INFORMATION);
}
