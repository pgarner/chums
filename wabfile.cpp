/*
 * Copyright 2014 by Philip N. Garner
 *
 * See the file COPYING for the licence associated with this software.
 *
 * Author(s):
 *   Phil Garner, September 2014
 */

#include <var.h>
#include "card.h"

namespace libvar
{
    /**
     * Ad-hoc parser for Windows Address Book (wab.exe) files
     */
    class WAB : public varfile
    {
    public:
        WAB();
        virtual var read(const char* iFile);
        virtual void write(const char* iFile, var iVar);

    private:
        void doElement(var iElem);
        enum {
            // NIL
            NIL = 0,
            
            // Common elements
            VALUE,
            LABELCOLLECTION,
            LABEL,

            // Header
            CONTACT,
            NOTES,
            CREATIONDATE,
            EXTENDED,

            // Contact ID
            CONTACTIDCOLLECTION,
            CONTACTID,

            // EMail
            EMAILADDRESSCOLLECTION,
            EMAILADDRESS,
            ADDRESS,

            // Physical address
            PHYSICALADDRESSCOLLECTION,
            PHYSICALADDRESS,
            COUNTRY,
            POSTALCODE,
            LOCALITY,
            STREET,

            // Name
            NAMECOLLECTION,
            NAME,
            FORMATTEDNAME,
            FAMILYNAME,
            GIVENNAME,

            // Phone
            PHONENUMBERCOLLECTION,
            PHONENUMBER,
            NUMBER,

            // Photo
            PHOTOCOLLECTION,
            PHOTO,

            // URL
            URLCOLLECTION,
            URL,

            // Position
            POSITIONCOLLECTION,
            POSITION,
            COMPANY,

            // Date
            DATECOLLECTION,
            DATE
        };
        enum {
            // Label types
            PREFERRED,
            BUSINESS,
            PERSONAL,
            FAX,
            VOICE,
            CELLULAR,
            USERTILE,
            BIRTHDAY
        };
        var mTokenMap;
        var mLabelMap;
        int mEntity;
        Card mCard;
        var mQuad;
    };


    /**
     * The factory
     */
    void factory(varfile** oFile)
    {
        *oFile = new WAB;
    }
}


using namespace libvar;


WAB::WAB()
{
    // Map strings to enums
    mTokenMap["c:Value"] = VALUE;
    mTokenMap["c:LabelCollection"] = LABELCOLLECTION;
    mTokenMap["c:Label"] = LABEL;

    mTokenMap["c:contact"] = CONTACT;
    mTokenMap["c:Notes"] = NOTES;
    mTokenMap["c:CreationDate"] = CREATIONDATE;
    mTokenMap["c:Extended"] = EXTENDED;

    mTokenMap["c:ContactIDCollection"] = CONTACTIDCOLLECTION;
    mTokenMap["c:ContactID"] = CONTACTID;

    mTokenMap["c:EmailAddressCollection"] = EMAILADDRESSCOLLECTION;
    mTokenMap["c:EmailAddress"] = EMAILADDRESS;
    mTokenMap["c:Address"] = ADDRESS;

    mTokenMap["c:PhysicalAddressCollection"] = PHYSICALADDRESSCOLLECTION;
    mTokenMap["c:PhysicalAddress"] = PHYSICALADDRESS;
    mTokenMap["c:Country"] = COUNTRY;
    mTokenMap["c:PostalCode"] = POSTALCODE;
    mTokenMap["c:Locality"] = LOCALITY;
    mTokenMap["c:Street"] = STREET;

    mTokenMap["c:NameCollection"] = NAMECOLLECTION;
    mTokenMap["c:Name"] = NAME;
    mTokenMap["c:FormattedName"] = FORMATTEDNAME;
    mTokenMap["c:FamilyName"] = FAMILYNAME;
    mTokenMap["c:GivenName"] = GIVENNAME;

    mTokenMap["c:PhoneNumberCollection"] = PHONENUMBERCOLLECTION;
    mTokenMap["c:PhoneNumber"] = PHONENUMBER;
    mTokenMap["c:Number"] = NUMBER;

    mTokenMap["c:PhotoCollection"] = PHOTOCOLLECTION;
    mTokenMap["c:Photo"] = PHOTO;

    mTokenMap["c:UrlCollection"] = URLCOLLECTION;
    mTokenMap["c:Url"] = URL;

    mTokenMap["c:PositionCollection"] = POSITIONCOLLECTION;
    mTokenMap["c:Position"] = POSITION;
    mTokenMap["c:Company"] = COMPANY;

    mTokenMap["c:DateCollection"] = DATECOLLECTION;
    mTokenMap["c:Date"] = DATE;
//    mTokenMap[""] = ;

    mLabelMap["Preferred"] = PREFERRED;
    mLabelMap["Business"] = BUSINESS;
    mLabelMap["Personal"] = PERSONAL;
    mLabelMap["Fax"] = FAX;
    mLabelMap["Voice"] = VOICE;
    mLabelMap["Cellular"] = CELLULAR;
    mLabelMap["UserTile"] = USERTILE;
    mLabelMap["wab:Birthday"] = BIRTHDAY;
}


