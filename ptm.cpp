//*****************************************************************************
/// @file ptm.cpp (pointer to member function)
/// @author Jonathan D. Lettvin
/// @date 20091109
// This tests vectors of maps of member pointers to abstract class methods.
// In other words, you can have layers of context
// within which functions can be run by string name but anonymously from C++.
// This mechanism may be used to hide instance data as an alternative to pimpl.
//*****************************************************************************
#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::vector; using std::string; using std::map;
using std::cout; using std::endl;

class pure {	//**************************************************************
  public:
    virtual void a( const string &N ) = 0;
    virtual void b( const string &N ) = 0;
};

class Base : public pure {	//**********************************************
  public:	/// Instantiate both pure virtual classes
    virtual void a( const string &N ) { cout << N << " = Base::a "; }
    virtual void b( const string &N ) { cout << N << " = Base::b "; }
};

class Mask : public Base {	//**********************************************
  public:	/// Instantiate mask base virtual classes
    void a( const string &N ) { cout << N << " = Mask::a "; }
};

int main() {	//**************************************************************
  // Create a member pointer map (with no instance in scope).
  vector< map< string, void ( pure::* )( const string & ) > > layer( 2UL );

  // Make a list of keywords
  vector< string > name;
  name.push_back( "1st" );
  name.push_back( "2nd" );

  // Fill the member pointer map (still with no instance in sight).
  layer[ 0 ][ name[ 0 ] ] = &pure::a;	layer[ 0 ][ name[ 1 ] ] = &pure::b;
  layer[ 1 ][ name[ 0 ] ] = &pure::b;	layer[ 1 ][ name[ 1 ] ] = &pure::a;

  // Instantiate one of both the base and derived classes
  Base base;
  Mask mask;

  // Run the member functions mapped to each name for each layer.
  for( size_t J = layer.size( ), j = 0UL, k = 0UL; j < J; ++j ) {
    for( size_t I = name.size( ), i = 0UL; i < I; ++i, ++k ) {
      ( base.*layer[ j ][ name[ i ] ] )( name[ i ] );
      ( mask.*layer[ j ][ name[ i ] ] )( name[ i ] );
      cout << endl;
    }
  }
  return 0;
}
