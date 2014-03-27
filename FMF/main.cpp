/* 
 * File:   main.cpp
 * Author: matthewsupernaw
 *
 * Created on March 26, 2014, 2:35 PM
 */

#include <cstdlib>
#include "Population.hpp"
#include "Recruitment.hpp"
#include "Selectivity.hpp"
#include "Mortality.hpp"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {


    //create a population data module
    noaa::nmfs::AgeBasedPopulation<double> population;

    //create a functor list
    std::vector<noaa::nmfs::PopulationFunctor<double>* > functors;

    //make a recruitment functor and add it to the list
    noaa::nmfs::recruitment::agebased::BevertonHolt<double> beverton_holt;
    functors.push_back(&beverton_holt);

    //make a selectivity functor and add it to the list
    noaa::nmfs::selectivity::agebased::Logistic<double> logistic_selectivity;
    functors.push_back(&logistic_selectivity);

    //make a mortality functor and add it to the list
    noaa::nmfs::mortality::agebased::ConstantRateMortality<double> constant_rate_mortality;
    functors.push_back(&constant_rate_mortality);

    double ret = 0;
    for (int t = 0; t < 40; t++) {
        population.SetCurrentYear(t);
        for (int i = 0; i < functors.size(); i++) {
            ret += functors[i]->Evaluate(&population);
        }
    }
    
    std::cout<<ret<<"\n";

    return 0;
}

