#include "Polarrovers.h"


Polarrovers::Polarrovers(double speed ,int nom,int checkupDuration):Rover(speed,nom,checkupDuration)
{
}
 void Polarrovers:: setspeed(double speed)
	{
		if (speed>0)
			Speed=speed;
	}
	double Polarrovers:: getspeed()
	{
		return Speed;
	}
	void Polarrovers:: setnumofmissions(int nom)
	{
		if  (nom>0)
			Nom=nom;
	}
	int Polarrovers:: getnumofmissions()
	{
		return Nom;
	}
	void Polarrovers:: setCheckupDuration(int checkupDuration)
	{
		if ( checkupDuration>0)
			CheckupDuration=checkupDuration;
	}
	int Polarrovers:: getCheckupDuration()
	{
		return CheckupDuration;
	}
	void Polarrovers:: setFinishcheckupday(int day)
	 {
		 if (day>0)
			 Finishcheckupday=day;
	 }
	 int Polarrovers:: getFinishcheckupday()
	 {
		 return Finishcheckupday;
	 }
	 void Polarrovers:: setFinishMaintenanceday(int day)
	 {
		  if (day>0)
			 FinishMaintenanceday=day;
	 }
	 int Polarrovers:: getFinishMaintenanceday()
	 {
		 return FinishMaintenanceday;
	 }
	 void Polarrovers:: setNomdone (int nomdone)
	 {
		 
			  Nomdone=nomdone;

	 }
	int Polarrovers:: getNomdone()
	{
		return Nomdone;
	}
	void Polarrovers:: incrementNumofcheckups()
	 {
		 Numofcheckups++;
	 }

	int Polarrovers:: getNumofcheckups()
	{
		return Numofcheckups;
	}
	int Polarrovers:: getExecutionDays(double TL,int MD)
	{
		//TL is the target loction km
		//MD is the mission duration in days
		int z;
		z=int (2*(TL/Speed));
		z=int (z/25);
		return (z+MD);
	}
	void Polarrovers:: incrementmissionsdone()
	{
       Nomdone++;
    }
Polarrovers::~Polarrovers(void)
{
}
