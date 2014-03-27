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
                class BevertonHolt : public noaa::nmfs::PopulationFunctor< BASE_TYPE, EVAL_TYPE> {
                public:

                    virtual void Initialize(PopulationDM<BASE_TYPE>* population_m) {
                    }

                    virtual const EVAL_TYPE Evaluate(PopulationDM<BASE_TYPE>* population_m) {


                        return EVAL_TYPE(1.0);
                    }


                private:

                    /**
                     * Beverton-holt recruitment function.
                     * 
                     * @param SPB_current
                     * @param Recr_virgin
                     * @param SPB_virgin
                     * @param steepness
                     * @return 
                     */
                    EVAL_TYPE Beverton_Holt(const EVAL_TYPE &SPB_current, const EVAL_TYPE &Recr_virgin, const EVAL_TYPE &SPB_virgin, const EVAL_TYPE &steepness) {

                        EVAL_TYPE SPB_curr_adj;
                        EVAL_TYPE Recr_virgin_adj;
                        EVAL_TYPE SPB_virgin_adj;
                        SPB_curr_adj = SPB_current + BASE_TYPE(0.100); // robust
                        Recr_virgin_adj = Recr_virgin;
                        SPB_virgin_adj = SPB_virgin;
                        return (BASE_TYPE(4.) * steepness * Recr_virgin_adj * 
                                SPB_curr_adj) / (SPB_virgin_adj * (BASE_TYPE(1.000) 
                                - steepness)+(BASE_TYPE(5.) * steepness - 
                                BASE_TYPE(1.000)) * SPB_curr_adj);
                    }

                };

                template<class BASE_TYPE, class EVAL_TYPE = BASE_TYPE>
                class Ricker : public noaa::nmfs::PopulationFunctor< BASE_TYPE, EVAL_TYPE> {
                public:

                    virtual void Initialize(PopulationDM<BASE_TYPE>* population_m) {
                    }

                    virtual const EVAL_TYPE Evaluate(PopulationDM<BASE_TYPE>* population_m) {
                        return EVAL_TYPE(1.0);
                    }


                private:

                    /**
                     * Ricker function taken from Stock Synthesis.
                     * 
                     * @param spb_current
                     * @param recr_virgin
                     * @param spb_virgin
                     * @param steepness
                     * @return 
                     */
                    EVAL_TYPE Ricker(const EVAL_TYPE &spb_current, const EVAL_TYPE &recr_virgin, const EVAL_TYPE &spb_virgin, const EVAL_TYPE &steepness) {

                        EVAL_TYPE Recr_virgin_adj;
                        EVAL_TYPE SPB_virgin_adj;
                        EVAL_TYPE SPB_curr_adj;

                        SPB_curr_adj = spb_current + BASE_TYPE(0.100); // robust
                        Recr_virgin_adj = recr_virgin;
                        SPB_virgin_adj = spb_virgin;
                        //   should use mfexp here
                        return Recr_virgin_adj * SPB_curr_adj / SPB_virgin_adj *
                                std::exp<EVAL_TYPE > (steepness * (BASE_TYPE(1.000) 
                                - SPB_curr_adj / SPB_virgin_adj));

                    }

                };

                template<class BASE_TYPE, class EVAL_TYPE = BASE_TYPE>
                class HockeyStick : public noaa::nmfs::PopulationFunctor< BASE_TYPE, EVAL_TYPE> {
                public:

                    virtual void Initialize(PopulationDM<BASE_TYPE>* population_m) {
                    }

                    virtual const EVAL_TYPE Evaluate(PopulationDM<BASE_TYPE>* population_m) {
                        return EVAL_TYPE(1.0);
                    }

                };

                template<class BASE_TYPE, class EVAL_TYPE = BASE_TYPE>
                class SurvivalBased : public noaa::nmfs::PopulationFunctor< BASE_TYPE, EVAL_TYPE> {
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


#endif	/* POPULATIONFUNCTORS_HPP */

