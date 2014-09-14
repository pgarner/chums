/*
 * Copyright 2014 by Philip N. Garner
 *
 * See the file COPYING for the licence associated with this software.
 *
 * Author(s):
 *   Phil Garner, September 2014
 */

#include <lv.h>

using namespace std;

int main(int argc, char** argv)
{
    vfile mscontact("wab");
    var contact = mscontact.read("example.contact");
    //cout << contact << endl;
    vfile vcard("vcf");
    var card = vcard.read("example.vcf");
    
    return 0;
}
