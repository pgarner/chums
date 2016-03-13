/*
 * Copyright 2014 by Philip N. Garner
 *
 * See the file COPYING for the licence associated with this software.
 *
 * Author(s):
 *   Phil Garner, September 2014
 */

#include "card.h"
#include <lube.h>

/*
 * Notes basically taken from http://tools.ietf.org/html/rfc6350
 *
 * N spec:
 *
 * The structured property value corresponds, in sequence, to
 *
 *   0: Family Names (also known as surnames)
 *   1: Given Names
 *   2: Additional Names
 *   3: Honorific Prefixes
 *   4: Honorific Suffixes
 *
 * The text components are separated by the SEMICOLON character (U+003B).
 * Individual text components can include multiple text values separated by the
 * COMMA character (U+002C).  This property is based on the semantics of the
 * X.520 individual name attributes [CCITT.X520.1988].  The property SHOULD be
 * present in the vCard object when the name of the object the vCard represents
 * follows the X.520 model.
 *
 * ADR spec:
 *
 * The structured type value consists of a sequence of address components.  The
 * component values MUST be specified in their corresponding position.  The
 * structured type value corresponds, in sequence, to
 *
 *   0: the post office box;
 *   1: the extended address (e.g., apartment or suite number);
 *   2: the street address;
 *   3: the locality (e.g., city);
 *   4: the region (e.g., state or province);
 *   5: the postal code;
 *   6: the country name (full name in the language specified in Section 5.1).
 *
 * When a component value is missing, the associated component separator MUST
 * still be specified.
 *
 * Phil: So, those 7 fields amount to six semicolons in the ADR field.
 */

using namespace libube;

var Card::append()
{
    // Append a vCard to the list
    static var vcard = "vcard";
    var v;
    v[0] = vcard;
    v[1] = nil;
    mCards.push(v);

    // Version is mandatory, and is always 4.0
    static var version = "version";
    static var v4 = "4.0";
    var q = quad(version);
    q[3] = v4;
    return mCards.top();
}

var Card::quad(var iName)
{
    static var text = "text";
    var q;
    q[0] = iName;
    q.resize(4);
    q[2] = text;
    mCards.top()[1].push(q);
    return q;
}

/**
 * Finds the first quad called "n", or creates it
 */
var Card::name()
{
    var qa = mCards.top()[1];
    for (int i=0; i<qa.size(); i++)
        if (qa[i][0] == "n")
            return qa[i];
    var q = quad("n");
    q[3].resize(5);
    return q;
}

/**
 * Finds the first quad called "adr" with ["type"]=iType, or creates it
 */
var Card::adr(var iType)
{
    var qa = mCards.top()[1];
    for (int i=0; i<qa.size(); i++)
        if (qa[i][0] == "adr")
        {
            if (iType)
            {
                if ( qa[i][1] &&
                     qa[i][1].index("type") &&
                     qa[i][1]["type"].index(iType) )
                    return qa[i];
            }
            else
                return qa[i];
        }
    var q = quad("adr");
    if (iType)
        q[1]["type"].push(iType);
    q[3].resize(7);
    return q;
}
