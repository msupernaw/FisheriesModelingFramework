/* 
 * File:   Population.hpp
 * Author: matthewsupernaw
 *
 * Created on March 26, 2014, 7:24 AM
 */

#ifndef NOAA_NMFS_POPULATION_HPP
#define	NOAA_NMFS_POPULATION_HPP

#include <map>
#include "Common.hpp"
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

        class PopulationAttributeBase :public noaa::nmfs::Object {
            std::string attribute_name;
        public:

            std::string GetName() const {
                return attribute_name;
            }

            void SetName(std::string name) {
                this->attribute_name = name;
            }

        public:

            PopulationAttributeBase(const std::string &name) : attribute_name(name) {
            }
        };

        template< class ATTRIBUTE_TYPE>
        class PopulationAttribute : public PopulationAttributeBase {
            ATTRIBUTE_TYPE attribute_value;



        public:

            operator ATTRIBUTE_TYPE() const{
                return this->attribute_value;
            }
            
            PopulationAttribute(const std::string &name,
                    const ATTRIBUTE_TYPE &value) : PopulationAttributeBase(name),
            attribute_value(value) {

            }

            PopulationAttribute(const PopulationAttribute& other) {

            }

            ATTRIBUTE_TYPE& GetAttributeValue()  {
                return attribute_value;
            }

            void SetAttributeValue(ATTRIBUTE_TYPE attribute_value) {
                this->attribute_value = attribute_value;
            }


            virtual std::string ToString(){
                std::stringstream ss;
                ss<<this->GetName()<<":"<<this->GetAttributeValue();
                return ss.str();
            }




        };

        /**
         * PopulationDM is a simulation data module object and serves as a
         * base class for other population types, such as AgeBasedPopulation,
         * or SizeBasedPopulation.
         * 
         */
        template< class T, class EVAL_TYPE = T>
        class PopulationDM : public noaa::nmfs::Object {
        protected:
            Configuration<T, EVAL_TYPE>* config; //general runtime configuration
            PopulationArea<T> area; //populations geographic area
            std::vector<PopulationDM<T, EVAL_TYPE>* > nearest_neighbors; //nearest populations of the same species
            std::map<std::string, PopulationAttributeBase*> attributes;
            std::map<std::string, PopulationFunctor<T, EVAL_TYPE>* > functors;

            typedef typename std::map<std::string, PopulationFunctor<T, EVAL_TYPE>* >::iterator FunctorIterator;
            typedef typename std::map<std::string, PopulationAttributeBase* >::iterator AttributeIterator;


            uint32_t current_year;
            uint32_t current_season;


        public:

            template<class ATTRIBUTE_TYPE>
            void AddAttribute(const std::string &name, const ATTRIBUTE_TYPE &attribute) {

                PopulationAttribute<ATTRIBUTE_TYPE> * attr
                        = new PopulationAttribute<ATTRIBUTE_TYPE > (name, attribute);
                this->attributes[name] = (PopulationAttributeBase*) attr;
            }

            PopulationAttributeBase* GetAttribute(const std::string &name) {
                return this->attributes[name];
            }
            
            template<class ATTRIBUTE_TYPE>
            ATTRIBUTE_TYPE& GetAttributeValue(std::string name){
                PopulationAttribute<ATTRIBUTE_TYPE> * attr
                        = (PopulationAttribute<ATTRIBUTE_TYPE> *)this->attributes[name];
                
                if(attr){
                    return attr->GetAttributeValue();
                }else{
                    std::cout<<"attribute \""<<name<<"\" not found in population name \""<<this->GetName()<<"\"";
                    exit(0);
                }
            }

            template<class FUNCTOR_TYPE>
            void CreateFunctor(const std::string &name, bool initialize = false) {
                this->functors[name] = new FUNCTOR_TYPE();
                if (initialize) {
                    this->functors[name]->Initialize(this);
                }
            }

            void InitializeFunctors() {
                FunctorIterator it;

                for (it = this->functors.begin(); it != this->functors.end(); it++) {
                    PopulationFunctor<T, EVAL_TYPE>* func = it->second;
                    func->Initialize(this);
                }

            }

            const EVAL_TYPE EvaluateFunctor(const std::string &name) {
                PopulationFunctor<T, EVAL_TYPE>* func = this->functors[name];
                if (func != NULL) {
                    return func->Evaluate(this);
                }

                return (EVAL_TYPE) 0.0;
            }

            const EVAL_TYPE SumFunctors() {
                FunctorIterator it;
                EVAL_TYPE ret = 0.0;
                for (it = this->functors.begin(); it != this->functors.end(); it++) {
                    PopulationFunctor<T, EVAL_TYPE>* func = it->second;
                    ret += func->Evaluate(this);
                }
                return ret;
            }

            PopulationArea<T> GetArea() const {
                return area;
            }

            void SetArea(PopulationArea<T> area) {
                this->area = area;
            }

            Configuration<T, EVAL_TYPE>* GetConfiguration() const {
                return config;
            }

            void SetConfiguration(Configuration<T, EVAL_TYPE>* config) {
                this->config = config;
            }

            std::vector<PopulationDM<T, EVAL_TYPE>*> GetNearestNeigbors() const {
                return nearest_neighbors;
            }

            void SetNearestNeigbors(std::vector<PopulationDM<T, EVAL_TYPE>*> nearestneighbors) {
                this->nearest_neighbors = nearestneighbors;
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

            void AddNeighbor(PopulationDM<T, EVAL_TYPE>* neighbor, T range = std::numeric_limits<T>::max()) {

            }

            virtual std::string ToString() {
                std::stringstream ss;

                ss << "\nPopulation Name: " << this->GetName() << "\n";
                ss << "Population Attributes: \n";
                AttributeIterator ait;

                for (ait = this->attributes.begin(); ait != this->attributes.end(); ait++) {
                    ss << " " << *ait->second<<"\n";
                }

                FunctorIterator it;
                ss << "Population Functors: \n";
                for (it = this->functors.begin(); it != this->functors.end(); it++) {
                    ss << " " << *it->second<<"\n";
                }


                return ss.str();
            }

        };



    }



}

template<class T,class T2, class charT, class traits>
std::basic_ostream<charT, traits>&
operator <<(std::basic_ostream<charT, traits>& out, const noaa::nmfs::PopulationDM<T,T2> &pop) {
    out<<pop.ToString();
    return out;
}


#endif	/* SSPOPULATION_HPP */

