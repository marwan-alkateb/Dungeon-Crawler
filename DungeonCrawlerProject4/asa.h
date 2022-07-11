#ifndef ASA_H
#define ASA_H

#include <list>
#include <algorithm>
#include <iostream>
#include <vector>

namespace asa
{
class Point {
public:
    int x, y {0};
    Point( int a=0 , int b=0 ) {x=a; y=b;}
    bool operator ==( const Point& o ) { return o.x == x && o.y == y; }
    Point operator +( const Point& o ) { return Point( o.x + x, o.y + y ); }
};

class map {
public:
    int w, h;
    std::vector<std::vector<char>> m;
    int operator() ( int x, int y ) { return m[x][y]; }
    map(std::vector<std::vector<char>>& v): w(v.size()), h(v.at(0).size()) {
        m.resize(w);
        for( int i = 0; i < w; i++ )
            m[i].resize(h);

        for( int r = 0; r < w; r++ )
            for( int s = 0; s < h; s++ )
                m[r][s] = v[r][s];
    }
};

class node {
public:
    Point pos, parent;
    int dist, cost;
    bool operator == (const node& o ) { return pos == o.pos; }
    bool operator == (const Point& o) { return pos == o; }
    bool operator  < (const node& o ) { return dist + cost < o.dist + o.cost; }
};
}

#endif // ASA_H
