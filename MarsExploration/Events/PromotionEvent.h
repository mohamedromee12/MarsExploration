#pragma once
#include"Event.h"
class PromotionEvent : public Event
{
public:
    PromotionEvent(int ed, int id);
	int getED();
    void Execute(LinkedPriorityQueue<EmergencyMission*> &we, LinkedQueue<PolarMission*> &wp, LinkedList<MountainousMission*>& wm);
    ~PromotionEvent();
};

