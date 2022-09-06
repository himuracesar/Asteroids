#include "ParserXMLCredits.h"

/**
* Constructor de ParserXMLCredits, aqui se inicializa la libreria(libxml) y se llena un vector
* ya con los valores extraidos del archivo
* @author Cesar Himura
*/
ParserXMLCredits::ParserXMLCredits()
{
    xmlInitParser();
	LIBXML_TEST_VERSION

	xmlKeepBlanksDefault( 0 );

	xmlDoc *doc = xmlParseFile("credits/credits.xml");

	if(doc == NULL)
        throw "failed to read the .xml file";


	xmlXPathContext *xpathCtx = xmlXPathNewContext(doc);

	if(xpathCtx == NULL)
        throw "failed to create the xpath context";

	xmlXPathObject *xpathObj = xmlXPathEvalExpression((xmlChar*)"/CREDITS/FONT", xpathCtx);

    font = (char*)(xpathObj->nodesetval->nodeTab[0]->children->content);

    xpathObj = xmlXPathEvalExpression((xmlChar*)"/CREDITS/TOTAL_GROUPS", xpathCtx);
	TOTAL_GROUPS = atoi((char*)(xpathObj->nodesetval->nodeTab[0]->children->content));

	xpathObj = xmlXPathEvalExpression((xmlChar*)"/CREDITS/SIZE_TITLE_GROUP", xpathCtx);
	SIZE_TITLE_GROUP = atoi((char*)(xpathObj->nodesetval->nodeTab[0]->children->content));

	xpathObj = xmlXPathEvalExpression((xmlChar*)"/CREDITS/SIZE_MEMBER_GROUP", xpathCtx);
	SIZE_MEMBER_GROUP = atoi((char*)(xpathObj->nodesetval->nodeTab[0]->children->content));

    stringstream ss;

	for(int indexGroup = 1; indexGroup <= TOTAL_GROUPS; indexGroup++)
    {
        sCredits scr;

        scr.first = "TG";

        ss.str("");
        ss << "/CREDITS/GROUP" << indexGroup << "/TITLE_GROUP";
        xpathObj = xmlXPathEvalExpression((xmlChar*)ss.str().c_str(), xpathCtx);

        scr.second = (char*)(xpathObj->nodesetval->nodeTab[0]->children->content);

        //libxml no puede leer un nodo vacio por lo que se le agrego esta etiqueta {WO_TG}.
        //Para manejarlo en C++ reasigno a un espacio porque no se puede comparar un string vacio
        if(scr.second == "{WO_TG}")
            scr.second = " ";

        vCredits.push_back(scr);

        ss.str("");
        ss << "/CREDITS/GROUP" << indexGroup << "/MEMBERS";
        xpathObj = xmlXPathEvalExpression((xmlChar*)ss.str().c_str(), xpathCtx);
        members = atoi((char*)(xpathObj->nodesetval->nodeTab[0]->children->content));

        for(int indexMember = 1; indexMember <= members; indexMember++)
        {
            scr.first = "MG";

            ss.str("");
            ss << "/CREDITS/GROUP" << indexGroup << "/MEMBER_GROUP" << indexMember;
            xpathObj = xmlXPathEvalExpression((xmlChar*)ss.str().c_str(), xpathCtx);

            scr.second = (char*)(xpathObj->nodesetval->nodeTab[0]->children->content);

            vCredits.push_back(scr);
        }//indexMember
    }//for indexGroup
}

ParserXMLCredits::~ParserXMLCredits()
{
}
