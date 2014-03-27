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
#include "Common.hpp"
using namespace std;

#define dvariable double

void BuildPopulationModel2() {



    //1. define  a population with base double and evaluation type dvariable
    noaa::nmfs::PopulationDM<double, dvariable> pop;

    /**
     * Data Section
     */

    //2. add an attribute telling functors that this is age based
    pop.AddAttribute<std::string > ("model_type", "age_based");

    //3. add an attribute for the number of age groups
    pop.AddAttribute<int>("number_of_age_groups", 20);

    //4. add an attribte for the initial numbers a age
    pop.AddAttribute<std::vector<uint32_t> >("initial_number_at_age", std::vector<uint32_t > (20));

    //5. add an attribute telling us how many years to simulate
    pop.AddAttribute<int>("years", 200);

    //5. add an attribute telling us how many seasons to simulate
    pop.AddAttribute<int>("seasons", 4);

    /**
     * Evaluation 
     */
    //add a beverton-hold functor
    pop.CreateFunctor<noaa::nmfs::recruitment::agebased::BevertonHoltFunctor<double,dvariable> >("beverton_holt");

    //add a mortality functor
    pop.CreateFunctor<noaa::nmfs::mortality::agebased::ConstantRateMortality<double,dvariable> >("mortality");

    //add a selectivity functor
    pop.CreateFunctor< noaa::nmfs::selectivity::agebased::Logistic<double,dvariable> >("logistic_selectivity");

    /**
     * Initialize 
     */
    //initialize registered functors
    pop.InitializeFunctors();

    int years = pop.GetAttributeValue<int>("years");
    int seasons = pop.GetAttributeValue<int>("seasons");
    
    dvariable ret = 0.0;
    for (int y = 0; y < years; y++) {
//        std::cout<<"year "<<y<<"\n";
        pop.SetCurrentYear(y);
        for (int s = 0; s < seasons; s++) {
//               std::cout<<" season "<<s<<"\n";
            pop.SetCurrentSeason(s);
            ret+=pop.SumFunctors();
        }
    }

    std::cout<<ret<<"\n";
}

using namespace noaa::nmfs;

/*
 * 
 */
int main(int argc, char** argv) {
BuildPopulationModel2();
exit(0);
    
    return 0;
}

