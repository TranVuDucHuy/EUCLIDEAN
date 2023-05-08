#include "Point.h"
#include "Line.h"
#include "Const.h"

Line& Line::operator=( const Line& l )
{
    A = l.A;
    B = l.B;

    return *this;
}

bool Line::operator==( Line l )
{
    return ( l.A == A && l.B == B );
};

/// Check if already had line
bool isExistLine( Line l, Line Lines[], int currentLines )
{
    for ( int i = 0; i < currentLines; i += 1 ) {
        if ( l == Lines[i] ) {return true;}
    }
    return false;
};

/// Check if two lines is parallel to each other
bool isParallel( Line l1, Line l2 )
{
    double x1 = l1.A.x - l1.B.x;
    double y1 = l1.A.y - l1.B.y;
    double x2 = l2.A.x - l2.B.x;
    double y2 = l2.A.y - l2.B.y;

    if( x1*y2 == x2*y1 )
    {
        return true;
    }
    return false;
};

/// Check if point is on line
bool isInLine ( Point p, Line l )
{
    double x1 = p.x - l.A.x;
    double y1 = p.y - l.A.y;
    double x2 = p.x - l.B.x;
    double y2 = p.y - l.B.y;

    if( x1*y2 == x2*y1 )
    {
        return true;
    }
    return false;
};

/// Line passing through two given points
Line through ( Point p1, Point p2 )
{
    Line l;

    double x1 = p1.x - p2.x;
    double y1 = p1.y - p2.y;

    if( x1 == 0 )
    {
        if( y1 == 0 )
        {
            l = Line( Point( 200*ratioHomothety, 120*ratioHomothety ) , Point( 200*ratioHomothety ,120*ratioHomothety ) );
        }
        else
        {
            l = Line( Point( p1.x, 120*ratioHomothety ), Point( p1.x, 600*ratioHomothety ) );
        }
    }
    else
    {
        if( y1 == 0 )
        {
            l = Line( Point( 200*ratioHomothety, p1.y ), Point( 680*ratioHomothety, p1.y ) );
        }
        else
        {
            double a = p1.x + x1*(120*ratioHomothety - p1.y)/y1;  //(a,120)  (200 <= a && 680 >= a)
            double b = p1.x + x1*(600*ratioHomothety - p1.y)/y1;  //(b,600)  (200 <= b && 680 >= b)
            double c = p1.y + y1*(200*ratioHomothety - p1.x)/x1;  //(200,c)  (120 <= c && 600 >= c)
            double d = p1.y + y1*(680*ratioHomothety - p1.x)/x1;  //(680,d)  (120 <= d && 600 >= d)

            //printf( " a =  %1.2f, b = %1.2f, c = %1.2f, d = %1.2f \n", a/ratioHomothety, b/ratioHomothety , c/ratioHomothety, d/ratioHomothety ) ;

            if( (200*ratioHomothety <= a && 680*ratioHomothety >= a) && (200*ratioHomothety <= b && 680*ratioHomothety >= b) )
            {
                l = Line( Point( a, 120*ratioHomothety ), Point( b, 600*ratioHomothety ) );;
            }
            if( (200*ratioHomothety <= a && 680*ratioHomothety >= a) && (120*ratioHomothety <  c && 600*ratioHomothety >= c) )
            {
                l = Line( Point( a, 120*ratioHomothety ), Point( 200*ratioHomothety, c ) );
            }
            if( (200*ratioHomothety <= a && 680*ratioHomothety >= a) && (120*ratioHomothety <  d && 600*ratioHomothety >= d) )
            {
                l = Line( Point( a, 120*ratioHomothety ), Point( 680*ratioHomothety, d ) );
            }
            if( (120*ratioHomothety <= c && 600*ratioHomothety >  c) && (200*ratioHomothety <= b && 680*ratioHomothety >= b) )
            {
                l = Line( Point( 200*ratioHomothety, c ), Point( b, 600*ratioHomothety ) );
            }
            if( (120*ratioHomothety <= d && 600*ratioHomothety >  d) && (200*ratioHomothety <= b && 680*ratioHomothety >= b) )
            {
                l = Line( Point( 680*ratioHomothety, d ), Point( b, 600*ratioHomothety ) );
            }
            if( (120*ratioHomothety <= c && 600*ratioHomothety >= c) && (120*ratioHomothety <= d && 600*ratioHomothety >= d) )
            {
                l = Line( Point( 200*ratioHomothety, c ), Point( 680*ratioHomothety, d ) );
            }
        }
    }
    return l;
};

