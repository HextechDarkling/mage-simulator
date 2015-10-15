/*
 * SpellBook.cpp
 *
 *  Created on: Oct 14, 2015
 *      Author: Jeremy
 */

#include "SpellBook.h"

SpellBook::SpellBook() : spellList(new std::vector<Spell>()) {}

void SpellBook::addSpell(std::string name, int element, int baseDmg) {
	Spell newspell;
	newspell.name = name;
	newspell.element = element;
	newspell.baseDamage = baseDmg;
	spellList->push_back(newspell);
}

bool SpellBook::removeSpell(std::string name) {
	bool removed = 0;
	int index = findSpell(name);
	if(index >= 0) {
		spellList->erase(spellList->begin() + index);
		removed = 1;
	}
	return removed;
}

int SpellBook::findSpell(std::string name) {
	int index = -1;
	int i = 0;
	for(std::vector<Spell>::iterator it = spellList->begin(); it != spellList->end(); it++,i++) {
			Spell s = *it;
			if (s.name.compare(name) == 0) {
				index = i;
				break;
			}
		}
	return index;
}

int SpellBook::getSpellElement(std::string name) {
	int index = findSpell(name);
	if(index >= 0) {
		return spellList->at(index).element;
	}
	return index;
}

int SpellBook::getSpellBaseDamage(std::string name) {
	int index = findSpell(name);
		if(index >= 0) {
			return spellList->at(index).baseDamage;
		}
		return index;
}


