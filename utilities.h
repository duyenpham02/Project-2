// Project 2
// Duyen Pham
// COSC 2030 - 01
// Dec 14, 2018


#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include <cmath>
#include <ctime>
#include <algorithm>
#include <string>

using namespace std;


// Calculate the ID hash
size_t IdHash(size_t parentId, std::string rawEvent) {
	std::hash<std::string> str_hash;
	std::hash<size_t> size_t_hash;
	return (str_hash(rawEvent) ^ size_t_hash(parentId));
}

// Calculate RHASH and LHASH
size_t LRHash(size_t ID, size_t parentId, std::string rawEvent, size_t LHASH, size_t RHASH) {
	std::hash<std::string> str_hash;
	std::hash<size_t> size_t_hash;
	return (str_hash(rawEvent) ^ size_t_hash(ID) 
		^ size_t_hash(parentId) ^ size_t_hash(LHASH) 
		^ size_t_hash(RHASH));
}

// Seed the random-number generator with current time so that
// the numbers will be different every time we run.
// WARNING:  Only do this once per run!
// The static variable called enforces the one call per run 
// rule.
void randomizeSeed()
{
	static bool called = false;
	if (!called)
	{
		srand((unsigned int)(std::time(NULL)));
		called = true;
	}
}

#endif