void WAB::doElement(var iElem)
{
    if (iElem.atype() != TYPE_PAIR)
        // Not an element; probably whitespace
        return;

    var name = iElem.at("name");
    var data = iElem.at("data");
    if (!mTokenMap.index(name))
    {
        std::cout << iElem.at("name") << std::endl;
        throw std::runtime_error("WAB::doElement: Unknown token");
    }

    var q;
    switch (mTokenMap[name].cast<int>())
    {
    case VALUE:
        // Value is a generic element that can apply to several entities.
        switch (mEntity)
        {
        case NIL:
            throw std::runtime_error("WAB::doElement: Undefined VALUE entity");
        case CONTACTID:
            mQuad[3] = data[0];
            break;
        case URL:
            mQuad[3] = data[0];
            break;
        case PHOTO:
            // Ignore photos for now
            //q = mCard.quad("photo");
            //q[3] = data;
            break;
        case DATE:
            mQuad[3] = data[0];
            break;
        default:
            throw std::runtime_error("WAB::doElement: Unknown VALUE entity");
        }
        break;
    case LABELCOLLECTION:
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case LABEL:
        if (!mLabelMap.index(data[0]))
        {
            std::cout << data[0] << std::endl;
            throw std::runtime_error("WAB::doElement: Unknown LABEL token");
        }
        switch (mLabelMap[data[0]].cast<int>())
        {
        case PREFERRED:
            mQuad[1]["pref"] = "1";
            break;
        case BUSINESS:
            mQuad[1]["type"].push("work");
            break;
        case PERSONAL:
            mQuad[1]["type"].push("home");
            break;
        case FAX:
            mQuad[1]["type"].push("fax");
            break;
        case VOICE:
            mQuad[1]["type"].push("voice");
            break;
        case CELLULAR:
            mQuad[1]["type"].push("cell");
            break;
        case USERTILE:
            break;
        case BIRTHDAY:
            mQuad[0] = "bday";
            break;
        default:
            throw std::runtime_error("WAB::doElement: Unknown LABEL");
        }
        break;

    case NOTES:
        mQuad = mCard.quad("note");
        mQuad[3] = data[0];
        break;
    case CREATIONDATE:
        mQuad = mCard.quad("rev");
        mQuad[3] = data[0];
        break;
    case EXTENDED:
        // Ignore this tag
        break;

    case CONTACTIDCOLLECTION:
        mEntity = NIL;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case CONTACTID:
        mEntity = CONTACTID;
        mQuad = mCard.quad("uid");
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;

    case EMAILADDRESSCOLLECTION:
        mEntity = NIL;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case EMAILADDRESS:
        mEntity = EMAILADDRESS;
        mQuad = mCard.quad("email");
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case ADDRESS:
        mQuad[3] = data[0];
        break;

    case PHYSICALADDRESSCOLLECTION:
        mEntity = NIL;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case PHYSICALADDRESS:
        mEntity = PHYSICALADDRESS;
        mQuad = mCard.quad("adr");
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case COUNTRY:
        mQuad[3][6] = data[0];
        break;
    case POSTALCODE:
        mQuad[3][5] = data[0];
        break;
    case LOCALITY:
        mQuad[3][3] = data[0];
        break;
    case STREET:
        mQuad[3][2] = data.join("");
        break;

    case NAMECOLLECTION:
        mEntity = NIL;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case NAME:
        mEntity = NAME;
        mQuad = mCard.quad("n");
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case FORMATTEDNAME:
        // Add an extra quad in the middle of assigning family and given names
        // to the NAME quad.  This might cause trouble if there is metadata.
        q = mCard.quad("fn");
        q[3] = data[0];
        break;
    case FAMILYNAME:
        if (mQuad[3])
            mQuad[3].unshift(data[0]);
        else
            mQuad[3][0] = data[0];
        break;
    case GIVENNAME:
        mQuad[3].push(data[0]);
        break;

    case PHONENUMBERCOLLECTION:
        mEntity = NIL;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case PHONENUMBER:
        mEntity = PHONENUMBER;
        mQuad = mCard.quad("tel");
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case NUMBER:
        mQuad[3] = data[0];
        break;

    case PHOTOCOLLECTION:
        mEntity = NIL;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case PHOTO:
        mEntity = PHOTO;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;

    case URLCOLLECTION:
        mEntity = NIL;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case URL:
        mEntity = URL;
        mQuad = mCard.quad("url");
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;

    case POSITIONCOLLECTION:
        mEntity = NIL;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case POSITION:
        mEntity = POSITION;
        mQuad = mCard.quad("org");
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case COMPANY:
        mQuad[3] = data[0];
        break;

    case DATECOLLECTION:
        mEntity = NIL;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case DATE:
        mEntity = DATE;
        mQuad = mCard.quad("DATE");
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;

    default:
        std::cout << "Unhandled: " << iElem.at("name") << std::endl;
        throw std::runtime_error("WAB::doElement: Unhandled token");        
    }
}


var WAB::read(const char* iFile)
{
    // Read the XML file
    vfile mscontact("xml");
    var contact = mscontact.read("example.contact");

    // Walk the DOM
    if (contact.at("name") != "c:contact")
        throw std::runtime_error("WAB::read: Not a contact");
    var data = contact["data"];
    mCard.append();
    for (int i=0; i<data.size(); i++)
        doElement(data[i]);
    
    return var(mCard);
}


void WAB::write(const char* iFile, var iVar)
{
}
