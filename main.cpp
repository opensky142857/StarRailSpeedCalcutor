// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>
#include<stdexcept>
using namespace std;
const int MAX_DIST = 10000;
bool DEBUG = false;
double KeSpeed = 0;
double LuoSpeed = 0;
double YuSpeed = 0;
double TingSpeed = 0;
class Person
{
public:
	string name;
	int speed;
	double extraPersentage;
	double speedUp;
	int extra10T;

	int moved;
	int guoMove;
	int mingMove;
	double total;
	double dist;

	Person(string name, int speed, double extraPersentage, double up) :name{ name }, speed{ speed }, extraPersentage{ extraPersentage }
	{
		extra10T = 2;
		speedUp = up;
		moved = 0;
		total = 0;
		guoMove = 0;
		mingMove = 0;
		dist = MAX_DIST;
	}
	double getBaseSpeed() {
		double re = speed + speedUp;
		re += speed * extraPersentage / 100.0;
		return re;
	}
	virtual double getSpeed()
	{
		double re = getBaseSpeed();
		if (extra10T > 0) {
			re += speed * 10 / 100.0;
		}
		return re;
	}

	/*double getDistRemained() {
		if (turns == 0) {

		}
	}*/

	double getETA() {
		return dist / getSpeed();
	}
	void addGuo() {
		guoMove++;
	}

	void addMing() {
		mingMove++;
	}

	void run(double sec) {
		total += sec;
		dist -= sec * getSpeed();
		if (dist < -1e-6) {
			throw runtime_error("negative time");
		}
		/*else if (dist < 1e-6) {
			onTurn();
			dist = MAX_DIST;
		}*/
	}

	virtual void onTurn() {
		++moved;
		if (DEBUG) {
			printf("\t%s(%d),guo wang %d, ming xian %d\n", name.c_str(), moved, guoMove, mingMove);
		}
		if (extra10T > 0) extra10T--;
		dist = MAX_DIST;
	}
};

class Ke : public Person
{
public:
	Ke(double extraPersentage, double up) :Person("Ke", 90, extraPersentage, up + KeSpeed)
	{
	}

	int TBuff;

	void onTurn() override {
		Person::onTurn();
		if (TBuff > 0) {
			TBuff--;
		}
	}
};


class Ting : public Person
{
public:
	Ting(shared_ptr<Ke> ke, double  extraPersentage, double up) :Person("Ting", 112, extraPersentage, up + TingSpeed), ke{ ke }
	{
		//dist = MAX_DIST * 0.6;
	}

	shared_ptr<Ke> ke;
	int extra20T = 0;

	double getSpeed() override {
		double re = Person::getSpeed();
		if (extra20T > 0) {
			re += 0.2 * speed;
		}
		return re;
	}

	void onTurn() override {
		Person::onTurn();
		if (extra20T > 0) {
			extra20T--;
		}

		if (ke->TBuff == 1) {
			auto kt = ke->getETA();
			//eta if do not use E
			auto tt = getETA();
			if (tt < kt) {
				if (DEBUG) {
					printf("Ting: A0\n");
				}
			}
			else {
				if (DEBUG) {
					printf("Ting: E0\n");
				}
				ke->TBuff = 3;
				extra20T = 1;
			}
		}
		else if (ke->TBuff <= 0) {
			if (DEBUG) {
				printf("Ting: E\n");
			}
			ke->TBuff = 3;
			extra20T = 1;
		}
		else {
			if (DEBUG) {
				printf("Ting: A\n");
			}
		}
	}

};

class Yu :public Person {
public:
	Yu(double extraPersentage, double up) :Person("Yu", 107, extraPersentage, up + YuSpeed) {}



};

class Luo :public Person {
public:
	Luo(double extraPersentage, double up) :Person("Luo", 101, extraPersentage, up + LuoSpeed) {}



};

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

