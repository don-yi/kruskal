/*!
  Implements several types of methods
  InsertEdge
  InsertVertex
  GetVertex returns a reference to Vertex by ID
  GetOutEdges from a vertex 
  Print
 */
/******************************************************************************/
/* VertexType requirements: 
   conversion ctor: VertexType( size_t )
   copy ctor        VertexType ( VertexType const& )
   comparable       VertexType < VertexType
   has a id that is by edges
   has a public ID 
 */

/* EdgeType requirements:
   ctor            EdgeType( size_t, size_t )
   copy ctor       EdgeType( EdgeType const& )
   has a public ID1 - returns the id of the first vertex
   has a public ID2 - returns the id of the second vertex
 */

#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <iostream>

template <typename VertexType, typename EdgeType>
class Graph {
		// maps vertex to a vector of outgoing edges, 
		// adjacency list
		std::map< VertexType, std::vector<EdgeType> > outgoining_edges;
		std::list< EdgeType > edges_all;
	public:
		//the usual type-getters
		typedef VertexType Vertex;
		typedef EdgeType   Edge;
		////////////////////////////////////////////////////////////
        Graph() : outgoining_edges(), edges_all() {}
		////////////////////////////////////////////////////////////
		void InsertEdge( EdgeType const& e ) { 
			outgoining_edges[ GetVertex(e.ID1()) ].push_back ( e );
			edges_all.push_back( e );
		}
		////////////////////////////////////////////////////////////
		void InsertVertex( VertexType const& v ) { 
			outgoining_edges.insert( std::make_pair( v, std::vector<EdgeType>()));
		}
		////////////////////////////////////////////////////////////
		void BuildFromEdgeArray( EdgeType * array, size_t const& size ) {
			for ( size_t i=0; i<size; ++i ) {
				EdgeType const& e = array[i];
				VertexType v1( e.ID1() ), v2( e.ID2() );

				//no duplicates are allowed in maps, so no checks
				outgoining_edges[v1];
				outgoining_edges[v2];
//				outgoining_edges.insert( std::make_pair/*<VertexType,std::vector<EdgeType> >*/( v1, std::vector<EdgeType>()));
//				outgoining_edges.insert( std::make_pair/*<VertexType,std::vector<EdgeType> >*/( v2, std::vector<EdgeType>()));

				//do not check double edges - they are legal in multipli-connected graphs
//				outgoining_edges[ GetVertex(e.ID1()) ].push_back ( e );
				edges_all.push_back( e );
			}
		}
		////////////////////////////////////////////////////////////
		VertexType const& GetVertex( size_t id ) const {
			typename 
				std::map< VertexType, std::vector<EdgeType> >::const_iterator 
				it = outgoining_edges.find( VertexType(id) );

			if ( it	!= outgoining_edges.end() ) return it->first;
			else throw "cannot find node in the graph";
		}
		////////////////////////////////////////////////////////////
		typename std::list<EdgeType> const& GetEdges( ) const {
			return edges_all;
		}
		////////////////////////////////////////////////////////////
		typename std::vector<EdgeType> const& GetOutEdges( size_t id ) const {
			typename 
				std::map< VertexType, std::vector<EdgeType> >::const_iterator it =
				outgoining_edges.find( VertexType(id) );
			if ( it	!= outgoining_edges.end() ) return it->second;
			else throw "cannot find node in the graph";
		}
		////////////////////////////////////////////////////////////
		typename std::vector<EdgeType> const& GetOutEdges( const VertexType & v) const {
			typename 
				std::map< VertexType, std::vector<EdgeType> >::const_iterator it =
				outgoining_edges.find( v );
			if ( it	!= outgoining_edges.end() ) return it->second;
			else throw "cannot find node in the graph";
		}
		////////////////////////////////////////////////////////////
		size_t Size() const {
			return outgoining_edges.size();
		}
		////////////////////////////////////////////////////////////
		//this won't compile if vertex and/or edge don't implement Name, 
		//you may change Name to ID for testing purposes
		friend std::ostream& operator<< (std::ostream& os, Graph const& g) {
			typename std::map< VertexType, std::vector<EdgeType> >::const_iterator 
				it   = g.outgoining_edges.begin(),
					 it_e = g.outgoining_edges.end();

			for ( ; it != it_e; ++it) {
				std::cout << "Vertex " << it->first.ID() << std::endl;
				size_t size = it->second.size();
				for(size_t i=0;i<size;++i) {
					std::cout << "\t" //<< it->second[i].GetName() 
						<< " (" << it->second[i].ID1() << " -> " 
						<< it->second[i].ID2() << ")" << std::endl;
				}
			}
			return os;
		}
};
#endif
