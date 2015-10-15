/*
 * SpellBook.h
 *
 *  Created on: Oct 14, 2015
 *      Author: Jeremy
 */

#ifndef SPELLBOOK_H_
#define SPELLBOOK_H_

#include <string>
#include <vector>

#define FIRE 0
#define WATER 1
#define EARTH 2
#define AIR 3
#define SPIRIT 4

struct Spell {
	std::string name;
	int element;
	int baseDamage;
};

class SpellBook {
private:
	std::vector<Spell>* spellList;
public:
	SpellBook();
	int getSpellElement(std::string name);
	int getSpellBaseDamage(std::string name);
	void addSpell(std::string name, int element, int baseDmg);
	bool removeSpell(std::string name);
	int findSpell(std::string name);
};


#endif /* SPELLBOOK_H_ */
