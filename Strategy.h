#pragma once
#include "Person.h"
#include "Runner.h"

class Strategy {
public:
	static const double extras[2];
	static const double up[9];
	int totalRounds;

	Strategy(double kes, double luos, double yus, double tings, int totalRounds) :totalRounds{ totalRounds }
	{
		KeSpeed = kes;
		LuoSpeed = luos;
		YuSpeed = yus;
		TingSpeed = tings;
	}

	virtual void run() {
		int ans = 0;
		double speed = 0;
		double tSpeed = 0;
		double p1=0, p2=0, p3=0, p4=0, p5=0, p6=0;

		for (int c1 = 0; c1 < 2; ++c1) {
			for (double c2 = 0; c2 < 40; c2 += 0.1) {
				Runner runner{ 6,25,0,25,extras[c1],c2,totalRounds };
				runner.run();
				auto res = runner.getGuoResultForKe();
				if (res > ans || (res == ans && runner.yu->getBaseSpeed() > speed) ||
					(res == ans && runner.yu->getBaseSpeed() == speed &&
						runner.ting->getBaseSpeed() > tSpeed)
					) {
					ans = res;
					p1 = 6;
					p2 = 25;
					p3 = 0;
					p4 = 25;
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
					printf("possible reuslt: %d,(%.1lf,%.1lf,%.lf,%.1lf,%.1lf,%.1lf)\n", res, 6.0, 25.0, 0.0, 25.0, extras[c1], c2);
					printf("Ke[%.1lf],Luo[%.1lf],Yu[%.1lf],Ting[%.1lf]\n",
						runner.ke->getBaseSpeed(),
						runner.luo->getBaseSpeed(),
						runner.yu->getBaseSpeed(),
						runner.ting->getBaseSpeed());
				}
			}
		}

		DEBUG = true;
		Runner runner{ p1,p2,p3,p4,p5,p6,totalRounds };
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

};

class Strategy_Show :public Strategy {
public:
	Strategy_Show(double kes, double luos, double yus, double tings, int totalRounds) :Strategy(kes,luos,yus,tings,totalRounds){

	}
	void run() override {
		int ans = 0;
		double speed = 0;
		double tSpeed = 0;
		double p1=6, p2=25, p3=0, p4=25, p5=6, p6=9;

		DEBUG = true;
		Runner runner{ p1,p2,p3,p4,p5,p6,totalRounds };
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
};

const double Strategy::extras[2] = { 0,6 };
const double Strategy::up[9] = { 0,6,8,9,12,13,16,20,25 };