# trading_groundhog_epitech (TECH 2 2018-2019)

The goal of this project is to extract some relevant information from the data received in real-time on standard input (each
float representing a temperature), in order to detect weather aberrations (droughts, severe colds, hurricanes
or any other extreme climatic condition whatsoever) as soon as possible.

Later, we may want to predict things on another timescale.
To do so, the program must, given a number of days (called period) as argument:
  1. wait for the next value to be written on the standard input,
  2. output, once enough data has been gathered, some technical indicators:
    a. the temperature increase average, g, observed on the last period,
    b. the relative temperature evolution, r, between the last given temperature and the temperature observed n-days ago,
    c. the standard deviation, s, of the temperatures observed during the last period,
    d. when appropriate, an alert as soon as it detects a switch in global tendency,
3. return to the first step, until the STOP keyword is read.

It is impossible to detect a switch at the precise moment it happens - otherwise the
algorithm would be way too sensitive to noise. However, the program need to detect it quite
soon, not at the very end of the algorithm.
Eventually, once the keyword is entered, it must output:
  1. the total number of tendency switches observed on the whole time-series,
  2. the list of the five biggest aberrations observed on the whole time-series (sorted by decreasing weirdness).

to launch:

    make / make re

SYNOPSIS
 
    ./groundhog period

DESCRIPTION
  
    period the number of days defining a period
   
Aymeric Astaing - EPITECH PARIS PROMO 2022
