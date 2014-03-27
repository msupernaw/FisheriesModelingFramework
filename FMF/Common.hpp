/* 
 * File:   Common.hpp
 * Author: matthewsupernaw
 *
 * Created on March 27, 2014, 8:07 AM
 */

#ifndef COMMON_HPP
#define	COMMON_HPP

#include <cmath>
#include <iostream>

#include <vector>



template<class T, class charT, class traits>
std::basic_ostream<charT, traits>&
operator <<(std::basic_ostream<charT, traits>& out, const std::vector<T> &v) {
    for (int i = 0; i < v.size(); i++) {
        out << v[i] << " ";
    }
    
    return out;
}





#endif	/* COMMON_HPP */

