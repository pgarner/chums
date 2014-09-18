/*
 * Copyright 2014 by Philip N. Garner
 *
 * See the file COPYING for the licence associated with this software.
 *
 * Author(s):
 *   Phil Garner, September 2014
 */

#include <fstream>
#include <var.h>


namespace libvar
{
    /**
     * Ad-hoc parser for LDIF files
     */
    class LDIF : public varfile
    {
    public:
        LDIF();
        virtual var read(const char* iFile);
        virtual void write(const char* iFile, var iVar);

    private:
        void doLine(var iLine);
        enum {
            O,
            DN,
            OBJECTCLASS,
            GIVENNAME,
            SN,
            CN,
            MAIL,
            MODIFYTIMESTAMP,
            HOMEPHONE,
            MOBILE,
            TELEPHONENUMBER,
            FACSIMILETELEPHONENUMBER,
            L,
            POSTALCODE,
            C,
            STREET,
            MOZILLACUSTOM1,
            MOZILLACUSTOM4,
            MOZILLASECONDEMAIL,
            MOZILLANICKNAME,
            MOZILLAHOMELOCALITYNAME,
            MOZILLAHOMEPOSTALCODE,
            MOZILLAHOMECOUNTRYNAME,
            MOZILLAHOMESTATE,
            MOZILLAHOMESTREET,
            MOZILLAHOMESTREET2,
            MOZILLAWORKSTREET2,
            MOZILLAWORKURL
        };
        var mTokenMap;
        var mVar;
    };


    /**
     * The factory
     */
    void factory(varfile** oFile)
    {
        *oFile = new LDIF;
    }
}


using namespace libvar;


LDIF::LDIF()
{
    // Map strings to enums
    mTokenMap["o"] = O;
    mTokenMap["dn"] = DN;
    mTokenMap["objectclass"] = OBJECTCLASS;
    mTokenMap["givenName"] = GIVENNAME;
    mTokenMap["sn"] = SN;
    mTokenMap["cn"] = CN;
    mTokenMap["mail"] = MAIL;
    mTokenMap["modifytimestamp"] = MODIFYTIMESTAMP;
    mTokenMap["homePhone"] = HOMEPHONE;
    mTokenMap["mobile"] = MOBILE;
    mTokenMap["telephoneNumber"] = TELEPHONENUMBER;
    mTokenMap["facsimiletelephonenumber"] = FACSIMILETELEPHONENUMBER;
    mTokenMap["l"] = L;
    mTokenMap["postalCode"] = POSTALCODE;
    mTokenMap["c"] = C;
    mTokenMap["street"] = STREET;
    mTokenMap["mozillaCustom1"] = MOZILLACUSTOM1;
    mTokenMap["mozillaCustom4"] = MOZILLACUSTOM4;
    mTokenMap["mozillaSecondEmail"] = MOZILLASECONDEMAIL;
    mTokenMap["mozillaNickname"] = MOZILLANICKNAME;
    mTokenMap["mozillaHomeLocalityName"] = MOZILLAHOMELOCALITYNAME;
    mTokenMap["mozillaHomePostalCode"] = MOZILLAHOMEPOSTALCODE;
    mTokenMap["mozillaHomeCountryName"] = MOZILLAHOMECOUNTRYNAME;
    mTokenMap["mozillaHomeState"] = MOZILLAHOMESTATE;
    mTokenMap["mozillaHomeStreet"] = MOZILLAHOMESTREET;
    mTokenMap["mozillaHomeStreet2"] = MOZILLAHOMESTREET2;
    mTokenMap["mozillaWorkStreet2"] = MOZILLAWORKSTREET2;
    mTokenMap["mozillaWorkUrl"] = MOZILLAWORKURL;
//    mTokenMap[""] = ;
}

void LDIF::doLine(var iLine)
{
    // Split on colon
    var s = iLine.split(":");
    std::cout << s << std::endl;

    // Process the first field
    if (!mTokenMap.index(s[0]))
    {
        std::cout << s[0] << std::endl;
        throw std::runtime_error("LDIF::doLine: Unknown token");
    }
    switch (mTokenMap[s[0]].cast<int>())
    {
    case DN: // Distinguished name
        std::cout << "DN" << std::endl;
        break;
    case O:
        std::cout << "O" << std::endl;
        break;
    case OBJECTCLASS:
        std::cout << "OBJECTCLASS" << std::endl;
        break;
    case GIVENNAME:
        std::cout << "GIVENNAME" << std::endl;
        break;
    case SN:
        std::cout << "SN" << std::endl;
        break;
    case CN:
        std::cout << "CN" << std::endl;
        break;
    case MAIL:
        std::cout << "MAIL" << std::endl;
        break;
    case MODIFYTIMESTAMP:
        std::cout << "MODIFYTIMESTAMP" << std::endl;
        break;
    case HOMEPHONE:
        std::cout << "HOMEPHONE" << std::endl;
        break;
    case MOBILE:
        std::cout << "MOBILE" << std::endl;
        break;
    case TELEPHONENUMBER:
        std::cout << "TELEPHONENUMBER" << std::endl;
        break;
    case L:
        std::cout << "L" << std::endl;
        break;
    case POSTALCODE:
        std::cout << "POSTALCODE" << std::endl;
        break;
    case C:
        std::cout << "C" << std::endl;
        break;
    case STREET:
        std::cout << "STREET" << std::endl;
        break;
    case FACSIMILETELEPHONENUMBER:
        std::cout << "FACSIMILETELEPHONENUMBER" << std::endl;
        break;
    case MOZILLACUSTOM1:
        std::cout << "MOZILLACUSTOM1" << std::endl;
        break;
    case MOZILLACUSTOM4:
        std::cout << "MOZILLACUSTOM4" << std::endl;
        break;
    case MOZILLASECONDEMAIL:
        std::cout << "MOZILLASECONDEMAIL" << std::endl;
        break;
    case MOZILLANICKNAME:
        std::cout << "MOZILLANICKNAME" << std::endl;
        break;
    case MOZILLAHOMELOCALITYNAME:
        std::cout << "MOZILLAHOMELOCALITYNAME" << std::endl;
        break;
    case MOZILLAHOMEPOSTALCODE:
        std::cout << "MOZILLAHOMEPOSTALCODE" << std::endl;
        break;
    case MOZILLAHOMECOUNTRYNAME:
        std::cout << "MOZILLAHOMECOUNTRYNAME" << std::endl;
        break;
    case MOZILLAHOMESTATE:
        std::cout << "MOZILLAHOMESTATE" << std::endl;
        break;
    case MOZILLAHOMESTREET:
        std::cout << "MOZILLAHOMESTREET" << std::endl;
        break;
    case MOZILLAHOMESTREET2:
        std::cout << "MOZILLAHOMESTREET2" << std::endl;
        break;
    case MOZILLAWORKSTREET2:
        std::cout << "MOZILLAWORKSTREET2" << std::endl;
        break;
    case MOZILLAWORKURL:
        std::cout << "MOZILLAWORKURL" << std::endl;
        break;
    default:
        std::cout << "Unhandled: " << s[0] << std::endl;
        throw std::runtime_error("LDIF::doLine: Unhandled token");        
    }
}


var LDIF::read(const char* iFile)
{
    // Open the file
    std::ifstream is(iFile);
    if (is.fail())
        throw std::runtime_error("LDIF::read: Open failed");

    // Basic scan over file
    var line;
    while (line.getline(is))
        // Skip the blank lines for the moment
        if (line.size() > 0)
            doLine(line);

    return nil;
}


void LDIF::write(const char* iFile, var iVar)
{
}
