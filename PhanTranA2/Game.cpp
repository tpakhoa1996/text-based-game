#include "stdafx.h"

Game* Game::currentGame = nullptr;

void Game::createNewGame(istream &gameConfig, istream& gameHelper) {
	clearGame();
	currentGame = new Game(gameConfig, gameHelper);
}

bool Game::runCurrentGame() {
	bool check = false;
	if (currentGame != nullptr) {
		check = true;
		currentGame->run();
	}
	return check;
}

void Game::clearGame() {
	delete currentGame;
	currentGame = nullptr;
}

Game::Game(istream &gameConfig, istream& gameHelper) {
	helper = new GameHelper();
	initGameConfig(JSON::read(gameConfig));
	initGameHelper(gameHelper);
}

void Game::initGameConfig(JSON* config) {
	// Time limit
	Time::setTimer(*config->at("timeLimit")->getInt());

	// Map
	helper->map = new Map(config->at("map"));

	// Character
	const JSON::Array* characterConfigList = config->at("characters")->getArray();
	helper->characterList = new GameHelper::CharacterVec();
	for (const auto& characterConfig : *characterConfigList) {
		string characterClass = *characterConfig->at("class")->getString();
		if (characterClass == "investigator") {
			helper->mainCharacter = new Investigator(characterConfig);
			helper->characterList->push_back(helper->mainCharacter);
			helper->characterList->back()->updateCurrentArea(helper->map);
		} else if (characterClass == "suspect") {
			helper->characterList->push_back(new Suspect(characterConfig));
			helper->characterList->back()->updateCurrentArea(helper->map);
		}
	}

	// Role
	const JSON::Array *roleConfigList = config->at("roles")->getArray();
	for (int i = 0; i < (int)roleConfigList->size(); i++) {
		helper->roles.push_back(new Role(roleConfigList->at(i)));
	}
	auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
	shuffle(
		helper->roles.begin(),
		helper->roles.end(),
		default_random_engine((int)seed)
	);
	Role::CharacterMap *characterMap = new Role::CharacterMap();
	for (
		int i = 0, r = 0; 
		i < (int)helper->characterList->size() &&
		r < (int)helper->roles.size();
		i++
	) {
		Character *character = helper->characterList->at(i);
		if (character->getCharacterClass() == Character::Class::Suspect) {
			Suspect *suspect = (Suspect*)character;
			suspect->setRole(helper->roles[r]);
			helper->roles[r]->setSuspect(suspect);
			characterMap->insert({ helper->roles[r]->getName(), suspect->getName() });
			r++;
		}
	}

	for (int i = 0; i < (int)helper->roles.size(); i++) {
		helper->roles[i]->resolveDialog(characterMap);
	}
	
	// Initial guess
	helper->guess = new Guess();

	delete characterMap;
	delete config;
}

void Game::initGameHelper(istream& gameHelper) {
	while (1) {
		SectionInput section(gameHelper);
		if (section.name.empty()) {
			break;
		}

		if (section.name == "Instruction_Section") {
			helper->instruction = section.stream.str();
		} else if (section.name == "Introduction_Section") {
			introduction = section.stream.str();
		}
	}
}


void Game::run() {
	intro();
	loop();
	end();
}

void Game::getPlayerInfo() {
	// get player name
	cout << "Enter your prefered name ( default is " << helper->mainCharacter->getName();
	cout << " )" << ": ";
	string name;
	getline(cin, name);
	if (name.length() > 0) {
		helper->mainCharacter->setName(name);
	}
}

void Game::intro() {
	cout << introduction << endl;
	system("pause");
	cout << endl << endl;
	getPlayerInfo();
	cout << "Hi " << helper->mainCharacter->getName() << "!" << endl;
	cout << helper->instruction << endl;
	system("pause");
	cout << endl << endl;
	string map = helper->map->renderOveralMap(
		helper->getMainCharacter()
	);
	cout << map << endl << endl;
	cout << "You are the letter " << helper->getMainCharacter()->getMarker();
	cout << " on the map" << endl;
	cout << "You are currently in ";
	cout << helper->getMainCharacter()->getCurrentArea()->getName() << endl;
	cout << endl;
	system("pause");
	cout << endl << endl;
}

void Game::loop() {
	helper->controlStack = new GameHelper::ControlStack();
	helper->controlStack->push(new MainCommandGroup(helper));
	while (!helper->controlStack->empty() && !Time::isTimeout()) {
		helper->controlStack->top()->execute();
	}

	if (!helper->controlStack->empty() && Time::isTimeout()) {
		cout << endl << "You have ran out of time." << endl << endl;
	}

	// clean up
	while (helper->goBackOneControlUnit());
}

void Game::end() {
	string answer;
	while (1) {
		cout << "Is this game easy to play?[yes/no]: ";
		getline(cin, answer);
		if (answer == "yes" || answer == "no") {
			break;
		}
	}
	cout << "Thank you for your feedback." << endl;
	if (answer == "no") {
		cout << "We will try to improve this game for your better experience." << endl;
	}
	cout << "Bye bye." << endl;
}

Game::~Game() {
	if (helper != nullptr) {
		delete helper;
	}
}
