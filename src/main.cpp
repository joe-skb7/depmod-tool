/* Makes modules list ordered by dependencies.
 *
 * Input: unordered "input.txt" file (got after depmod.sh processing)
 * Output: ordered list of modules in "output.txt" file
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include "parser.h"
#include "sorter.h"

#define UNUSED(a) ((void)a)

using namespace std;

bool verbose_mode = false;

void printModulesOrdered(const Sorter::ModTree &modTree)
{
	ofstream outFile;
	outFile.open("output.txt", ios_base::out | ios_base::trunc);

	for (size_t i = 0; i < modTree.size(); ++i) {
		if (verbose_mode)
			cout << "*** Level " << i << " ***" << endl;
		Sorter::ModLevel curLevel = modTree.at(i);
		for (Sorter::ModLevel::iterator it = curLevel.begin();
				it != curLevel.end(); ++it) {
			outFile << *it << "\n";
			if (verbose_mode)
				cout << *it << endl;
		}
		if (verbose_mode)
			cout << endl;
	}

	outFile.close();
}

int main(int argc, char *argv[])
{
	// Parsing of cmdline
	if (argc == 2 && strcmp(argv[1], "-v") == 0)
		verbose_mode = true;

	// Parsing
	map<string, list<string> > parsedData;
	Parser *parser = new Parser;
	if (!parser->readFile("input.txt") || !parser->parseFileContent()) {
		delete parser;
		return EXIT_FAILURE;
	}
	parsedData = parser->getParsedInfo();
	delete parser;

	// Ordering modules by levels
	Sorter::ModTree modTree;
	Sorter *sorter = new Sorter(parsedData);
	if (!sorter->sort()) {
		delete sorter;
		return EXIT_FAILURE;
	}
	modTree = sorter->modTree();
	delete sorter;

	// Ordered modules to file/console
	printModulesOrdered(modTree);

	return EXIT_SUCCESS;
}
