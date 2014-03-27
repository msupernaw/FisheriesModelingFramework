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

noaa::nmfs::PopulationDM<double, double>* BuildPopulationModel(const std::string &name) {

    noaa::nmfs::PopulationDM<double, double>* pop =
    new noaa::nmfs::PopulationDM<double, double>();
    pop->SetName(name);
    pop->AddAttribute<int>("number_of_age_groups", 20);
    pop->AddAttribute<std::vector<uint32_t> >("intial_number_at_age", std::vector<uint32_t>(20));
    pop->AddAttribute<double>("R_0", 100000.000);
    pop->CreateFunctor<noaa::nmfs::recruitment::agebased::BevertonHoltFunctor<double> >("beverton_holt");
    pop->CreateFunctor<noaa::nmfs::mortality::agebased::ConstantRateMortality<double> >("mortality");
    pop->CreateFunctor< noaa::nmfs::selectivity::agebased::Logistic<double> >("logistic_selectivity");
    pop->InitializeFunctors();
    std::cout<<pop->ToString()<<"\n";
    
    
    return pop;
}

using namespace noaa::nmfs;

/*
 * 
 */
int main(int argc, char** argv) {

    noaa::nmfs::PopulationDM<double, double>* pop = BuildPopulationModel("test population"); 
    
    noaa::nmfs::PopulationAttribute<std::vector<uint32_t> >* naa = 
            (noaa::nmfs::PopulationAttribute<std::vector<uint32_t> >*)pop->GetAttribute("intial_number_at_age");
    std::cout<<naa->GetAttributeValue()<<"\n";
    delete pop;
    std::vector<int> iv(10, 1);
    
    std::cout<<iv<<"\n";
    
    exit(0);
    
    //create a population data module
    noaa::nmfs::PopulationDM<double> population;

    population.AddAttribute<std::string > ("type", "age_based");

    population.AddAttribute<std::vector<double> >("yield", std::vector<double>(1000));

    noaa::nmfs::PopulationAttribute<std::vector<double> >* attr =
            (noaa::nmfs::PopulationAttribute<std::vector<double> >*) population.GetAttribute("type");

    std::cout << attr->GetName() << "\n";



    //create a functor list
    std::vector<noaa::nmfs::PopulationFunctor<double>* > functors;

    population.CreateFunctor<noaa::nmfs::recruitment::agebased::BevertonHoltFunctor<double> >("beverton_holt");
    population.CreateFunctor<noaa::nmfs::mortality::agebased::ConstantRateMortality<double> >("mortality");
    population.CreateFunctor< noaa::nmfs::selectivity::agebased::Logistic<double> >("logistic_selectivity");
    population.InitializeFunctors();

    ////    //make a recruitment functor and add it to the list
    //    noaa::nmfs::recruitment::agebased::BevertonHoltFunctor<double> beverton_holt;
    //    functors.push_back(&beverton_holt);

    //make a selectivity functor and add it to the list
    //    noaa::nmfs::selectivity::agebased::Logistic<double> logistic_selectivity;
    //    functors.push_back(&logistic_selectivity);
    //
    //    //make a mortality functor and add it to the list
    //    noaa::nmfs::mortality::agebased::ConstantRateMortality<double> constant_rate_mortality;
    //    functors.push_back(&constant_rate_mortality);

    double ret = 0;
    for (int t = 0; t < 400; t++) {
        population.SetCurrentYear(t);
        std::cout << population.GetCurrentYear() << "\n";
        ret += population.SumFunctors();
        //        for (int i = 0; i < functors.size(); i++) {
        //            ret += functors[i]->Evaluate(&population);
        //        }
        //        ret+=population.EvaluateFunctor("beverton_holt");
    }

    std::cout << ret << "\n";

    return 0;
}

