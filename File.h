#pragma once

#include <fstream>
#include <string>

class File
{
public:
	File();

	bool openRead(const std::string& _filename);

	bool getInt(int* result);
	bool getFloat(float* result);
	bool getString(std::string* result);

	bool isEndOfFile();
	void reportError(const std::string& errorMessage);

private:
	std::ifstream m_file;
	std::string m_filename;
	int m_lineNumber;

};