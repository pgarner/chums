/*
 * Copyright 2014 by Philip N. Garner
 *
 * See the file COPYING for the licence associated with this software.
 *
 * Author(s):
 *   Phil Garner, September 2014
 */

#include <lube.h>
#include <lube/path.h>

using namespace std;

int main(int argc, char** argv)
{
    // Should use $HOME here
    lube::module m("path");
    lube::path* p = lube::create(m, "/home/phil/Dropbox/Contacts");

    // Get a diretory listing
    var c = p->dir();

    // load files into a WAB thang
    lube::file wab("wab");
    var x;
    for (int i=0; i<c.size(); i++)
        x = wab.read(c.key(i).str());
    
    cout << x << endl;
    return 0;
}
