#include "Mountainousrovers.h"

Mountainousrovers::Mountainousrovers(double speed ,int nom,int checkupDuration):Rover(speed,nom,checkupDuration)
{
}
 void Mountainousrovers:: setspeed(double speed)
	{
		if (speed>0)
			Speed=speed;
	}
	double Mountainousrovers:: getspeed()
	{
		return Speed;
	}
	void Mountainousrovers:: setnumofmissions(int nom)
	{
		if  (nom>0)
			Nom=nom;
	}
	int Mountainousrovers:: getnumofmissions()
	{
		return Nom;
	}
	void Mountainousrovers:: setCheckupDuration(int checkupDuration)
	{
		if ( checkupDuration>0)
			CheckupDuration=checkupDuration;
	}
	int Mountainousrovers:: getCheckupDuration()
	{
		return CheckupDuration;
	}
	void Mountainousrovers:: setFinishcheckupday(int day)
	 {
		 if (day>0)
			 Finishcheckupday=day;
	 }
	 int Mountainousrovers:: getFinishcheckupday()
	 {
		 return Finishcheckupday;
	 }
	 void Mountainousrovers:: setFinishMaintenanceday(int day)
	 {
		  if (day>0)
			 FinishMaintenanceday=day;
	 }
	 int Mountainousrovers:: getFinishMaintenanceday()
	 {
		 return FinishMaintenanceday;
	 }
	 void Mountainousrovers:: setNomdone (int nomdone)
	 {
		 
			  Nomdone=nomdone;

	 }
	int Mountainousrovers:: getNomdone()
	{
		return Nomdone;
	}
	void Mountainousrovers:: incrementNumofcheckups()
	 {
		 Numofcheckups++;
	 }

	int Mountainousrovers:: getNumofcheckups()
	{
		return Numofcheckups;
	}
	int Mountainousrovers:: getExecutionDays(double TL,int MD)
	{
		//TL is the target loction km
		//MD is the mission duration in days
		int z;
		z=int (2*(TL/Speed));
		z=int (z/25);
		return (z+MD);
	}
	void Mountainousrovers:: incrementmissionsdone()
	{
       Nomdone++;
    }
Mountainousrovers::~Mountainousrovers(void)
{
}
