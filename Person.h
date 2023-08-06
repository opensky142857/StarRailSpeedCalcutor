#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>
#include "Common.h"


using namespace std;
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
		extra10T = 0;
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

class Luo :public Person {
public:
	Luo(double extraPersentage, double up) :Person("Luo", 101, extraPersentage, up + LuoSpeed) {}
};

class Yu :public Person {
public:
	Yu(double extraPersentage, double up) :Person("Yu", 107, extraPersentage, up + YuSpeed) {}
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
