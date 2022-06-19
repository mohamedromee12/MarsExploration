#include "MountainousMission.h"

MountainousMission::MountainousMission( int ID, double Target_location, int mission_duration, double Si, int fd):Mission(ID,Target_location,mission_duration,Si, fd)
{
	AutoP = 0;
	AutoPDay = 0;
}

void MountainousMission::set_id(int ID)
{
	id=ID;
}

int MountainousMission::get_id()
{
	return id;
}

void MountainousMission::set_tloc(double Target_location)
{
	tloc=Target_location;
}

double MountainousMission::get_tloc()
{
	return tloc;
}

void MountainousMission::set_mdur(int mission_duration)
{
	mdur=mission_duration;
}

int MountainousMission::get_mdur()
{
	return mdur;
}

void MountainousMission::set_si(double Si)
{
	Significance=Si;
}

double MountainousMission::get_si()
{
	return Significance;
}

void MountainousMission::set_FD(int fd)
{
	FD = fd;
}
int MountainousMission::get_FD()
{
	return FD;
}

void MountainousMission::set_R(Rover* r)
{
	R = r;
}
Rover* MountainousMission::get_R()
{
	return R;
}
void MountainousMission:: setAutoP(int D)
{
	if (D>0)
		AutoP=D;
}
int MountainousMission:: getAutoP()
{
	return AutoP;
}
	
int MountainousMission:: getAutoPDay()
{
	return (AutoP+FD);
}

MountainousMission::~MountainousMission()
{

}
