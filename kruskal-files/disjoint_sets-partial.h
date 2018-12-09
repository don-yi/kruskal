/*!
  \brief  Disoint sets using quick find implementation (linked lists and 
  a look-up table)

Implements:
	ctor (size)
	Make( id )      initialize
	Join( id,id )   join 2 sets
	GetRepresentative( id )

Rationale:
	elements of the set are assumed to be contiguous 0,1,2,3,....
*/

#ifndef DISJOINT_SETS_H
#define DISJOINT_SETS_H
#include <cstdlib>
#include <fstream> //ostream, istream

////////////////////////////////////////////////////////////
class DisjointSets {
	public:
		DisjointSets( size_t const& capacity );
		~DisjointSets();
		void   Make( );
		void   Join( size_t const& id1, size_t const& id2 );
		size_t GetRepresentative( size_t const& id ) const;
		size_t operator[]( size_t const& id ) const;
		friend std::ostream& operator<< (std::ostream& os, DisjointSets const& ds);
		DisjointSets( DisjointSets const& ) = delete;
		DisjointSets& operator=( DisjointSets const& ) = delete;
	private:
};


#endif
