#pragma once
#include "Person.h"
using namespace std;

inline bool cmp(shared_ptr<Person> p1, shared_ptr<Person>p2) {
	return p1->getETA() < p2->getETA();
}

class Runner {
public:
	Runner(double keExtra, double keUp, double luoExtra, double luoUp, double yuExtra, double yuUp, double tingExtra, double tingUp, int turns)
	{

		ke = std::make_shared<Ke>(keExtra, keUp);
		init(luoExtra, luoUp, yuExtra, yuUp, tingExtra, tingUp, turns);
	}

	Runner(double luoExtra, double luoUp, double yuExtra, double yuUp, double tingExtra, double tingUp, int turns)
	{
		ke = std::make_shared<Ke>(0, 0);
		init(luoExtra, luoUp, yuExtra, yuUp, tingExtra, tingUp, turns);
	}

	void init(double luoExtra, double luoUp, double yuExtra, double yuUp, double tingExtra, double tingUp, int turns) {
		MAX_TURN = turns;

		luo = std::make_shared<Luo>(luoExtra, luoUp);
		yu = std::make_shared<Yu>(yuExtra, yuUp);
		ting = std::make_shared<Ting>(ke, tingExtra, tingUp);
		v.emplace_back(ke);
		v.emplace_back(luo);
		v.emplace_back(yu);
		v.emplace_back(ting);
	}

	shared_ptr<Ke> ke;
	shared_ptr<Person> luo;
	shared_ptr<Person> yu;
	shared_ptr<Person> ting;

	vector<shared_ptr<Person>> v;
	int MAX_TURN;
	bool guo = false;
	int ming = 0;

	void run() {
		int turn = 0;
		double total = 0;
		guo = false;
		ming = 0;

		while (true) {
			sort(v.begin(), v.end(), cmp);
			if (DEBUG)
			{
				printf("current states:\n");
				for (auto i = v.begin(); i != v.end(); ++i) {
					printf("%s at %.2lf(speed %.2lf)\n", (*i)->name.c_str(), (*i)->getETA(), (*i)->getSpeed());
				}
			}

			auto now = v[0];
			auto elaps = now->getETA();
			total += elaps;
			if (turn == 0 && total >= 150) {
				turn++;
				total -= 150;
				if (DEBUG) {
					printf("into turn %d\n", turn);
				}
			}
			else if (total >= 100) {
				turn++;
				total -= 100;
				if (DEBUG) {
					printf("into turn %d\n", turn);
				}
			}
			if (turn >= MAX_TURN) break;

			if (now->name == "Yu") {
				guo = true;
				ming = 2;
			}

			for (auto i = v.begin(); i != v.end(); ++i) {
				(*i)->run(elaps);
			}

			for (auto i = v.begin(); i != v.end(); ++i) {
				if ((*i)->dist < 1e-6) {
					if ((*i)->name != "Yu") {
						if (guo) {
							(*i)->addGuo();
							guo = false;
						}
						if (ming > 0) {
							(*i)->addMing();
							ming--;
						}
					}
					(*i)->onTurn();

				}
			}
		}
	}


	int getGuoResultForKe() {
		if (ke->mingMove != ke->moved) {
			return -1;
		}
		return ke->guoMove;
	}

};
