#ifndef SORTER_H
#define SORTER_H

#include <map>
#include <list>
#include <string>
#include <vector>

using namespace std;

class Sorter
{
public:
	typedef list<string> ModLevel;
	typedef vector<ModLevel> ModTree;

	explicit Sorter(const map<string, list<string> > &allModules);
	bool sort();
	ModTree modTree() const;

private:
	bool isDepsMet(string modName, int curLevelNum) const;

	map<string, list<string> > m_pool;
	ModTree m_tree;
};

#endif // SORTER_H
