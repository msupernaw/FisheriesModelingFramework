/* 
 * File:   SSPopulation.hpp
 * Author: matthewsupernaw
 *
 * Created on March 26, 2014, 7:24 AM
 */

#ifndef SSPOPULATION_HPP
#define	SSPOPULATION_HPP

#include "Config.hpp"
#include "util/geometry/Polygon.hpp"
#include "Object.hpp"
namespace noaa {
    namespace nmfs {

        template<class T>
        class PopulationArea {
            Polygon<T> area;
            T extended_area;

        };


        template< class T, class EVAL_TYPE>
        class PopulationDM;

        template< class T, class EVAL_TYPE>
        class AgeBasedPopulation;

        
        /**
         * Population Functors take a PopulationDM as input and 
         * make evaluations based on the data stored in the 
         * PopulationDM. Example functors include mortality, 
         * recruitment, etc.
         */
        template< class T, class EVAL_TYPE = T>
        class PopulationFunctor : public noaa::nmfs::Object {
            PopulationDM<EVAL_TYPE, T>* population_m;


        public:

            PopulationFunctor() {
                this->SetName("noaa::PopulationFunctor");
            }

            virtual void Initialize(PopulationDM<T, EVAL_TYPE>* population_m) {
            }


            virtual const EVAL_TYPE Evaluate(PopulationDM<T, EVAL_TYPE>* population_m) = 0;
        };

        /**
         * PopulationDM is a simulation data module object and serves as a
         * base class for other population types, such as AgeBasedPopulation,
         * or SizeBasedPopulation.
         * 
         */
        template< class T, class EVAL_TYPE = T>
        class PopulationDM : noaa::nmfs::Object{
        protected:
            Configuration<T, EVAL_TYPE>* config; //general runtime configuration
            PopulationArea<T> area; //populations geographic area
            std::vector<PopulationDM<T, EVAL_TYPE>* > nearest_niegbors; //nearest populations of the same species

            //varying time step info
            uint32_t start_year;
            uint32_t end_year;
            uint32_t seasons;
            uint32_t current_year;
            uint32_t current_season;


        public:

            PopulationArea<T> GetArea() const {
                return area;
            }

            void SetArea(PopulationArea<T> area) {
                this->area = area;
            }

            Configuration<T,EVAL_TYPE>* GetConfiguration() const {
                return config;
            }

            void SetConfiguration(Configuration<T, EVAL_TYPE>* config) {
                this->config = config;
            }

            uint32_t GetCurrentSeason() const {
                return current_season;
            }

            void SetCurrentSeason(uint32_t current_season) {
                this->current_season = current_season;
            }

            uint32_t GetCurrentYear() const {
                return current_year;
            }

            void SetCurrentYear(uint32_t current_year) {
                this->current_year = current_year;
            }

            uint32_t GetEndYear() const {
                return end_year;
            }

            void SetEndYear(uint32_t end_year) {
                this->end_year = end_year;
            }

            std::vector<PopulationDM<T, EVAL_TYPE>*> GetNearestNiegbors() const {
                return nearest_niegbors;
            }

            void SetNearestNiegbors(std::vector<PopulationDM<T, EVAL_TYPE>*> nearest_niegbors) {
                this->nearest_niegbors = nearest_niegbors;
            }

            uint32_t GetNumberOfSeasons() const {
                return seasons;
            }

            void SetNumberOfSeasons(uint32_t seasons) {
                this->seasons = seasons;
            }

            uint32_t GetStartYear() const {
                return start_year;
            }

            void SetStartYear(uint32_t start_year) {
                this->start_year = start_year;
            }



        };

        /**
         * AgeBasedPopulation class.
         * 
         * A Fishery modeling data module object that holds age relevant 
         * information about a population of fish.
         * 
         */
        template< class T, class EVAL_TYPE = T>
        class AgeBasedPopulation : public PopulationDM<T, EVAL_TYPE> {
            uint32_t numbers_at_age;

            /***************************************************************
             *              Age based modeling data.                       *
             ***************************************************************/
            std::vector<uint32_t> ages;
            std::vector<uint32_t > numbers_at_age_males;
            std::vector<uint32_t > numbers_at_age_females;
            std::vector<uint32_t > biomass_at_age_males;
            std::vector<uint32_t > biomass_at_age_females;
            std::vector<T> length_at_age_males;
            std::vector<T> length_at_age_females;
            std::vector<T> fecundity_at_age_males;
            std::vector<T> fecundity_at_age_females;

        public:






        };

    }


}

#endif	/* SSPOPULATION_HPP */

