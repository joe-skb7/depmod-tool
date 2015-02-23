#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <list>
#include <map>

using namespace std;

class Parser
{
public:
	bool readFile(const char *filePath);
	bool parseFileContent();
	list<string> getDeps(const string &mod) const;
	list<string> getModulesList();
	map<string, list<string> > getParsedInfo() const;

private:
	list<string> &split(const string &s, char delim, list<string> &elems);
	list<string> split(const string &s, char delim);

	list<string> m_fileContent;		// file lines
	map<string, list<string> > m_modDeps;	// [module] = deps_list
};

#endif // PARSER_H
