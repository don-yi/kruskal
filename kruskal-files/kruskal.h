#ifndef KRUSKAL_H
#define KRUSKAL_H
#include "disjoint_sets.h"
#include "graph.h"

template <typename Vertex, typename Edge>
std::vector<Edge> kruskal( Graph<Vertex,Edge> const& g )
{
  std::vector<Edge> mst{};

  // Sort all edges E in non - decreading order
  auto E = g.GetEdges();
  E.sort(
    [](const Edge& e1, const Edge& e2)
  {
    return e1.Weight() < e2.Weight();
  }
  );

  // Remove duplicates.
  //for (auto && edge : edges_all)
  //{
  //}

  const auto verCt = E.size() - 1;

  // Make disjoint sets.
	DisjointSets ds(verCt);
  for (size_t i = 0; i < verCt; ++i)
  {
    ds.Make();
  }

  for (auto& e : E)
  {
    auto rep1 = ds[e.ID1()];
    auto rep2 = ds[e.ID2()];

    // mst U e (union)
    if (rep1 == rep2)
    {
      continue;
    }
    // add edge to MST
    else
    {
      ds.Join(rep1, rep2);
      mst.push_back(e);
    }
  }

	return mst;
}

#endif
