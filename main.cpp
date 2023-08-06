// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>
#include<stdexcept>
#include "Person.h"
#include "Runner.h"
#include "Strategy.h"
using namespace std;

int main()
{
	//Strategy_Show my(0, 4.9, 2.0, 2, 10);
	Strategy my(2.6, 4.9, 2.0, 2, 10);
	my.run();
	//double extras[2] = { 0,6 };
	//double up[] = { 0,6,8,9,12,13,16,20,25 };
	//KeSpeed = 0;
	//LuoSpeed = 4.9;
	//YuSpeed = 2.0;
	//TingSpeed = 2.3;

	//{
	//	DEBUG = true;
	//	Runner runner{ 6,25,0,25,0,9,10 };
	//	runner.run();
	//	auto res = runner.getGuoResultForKe();

	//	printf("Ke[%.1lf],Luo[%.1lf],Yu[%.1lf],Ting[%.1lf]\n",
	//		runner.ke->getBaseSpeed(),
	//		runner.luo->getBaseSpeed(),
	//		runner.yu->getBaseSpeed(),
	//		runner.ting->getBaseSpeed());
	//	DEBUG = false;
	//}

	//int ans = 0;
	//double speed = 0;
	//double tSpeed = 0;
	//double p1, p2, p3, p4, p5, p6;

	///*for (int c1 = 0; c1 < 2; ++c1) {
	//	for (double c2 = 0; c2 < 30; c2 += 0.1) {
	//		Runner runner{ 6,25,0,25,extras[c1],c2,10 };
	//		runner.run();
	//		auto res = runner.getGuoResultForKe();
	//		if (res > ans || (res == ans && runner.ting->getBaseSpeed() > speed)) {
	//			ans = res;
	//			p1 = 6;
	//			p2 = 25;
	//			p3 = 0;
	//			p4 = 25;
	//			p5 = extras[c1];
	//			p6 = c2;
	//			speed = runner.ting->getBaseSpeed();
	//			printf("better reuslt: %d,(%.1lf,%.1lf,%.lf,%.1lf,%.1lf,%.1lf)\n", ans, p1, p2, p3, p4, p5, p6);
	//		}

	//	}
	//}

	//for (int a1 = 0; a1 < 2; ++a1) {
	//	for (int a2 = 0; a2 < 9; ++a2) {
	//		for (int c1 = 0; c1 < 2; ++c1) {
	//			for (double c2 = 0; c2 < 30; c2 += 0.1) {
	//				Runner runner{ extras[a1],up[a2],0,25,extras[c1],c2,10 };
	//				runner.run();
	//				auto res = runner.getGuoResultForKe();
	//				if (res > ans || (res == ans && runner.ting->getBaseSpeed() > speed)) {
	//					ans = res;
	//					p1 = extras[a1];
	//					p2 = up[a2];
	//					p3 = 0;
	//					p4 = 25;
	//					p5 = extras[c1];
	//					p6 = c2;
	//					speed = runner.ting->getBaseSpeed();
	//					printf("better reuslt: %d,(%.1lf,%.1lf,%.lf,%.1lf,%.1lf,%.1lf)\n", ans, p1, p2, p3, p4, p5, p6);
	//				}

	//			}
	//		}
	//	}
	//}*/

	//for (int a1 = 0; a1 < 2; ++a1) {
	//	for (int a2 = 0; a2 < 9; a2 += 1) {
	//		printf("a2=%d\n", a2);
	//		for (int b1 = 0; b1 < 2; ++b1) {
	//			for (int b2 = 0; b2 < 9; b2 += 1) {
	//				for (int c1 = 0; c1 < 2; ++c1) {
	//					for (double c2 = 0; c2 < 40; c2 += 1) {
	//						Runner runner{ extras[a1],up[a2],extras[b1],up[b2],extras[c1],c2,10 };
	//						runner.run();
	//						auto res = runner.getGuoResultForKe();
	//						if (res > ans || (res == ans && runner.yu->getBaseSpeed() > speed) ||
	//							(res == ans && runner.yu->getBaseSpeed() == speed &&
	//								runner.ting->getBaseSpeed() > tSpeed)
	//							) {
	//							ans = res;
	//							p1 = extras[a1];
	//							p2 = a2;
	//							p3 = extras[b1];
	//							p4 = b2;
	//							p5 = extras[c1];
	//							p6 = c2;
	//							speed = runner.yu->getBaseSpeed();
	//							tSpeed = runner.ting->getBaseSpeed();
	//							printf("better reuslt: %d,(%.1lf,%.1lf,%.lf,%.1lf,%.1lf,%.1lf)\n", ans, p1, p2, p3, p4, p5, p6);
	//							printf("Ke[%.1lf],Luo[%.1lf],Yu[%.1lf],Ting[%.1lf]\n",
	//								runner.ke->getBaseSpeed(),
	//								runner.luo->getBaseSpeed(),
	//								runner.yu->getBaseSpeed(),
	//								runner.ting->getBaseSpeed());
	//						}
	//						else if (res >= 7) {
	//							printf("possible reuslt: %d,(%.1lf,%.1lf,%.lf,%.1lf,%.1lf,%.1lf)\n", res, extras[a1], a2, extras[b1], b2, extras[c1], c2);
	//							printf("Ke[%.1lf],Luo[%.1lf],Yu[%.1lf],Ting[%.1lf]\n",
	//								runner.ke->getBaseSpeed(),
	//								runner.luo->getBaseSpeed(),
	//								runner.yu->getBaseSpeed(),
	//								runner.ting->getBaseSpeed());
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}



	//DEBUG = true;
	//Runner runner{ p1,p2,p3,p4,p5,p6,10 };
	//runner.run();
	//auto res = runner.getGuoResultForKe();
	//DEBUG = false;

	//printf("best reuslt: %d, (%.1lf,%.1lf,%.lf,%.1lf,%.1lf,%.1lf)\n", ans, p1, p2, p3, p4, p5, p6);
	//printf("Ke[%.1lf],Luo[%.1lf],Yu[%.1lf],Ting[%.1lf]\n",
	//	runner.ke->getBaseSpeed(),
	//	runner.luo->getBaseSpeed(),
	//	runner.yu->getBaseSpeed(),
	//	runner.ting->getBaseSpeed());


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
