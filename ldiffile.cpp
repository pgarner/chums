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

#include "card.h"

namespace libvar
{
    /**
     * Ad-hoc parser for LDIF files
     *
     * ...actually probably quite tied to the type of LDIF that mozilla
     * exports.  That said, that's the file I want to parse.
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
            MOZILLACUSTOM2,
            MOZILLACUSTOM3,
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
        Card mCard;
    };


    /**
     * The factory
     */
    void factory(Module** oModule, var iArg)
    {
        *oModule = new LDIF;
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
    mTokenMap["mozillaCustom2"] = MOZILLACUSTOM2;
    mTokenMap["mozillaCustom3"] = MOZILLACUSTOM3;
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
    var s = iLine.split(":", 2);
    s[1].strip();

    // Process the first field
    if (!mTokenMap.index(s[0]))
    {
        std::cout << s[0] << std::endl;
        throw std::runtime_error("LDIF::doLine: Unknown token");
    }

    // The Mozilla stuff defaults to "work"; i.e., L, C, STREET etc.  The
    // qualified ones (MOZILLAHOMEPOSTALCODE etc.) are "home".
    var q;
    switch (mTokenMap[s[0]].cast<int>())
    {
    case DN:
        // Distinguished name
        //
        // This is the one that indicates a new card.  I'm not sure it's
        // guaranteed to come first, but let's go with it for now.
        mCard.append();
        break;
    case O:
        q = mCard.quad("org");
        q[3] = s[1];
        break;
    case OBJECTCLASS:
        // Ignore this one
        break;
    case GIVENNAME:
        q = mCard.name();
        q[3][1] = s[1];
        break;
    case SN:
        q = mCard.name();
        q[3][0] = s[1];
        break;
    case CN:
        q = mCard.quad("fn");
        q[3] = s[1];
        break;
    case MAIL:
    case MOZILLASECONDEMAIL:
        q = mCard.quad("email");
        q[3] = s[1];
        break;
    case MODIFYTIMESTAMP:
        q = mCard.quad("rev");
        q[3] = s[1];
        break;
    case HOMEPHONE:
        q = mCard.quad("tel");
        q[1]["type"].push("home");
        q[3] = s[1];
        break;
    case MOBILE:
        q = mCard.quad("tel");
        q[1]["type"].push("cell");
        q[3] = s[1];
        break;
    case TELEPHONENUMBER:
        q = mCard.quad("tel");
        q[3] = s[1];
        break;
    case L:
        q = mCard.adr("work");
        q[3][3] = s[1];
        break;
    case POSTALCODE:
        q = mCard.adr("work");
        q[3][5] = s[1];
        break;
    case C:
        q = mCard.adr("work");
        q[3][6] = s[1];
        break;
    case STREET:
        q = mCard.adr("work");
        q[3][2] = s[1];
        break;
    case FACSIMILETELEPHONENUMBER:
        q = mCard.quad("tel");
        q[1]["type"].push("fax");
        q[3] = s[1];
        break;
    case MOZILLACUSTOM1:
    case MOZILLACUSTOM2:
    case MOZILLACUSTOM3:
    case MOZILLACUSTOM4:
        q = mCard.quad("note");
        q[1]["type"].push("mozillacustom");
        q[3] = s[1];
        break;
    case MOZILLANICKNAME:
        q = mCard.quad("nickname");
        q[3] = s[1];
        break;
    case MOZILLAHOMELOCALITYNAME:
        q = mCard.adr("home");
        q[3][3] = s[1];
        break;
    case MOZILLAHOMEPOSTALCODE:
        q = mCard.adr("home");
        q[3][5] = s[1];
        break;
    case MOZILLAHOMECOUNTRYNAME:
        q = mCard.adr("home");
        q[3][6] = s[1];
        break;
    case MOZILLAHOMESTATE:
        q = mCard.adr("home");
        q[3][4] = s[1];
        break;
    case MOZILLAHOMESTREET:
        q = mCard.adr("home");
        q[3][2] = s[1];
        break;
    case MOZILLAHOMESTREET2:
        q = mCard.adr("home");
        q[3][2].append(", ");
        q[3][2].append(s[1]);
        break;
    case MOZILLAWORKSTREET2:
        // "Work street 1" is just "street"
        q = mCard.adr("work");
        q[3][2].append(", ");
        q[3][2].append(s[1]);
        break;
    case MOZILLAWORKURL:
        q = mCard.quad("url");
        q[1]["type"].push("work");
        q[3] = s[1];
        break;
    default:
        std::cout << "Unhandled: " << s[0] << std::endl;
        std::cout << s << std::endl;
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

    return var(mCard);
}


void LDIF::write(const char* iFile, var iVar)
{
}
