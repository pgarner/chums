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
    file vcf("vcf");
    var vcard = vcf.read("example3.vcf");
    vcf.write("vcard.vcf", vcard);
    cout << "vCard: " << vcard << endl;

    file wab("wab");
    var contact = wab.read("example.contact");
    vcf.write("contact.vcf", contact);
    cout << "Contact: " << contact << endl;

    file ldif("ldif");
    var ldap = ldif.read("example.ldif");
    vcf.write("ldap.vcf", ldap);
    cout << "LDAP: " << ldap << endl;
    
    return 0;
}
