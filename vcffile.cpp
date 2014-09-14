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
     * Ad-hoc parser for vCard files
     */
    class VCard : public varfile
    {
    public:
        VCard();
        virtual var read(const char* iFile);
        virtual void write(const char* iFile, var iVar);

    private:
        void doLine(var iLine);
        enum {
            BEGIN,
            END,
            VCARD,
            VERSION,
            EMAIL,
            N,
            FN,
            ORG,
            TEL,
            BDAY,
            ADR
        };
        var mTokenMap;
        var mVar;
    };


    /**
     * The factory
     */
    void factory(varfile** oFile)
    {
        *oFile = new VCard;
    }
}


using namespace libvar;


VCard::VCard()
{
    // Map strings to enums
    mTokenMap["BEGIN"] = BEGIN;
    mTokenMap["END"] = END;
    mTokenMap["VCARD"] = VCARD;
    mTokenMap["VERSION"] = VERSION;
    mTokenMap["EMAIL"] = EMAIL;
    mTokenMap["N"] = N;
    mTokenMap["FN"] = FN;
    mTokenMap["ORG"] = ORG;
    mTokenMap["TEL"] = TEL;
    mTokenMap["BDAY"] = BDAY;
    mTokenMap["ADR"] = ADR;
//    mTokenMap[""] = ;
}

void VCard::doLine(var iLine)
{
    // Get rid of the CR
    if (iLine.top() == '\r')
        iLine.pop();

    // Split on colon
    var s = iLine.split(":");
    std::cout << s << std::endl;

    // Split on semicolon
    var l = s[0].split(";");

    // Process the first field
    if (!mTokenMap.index(l[0]))
    {
        std::cout << l[0] << std::endl;
        throw std::runtime_error("VCard::doLine: Unknown token");
    }
    switch (mTokenMap[l[0]].cast<int>())
    {
    case BEGIN:
        std::cout << "BEGIN" << std::endl;
        break;
    case END:
        std::cout << "END" << std::endl;
        break;
    case VERSION:
        std::cout << "VERSION" << std::endl;
        break;
    case EMAIL:
        std::cout << "EMAIL" << std::endl;
        break;
    case N:
        std::cout << "N" << std::endl;
        break;
    case FN:
        std::cout << "FN" << std::endl;
        break;
    case ORG:
        std::cout << "ORG" << std::endl;
        break;
    case TEL:
        std::cout << "TEL" << std::endl;
        break;
    case BDAY:
        std::cout << "BDAY" << std::endl;
        break;
    case ADR:
        std::cout << "ADR" << std::endl;
        break;
    default:
        std::cout << "Unhandled: " << s[0] << std::endl;
        throw std::runtime_error("VCard::doLine: Unhandled token");        
    }
}


var VCard::read(const char* iFile)
{
    // Open the file
    std::ifstream is(iFile);
    if (is.fail())
        std::cout << "VCard::read: Open failed" << std::endl;

    // Read it.  vCard lines that begin with a space are continuations of the
    // previous line, at least in the later versions, so deal with that before
    // trying any parsing.
    var line;
    var next;
    line.getline(is);
    while (next.getline(is))
    {
        if (next[0] == ' ')
        {
            next.shift();
            line.append(next);
        }
        else
        {
            doLine(line);
            line = next;
            next = nil; // getline() will read into the current storage, so
                        // suppress that
        }
    }
    if (next)
        doLine(next);

    return nil;
}


void VCard::write(const char* iFile, var iVar)
{
}
