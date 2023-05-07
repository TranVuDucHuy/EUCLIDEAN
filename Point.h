#ifndef POINT_H
#define POINT_H

#include "Const.h"

struct Point
{
    double x;
    double y;

    Point( double x_ = 200*ratioHomothety, double y_ = 120*ratioHomothety ) : x( x_ ), y( y_ ) {}

    bool operator==( Point p );

    Point& operator=( const Point& p );
};

/// Check if already had point
bool isExistPoint( Point p, Point Points[], int currentPoints );

/// Check if point is inside the board
bool isInside( Point p );

/// Given points for each content
void setPoints( Point Points[][ TOTAL_POINTS ] );

/// Number of given points for each content
void setCurrentPoints( int CurrentPoints[] );

/// Max points can be created for each content
void setMaxPoints( int MaxPoints[] );

/// Point's tests for each content
void setTestPoints( Point TestPoints[] );

#endif
