#pragma once
#ifndef UI_CLASS
#define UI_CLASS
#include<string>

class MarsStation;
class UI
{
private:
	MarsStation* station;
	std::string inputfile;
public:
	UI(MarsStation* st);
	void loadInputFile();
	void createOutputFile();
	void printDataOfDay(int day);
	void silentMode();
	void waitEnter();
	void waitSecond();
	int getModeOfSim();
	void printFailedMission(int id);
	void printDayNumber(int day);
};
#endif