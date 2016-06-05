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
using namespace lube;

int main(int argc, char** argv)
{
    // Start with a vCard
    filemodule vcfm("vcf");
    file& vcf = vcfm.create();
    var vcard = vcf.read(TEST_DIR "/test.vcf");
    vcf.write("vcard-out.vcf", vcard);
    cout << "vCard: " << vcard << endl;

    // Windoze Address Book
    filemodule wabm("wab");
    file& wab = wabm.create();
    var contact = wab.read(TEST_DIR "/test.contact");
    vcf.write("contact-out.vcf", contact);
    cout << "Contact: " << contact << endl;

#if 0
    // LDAP file
    filemodule ldifm("ldif");
    file& ldif = ldifm.create();
    var ldap = ldif.read(TEST_DIR "/test.ldif");
    vcf.write("ldap-out.vcf", ldap);
    cout << "LDAP: " << ldap << endl;
#endif

    return 0;
}
