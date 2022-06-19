#include "Rover.h"

Rover:: Rover(){}

int Rover::count = 0;

   Rover:: Rover(double speed ,int nom,int checkupDuration )
    {
		ID = ++count;

		if (speed>0 && nom>0 && checkupDuration>0)
		{
			Speed=speed;
			Nom=nom;
			CheckupDuration=checkupDuration;
		}
		else
		{
			Speed = 0;
			Nom = 0;
			CheckupDuration = 0;
		}
		Nomdone=0;    //intaial value
		Numofcheckups=0; //intaial value
		Finishcheckupday = 0;
		FinishMaintenanceday = 0;
		M_Speed=Speed;
    }
   void Rover:: setspeed(double speed)
	{
		if (speed>0)
			Speed=speed;
	}
	double Rover:: getspeed()
	{
		return Speed;
	}
	void Rover:: setnumofmissions(int nom)
	{
		if  (nom>0)
			Nom=nom;
	}
	int Rover:: getnumofmissions()
	{
		return Nom;
	}
	void Rover:: setCheckupDuration(int checkupDuration)
	{
		if ( checkupDuration>0)
			CheckupDuration=checkupDuration;
	}
	int Rover:: getCheckupDuration()
	{
		return CheckupDuration;
	}
	 void Rover:: setFinishcheckupday(int day)
	 {
		 if (day>0)
			 Finishcheckupday=day;
	 }
	 int Rover:: getFinishcheckupday()
	 {
		 return Finishcheckupday;
	 }
	 void Rover:: setFinishMaintenanceday(int day)
	 {
		  if (day>0)
			 FinishMaintenanceday=day;
	 }
	 int Rover:: getFinishMaintenanceday()
	 {
		 return FinishMaintenanceday;
	 }
	 void Rover:: setNomdone (int nomdone)
	 {
		
			  Nomdone=nomdone;

	 }
	int Rover:: getNomdone()
	{
		return Nomdone;
	}
	 void Rover:: incrementNumofcheckups()
	 {
		 Numofcheckups++;
	 }
	

	int Rover:: getNumofcheckups()
	{
		return Numofcheckups;
	}

	int Rover:: getExecutionDays(double TL,int MD)
	{
		//TL is the target loction km
		//MD is the mission duration in days
		int z;
		z=int (2*(TL/Speed));
		z=int (z/25);
		return (z+MD);
	}
	void Rover:: incrementmissionsdone()
	{
       Nomdone++;
    }


	void Rover::setid(int id){
		ID = id;
	}

	int Rover::getid(){
		return ID;
	}

	double Rover::get_mspeed()
	{
		return M_Speed;
	}




Rover::~Rover(void)
{
}
