/* RecruitmentFunctors.hpp
 * Author: matthewsupernaw
 *
 * Created on March 26, 2014, 10:49 AM
 */

#ifndef POPULATIONFUNCTORS_HPP
#define	POPULATIONFUNCTORS_HPP

#include "Common.hpp"
#include "Population.hpp"


namespace noaa {
    namespace nmfs {
        namespace recruitment {

            namespace lengthbased {

            }

            namespace agebased {


                //Functions

                /**
                 * Implementation of the Ricker recruitment model.
                 * @param SPB_current
                 * @return 
                 */
                template<class BASE_TYPE, class EVAL_TYPE >
                static const EVAL_TYPE Ricker(const EVAL_TYPE& SPB_current, const EVAL_TYPE &Recr_virgin, const EVAL_TYPE &SPB_virgin, const EVAL_TYPE &steepness) {

                    EVAL_TYPE Recr_virgin_adj;
                    EVAL_TYPE SPB_virgin_adj;
                    EVAL_TYPE SPB_curr_adj;

                    SPB_curr_adj = SPB_current + BASE_TYPE(0.100); // robust
                    Recr_virgin_adj = Recr_virgin;
                    SPB_virgin_adj = SPB_virgin;
                    return Recr_virgin_adj * SPB_curr_adj / SPB_virgin_adj * std::exp<EVAL_TYPE > (steepness * (BASE_TYPE(1.000) - SPB_curr_adj / SPB_virgin_adj));

                }

                /**
                 *  Implementation of the BevertonHolt recruitment model.
                 * @param SPB_current
                 * @return 
                 */
                template<class BASE_TYPE, class EVAL_TYPE >
                static const EVAL_TYPE BevertonHolt(const EVAL_TYPE& SPB_current, const EVAL_TYPE &Recr_virgin, const EVAL_TYPE &SPB_virgin, const EVAL_TYPE &steepness) {

                    EVAL_TYPE SPB_curr_adj;
                    EVAL_TYPE Recr_virgin_adj;
                    EVAL_TYPE SPB_virgin_adj;
                    SPB_curr_adj = SPB_current + BASE_TYPE(0.100); // robust
                    Recr_virgin_adj = Recr_virgin;
                    SPB_virgin_adj = SPB_virgin;
                    return (BASE_TYPE(4.) * steepness * Recr_virgin_adj * SPB_curr_adj) / (SPB_virgin_adj * (BASE_TYPE(1.000) - steepness)+(BASE_TYPE(5.) * steepness - BASE_TYPE(1.000)) * SPB_curr_adj);
                }

                /**
                 *  Implementation of the None recruitment model.
                 * @param SPB_current
                 * @return 
                 */
                template<class BASE_TYPE, class EVAL_TYPE >
                static const EVAL_TYPE None(const EVAL_TYPE& SPB_current) {

                    return SPB_current + BASE_TYPE(0.100);
                }

                /**
                 * 
                 * @param MinPoss
                 * @param MaxPoss
                 * @param Inflec
                 * @param Xvar
                 * @param Y1
                 * @param Y2
                 * @return 
                 */
                template<class BASE_TYPE, class EVAL_TYPE >
                static const EVAL_TYPE Join_Fxn(const EVAL_TYPE& MinPoss, const EVAL_TYPE& MaxPoss, const EVAL_TYPE& Inflec, const EVAL_TYPE& Xvar, const EVAL_TYPE& Y1, const EVAL_TYPE& Y2) {
                    EVAL_TYPE Yresult;
                    EVAL_TYPE join;
                    join = BASE_TYPE(1.000) / (BASE_TYPE(1.000) + std::exp(BASE_TYPE(1000.0) * (Xvar - Inflec) / (MaxPoss - MinPoss))); //  steep joiner at the inflection
                    Yresult = Y1 * (join) + Y2 * (BASE_TYPE(1.000) - join);
                    return Yresult;
                }

