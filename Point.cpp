#include "Point.h"
#include "Const.h"

bool Point::operator==( Point p )
{
    return ( ( p.x == x ) && ( p.y == y ) );
};

bool isExistPoint( Point p, Point Points[], int currentPoints )
{
    for( int i = 0; i < currentPoints; i += 1 )
    {
        if( p == Points[ i ] )
        {
            return true;
        }
    }
    return false;
};

Point& Point::operator=( const Point& p )
{
    x = p.x;
    y = p.y;

    return *this;
}

void setPoints( Point Points[][ TOTAL_POINTS ] )
{
    for( int j = 0; j < TOTAL_CONTENTS; j += 1 )
    {
        for( int i = 0; i < 49; i += 1 )
        {
            Points[ j ][ i ] = Point( 200*ratioHomothety + (i%7)*80*ratioHomothety, 120*ratioHomothety + (i/7)*80*ratioHomothety );
        }
    }

    Points[ 0 ][ 49 ] = Point( 1280664, 415800 );
    Points[ 1 ][ 49]  = Point( 727650, 519750 );
}

void setCurrentPoints( int CurrentPoints[] )
{
    for( int i = 0; i < TOTAL_CONTENTS; i += 1 )
    {
        CurrentPoints[ i ] = 0;
    }

    CurrentPoints[ 0 ] = 1;
    CurrentPoints[ 1 ] = 1;
}

void setMaxPoints( int MaxPoints[] )
{
    for( int i = 0; i < TOTAL_CONTENTS; i += 1)
    {
        MaxPoints[ i ] = 22;
    }

    MaxPoints[ 0 ] = 2;
    MaxPoints[ 1 ] = 2;
}

void setTestPoints( Point TestPoints[] )
{
    for( int i = 0; i < TOTAL_CONTENTS; i += 1 )
    {
        TestPoints[ i ] = Point( 200*ratioHomothety , 120*ratioHomothety );
    }

    TestPoints[ 0 ] = Point( 200*ratioHomothety , 120*ratioHomothety );
    TestPoints[ 1 ] = Point( 200*ratioHomothety , 120*ratioHomothety );
}

bool isInside( Point p )
{
    if( ( p.x >= 200*ratioHomothety ) && ( p.x <= 680*ratioHomothety ) && ( p.y >= 120*ratioHomothety ) && ( p.y <= 600*ratioHomothety ) )
    {
        return true;
    }
    return false;
}
