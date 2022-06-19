#pragma once

#ifndef MARS_CLASS
#define MARS_CLASS

#include"DS\LinkedPriorityQueue.h"
#include"DS\LinkedList.h"
#include"DS\LinkedQueue.h"
#include"Events\Event.h"
#include"Missions\EmergencyMission.h"
#include"Rovers\Rover.h"
#include"Rovers\Emergencyrovers.h"
#include"Rovers\Polarrovers.h"
#include"Rovers\Mountainousrovers.h"
#include"Events\FormulationEvent.h"
#include"Events\CancellationEvent.h"
#include"Events\PromotionEvent.h"
#include"Missions\PolarMission.h"
#include"Missions\MountainousMission.h"
#include"UI.h"

class MarsStation
{
private:
	UI* ui;
	int autoP;
	int auto_promoted;
	int Day;
	int modeOfSim;
protected:
	LinkedPriorityQueue<Event*> EventList;
	LinkedQueue<PolarMission*> WPMList;
	LinkedList<MountainousMission*> WMMList;
	LinkedPriorityQueue<EmergencyMission*> WEMList;
	LinkedPriorityQueue<Mission*> IEList;
	LinkedPriorityQueue<Mission*> CMList;
	LinkedPriorityQueue<Polarrovers*> WPRList;
	LinkedPriorityQueue<Mountainousrovers*> WMRList;
	LinkedPriorityQueue<Emergencyrovers*> WERList;
	LinkedPriorityQueue<Rover*> IMRList;
	LinkedPriorityQueue<Rover*> ICURList;
public:
	MarsStation();

	void Simulate();

	void ReadInput();

	void createMrovers(int n, double* speed, int nom, int checkUp);

	void createProvers(int n, double* speed, int nom, int checkUp);

	void createErovers(int n, double* speed, int nom, int checkUp);

	void setAutoP(int n);

	void addFEvent(MissionType type, int ed, int id, int tloc, int mdur, int sig);

	void addXEvent(int ed, int id);

	void addPEvent(int ed, int id);

	LinkedPriorityQueue<Mission*>* completedMissions();

	LinkedPriorityQueue<Polarrovers*>* polarRovers();

	LinkedPriorityQueue<Mountainousrovers*>* mountRovers();

	LinkedPriorityQueue<Emergencyrovers*>* emergRovers();

	LinkedQueue<PolarMission*>* polarMissions();

	LinkedList<MountainousMission*>* mountMissions();

	LinkedPriorityQueue<EmergencyMission*>* emergMissions();

	LinkedPriorityQueue<Mission*>* inExec();

	LinkedPriorityQueue<Rover*>* inCheck();

	LinkedPriorityQueue<Rover*>* inMaint();

	void setMode(int mode);

	int getMode();

	int getAutoPromoted();

	void failed_func(LinkedPriorityQueue<Mission*>& ine_M);

	~MarsStation();
};
#endif