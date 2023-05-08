#ifndef LINE_H
#define LINE_H

#include "Point.h"
#include "Const.h"

struct Point;

struct Line
{
    Point A;
    Point B;

    Line(Point a = Point( 200*ratioHomothety, 120*ratioHomothety ) , Point b = Point( 200*ratioHomothety, 120*ratioHomothety ) ) : A(a), B(b) {}

    Line& operator=( const Line& l );

    bool operator==( Line l );
};

/// Check if already had line
bool isExistLine( Line l, Line Lines[], int currentLines );

/// Check if two lines is parallel to each other
bool isParallel( Line l1, Line l2 );

/// Check if point is on line
bool isInLine( Point p, Line l );

/// Line passing through two given points
Line through( Point p1, Point p2 );

/// Intersection of two given lines
Point intersection( Line l1, Line l2 );

/// Given lines for each content
void setLines( Line Lines[][ TOTAL_LINES ] );

/// Number of given lines for each content
void setCurrentLines ( int CurrentLines[] );

/// Maximum number of lines can be created for each content
void setMaxLines ( int MaxLines[] );

/// Line's tests for each content
void setTestLines ( Line TestLines[] );

#endif
