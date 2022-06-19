#include "CancellationEvent.h"

CancellationEvent::CancellationEvent(int ed, int id): Event(ed, id)
{
}
int CancellationEvent:: getED()
{
	return ED;
}
void CancellationEvent::Execute(LinkedPriorityQueue<EmergencyMission*> &we, LinkedQueue<PolarMission*> &wp, LinkedList<MountainousMission*>& wm)
{
	int index;
	MountainousMission* temp;
	int N = wm.getLength();
	bool z=false;
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
	delete temp;
	}
}
CancellationEvent::~CancellationEvent(){}