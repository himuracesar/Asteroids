#ifndef PARSERXMLCREDITS_H
    #define PARSERXMLCREDITS_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <libxml/xpath.h>

using namespace std;

/**
* Parsea un archivo XML donde se encuentran los creditos del juegos
* @author Cesar Himura
*/
class ParserXMLCredits
{
    private:
        int TOTAL_GROUPS;
        int SIZE_TITLE_GROUP;
        int SIZE_MEMBER_GROUP;
        int members;

        string font;

        typedef pair<string, string> sCredits;

        vector<sCredits> vCredits;

    public:
        ParserXMLCredits();
        ~ParserXMLCredits();
        string getFont(){return font;};
        int getSizeTitleGroup(){return SIZE_TITLE_GROUP;}
        int getSizeMemberGroup(){return SIZE_MEMBER_GROUP;};
        vector<sCredits> getCredits(){return vCredits;};
};

#endif // PARSERXMLCREDITS_H
