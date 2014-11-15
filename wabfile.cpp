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
        var mContact; ///< The contact to be populated

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
        var mTokenMap;
        int mEntity;
        Card mCard;
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
}


void WAB::doElement(var iElem)
{
    if (iElem.atype() != TYPE_PAIR)
    {
        std::cout << "Skipping non-element" << std::endl;
        return;
    }

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
        switch (mEntity)
        {
        case NIL:
            throw std::runtime_error("WAB::doElement: Undefined VALUE entity");
        case CONTACTID:
            q = mCard.quad("uri");
            q[3] = data;
            break;
        case PHOTO:
            // Ignore photos for now
            //q = mCard.quad("photo");
            //q[3] = data;
            break;
        default:
            throw std::runtime_error("WAB::doElement: Unknown VALUE entity");
        }
        break;
    case LABELCOLLECTION:
        std::cout << "LabelCollection" << std::endl;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case LABEL:
        std::cout << "Label" << std::endl;
        break;

    case NOTES:
        q = mCard.quad("note");
        q[3] = data;
        break;
    case CREATIONDATE:
        q = mCard.quad("rev");
        q[3] = data;
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
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case ADDRESS:
        std::cout << "Address" << std::endl;
        break;

    case PHYSICALADDRESSCOLLECTION:
        mEntity = NIL;
        std::cout << "PhysicalAddressCollection" << std::endl;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case PHYSICALADDRESS:
        std::cout << "PhysicalAddress" << std::endl;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case COUNTRY:
        std::cout << "Country" << std::endl;
        break;
    case POSTALCODE:
        std::cout << "PostalCode" << std::endl;
        break;
    case LOCALITY:
        std::cout << "Locality" << std::endl;
        break;
    case STREET:
        std::cout << "Street" << std::endl;
        break;

    case NAMECOLLECTION:
        mEntity = NIL;
        std::cout << "NameCollection" << std::endl;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case NAME:
        std::cout << "Name" << std::endl;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case FORMATTEDNAME:
        std::cout << "FormattedName" << std::endl;
        break;
    case FAMILYNAME:
        std::cout << "FamilyName" << std::endl;
        break;
    case GIVENNAME:
        std::cout << "GivenName" << std::endl;
        break;

    case PHONENUMBERCOLLECTION:
        mEntity = NIL;
        std::cout << "PhoneNumberCollection" << std::endl;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case PHONENUMBER:
        std::cout << "PhoneNumber" << std::endl;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case NUMBER:
        std::cout << "Number" << std::endl;
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
        std::cout << "UrlCollection" << std::endl;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case URL:
        std::cout << "Url" << std::endl;
        break;

    case POSITIONCOLLECTION:
        mEntity = NIL;
        std::cout << "PositionCollection" << std::endl;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case POSITION:
        std::cout << "Position" << std::endl;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case COMPANY:
        std::cout << "Company" << std::endl;
        break;

    case DATECOLLECTION:
        mEntity = NIL;
        std::cout << "DateCollection" << std::endl;
        for (int i=0; i<data.size(); i++)
            doElement(data[i]);
        break;
    case DATE:
        std::cout << "Date" << std::endl;
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
