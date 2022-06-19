#pragma once
#include"..\Constants.h"
#include"..\DS\LinkedPriorityQueue.h"
#include"..\DS\LinkedList.h"
#include"..\DS\LinkedQueue.h"
#include"..\Missions\EmergencyMission.h"
#include"..\Missions\PolarMission.h"
#include"..\Missions\MountainousMission.h"
class Event{
protected:
	//Event day
	int ED;
	//mission ID
	int ID;
public:
	Event(int ed, int id)
	{
		if (ed > 0)
			ED = ed;
		else
			ED = 0;
		ID = id;
	}
	void setED( int D)
	{
		if (D>0)
			ED=D;
	}
	virtual int getED()
	{
		return ED;
	}
	virtual void Execute(LinkedPriorityQueue<EmergencyMission*> &we, LinkedQueue<PolarMission*> &wp, LinkedList<MountainousMission*>& wm) = 0;
	virtual ~Event(){}
};