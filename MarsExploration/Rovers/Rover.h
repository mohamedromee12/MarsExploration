#pragma once
class Rover
{
	static int count;
protected:
	
	int ID;
	double Speed;
	double M_Speed; //max speed
	int Nom;   //=4   //number of missions can be done before checkup
	int CheckupDuration;  //number of days to finish checkup
	int Finishcheckupday;  //the day that the rover finish checkup in and ready to take mission
	int FinishMaintenanceday; //(bonus)the day that the rover finish Maintenance in and ready to take mission
	int Nomdone;     //number of missions done by rover before its checkup
	int Numofcheckups; //number of checkups done fore the rover
	
public:
	Rover();
	Rover(double speed ,int nom,int checkupDuration );
	virtual void setspeed(double speed);
	virtual double getspeed();
	virtual void setnumofmissions(int nom);
	virtual int getnumofmissions();
	virtual void setCheckupDuration(int checkupDuration); 
	virtual int getCheckupDuration();
	virtual void setFinishcheckupday(int day);
	virtual int getFinishcheckupday();
	virtual void setFinishMaintenanceday(int day);
	virtual int getFinishMaintenanceday();
	virtual void setNomdone (int nomdone);
	virtual int getNomdone();
	virtual void incrementNumofcheckups();
	virtual int getNumofcheckups();

	virtual int getExecutionDays(double TL,int MD);  //the needed time to reach target location and do the mission and return back to the station
	virtual void incrementmissionsdone();  //increment Nomdone to use it in checkup

	virtual void setid(int id);
	virtual int getid();

	virtual double get_mspeed();


	~Rover(void);
};

