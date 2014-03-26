/* 
 * File:   Config.hpp
 * Author: matthewsupernaw
 *
 * Created on March 25, 2014, 11:21 AM
 */

#ifndef CONFIG_HPP
#define	CONFIG_HPP


#include <vector>
#include <pair.h>

template<class T, class EVAL_TYPE = T>
class Configuration{
    std::vector<std::pair<EVAL_TYPE*, uint32_t> > registered_estimable_types;

    
   
    public:
        
    
        void RegisterEstimable( EVAL_TYPE& estimable, uint32_t phase =0){
            this->registered_estimable_types.push_back(std::pair<EVAL_TYPE*,uint32_t>(&estimable,phase));
        }
        
    std::vector<std::pair<EVAL_TYPE*, uint32_t> > GetRegisteredEstimableTypes() const {
        return registered_estimable_types;
    }

       
    
};


#endif	/* CONFIG_HPP */

