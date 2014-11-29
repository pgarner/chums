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
    vfile vcf("vcf");
    var vcard = vcf.read("example3.vcf");
    vcf.write("vcard.vcf", vcard);
    cout << "vCard: " << vcard << endl;

    vfile wab("wab");
    var contact = wab.read("example.contact");
    vcf.write("contact.vcf", contact);
    cout << "Contact: " << contact << endl;
    return 0;

    vfile ldif("ldif");
    var ldap = ldif.read("example.ldif");
    
    return 0;
}
