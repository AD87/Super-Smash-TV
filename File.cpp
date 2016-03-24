#pragma once

#include <assert.h>
#include "File.h"
#include "ReportError.h"

File::File() :
m_lineNumber(0)
{

}

bool File::isEndOfFile(){
	return m_file.eof();
}

void File::reportError(const std::string& errorMessage)
{
	std::string string=
		m_filename
		+ " line: "
		+ std::to_string(m_lineNumber)
		+ ": "
		+ errorMessage;

	::ReportError(string);
}

bool File::openRead(const std::string& _filename)
{
	m_file.open(_filename);
	assert(m_file.is_open());
	m_filename = _filename;
	return m_file.is_open();
}

bool File::getInt(int* result){
	std::string str;
	if (getString(&str)){
		*result = atoi(str.c_str());
		return true;
	}
	return false;
}

bool File::getFloat(float* result){
	std::string str;
	if (getString(&str)){
		*result = static_cast<float> (atof(str.c_str()));
		return true;
	}
	return false;
}

bool File::getString(std::string* result){
	assert(m_file.is_open());

	while (true){
		if (m_file.eof()){
			return false;
		}
		m_lineNumber++;

		std::string str;
		std::getline(m_file, str);

		if (str.empty()){
			continue;
		}

		if (str[0] == '#'){
			continue;
		}

		*result = str;
		break;
	}

	return true;
}