#include "MenuCommand.h"


namespace WMenu {
	MenuCommand::MenuCommand(wstring key, wstring description) : key(key), description(description) {}


	MenuCommand::~MenuCommand() {}


	wstring MenuCommand::getKey() {
		return this->key;
	}


	wstring MenuCommand::getDescription() {
		return this->description;
	}
}
