#include <cctype>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "parser.h"

using namespace std;

bool Parser::readFile(const char *filePath)
{
	cout << "---> Reading input file..." << endl;

	m_fileContent.clear();

	ifstream file(filePath);
	if (!file.is_open()) {
		cerr << "*** Error: Unable to open file" << endl;
		return false;
	}

	string line;
	while (file.good()) {
		getline(file, line);
		if (line.empty())
			continue;
		m_fileContent.push_back(line);
	}

	file.close();

	return true;
}

bool Parser::parseFileContent()
{
	cout << "---> Parse input file content..." << endl;

	m_modDeps.clear();

	for (list<string>::iterator it = m_fileContent.begin();
			it != m_fileContent.end(); ++it) {
		string s = *it;

		// Separate by ':'
		unsigned delimPos = s.find(':');
		if (delimPos == std::string::npos) {
			cerr << "*** Error: Delimeter not found at line: "
					<< s << endl;
			return false;
		}
		string mod(s, 0, delimPos);
		string depsStr(s, delimPos + 1, s.length() - delimPos);

		// Remove whitespaces
		string::iterator remIt;
		remIt = remove_if(mod.begin(), mod.end(), ::isspace);
		mod.erase(remIt, mod.end());
		remIt = remove_if(depsStr.begin(), depsStr.end(), ::isspace);
		depsStr.erase(remIt, depsStr.end());

		// Parse dependencies
		list<string> deps = split(depsStr, ',');

		// Add entry: [module] = dependecies list
		m_modDeps[mod] = deps;
	}

	return true;
}


list<string> Parser::getDeps(const string &mod) const
{
	return m_modDeps.at(mod);
}


list<string> Parser::getModulesList()
{
	list<string> modules;

	for (map<string, list<string> >::iterator it = m_modDeps.begin();
			it != m_modDeps.end(); ++it) {
		modules.push_back(it->first);
	}

	return modules;
}

map<string, list<string> > Parser::getParsedInfo() const
{
	return m_modDeps;
}

// private

list<string> &Parser::split(const string &s, char delim, list<string> &elems)
{
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim))
		elems.push_back(item);

	return elems;
}

list<string> Parser::split(const string &s, char delim)
{
	list<string> elems;
	return split(s, delim, elems);
}
