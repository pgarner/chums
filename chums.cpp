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
using namespace lube;

int main(int argc, char** argv)
{
    // Command line
    var arg(argc, argv);
    if (arg.size() != 3)
        throw lube::error("Must have two arguments");

    // Start with a vCard
    filemodule vcfm("vcf");
    file& vcf = vcfm.create();
    var vcard = vcf.read(arg[1]);

    // Write another format
    filemodule wabm("wab");
    file& wab = wabm.create();
    wab.write(arg[2], vcard);

    return 0;
}
