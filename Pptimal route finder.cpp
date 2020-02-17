#include <list>
#include <algorithm>
#include <iostream>
using namespace std;

class point
{
public:
	int x, y;
    point(int a = 0, int b = 0 )
	{
		x = a; y = b;
	}
    bool operator ==(const point& p )
	{
		return p.x == x && p.y == y;
	}
    point operator +(const point& p )
	{
		point brandNew;
		brandNew.x = x + p.x;
		brandNew.y = y + p.y;
		return brandNew;
	}
	void print()
	{
		cout<<x<<","<<y<<endl;
	}
};

class map
{
public:
	char m[8][8];
	int w;
	int h;
	map()
	{
		char t[8][8]=
		{
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 1, 1, 1, 0},
			{0, 0, 1, 0, 0, 0, 1, 0},
			{0, 0, 1, 0, 0, 0, 1, 0},
			{0, 0, 1, 1, 1, 1, 1, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0}
		};
		w=8;
		h=8;
        for( int r = 0; r < h; r++ )
		{
            for( int s = 0; s < w; s++ )
			{
                m[s][r] = t[r][s];
			}
		}
	}
	int operator() ( int x, int y )
	{
		return m[x][y];
	}
};

class node
{
	public:
		    int dist, cost;
			point pos;
			point parent;
    bool operator == (const node& n )
	{
		return pos == n.pos;
	}
    bool operator == (const point& n )
	{
		return pos == n;
	}
    bool operator < (const node& n )
	{
		return dist + cost < n.dist + n.cost;
	}
};

class aStar
{
public:
	map m;
	point end, start;
    point neighbours[8];
    list<node> open;
    list<node> closed;

	 aStar()
	 {
        neighbours[0] = point( -1, -1 ); neighbours[1] = point(  1, -1 );
        neighbours[2] = point( -1,  1 ); neighbours[3] = point(  1,  1 );
        neighbours[4] = point(  0, -1 ); neighbours[5] = point( -1,  0 );
        neighbours[6] = point(  0,  1 ); neighbours[7] = point(  1,  0 );
     }

	int calcDist(point& p )
	{
        int x = end.x - p.x;
		int y = end.y - p.y;
        return sqrt( x * x + y * y );
    }

    bool isValid(point& p)
	{
        return (p.x >=0 && p.y >=0 && p.x < m.w && p.y < m.h );
    }

	 bool existPoint( point& p, int cost )
	 {
        list<node>::iterator i;
        i = find( closed.begin(), closed.end(), p );
        if( i != closed.end() )
		{
            if( ( *i ).cost + ( *i ).dist < cost )
				return true;
            else
			{
				closed.erase( i );
				return false;
			}
        }
        i = find( open.begin(), open.end(), p );
        if( i != open.end() )
		{
            if( ( *i ).cost + ( *i ).dist < cost )
				return true;
            else
			{
				open.erase( i );
				return false;
			}
        }
        return false;
    }

	bool fillOpen( node& n )
	{
        int stepCost, nc, dist;
        point neighbour;
 
        for( int x = 0; x < 8; x++ )
		{
            // one can make diagonals have different cost
            stepCost = x < 4 ? 1 : 2;
            neighbour = n.pos + neighbours[x];
            if( neighbour == end )
				return true;
 
            if( isValid( neighbour ) && m( neighbour.x, neighbour.y ) != 1 )
			{
                nc = stepCost + n.cost;
                dist = calcDist( neighbour );
                if( !existPoint( neighbour, nc + dist ) )
				{
                    node m;
                    m.cost = nc; m.dist = dist;
                    m.pos = neighbour; 
                    m.parent = n.pos;
                    open.push_back( m );
                }
            }
        }
        return false;
    }

	 bool search( point& s, point& e, map& mp )
	 {
        node n; end = e; start = s; m = mp;
        n.cost = 0; n.pos = s; n.parent = 0; n.dist = calcDist( s ); 
        open.push_back( n );
        while( !open.empty() )
		{
            //open.sort();
            node n = open.front();
            open.pop_front();
            closed.push_back( n );
			if( fillOpen( n ) )
					return true;
        }
        return false;
    }

	 int path( std::list<point>& path )
	 {
        path.push_front( end );
        int cost = 1 + closed.back().cost; 
        path.push_front( closed.back().pos );
        point parent = closed.back().parent;
 
        for( std::list<node>::reverse_iterator i = closed.rbegin(); i != closed.rend(); i++ )
		{
            if( ( *i ).pos == parent && !( ( *i ).pos == start ) )
			{
                path.push_front( ( *i ).pos );
                parent = ( *i ).parent;
            }
        }
        path.push_front( start );
        return cost;
    }
};

int main()
{
    map M;
	point s(2, 2);
	point e( 7, 7 );
	aStar as;
 
    if( as.search( s, e, M ) )
	{
        list<point> path;
        int c = as.path( path );
        for( int y = 0; y < 8; y++ )
		{
            for( int x = 0; x < 8; x++ )
			{
                if( x >= 0 || y >= 0 || x <= 7 || y <= 7 || M( x, y ) == 0 )
				{
                    if( find( path.begin(), path.end(), point( x, y ) )!= path.end() )
                        cout << "x";
                    else
						cout << ".";
                }
            }
            cout << "\n";
        }
 
        cout << "\nPath cost " << c << ": ";
        for(list<point>::iterator i = path.begin(); i != path.end(); i++ )
		{
            cout<< "(" << ( *i ).x << ", " << ( *i ).y << ") ";
        }
    }
    cout << "\n\n";
	system("pause");
	return 0;
}