int main()
{
	double extras[2] = { 0,6 };
	double up[] = { 0,6,8,9,12,13,16,20,25 };
	KeSpeed = 0;
	LuoSpeed = 4.9;
	YuSpeed = 2.0;
	TingSpeed = 2.3;

	{
		DEBUG = true;
		Runner runner{ 6,25,0,25,0,9,10 };
		runner.run();
		auto res = runner.getGuoResultForKe();

		printf("Ke[%.1lf],Luo[%.1lf],Yu[%.1lf],Ting[%.1lf]\n",
			runner.ke->getBaseSpeed(),
			runner.luo->getBaseSpeed(),
			runner.yu->getBaseSpeed(),
			runner.ting->getBaseSpeed());
		DEBUG = false;
	}

	int ans = 0;
	double speed = 0;
	double tSpeed = 0;
	double p1, p2, p3, p4, p5, p6;

	/*for (int c1 = 0; c1 < 2; ++c1) {
		for (double c2 = 0; c2 < 30; c2 += 0.1) {
			Runner runner{ 6,25,0,25,extras[c1],c2,10 };
			runner.run();
			auto res = runner.getGuoResultForKe();
			if (res > ans || (res == ans && runner.ting->getBaseSpeed() > speed)) {
				ans = res;
				p1 = 6;
				p2 = 25;
				p3 = 0;
				p4 = 25;
				p5 = extras[c1];
				p6 = c2;
				speed = runner.ting->getBaseSpeed();
				printf("better reuslt: %d,(%.1lf,%.1lf,%.lf,%.1lf,%.1lf,%.1lf)\n", ans, p1, p2, p3, p4, p5, p6);
			}

		}
	}

	for (int a1 = 0; a1 < 2; ++a1) {
		for (int a2 = 0; a2 < 9; ++a2) {
			for (int c1 = 0; c1 < 2; ++c1) {
				for (double c2 = 0; c2 < 30; c2 += 0.1) {
					Runner runner{ extras[a1],up[a2],0,25,extras[c1],c2,10 };
					runner.run();
					auto res = runner.getGuoResultForKe();
					if (res > ans || (res == ans && runner.ting->getBaseSpeed() > speed)) {
						ans = res;
						p1 = extras[a1];
						p2 = up[a2];
						p3 = 0;
						p4 = 25;
						p5 = extras[c1];
						p6 = c2;
						speed = runner.ting->getBaseSpeed();
						printf("better reuslt: %d,(%.1lf,%.1lf,%.lf,%.1lf,%.1lf,%.1lf)\n", ans, p1, p2, p3, p4, p5, p6);
					}

				}
			}
		}
	}*/

	for (int a1 = 0; a1 < 2; ++a1) {
		for (int a2 = 0; a2 < 9; a2+=1) {
			printf("a2=%d\n", a2);
			for (int b1 = 0; b1 < 2; ++b1) {
				for (int b2 = 0; b2 < 9; b2+=1) {
					for (int c1 = 0; c1 < 2; ++c1) {
						for (double c2 = 0; c2 < 40; c2+=1) {
							Runner runner{ extras[a1],up[a2],extras[b1],up[b2],extras[c1],c2,10 };
							runner.run();
							auto res = runner.getGuoResultForKe();
							if (res > ans || (res == ans && runner.yu->getBaseSpeed() > speed) ||
								(res == ans && runner.yu->getBaseSpeed() == speed &&
									runner.ting->getBaseSpeed() > tSpeed)
								) {
								ans = res;
								p1 = extras[a1];
								p2 = a2;
								p3 = extras[b1];
								p4 = b2;
								p5 = extras[c1];
								p6 = c2;
								speed = runner.yu->getBaseSpeed();
								tSpeed = runner.ting->getBaseSpeed();
								printf("better reuslt: %d,(%.1lf,%.1lf,%.lf,%.1lf,%.1lf,%.1lf)\n", ans, p1, p2, p3, p4, p5, p6);
								printf("Ke[%.1lf],Luo[%.1lf],Yu[%.1lf],Ting[%.1lf]\n",
									runner.ke->getBaseSpeed(),
									runner.luo->getBaseSpeed(),
									runner.yu->getBaseSpeed(),
									runner.ting->getBaseSpeed());
							}
							else if (res >= 7) {
								printf("possible reuslt: %d,(%.1lf,%.1lf,%.lf,%.1lf,%.1lf,%.1lf)\n", res, extras[a1], a2, extras[b1], b2, extras[c1], c2);
								printf("Ke[%.1lf],Luo[%.1lf],Yu[%.1lf],Ting[%.1lf]\n",
									runner.ke->getBaseSpeed(),
									runner.luo->getBaseSpeed(),
									runner.yu->getBaseSpeed(),
									runner.ting->getBaseSpeed());
							}
						}
					}
				}
			}
		}
	}



	DEBUG = true;
	Runner runner{ p1,p2,p3,p4,p5,p6,10 };
	runner.run();
	auto res = runner.getGuoResultForKe();
	DEBUG = false;

	printf("best reuslt: %d, (%.1lf,%.1lf,%.lf,%.1lf,%.1lf,%.1lf)\n", ans, p1, p2, p3, p4, p5, p6);
	printf("Ke[%.1lf],Luo[%.1lf],Yu[%.1lf],Ting[%.1lf]\n",
		runner.ke->getBaseSpeed(),
		runner.luo->getBaseSpeed(),
		runner.yu->getBaseSpeed(),
		runner.ting->getBaseSpeed());


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