/// Intersection of two given lines
Point intersection ( Line l1, Line l2 )
{
    Point p;

    double x1 = l1.A.x - l1.B.x;
    double y1 = l1.A.y - l1.B.y;
    double x2 = l2.A.x - l2.B.x;
    double y2 = l2.A.y - l2.B.y;

    double det = x1*y2 - x2*y1;

    if( det == 0 )
    {
        return Point( 200*ratioHomothety, 120*ratioHomothety);
    }
    else
    {
        p.x = ( l2.A.x*y2*x1 - l1.A.x*x2*y1 + (l1.A.y - l2.A.y)*x1*x2 )/det;
        p.y = ( l1.A.y*y2*x1 - l2.A.y*x2*y1 + (l2.A.x - l1.A.x)*y1*y2 )/det;
    }
    return p;
};

/// Given lines for each content
void setLines( Line Lines[][ TOTAL_LINES ] )
{
    for( int j = 0; j < TOTAL_CONTENTS; j += 1 )
    {
        /// 7 horizontal lines
        for( int i = 0; i < 7; i += 1 )
        {
            Lines[ j ][ i ] = Line( Point( 200*ratioHomothety, 120*ratioHomothety + i*80*ratioHomothety ), Point( 680*ratioHomothety, 120*ratioHomothety + i*80*ratioHomothety ) );
        }

        /// 7 vertical lines
        for( int i = 7; i < 14; i += 1 )
        {
            Lines[ j ][ i ] = Line( Point( 200*ratioHomothety + (i-7)*80*ratioHomothety, 120*ratioHomothety ), Point( 200*ratioHomothety + (i-7)*80*ratioHomothety, 600*ratioHomothety ) );
        }
    }

    Lines[ 0 ][ 14 ] = Line( Point( 415800, 249480 ) , Point( 1014552, 1247400 ) );
    Lines[ 0 ][ 15 ] = Line( Point( 1247400, 249480 ) , Point( 1413720, 1081080 ) );

    Lines[ 1 ][ 14 ] = Line( Point( 637560, 249480 ) , Point( 970200, 1247400 ) );
    Lines[ 1 ][ 15 ] = Line( Point( 415800, 415800 ) , Point( 1413720, 748440 ) );
}

/// Number of given lines for each content
void setCurrentLines( int CurrentLines[] )
{
    for( int i = 0; i < TOTAL_CONTENTS; i += 1 )
    {
        CurrentLines[ i ] = 0;
    }

    CurrentLines[ 0 ] = 2;
    CurrentLines[ 1 ] = 2;
}

/// Maximum number of lines can be created for each content
void setMaxLines ( int MaxLines[] )
{
    for( int i = 0; i < TOTAL_CONTENTS; i += 1 )
    {
        MaxLines[ i ] = 22;
    }

    MaxLines[ 0 ] = 4;
    MaxLines[ 1 ] = 4;
}

/// Line's tests for each content
void setTestLines ( Line TestLines[] )
{
    for( int i = 0; i < TOTAL_CONTENTS; i += 1 )
    {
        TestLines[ i ] = Line( Point( 200*ratioHomothety, 120*ratioHomothety ), Point( 680*ratioHomothety, 120*ratioHomothety ) );
    }

    TestLines[ 0 ] = Line( Point( 1180872, 249480 ) , Point( 1413720, 637560 ) );
    TestLines[ 1 ] = Line( Point( 457380, 249480 ) , Point( 1413720, 1205820 ) );
}
