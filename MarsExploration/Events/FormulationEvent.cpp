#include "FormulationEvent.h"

FormulationEvent::FormulationEvent(MissionType MT, int ed, int id, double Tloc, int Mdur, double Sig): Event(ed,id)
{
	mt = MT;
	if (Tloc > 0)
		TLOC = Tloc;
	else
		TLOC = 0;
	if (Mdur > 0)
		MDUR = Mdur;
	else
		MDUR = 0;
	SIG = Sig;
}
int FormulationEvent:: getED()
{
	return ED;
}
void FormulationEvent::Execute(LinkedPriorityQueue<EmergencyMission*>& we, LinkedQueue<PolarMission*>& wp, LinkedList<MountainousMission*>& wm)
{
	if (mt == MissionType::E)
	{
		EmergencyMission* newMission = new EmergencyMission(ID, TLOC, MDUR, SIG, ED);
		we.add(newMission, newMission->get_pri());
	}
	else if (mt == MissionType::P)
	{
		PolarMission* newMission1 = new PolarMission(ID, TLOC, MDUR, SIG, ED);
		wp.enqueue(newMission1);
	}
	else {
		MountainousMission* newMission2 = new MountainousMission(ID, TLOC, MDUR, SIG, ED);
		wm.insert(newMission2);
	}
}
FormulationEvent::~FormulationEvent()
{

}