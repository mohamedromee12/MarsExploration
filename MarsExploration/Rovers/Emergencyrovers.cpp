#include "Emergencyrovers.h"

Emergencyrovers::Emergencyrovers(double speed ,int nom,int checkupDuration):Rover(speed,nom,checkupDuration)
{
}
 void Emergencyrovers:: setspeed(double speed)
	{
		if (speed>0)
			Speed=speed;
			//Rover::setspeed(speed);
	}
	double Emergencyrovers:: getspeed()
	{
		return Speed;
	}
	void Emergencyrovers:: setnumofmissions(int nom)
	{
		if  (nom>0)
			Nom=nom;
	}
	int Emergencyrovers:: getnumofmissions()
	{
		return Nom;
	}
	void Emergencyrovers:: setCheckupDuration(int checkupDuration)
	{
		if ( checkupDuration>0)
			CheckupDuration=checkupDuration;
	}
	int Emergencyrovers:: getCheckupDuration()
	{
		return CheckupDuration;
	}
	void Emergencyrovers:: setFinishcheckupday(int day)
	 {
		 if (day>0)
			 Finishcheckupday=day;
	 }
	 int Emergencyrovers:: getFinishcheckupday()
	 {
		 return Finishcheckupday;
	 }
	 void Emergencyrovers:: setFinishMaintenanceday(int day)
	 {
		  if (day>0)
			 FinishMaintenanceday=day;
	 }
	 int Emergencyrovers:: getFinishMaintenanceday()
	 {
		 return FinishMaintenanceday;
	 }
	 void Emergencyrovers:: setNomdone (int nomdone)
	 {
		 
			  Nomdone=nomdone;

	 }
	int Emergencyrovers:: getNomdone()
	{
		return Nomdone;
	}
	void Emergencyrovers:: incrementNumofcheckups()
	 {
		 Numofcheckups++;
	 }

	int Emergencyrovers:: getNumofcheckups()
	{
		return Numofcheckups;
	}
	int Emergencyrovers:: getExecutionDays(double TL,int MD)
	{
		//TL is the target loction km
		//MD is the mission duration in days
		int z;
		z=int (2*(TL/Speed));
		int m=int (z/25);
		return (m+MD);
	}
	void Emergencyrovers:: incrementmissionsdone()
	{
       Nomdone++;
    }

Emergencyrovers::~Emergencyrovers(void)
{
}
