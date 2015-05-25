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
     * Ad-hoc parser for vCard files
     */
    class VCard : public File
    {
    public:
        VCard();
        virtual var read(var iFile);
        virtual void write(var iFile, var iVar);

    private:
        void doLine(var iLine);
        void doAttr(var iQuad, var iAttr);
        void writeCard(std::ofstream& iOS, var iVar);
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
            ADR,
            TITLE,
            PHOTO,
            REV,
            URL,
            NOTE
        };
        enum {
            TYPE,
            VALUE,
            CELL,
            HOME,
            WORK,
            VOICE,
            PREF,
            XINTERNET,
            CHARSET,
            ENCODING,
            MEDIATYPE,
            LABEL
        };
        var mTokenMap;
        var mAttrMap;
        Card mCard;
        var mVersion;
    };


    /**
     * The factory
     */
    void factory(Module** oModule, var iArg)
    {
        *oModule = new VCard;
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
    mTokenMap["TITLE"] = TITLE;
    mTokenMap["PHOTO"] = PHOTO;
    mTokenMap["REV"] = REV;
    mTokenMap["URL"] = URL;
    mTokenMap["NOTE"] = NOTE;
//    mTokenMap[""] = ;
    mAttrMap["TYPE"] = TYPE;
    mAttrMap["VALUE"] = VALUE;
    mAttrMap["CELL"] = CELL;
    mAttrMap["HOME"] = HOME;
    mAttrMap["WORK"] = WORK;
    mAttrMap["VOICE"] = VOICE;
    mAttrMap["PREF"] = PREF;
    mAttrMap["X-INTERNET"] = XINTERNET;
    mAttrMap["CHARSET"] = CHARSET;
    mAttrMap["ENCODING"] = ENCODING;
    mAttrMap["MEDIATYPE"] = MEDIATYPE;
    mAttrMap["LABEL"] = LABEL;
}

void VCard::doLine(var iLine)
{
    // Get rid of the CR
    if (iLine.top() == '\r')
        iLine.pop();

    // Split on first colon
    var s = iLine.split(":", 2);

    // Split on semicolon
    var l = s[0].split(";");
    var t = l.shift();

    // Process the first field
    if (!mTokenMap.index(t))
    {
        std::cout << t << std::endl;
        throw error("VCard::doLine: Unknown token");
    }

    var q;
    switch (mTokenMap[t].cast<int>())
    {
    case BEGIN:
        // Should perhaps initialise a temporary
        mCard.append();
        break;
    case END:
        // Should perhaps transfer temporary to full array
        break;
    case VERSION:
        // The version in memory is always the latest vCard version,
        // corresponding directly to a jCard.  This is the version of the file
        // being read.
        mVersion = s[1];
        break;
    case EMAIL:
        q = mCard.quad("email");
        doAttr(q, l);
        q[3] = s[1];
        break;
    case N:
        q = mCard.quad("n");
        doAttr(q, l);
        q[3] = s[1].split(";");
        break;
    case FN:
        q = mCard.quad("fn");
        doAttr(q, l);
        q[3] = s[1];
        break;
    case ORG:
        q = mCard.quad("org");
        doAttr(q, l);
        q[3] = s[1];
        break;
    case TEL:
        q = mCard.quad("tel");
        doAttr(q, l);
        q[3] = s[1];
        break;
    case BDAY:
        q = mCard.quad("bday");
        doAttr(q, l);
        q[3] = s[1];
        break;
    case ADR:
        q = mCard.quad("adr");
        doAttr(q, l);
        q[3] = s[1].split(";");
        break;
    case TITLE:
        q = mCard.quad("title");
        doAttr(q, l);
        q[3] = s[1];
        break;
    case PHOTO:
        q = mCard.quad("photo");
        doAttr(q, l);
        q[3] = s[1];
        break;
    case REV:
        q = mCard.quad("rev");
        doAttr(q, l);
        q[3] = s[1];
        break;
    case URL:
        q = mCard.quad("url");
        doAttr(q, l);
        q[3] = s[1];
        break;
    case NOTE:
        q = mCard.quad("note");
        doAttr(q, l);
        q[3] = s[1];
        break;
    default:
        std::cout << "Unhandled: " << s[0] << std::endl;
        throw error("VCard::doLine: Unhandled token");        
    }
}

