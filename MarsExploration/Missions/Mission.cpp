#include "Mission.h"

Mission::Mission( int ID, double Target_location, int mission_duration, double Si, int fd)
{
	id=ID;
	tloc=Target_location;
	mdur=mission_duration;
	Significance=Si;
	FD = fd;
	R = nullptr;
	fprob = 0;
	sprob = 0;
	td_days = 0;
	CD = 0;
	ED = 0;
	WD = 0;
}

void Mission::set_id(int ID)
{
	id=ID;
}

int Mission::get_id()
{
	return id;
}

void Mission::set_tloc(double Target_location)
{
	tloc=Target_location;
}

double Mission::get_tloc()
{
	return tloc;
}

void Mission::set_mdur(int mission_duration)
{
	mdur=mission_duration;
}

int Mission::get_mdur()
{
	return mdur;
}

void Mission::set_si(double Si)
{
	Significance=Si;
}

double Mission::get_si()
{
	return Significance;
}

void Mission::set_FD(int fd)
{
	FD = fd;
}
int Mission::get_FD()
{
	return FD;
}

void Mission::set_R(Rover* r)
{
	R = r;
}
Rover* Mission::get_R()
{
	return R;
}

void Mission::set_WD(int wd){
	WD = wd;
}

int Mission::get_WD(){
	return WD;
}

void Mission::set_CD(int cd){
	CD = cd;
	if(R)
	{
		sprob=(((tloc/R->getspeed())/25)+mdur)+WD+FD; // rovers arriver and executed the mission ( the day that the rover will come back from the target location)
		fprob=0.7*(((tloc/R->get_mspeed())/25))+mdur;   // mission failed probability equation
		td_days=int(((tloc/R->getspeed())/25)+WD+FD);  // day that the rover arrive to the target location
	}
}

int Mission::get_CD(){
	return CD;
}

void Mission::set_ED(int ed){
	ED = ed;
}

int Mission::get_ED(){
	return ED;
}

void Mission::set_fprob(double FP)
{
	fprob=FP;
}

double Mission::get_fprob()
{
	return fprob;
}

double Mission::get_sprob()
{
	return sprob;
}

int Mission::get_td_days()
{
	return td_days;
}




Mission::~Mission()
{

}

