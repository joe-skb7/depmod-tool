// TODO: Rewrite the whole file using "topological sort" algorithm

#include <iostream>
#include "sorter.h"

using namespace std;

Sorter::Sorter(const map<string, list<string> > &allModules)
	: m_pool(allModules)
{
}

bool Sorter::sort()
{
	cout << "---> Sorting modules..." << endl;

	// Main algorithm
	int curLevelNum = -1;
	while (!m_pool.empty()) {
		ModLevel curLevel;
		++curLevelNum;

		// Check all modules
		for (map<string, list<string> >::iterator it = m_pool.begin();
				it != m_pool.end(); /* do not incr. here*/) {
			string modName = it->first;
			if (isDepsMet(modName, curLevelNum)) {
				curLevel.push_back(modName);
				m_pool.erase(it++);
			} else {
				++it;
			}
		}

		if (curLevel.empty()) {
			cerr << "*** Error: fatal error in algorithm" << endl;
			cerr << "File: " << __FILE__ << "; line: " << __LINE__;
			return false;
		}
		m_tree.push_back(curLevel);
	}

	return true;
}

Sorter::ModTree Sorter::modTree() const
{
	return m_tree;
}

bool Sorter::isDepsMet(string modName, int curLevelNum) const
{
	list<string> deps = m_pool.at(modName);

	if (deps.empty())
		return true;

	if (curLevelNum == 0)
		return false; // deps not empty @ level0

	// Iterate over bottom levels, looking for dependencies; remove if found
	for (int i = 0; i < curLevelNum; ++i) {
		ModLevel checkLevel = m_tree.at(i);
		for (ModLevel::iterator it = checkLevel.begin();
				it != checkLevel.end(); ++it) {
			string checkMod = *it;
			// Check if this module is dep for modName
			for (list<string>::iterator itDep = deps.begin();
					itDep != deps.end(); /* don't incr */) {
				string checkDep = *itDep;
				if (checkDep == checkMod)
					deps.erase(itDep++);
				else
					++itDep;
			}
		}
	}

	return deps.empty();
}
