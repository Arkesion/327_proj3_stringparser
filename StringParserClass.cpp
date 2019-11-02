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

//set Tags function
int StringParserClass::setTags(const char *pStart, const char *pEnd) {
	if (pStart == NULL || pEnd == NULL)
		return ERROR_TAGS_NULL;

	int startLength = strlen(pStart);
	int endLength = strlen(pEnd);

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
	char *SST = pDataToSearchThru;
	char *EST = pDataToSearchThru + pDataToSearchThruLength;
	char *SET = pDataToSearchThru;
	char *EET = pDataToSearchThru + pDataToSearchThruLength;

	std::string aString = "";

	while (findTag(pStartTag, pDataToSearchThru, EST) == SUCCESS) {
		if (findTag(pEndTag, SET, EET) == FAIL)
			return SUCCESS;
		if (findTag(pEndTag, SET, EET) == SUCCESS) {
			while (EST != SET) {
				aString += *EST;
				EST++;
			}

			myVector.push_back(aString);
			aString = "";

			pDataToSearchThru = EET;
			pDataToSearchThruLength = strlen(pDataToSearchThru);

			EST = pDataToSearchThru + pDataToSearchThruLength;
			EET = pDataToSearchThru + pDataToSearchThruLength;
			SET = pDataToSearchThru;
			SST = pDataToSearchThru;
		}
	}
	return SUCCESS;
}


void StringParserClass::cleanup() {
	if (pStartTag) {
		delete[] (pStartTag);
		pStartTag = 0;
	}
	if (pEndTag) {
		delete[] (pStartTag);
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
