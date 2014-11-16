/*
 * Copyright 2014 by Idiap Research Institute, http://www.idiap.ch
 *
 * See the file COPYING for the licence associated with this software.
 *
 * Author(s):
 *   Phil Garner, September 2014
 */

#include "card.h"
#include <lv.h>

/*
 * Notes basically taken from http://tools.ietf.org/html/rfc6350
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

using namespace libvar;

Card::Card()
{
    //mCard[0] = "vcard";
    //mCard[1] = nil;
}

var Card::append()
{
    static var vcard = "vcard";
    var v;
    v[0] = vcard;
    v[1] = nil;
    mCards.push(v);
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
