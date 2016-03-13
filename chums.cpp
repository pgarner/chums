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
    // Command line
    var arg(argc, argv);
    if (arg.size() != 3)
        throw lube::error("Must have two arguments");

    // Start with a vCard
    lube::file vcf("vcf");
    var vcard = vcf.read(arg[1]);

    // Write another format
    lube::file wab("wab");
    wab.write(arg[2], vcard);

    return 0;
}