void VCard::doAttr(var iQuad, var iAttr)
{
    for (int i=0; i<iAttr.size(); i++)
    {
        var a = iAttr[i].split("=", 2);
        var t = a[0];
        if (!mAttrMap.index(t))
        {
            std::cout << t << std::endl;
            throw error("VCard::doAttr: Unknown token");
        }

        var tmp;
        switch (mAttrMap[t].cast<int>())
        {
            // Version 2.1 legacy types
        case CELL:
            iQuad[1]["type"].push("cell");
            break;
        case HOME:
            iQuad[1]["type"].push("home");
            break;
        case WORK:
            iQuad[1]["type"].push("work");
            break;
        case VOICE:
            iQuad[1]["type"].push("voice");
            break;
        case PREF:
            iQuad[1]["type"].push("pref");
            break;

            // Version 3 and later type encodings
        case TYPE:
            tmp = a[1].tolower().split(",");
            for (int i=0; i<tmp.size(); i++)
                if (tmp[i] == "pref")
                    iQuad[1]["pref"] = "1";
                else
                    iQuad[1]["type"].push(tmp[i]);
            break;
        case VALUE:
            iQuad[2] = a[1];
            break;
        case MEDIATYPE:
            iQuad[1]["mediatype"] = a[1];
            break;
        case LABEL:
            iQuad[1]["label"] = a[1];
            break;

            // Whacko encoding stuff
        case XINTERNET:
            std::cout << t << std::endl;
            break;
        case CHARSET:
            std::cout << t << std::endl;
            break;
        case ENCODING:
            std::cout << t << std::endl;
            break;
        default:
            std::cout << "Unhandled: " << iAttr << std::endl;
            throw error("VCard::doAttr: Unhandled token");
        }
    }
}

var VCard::read(var iFile)
{
    // Open the file
    std::ifstream is(iFile.str());
    if (is.fail())
        throw error("VCard::read: Open failed");

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
    if (line)
        doLine(line);

    return var(mCard);
}


void VCard::write(var iFile, var iVar)
{
    // vCards are required to use CRLF as line ends.  The natural line end is
    // machine dependent ('\n' is translated in text mode to the right thing).
    // Rather, guarantee CRLF by opening in binary mode and writing CRLF
    // explicitly.  https://en.wikipedia.org/wiki/Newline
    std::ofstream os(iFile.str(), std::ofstream::out | std::ofstream::binary);
    if (os.fail())
        throw error("vcffile::write(): Open failed");

    var v = var(iVar);
    for (int i=0; i<v.size(); i++)
        writeCard(os, v[i]);
}

void VCard::writeCard(std::ofstream& iOS, var iVar)
{
    static char crlf[] = "\r\n";
    if (iVar[0] != "vcard")
        throw error("vcffile::writeCard(): Not a vCard");
    iOS << "BEGIN:VCARD" << crlf;
    for (int i=0; i<iVar[1].size(); i++)
    {
        var v = iVar[1][i];
        iOS << v[0].copy().toupper().str();
        for (int j=0; j<v[1].size(); j++)
        {
            iOS << ";" << v[1].key(j).copy().toupper().str() << "=";
            iOS << ( v[1][j].atype() == TYPE_CHAR
                     ? v[1][j].str()
                     : v[1][j].join(",").str() );
        }
        if (v[2] != "text")
            iOS << ";" << "VALUE=" << v[2].str();
        iOS << ":";
        iOS << (v[3].atype() == TYPE_CHAR ? v[3].str() : v[3].join(";").str());
        iOS << crlf;
    }
    iOS << "END:VCARD" << crlf;
}
