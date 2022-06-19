#include "PromotionEvent.h"

PromotionEvent::PromotionEvent(int ed, int id) : Event(ed, id)
{
}
int PromotionEvent:: getED()
{
	return ED;
}
void PromotionEvent::Execute(LinkedPriorityQueue<EmergencyMission*> &we, LinkedQueue<PolarMission*> &wp, LinkedList<MountainousMission*>& wm)
{
	int index;
	MountainousMission* temp;
	bool z=false;
	int N = wm.getLength();
	for (index = 0; index < N; index++)
	{
		if (wm.getEntry(index)->get_id() == ID)
		{
			z=true;
			break;
		}
	}
	if (z)
	{
	wm.remove(index, temp);
	EmergencyMission* newMission = new EmergencyMission(temp->get_id(), temp->get_tloc(), temp->get_mdur(), temp->get_si(), temp->get_FD());
	delete temp;
	we.add(newMission, newMission->get_pri());
	}
}
PromotionEvent::~PromotionEvent() {}