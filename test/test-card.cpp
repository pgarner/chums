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

    // Windoze Address Book
    lube::file wab("wab");
    var contact = wab.read(TEST_DIR "/test.contact");
    vcf.write("contact-out.vcf", contact);
    cout << "Contact: " << contact << endl;

#if 0
    // LDAP file
    lube::file ldif("ldif");
    var ldap = ldif.read(TEST_DIR "/test.ldif");
    vcf.write("ldap-out.vcf", ldap);
    cout << "LDAP: " << ldap << endl;
#endif

    return 0;
}
