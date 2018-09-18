#pragma once
class Guess {
public:
	Guess();
	~Guess();
	void setItem(Item*);
	void setSuspect(Suspect*);
	Item* getItem();
	Suspect* getSuspect();
private:
	Suspect *suspect;
	Item *item;
};