                /**
                 * Implementation of the Hockey Stick recruitment model.
                 * @param SPB_current
                 * @return 
                 */
                template<class BASE_TYPE, class EVAL_TYPE >
                static const EVAL_TYPE HockeyStick(const EVAL_TYPE& SPB_current, const EVAL_TYPE &Recr_virgin, const EVAL_TYPE &SPB_virgin, const EVAL_TYPE &SR_parm, const EVAL_TYPE &steepness) {

                    EVAL_TYPE SPB_curr_adj;
                    EVAL_TYPE Recr_virgin_adj;
                    EVAL_TYPE SPB_virgin_adj;
                    SPB_curr_adj = SPB_current + BASE_TYPE(0.100); // robust
                    Recr_virgin_adj = Recr_virgin;
                    SPB_virgin_adj = SPB_virgin;
                    //        if (SR_parm.indexmax() < 3) {
                    //            cout << "Critical error:  see warning" << endl;
                    //    #warning will eventually add standard logging...
                    //            std::cerr << "SR_param index out of bounds." << endl;
                    //            exit(1);
                    //        }
                    EVAL_TYPE temp = SR_parm * Recr_virgin_adj + SPB_curr_adj / (steepness * SPB_virgin_adj)*(Recr_virgin_adj - SR_parm * Recr_virgin_adj); //  linear decrease below steepness*SPB_virgin_adj
                    return Join_Fxn<EVAL_TYPE > (BASE_TYPE(0.0) * SPB_virgin_adj, SPB_virgin_adj, steepness*SPB_virgin_adj, SPB_curr_adj, temp, Recr_virgin_adj);
                }

                /**
                 * Implementation of the Constrained  Beverton-Holt constrained 
                 * recruitment model.
                 * @param SPB_current
                 * @return 
                 */
                template<class BASE_TYPE, class EVAL_TYPE >
                static const EVAL_TYPE BevertonHoltConstrained(const EVAL_TYPE &SPB_current, const EVAL_TYPE &Recr_virgin, const EVAL_TYPE &SPB_virgin, const EVAL_TYPE &steepness) {


                    EVAL_TYPE SPB_BH1;
                    EVAL_TYPE Recr_virgin_adj;
                    EVAL_TYPE SPB_virgin_adj;
                    //        T steepness;
                    EVAL_TYPE SPB_curr_adj;

                    SPB_curr_adj = SPB_current + BASE_TYPE(0.100); // robust
                    Recr_virgin_adj = Recr_virgin;
                    SPB_virgin_adj = SPB_virgin;

                    if (SPB_curr_adj > SPB_virgin_adj) {
                        SPB_BH1 = SPB_virgin_adj;
                    } else {
                        SPB_BH1 = SPB_curr_adj;
                    }
                    return (BASE_TYPE(4.) * steepness * Recr_virgin_adj * SPB_BH1) / (SPB_virgin_adj * (BASE_TYPE(1.) - steepness)+(BASE_TYPE(5.) * steepness - BASE_TYPE(1.)) * SPB_BH1);
                }

                /**
                 * Implementation of the Survival recruitment model.
                 * @param SPB_current
                 * @return 
                 */
                template<class BASE_TYPE, class EVAL_TYPE >
                static const EVAL_TYPE Survival(const EVAL_TYPE &SPB_current) {
                    std::cerr << __func__ << " Not Yet implemented." << std::endl;
                    EVAL_TYPE ret = BASE_TYPE(0);
                    return ret;
                }

                template<class BASE_TYPE, class EVAL_TYPE = BASE_TYPE>
                class BevertonHoltFunctor : public noaa::nmfs::PopulationFunctor< BASE_TYPE, EVAL_TYPE> {
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

                /**
                 *Base class for a recruitment object.
                 */
                template<class BASE_TYPE, class EVAL_TYPE = BASE_TYPE>
                class RecruitmentBase : public noaa::nmfs::PopulationFunctor< BASE_TYPE, EVAL_TYPE> {
                };

                template<class BASE_TYPE, class EVAL_TYPE = BASE_TYPE>
                class RickerFunctor : public RecruitmentBase< BASE_TYPE, EVAL_TYPE> {
                public:

                    virtual void Initialize(PopulationDM<BASE_TYPE>* population_m) {
                    }

                    virtual const EVAL_TYPE Evaluate(PopulationDM<BASE_TYPE>* population_m) {
                        return EVAL_TYPE(1.0);
                    }






                };

                template<class BASE_TYPE, class EVAL_TYPE = BASE_TYPE>
                class HockeyStickFunctor : public RecruitmentBase< BASE_TYPE, EVAL_TYPE> {
                public:

                    virtual void Initialize(PopulationDM<BASE_TYPE>* population_m) {
                    }

                    virtual const EVAL_TYPE Evaluate(PopulationDM<BASE_TYPE>* population_m) {
                        return EVAL_TYPE(1.0);
                    }

                };

                template<class BASE_TYPE, class EVAL_TYPE = BASE_TYPE>
                class SurvivalBased : public RecruitmentBase< BASE_TYPE, EVAL_TYPE> {
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

