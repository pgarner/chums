#include "familytree.h"

int main(int argc, char **argv)
{
    FamilyTree tree;
    //tree.loadGEDCOM("tests.ged");
    //tree.loadGEDCOM("Phil.ged");
    tree.loadGEDCOM("gedr8442.ged");
    //tree.loadGEDCOM("ged3.ged");
    tree.saveGraphViz("test.dot");
    return 0;
}
