/*
   MenuCommand.cpp, WonderMenu.cpp MenuCommand.h MenuCommandEmpty.h WonderMenu.h WonderMenuExceptions.h WMenu.h

   Copyright (C) 2019 Andrieiev Danil

   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
	  claim that you wrote the original source code. If you use this source code
	  in a product, an acknowledgment in the product documentation would be
	  appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
	  misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   Andrieiev Danil danssg08@gmail.com

   version 1.1.0
*/
#include "WonderMenu.h"
#include "MenuCommandEmpty.h"

namespace WMenu {
	WonderMenu::WonderMenu(wstring exitCommand) : MSet(&comparator), exitCommand(exitCommand) {}

	WonderMenu::WonderMenu() : WonderMenu(L"exit") {}


	WonderMenu::~WonderMenu() {
		for (MenuCommand* item : *this) {
			delete item;
		}
	}


	void WonderMenu::addCommand(MenuCommand* command) {
		if (!command) {
			throw ZeroPointerException();
		}
		try {
			delete this->find(command->getKey());
			this->insert(command);
		}
		catch (NoObjectFoundException e) {
			this->insert(command);
		}
	}


	void WonderMenu::start() {
		while (true) {
			this->print();
			wstring buffer;
			wstring command;
			wcin >> command;
			for (size_t i = command.length(); i > 0 ; i--) {
				wcin.putback(command[i-1]);
			}
			getline(wcin, buffer);
			try {
				MenuCommand* item = this->find(command);
				item->handleCommnad(buffer);
			}
			catch (NoObjectFoundException e) {
				wcout << L"Error: Unknown command" << endl;
			}
			if (command.compare(this->exitCommand) == 0) {
				break;
			}
		}
	}


	MenuCommand* WonderMenu::find(wstring key) {
		MenuCommandEmpty finder(key);
		iterator item =  MSet::find(&finder);
		if (item == this->cend()) {
			throw NoObjectFoundException();
		}
		return *item;
	}


	bool WonderMenu::comparator(MenuCommand* less, MenuCommand* higher) {
		int comparingResult = less->getKey().compare(higher->getKey());
		if (comparingResult == -1) {
			return true;
		} 
		return false;
	}
}
