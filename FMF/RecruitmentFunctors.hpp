/* RecruitmentFunctors.hpp
 * Author: matthewsupernaw
 *
 * Created on March 26, 2014, 10:49 AM
 */

#ifndef POPULATIONFUNCTORS_HPP
#define	POPULATIONFUNCTORS_HPP


#include "Population.hpp"


namespace noaa {
    namespace nmfs {
        namespace recruitment {
            
            namespace lengthbased {
                
            }
            
            namespace agebased {

                template<class BASE_TYPE, class EVAL_TYPE = BASE_TYPE>
                class BevertonHolt : public noaa::nmfs::PopulationFunctor< BASE_TYPE,EVAL_TYPE> {
                public:

                    virtual void Initialize(PopulationDM<BASE_TYPE>* population_m) {
                    }

                    virtual const EVAL_TYPE Evaluate(PopulationDM<BASE_TYPE>* population_m) {
                    }

                };

                template<class BASE_TYPE, class EVAL_TYPE = BASE_TYPE>
                class Ricker : public noaa::nmfs::PopulationFunctor< BASE_TYPE,EVAL_TYPE> {
                public:

                    virtual void Initialize(PopulationDM<BASE_TYPE>* population_m) {
                    }

                    virtual const EVAL_TYPE Evaluate(PopulationDM<BASE_TYPE>* population_m) {
                    }

                };

                template<class BASE_TYPE, class EVAL_TYPE = BASE_TYPE>
                class HockeyStick : public noaa::nmfs::PopulationFunctor< BASE_TYPE,EVAL_TYPE> {
                public:

                    virtual void Initialize(PopulationDM<BASE_TYPE>* population_m) {
                    }

                    virtual const EVAL_TYPE Evaluate(PopulationDM<BASE_TYPE>* population_m) {
                    }

                };

                template<class BASE_TYPE, class EVAL_TYPE = BASE_TYPE>
                class SurvivalBased : public noaa::nmfs::PopulationFunctor< BASE_TYPE,EVAL_TYPE> {
                public:

                    virtual void Initialize(PopulationDM<BASE_TYPE>* population_m) {
                    }

                    virtual const EVAL_TYPE Evaluate(PopulationDM<BASE_TYPE>* population_m) {
                    }

                };


            }


        }
        
        
    }
}


#endif	/* POPULATIONFUNCTORS_HPP */

