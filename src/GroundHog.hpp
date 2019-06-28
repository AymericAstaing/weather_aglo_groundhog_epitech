#ifndef GROUNDHOG_H_
#define GROUNDHOG_H_

#include <vector>
#include "Ground.hpp"

class GroundHog {
    public:
                            GroundHog(int);
                            ~GroundHog();
        void                add_array_value(std::vector<float>&, float);
        int                 get_period() const;
        int                 get_index() const;
        void                set_sign(int);
        int                 get_sign()const;
        void                store_deviation_gap();
        void                set_last_percent(float);
        float               get_last_percent() const;
        void                increase_switch_nbr();
        int                 get_switch_nbr();
        std::vector<float>  get_temp_array() const;
        std::vector<float>  get_deviation_array() const;
        std::vector<float>  find_weirdest_values() const;
        void                store_temp(std::string);
        void                store_deviation(float);
    private:
        std::vector<float>  temp_array;
        std::vector<float>  deviation_array;
        int                 day_index = 0;
        int                 sign = -1;
        int                 period;
        int                 index = 0;
        float               last_percent = 0;
        bool                is_switching = false;
        int                 switch_nbr = 0;
};

#endif