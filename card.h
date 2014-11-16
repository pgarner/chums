/*
 * Copyright 2014 by Idiap Research Institute, http://www.idiap.ch
 *
 * See the file COPYING for the licence associated with this software.
 *
 * Author(s):
 *   Phil Garner, September 2014
 */

#ifndef CARD_H
#define CARD_H

#include <var.h>

namespace libvar
{
    class Card
    {
    public:
        Card();
        explicit operator var() const { return mCards; };
        var append();
        var quad(var iName);
    private:
        var mCards; ///< The array of cards
    };
}

#endif // CARD_H
