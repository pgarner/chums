/*
 * Copyright 2014 by Philip N. Garner
 *
 * See the file COPYING for the licence associated with this software.
 *
 * Author(s):
 *   Phil Garner, September 2014
 */

#include <lube.h>

using namespace std;

int main(int argc, char** argv)
{
    // Start with a vCard
    lube::file vcf("vcf");
    var vcard = vcf.read(TEST_DIR "/test.vcf");
    vcf.write("vcard-out.vcf", vcard);
    cout << "vCard: " << vcard << endl;

    lube::file wab("wab");
    var contact = wab.read("example.contact");
    vcf.write("contact-out.vcf", contact);
    cout << "Contact: " << contact << endl;

    lube::file ldif("ldif");
    var ldap = ldif.read("example.ldif");
    vcf.write("ldap-out.vcf", ldap);
    cout << "LDAP: " << ldap << endl;
    
    return 0;
}