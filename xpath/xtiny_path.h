#pragma once

#include <tinyxml.h>
#include <vector>
#include <string>

std::vector<TiXmlBase*> request_by_xpath(const std::string& xpath, TiXmlNode* node);
std::vector<const TiXmlBase*> request_by_xpath(const std::string& xpath, const TiXmlNode* node);
