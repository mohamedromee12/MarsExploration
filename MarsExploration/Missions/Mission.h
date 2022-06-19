#pragma once
#include"..\Rovers\Rover.h"
class Mission
{
protected:
	int id;
	double tloc;
	int mdur;
	double Significance;
	int FD;
	int WD;
	int CD;
	int ED;
	double fprob;  // failed probability
	double sprob;  // success probability
	int td_days; // day that the rover arrive to the target location
	// pointer to rover
	Rover* R;
public:
	Mission( int ID, double Target_location, int mission_duration, double Si, int FD);
	virtual void set_id(int ID);
	virtual int get_id();
	virtual void set_tloc(double Target_location);
	virtual double get_tloc();
	virtual void set_mdur(int mission_duration);
	virtual int get_mdur();
	virtual void set_si(double Si);
	virtual double get_si();
	virtual void set_FD(int fd);
	virtual int get_FD();
	virtual void set_R(Rover* r);
	virtual Rover* get_R();
	virtual void set_WD(int wd);
	virtual int get_WD();
	virtual void set_CD(int cd);
	virtual int get_CD();
	virtual void set_ED(int ed);
	virtual int get_ED();
	virtual void set_fprob(double FP);
	virtual double get_fprob();
	virtual double get_sprob();
	virtual int get_td_days();
	~Mission();
};
