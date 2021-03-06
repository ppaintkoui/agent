/*
 * XML.h
 *
 *  Created on: 01/sep/2014
 *      Author: Stefano Ceccherini
 */

#ifndef XML_H_
#define XML_H_

#include <string>

namespace tinyxml2 {
	class XMLDocument;
};

class XML {
public:
	static std::string ToString(const tinyxml2::XMLDocument& document);
	static bool Compress(const tinyxml2::XMLDocument& document, char*& destination, size_t& destLength);
	static bool Uncompress(const char* source, size_t sourceLen, tinyxml2::XMLDocument& document);
	static std::string GetTextElementValue(const tinyxml2::XMLDocument& document, std::string elementName);
};

#endif /* XML_H_ */
