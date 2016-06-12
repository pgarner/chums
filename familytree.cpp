#include "familytree.h"

#include <fstream>
#include <boost/graph/graphviz.hpp>

void FamilyTree::loadGEDCOM(const char* iFileName)
{
    lube::filemodule gm("ged");
    lube::file& vf = gm.create();
    var ged = vf.read(iFileName);

    std::cout << "Individuals: " << ged["Individual"].size() << std::endl;
    std::cout << "Families: " << ged["Family"].size() << std::endl;

    // Add to graph
    for (int i=0; i<ged["Individual"].size(); i++)
    {
        // Rely on vertex, returned by add_vertex(), just being an
        // integer that increments with each call.
        vertex v = addIndividual();
        if ((int)v != i)
            throw std::runtime_error(
                "FamilyTree::loadGEDCOM: vertex out of order"
            );
        var& ind = getIndividual(v);
        ind = ged["Individual"][i];
    }
    for (int i=0; i<ged["Family"].size(); i++)
    {
        var f = ged["Family"][i];
        var h = f.at("HUSB");
        var w = f.at("WIFE");
        h.dereference();
        w.dereference();
        for (int c=0; c<f["CHIL"].size(); c++)
        {
            var k = f["CHIL"][c];
            if (h)
                addRelationship(h.cast<int>(), k.cast<int>());
            if (w)
                addRelationship(w.cast<int>(), k.cast<int>());
        }
    }
}

FamilyTree::vertex FamilyTree::addIndividual()
{
    vertex v = add_vertex(mGraph);
    return v;
}

FamilyTree::edge FamilyTree::addRelationship(vertex iID1, vertex iID2)
{
    std::pair<edge, bool> ret;
    ret = add_edge(iID1, iID2, mGraph);
    return ret.first;
}

template <class T>
class LabelWriter
{
public:
    LabelWriter(T& iGraph) : mGraph(iGraph) {}
    template <class VertexOrEdge>
    void operator()(std::ostream& iOut, const VertexOrEdge& iV) const
    {
        var v = mGraph[iV];
        if (v.at("NAME"))
            // Should replace with escaped quote rather than nothing
            iOut << "[label=\"" << v.at("NAME").replace("\"", "").str() << "\"]";
    }
private:
    T& mGraph;
};

void FamilyTree::saveGraphViz(const char* iFileName)
{
    std::ofstream ofs(iFileName, std::ofstream::out);
    LabelWriter<graph> lw(mGraph);
    write_graphviz(ofs, mGraph, lw);
}
