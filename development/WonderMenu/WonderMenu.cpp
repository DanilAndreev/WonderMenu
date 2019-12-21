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
			if (command.compare(this->exitCommand) == 0) {
				break;
			}
			try {
				MenuCommand* item = this->find(command);
				item->handleCommnad(buffer);
			}
			catch (NoObjectFoundException e) {
				wcout << L"Error: Unknown command" << endl;
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
