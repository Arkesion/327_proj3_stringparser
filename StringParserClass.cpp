/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: Kevin Quirici
 */

#include <string>
#include <string.h>

#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"

using namespace KP_StringParserClass;

const int SIZE = 255;

//constructor
StringParserClass::StringParserClass(void) {
	pStartTag = new char[SIZE];
	pEndTag = new char[SIZE];
	areTagsSet = false;
}

//cleanup
StringParserClass::~StringParserClass(void) {
	cleanup();
	areTagsSet = false;
}

//Sets Tags function
int StringParserClass::setTags(const char *pStart, const char *pEnd) {
	if (pStart == NULL || pEnd == NULL)
		return ERROR_TAGS_NULL;

	int startLength = strlen(pStart);
	int endLength = strlen(pEnd);

	//Deep Copy for Start and end length
	pStartTag = new char[startLength + 1];
	pEndTag = new char[endLength + 1];
	strncpy(pStartTag, pStart, startLength);
	strncpy(pEndTag, pEnd, endLength);

	areTagsSet = true;
	return SUCCESS;
}

int StringParserClass::getDataBetweenTags(char *pDataToSearchThru, std::vector<std::string> &myVector) {

	myVector.clear();

	if (areTagsSet == false)
		return ERROR_TAGS_NULL;

	if (pDataToSearchThru == NULL)
		return ERROR_DATA_NULL;

	int pDataToSearchThruLength = strlen(pDataToSearchThru);
	//char *endOfData = (pDataToSearchThru + pDataToSearchThruLength);

	char *startStartTag = pDataToSearchThru;
	char *endStartTag = pDataToSearchThru + pDataToSearchThruLength;
	char *startEndTag = pDataToSearchThru;
	char *endEndTag = pDataToSearchThru + pDataToSearchThruLength;


	while (findTag(pStartTag, startStartTag, endStartTag) == SUCCESS) {

		if (findTag(pEndTag, startEndTag, endEndTag) == FAIL)
			return SUCCESS;

		std::string aString = "";

		while (endStartTag != startEndTag) {
			aString += *endStartTag;
			endStartTag++;
		}

		myVector.push_back(aString);

		pDataToSearchThru = endEndTag;
		pDataToSearchThruLength = strlen(pDataToSearchThru);

		startStartTag = endEndTag;
		endStartTag = endEndTag + pDataToSearchThruLength;
		startEndTag = endEndTag;
		endEndTag = endEndTag + pDataToSearchThruLength;
	}
	return SUCCESS;
}


void StringParserClass::cleanup() {
	if (pStartTag) {
		delete[] pStartTag;
	}
	if (pEndTag) {
		delete[] pEndTag;
		pEndTag = 0;
	}
}

int StringParserClass::findTag(char *pTagToLookFor, char *&pStart, char *&pEnd) {
	if (pStart == NULL || pEnd == NULL)
		return ERROR_TAGS_NULL;

	int arrayLength = strlen(pTagToLookFor);

	while (pStart != pEnd) {
		if (*pTagToLookFor == *pStart) {
			if (strncmp(pStart, pTagToLookFor, arrayLength) == 0) {
				pEnd = pStart + arrayLength;
				return SUCCESS;
			}
		}
		pStart++;
	}
	return FAIL;
}
