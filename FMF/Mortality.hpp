/* 
 * File:   Mortality.hpp
 * Author: matthewsupernaw
 *
 * Created on March 26, 2014, 3:54 PM
 */

#ifndef NOAA_NMFS_MORTALITY_HPP
#define	NOAA_NMFS_MORTALITY_HPP


namespace noaa {
    namespace nmfs {

        namespace mortality {

            namespace lengthbased {

            }

            namespace agebased {

                template<class BASE_TYPE, class EVAL_TYPE = BASE_TYPE>
                class ConstantRateMortality : public noaa::nmfs::PopulationFunctor< BASE_TYPE, EVAL_TYPE> {
                public:

                    virtual void Initialize(PopulationDM<BASE_TYPE>* population_m) {
                    }

                    virtual const EVAL_TYPE Evaluate(PopulationDM<BASE_TYPE>* population_m) {
                        return EVAL_TYPE(1.0);
                    }

                };
            }
        }


    }
}


#endif	/* MORTALITYFUNCTORS_HPP */

