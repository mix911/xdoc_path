#pragma once

#include <json_spirit.h>
#include <string>
#include <stddef.h>

const json_spirit::Value&   get_value(const std::string&  jpath, const json_spirit::Value&   value);
const json_spirit::mValue&  get_value(const std::string&  jpath, const json_spirit::mValue&  value);
const json_spirit::wValue&  get_value(const std::wstring& jpath, const json_spirit::wValue&  value);
const json_spirit::wmValue& get_value(const std::wstring& jpath, const json_spirit::wmValue& value);

json_spirit::Value&     get_value(const std::string&  jpath, json_spirit::Value&   value);
json_spirit::mValue&    get_value(const std::string&  jpath, json_spirit::mValue&  value); 
json_spirit::wValue&    get_value(const std::wstring& jpath, json_spirit::wValue&  value);
json_spirit::wmValue&   get_value(const std::wstring& jpath, json_spirit::wmValue& value);

const json_spirit::Object&   get_obj(const std::string&  jpath, const json_spirit::Value&   value);
const json_spirit::mObject&  get_obj(const std::string&  jpath, const json_spirit::mValue&  value);
const json_spirit::wObject&  get_obj(const std::wstring& jpath, const json_spirit::wValue&  value);
const json_spirit::wmObject& get_obj(const std::wstring& jpath, const json_spirit::wmValue& value);

json_spirit::Object&   get_obj(const std::string&  jpath,   json_spirit::Value&   value);
json_spirit::mObject&  get_obj(const std::string&  jpath,   json_spirit::mValue&  value);
json_spirit::wObject&  get_obj(const std::wstring& jpath,   json_spirit::wValue&  value);
json_spirit::wmObject& get_obj(const std::wstring& jpath,   json_spirit::wmValue& value);

const json_spirit::Array&   get_array(const std::string&  jpath, const json_spirit::Value&   value);
const json_spirit::mArray&  get_array(const std::string&  jpath, const json_spirit::mValue&  value); 
const json_spirit::wArray&  get_array(const std::wstring& jpath, const json_spirit::wValue&  value);
const json_spirit::wmArray& get_array(const std::wstring& jpath, const json_spirit::wmValue& value);

json_spirit::Array&   get_array(const std::string&  jpath, json_spirit::Value&   value);
json_spirit::mArray&  get_array(const std::string&  jpath, json_spirit::mValue&  value); 
json_spirit::wArray&  get_array(const std::wstring& jpath, json_spirit::wValue&  value);
json_spirit::wmArray& get_array(const std::wstring& jpath, json_spirit::wmValue& value);

const std::string&  get_str(const std::string&  jpath, const json_spirit::Value&   value);
const std::string&  get_str(const std::string&  jpath, const json_spirit::mValue&  value);
const std::wstring& get_str(const std::wstring& jpath, const json_spirit::wValue&  value);
const std::wstring& get_str(const std::wstring& jpath, const json_spirit::wmValue& value);

std::string&  get_str(const std::string&  jpath, json_spirit::Value&   value);
std::string&  get_str(const std::string&  jpath, json_spirit::mValue&  value);
std::wstring& get_str(const std::wstring& jpath, json_spirit::wValue&  value);
std::wstring& get_str(const std::wstring& jpath, json_spirit::wmValue& value);

bool get_bool(const std::string&  jpath, const json_spirit::Value&   value);
bool get_bool(const std::string&  jpath, const json_spirit::mValue&  value);
bool get_bool(const std::wstring& jpath, const json_spirit::wValue&  value);
bool get_bool(const std::wstring& jpath, const json_spirit::wmValue& value);

int get_int(const std::string&  jpath, const json_spirit::Value&   value);
int get_int(const std::string&  jpath, const json_spirit::mValue&  value);
int get_int(const std::wstring& jpath, const json_spirit::wValue&  value);
int get_int(const std::wstring& jpath, const json_spirit::wmValue& value);

std::int64_t get_int64(const std::string&  jpath, const json_spirit::Value&   value);
std::int64_t get_int64(const std::string&  jpath, const json_spirit::mValue&  value);
std::int64_t get_int64(const std::wstring& jpath, const json_spirit::wValue&  value);
std::int64_t get_int64(const std::wstring& jpath, const json_spirit::wmValue& value);

std::uint64_t get_uint64(const std::string&  jpath, const json_spirit::Value&   value);
std::uint64_t get_uint64(const std::string&  jpath, const json_spirit::mValue&  value);
std::uint64_t get_uint64(const std::wstring& jpath, const json_spirit::wValue&  value);
std::uint64_t get_uint64(const std::wstring& jpath, const json_spirit::wmValue& value);

double get_real(const std::string&  jpath, const json_spirit::Value&   value);
double get_real(const std::string&  jpath, const json_spirit::mValue&  value);
double get_real(const std::wstring& jpath, const json_spirit::wValue&  value);
double get_real(const std::wstring& jpath, const json_spirit::wmValue& value);
