#pragma once
#include "Mission.h"
class EmergencyMission: public Mission
{
private:
	float priority;
public:
	EmergencyMission( int ID, double Target_location, int mission_duration, double Si, int fd);
	virtual void set_id(int ID);
	virtual int get_id();
	virtual void set_tloc(double Target_location);
	virtual double get_tloc();
	virtual void set_mdur(int mission_duration);
	virtual int get_mdur();
	virtual void set_si(double Si);
	virtual double get_si();
	virtual void set_pri(int Target_location, int mission_duration, int Si);
	virtual float get_pri();
	virtual void set_FD(int fd);
	virtual int get_FD();
	virtual void set_R(Rover* r);
	virtual Rover* get_R();
	~EmergencyMission();
};
