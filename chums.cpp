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
    // Start with a vCard
    vfile vcard("vcf");
    var card = vcard.read("example3.vcf");
    vcard.write("out.vcf", card);
    cout << card << endl;
    return 0;

    vfile mscontact("wab");
    var contact = mscontact.read("example.contact");
    cout << contact << endl;
    return 0;

    vfile ldif("ldif");
    var ldap = ldif.read("example.ldif");
    
    return 0;
}
