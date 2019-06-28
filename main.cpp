/*
** EPITECH PROJECT, 2018
** GroundHog Project
** File description:
** Makefile of GroundHog
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <sstream>
#include "src/Ground.hpp"
#include "src/Calculations.hpp"
#include "src/GroundHog.hpp"

bool end_detection(std::string input) {
    if (input.compare(USER_STOPED) == 0)
        return (true);
    return (false);
}

bool is_help_requiered(char *arg) {
    if (strcmp(arg, HELP_FLAG) != 0)
        return (false);
    std::ifstream f(HELP_FILE);
    if (f.is_open())
        std::cout << f.rdbuf() << std::endl;
    return (true);
}

int argument_is_valid(char *period) {
    if (Calculations::contains_char(period, WITHOUT_POINT))
        return(-1);
    int p = atoi(period);
    if (p < 1)
        return (-1);
    return (p);
}

bool error_line(std::string s) {
    if (Calculations::contains_char(s, WITH_POINT))
        return (true);
    try {
    float c = std::stof(s);
    (void)c;
    } catch (...) {
        return (true);
    }
    return (false);
}

void determine_current_trend(GroundHog *hog) {
    int current_index = hog->get_index();
    std::vector<float> tmp = hog->get_temp_array();
    float res = 0;
    for (int i = hog->get_index() - 1; i > (current_index - 4); i--)
        res += tmp[i] - tmp[i - 1];
    if (res < 0)
        hog->set_sign(NEXT_SWITCH_INCREASE);
    else
        hog->set_sign(NEXT_SWITCH_DECREASE);
}

void detect_switch(GroundHog *hog) {
    int current_index = hog->get_temp_array().size() - 1;
    std::vector<float> tmp = hog->get_temp_array();
    float current_value = tmp[current_index];
    int ko = 0;
    int ok = 0;

    if (hog->get_sign() == NEXT_SWITCH_DECREASE) {
        for (int i = current_index; i > (current_index - 5); i--) {
            if (tmp[i] > current_value)
                ok++;
            else
                ko++; 
        }
    } else {
         for (int i = current_index; i > (current_index - 5); i--) {
            if (tmp[i] < current_value)
                ok++;
            else
                ko++; 
        }
    }
    if (ok > 3) {
        std::cout << SWITCH_DISPLAY;
        hog->increase_switch_nbr();
        if (hog->get_sign() == NEXT_SWITCH_DECREASE)
            hog->set_sign(NEXT_SWITCH_INCREASE);
        else
            hog->set_sign(NEXT_SWITCH_DECREASE);
          
    } 
}

void print_weirdest_values(GroundHog* hog) {
        if (hog->get_temp_array().size() <= (unsigned) hog->get_period()) {
            std::cout << "No weirdest values." << std::endl;
            return;
        }
        std::vector<float> weird_values = hog->find_weirdest_values();
        std::cout << weird_values.size() << " weirdest values are [";
        printf("%.1f", weird_values[0]);
        for (unsigned int i = 1; i < weird_values.size(); i++)
            printf(", %.1f", weird_values[i]);
        std::cout << "]" << std::endl;
}
 
int start_input_broadcast(GroundHog* hog) {
    int loop_nbr = 0;

    for (std::string line; std::getline(std::cin, line); loop_nbr++, std::cout << "\n") {
        if (!line.empty() && end_detection(line)) {
            std::cout << "Global tendency switched " << hog->get_switch_nbr() << " times" << std::endl;
            print_weirdest_values(hog);
            return (EXIT_SUCCESS);
        }
        if (error_line(line)) {
            delete(hog);
            return(EXIT_FAIL);
        }
        hog->store_temp(line);
        hog->store_deviation_gap();
        if (loop_nbr == 4)
            determine_current_trend(hog);
        std::cout << "g=" << Calculations::get_increase_average(hog) << "    r=" << Calculations::get_temperature_evolution(hog) << 
        (char)37 << "    s=" << Calculations::get_deviation(hog);
         if (loop_nbr > 4)
            detect_switch(hog);
    }
    return (EXIT_FAIL);
}

int main(int argc, char **argv) {
    if (argc != 2)
        return (EXIT_FAIL);
    if (is_help_requiered(argv[1]))
        return (EXIT_SUCCESS);
    int period = argument_is_valid(argv[1]);
    if (period == -1)
        return (EXIT_FAIL);
    GroundHog* hog = new GroundHog(period);
    if (start_input_broadcast(hog) == EXIT_SUCCESS) {
        delete(hog);
        return (EXIT_SUCCESS);
    }  
    delete(hog);
    return (EXIT_FAIL);
}