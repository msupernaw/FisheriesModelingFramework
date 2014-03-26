/* 
 * File:   SelectivityFunctors.hpp
 * Author: matthewsupernaw
 *
 * Created on March 26, 2014, 10:57 AM
 */

#ifndef SELECTIVITYFUNCTORS_HPP
#define	SELECTIVITYFUNCTORS_HPP

#include "atl/Distributions.hpp"

namespace noaa {
    namespace nmfs {

        namespace selectivity {

            namespace lengthbased {

            }

            namespace agebased {

                
                template<class BASE_TYPE, class EVAL_TYPE = BASE_TYPE>
                class Logistic : public noaa::nmfs::PopulationFunctor< BASE_TYPE,EVAL_TYPE> {
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
#endif	/* SELECTIVITYFUNCTORS_HPP */

