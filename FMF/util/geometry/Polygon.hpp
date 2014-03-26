/* 
 * File:   Polygon.hpp
 * Author: matthewsupernaw
 *
 * Created on March 24, 2014, 8:17 AM
 */

#ifndef POLYGON_HPP
#define	POLYGON_HPP

#include <vector>
#include "Point.hpp"



/**
 * Polygon object. Used to describe 
 * geographic areas in the NMFS Fishery 
 * Modeling Framework.
 */
template<class T>
class Polygon{
    
    std::vector<Point<T> > points;
    T centroid_x, centroid_y;
    public:
        
        
    
    
    
};


#endif	/* POLYGON_HPP */

