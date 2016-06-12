#ifndef FAMILYTREE_H
#define FAMILYTREE_H

#include <lube.h>
#include <boost/graph/adjacency_list.hpp>

class FamilyTree
{
    typedef boost::adjacency_list<
        boost::vecS,
        boost::vecS,
        boost::bidirectionalS,
        var,
        var
        >
    graph;

public:
    typedef boost::graph_traits<graph>::vertex_descriptor vertex;
    typedef boost::graph_traits<graph>::edge_descriptor edge;

    void loadGEDCOM(const char* iFileName);
    void saveGraphViz(const char* iFileName);
    vertex addIndividual();
    var& getIndividual(vertex iID) { return mGraph[iID]; };
    edge addRelationship(vertex iID1, vertex iID2);

private:
    graph mGraph;
};

#endif // FAMILYTREE_H
