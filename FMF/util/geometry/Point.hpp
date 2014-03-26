/* 
 * File:   Point.hpp
 * Author: matthewsupernaw
 *
 * Created on March 24, 2014, 8:16 AM
 */

#ifndef POINT_HPP
#define	POINT_HPP

template<class T>
class Point {
    T x;
    T y;
    T z;

public:

    Point():x(0), y(0), z(0) {

    }
    
    Point(const T& x, const T& y):x(x), y(y), z(0) {

    }
    
};

#endif	/* POINT_HPP */

