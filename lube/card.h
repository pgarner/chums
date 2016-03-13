/*
 * Copyright 2014 by Philip N. Garner
 *
 * See the file COPYING for the licence associated with this software.
 *
 * Author(s):
 *   Phil Garner, September 2014
 */

#ifndef CARD_H
#define CARD_H

#include <lube/var.h>

namespace libube
{
    class Card
    {
    public:
        explicit operator var() const { return mCards; };
        var append();
        var quad(var iName);
        var name();
        var adr(var iType=nil);
    private:
        var mCards; ///< The array of cards
    };
}

#endif // CARD_H
