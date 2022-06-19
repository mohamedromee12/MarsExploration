#include "MarsStation.h"
#include"UI.h"
#include <iostream>
using namespace std;
MarsStation::MarsStation(){
	ui = new UI(this);
	auto_promoted = 0;
	Day=1;
	modeOfSim = ui->getModeOfSim();
	autoP = 0;
}

void MarsStation::Simulate()
{
	ReadInput();               //reading the text file
	bool enterednumberofmount=false;
	if(modeOfSim == 3)
		ui->silentMode();
	//////////////////////////////////////////////////////////////////////////////////////////////////
	                            //     starting simulation from Day 1  //
	/////////////////////////////////////////////////////////////////////////////////////////////////

	while (!EventList.isEmpty() || !WPMList.isEmpty() || !WMMList.isEmpty() || !WEMList.isEmpty() || !IEList.isEmpty() ||!IMRList.isEmpty() || !ICURList.isEmpty())
	{
		if(modeOfSim != 3)
			ui->printDayNumber(Day);
		//////////////////////////////////////////////////////////////////////////////////////////
	     //  searching for the rovers which finished checkup and return it back to it's list //
		//////////////////////////////////////////////////////////////////////////////////////////
		bool condition1=true;
		while(!ICURList.isEmpty()&&condition1)
		{
			Rover *R;
			
			ICURList.peek(R);
			if (int (R->getFinishcheckupday()) == Day)
			{
				ICURList.remove(R);
				
				Emergencyrovers* R1 = dynamic_cast<Emergencyrovers*>(R);
				if(R1){
					R1->setNomdone(0);
                        WERList.add(R1,R->getspeed());
                     }     
				Polarrovers* R2 = dynamic_cast<Polarrovers*>(R);
				if(R2){
					R2->setNomdone(0);
                        WPRList.add(R2,R->getspeed());
                     }  
				Mountainousrovers* R3 = dynamic_cast<Mountainousrovers*>(R);
				if(R3){
					R3->setNomdone(0);
                        WMRList.add(R3,R->getspeed());
                     } 

			}
			else 
				condition1=false;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////


		///////////////////////////////////////////////////////////////////////////////////////////////////
		   //  searching for the rovers which finished Maintance and return it back to it's list //
		//////////////////////////////////////////////////////////////////////////////////////////////////
		bool condition2=true;
		while(!IMRList.isEmpty()&&condition2)
		{
			Rover *R;
			
			IMRList.peek(R);
			if (int (R->getFinishMaintenanceday()) == Day)
			{
				IMRList.remove(R);
				Emergencyrovers* R1 = dynamic_cast<Emergencyrovers*>(R);
				if(R1){
                        WERList.add(R1,R->getspeed());
                     }     
				Polarrovers* R2 = dynamic_cast<Polarrovers*>(R);
				if(R2){
                        WPRList.add(R2,R->getspeed());
                     }  
				Mountainousrovers* R3 = dynamic_cast<Mountainousrovers*>(R);
				if(R3){
                        WMRList.add(R3,R->getspeed());
                     } 

			}
			else 
				condition2=false;
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////

		failed_func(IEList);    // Check if there any mission failed 

		////////////////////////////////////////////////////////////////////////////////////////////////////////
		                                      // Execute the events //
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		bool condition3=true;
		while (!EventList.isEmpty()&&condition3 )
		{
			Event *E;
			EventList.peek(E);
			if (E->getED()==Day)
			{
				EventList.remove(E);
				FormulationEvent* E1 = dynamic_cast<FormulationEvent*>(E);
				if (E1)
				{
					E1->Execute(WEMList,WPMList,WMMList);
				}
				CancellationEvent* E2 = dynamic_cast<CancellationEvent*>(E);
				if (E2)
				{
					E2->Execute(WEMList,WPMList,WMMList);
				}
				PromotionEvent* E3 = dynamic_cast<PromotionEvent*>(E);
				if (E3)
				{
					E3->Execute(WEMList,WPMList,WMMList);
				}

			}
			else 
				condition3=false;

		}
		
		////////////////////////////////////////////////////////////////////////////////////////////////////
		  // searching for the mountainous mission which should be Auto promoted to Emergency mission //
		////////////////////////////////////////////////////////////////////////////////////////////////////

		bool z=true;
		while (!WMMList.isEmpty()&&z)
		{
			int index;
			bool entered =false;
	  MountainousMission* temp;
	  int N = WMMList.getLength();
	for (index = 0; index < N; index++)
	{
		if (z && index!=0 && entered)
			index--;
		if (WMMList.getEntry(index)->get_FD()+autoP == Day)
		{
			auto_promoted++;
			entered =true;
			z=true;
			WMMList.remove(index, temp);
	        EmergencyMission* newMission = new EmergencyMission(temp->get_id(), temp->get_tloc(), temp->get_mdur(), temp->get_si(), temp->get_FD());
	        delete temp;
	        WEMList.add(newMission, newMission->get_pri());
			
			N--;
		}
		else
			z=false;
	}
	

		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////


		///////////////////////////////////////////////////////////////////////////////////////////////////////
		            //  searching for the complited missions and return the rovers to it's lists //
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		bool condition4=true;
		while (!IEList.isEmpty()&&condition4)
		{
			Mission * M;
			IEList.peek(M);

			if (int (M->get_CD())==Day)
			{
				IEList.remove(M);
				CMList.add(M,(1/(M->get_CD())));
				Rover * R=M->get_R();
				R->incrementmissionsdone();

				//////////////////////add checkup condition here//////////////

				if (R->getNomdone()==R->getnumofmissions())        //if true : the Rover need to checkup
				{
					R->incrementNumofcheckups();
					R->setFinishcheckupday(Day+R->getCheckupDuration());  //setting the day in which the Rover will get out from checkup list
					ICURList.add(R,1.0/(R->getFinishcheckupday()));
				}

				//////////////////////add maintance condition here//////////////

				else if (R->getNumofcheckups()>2 && R->getNomdone()==int ((R->getnumofmissions()+1)/2))  //if true : the Rover need to maintance
				{
				int z=	(R->getCheckupDuration()+1)/2;
				int m=Day+z;
				R->setFinishMaintenanceday(m);     //setting the day in which the Rover will get out from maintance list
				IMRList.add(R,1.0/(R->getFinishMaintenanceday()));
				}

				////////////////////Return the Rover to it's list//////////////////////
				else
				{
					Emergencyrovers* R1 = dynamic_cast<Emergencyrovers*>(R);
				if(R1){
                        WERList.add(R1,R->getspeed());
                     }     
				Polarrovers* R2 = dynamic_cast<Polarrovers*>(R);
				if(R2){
                        WPRList.add(R2,R->getspeed());
                     }  
				Mountainousrovers* R3 = dynamic_cast<Mountainousrovers*>(R);
				if(R3){
                        WMRList.add(R3,R->getspeed());
                     } 
				}
				
			}
			else 
				condition4=false;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////



		///////////////////////////////////////////////////////////////////////////////////////////////////////
		                           //  Execute the Emergency Missions //
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		bool condition5=true;
		while (!WEMList.isEmpty()&&condition5)
		{
			EmergencyMission * ME;
			if (!WERList.isEmpty())   //if true : the mission will take an emergency Rover
			{
				WEMList.remove(ME);
				Emergencyrovers * R;
				WERList.remove(R);
				ME->set_R(R);                   // setting the Rover which will take the mission
				ME->set_WD((Day-(ME->get_FD())));        //setting waiting days of the mission
				int D =R->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);                                                 //setting the execution days of the mission
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());       //setting the complition day of the mission
				IEList.add(ME,(1.0/(ME->get_CD())));        //adding the mission to in execution missions list
			}


			else if (!WMRList.isEmpty())    //if true : the mission will take  Mountainous Rover
			{
				WEMList.remove(ME);
				Mountainousrovers * R;
				WMRList.remove(R);
				ME->set_R(R);                   // setting the Rover which will take the mission
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);                                     //setting the execution days of the mission
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());        //setting the complition day of the mission
				IEList.add(ME,(1.0/(ME->get_CD())));                       //adding the mission to in execution missions list
			}


			else if (!WPRList.isEmpty())            //if true : the mission will take  Polar Rover
			{
				WEMList.remove(ME);
				Polarrovers * R;
				WPRList.remove(R);
				ME->set_R(R);                    // setting the Rover which will take the mission
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);                                           //setting the execution days of the mission
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());             //setting the complition day of the mission
				IEList.add(ME,(1.0/(ME->get_CD())));                      //adding the mission to in execution missions list
			}



			else if (!IMRList.isEmpty())           //if true : the mission will take Rover from the in maintance list
			{
				LinkedPriorityQueue<Rover*>temp;      //temp of inmaintance list
				Rover * R;
				bool found=false;
				while (!IMRList.isEmpty()&& !found)        //searching for emergency rover first
				{
				IMRList.remove(R);
				Emergencyrovers* R1 = dynamic_cast<Emergencyrovers*>(R);
				if(R1){
					WEMList.remove(ME);
                       R1->setspeed(R1->getspeed()/2);        //setting the rover speed to half of the original speed
					   ME->set_R(R1);
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R1->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());
				IEList.add(ME,(1.0/(ME->get_CD())));
				found=true;
                     }     
				else
				{
					temp.add(R,1.0/(R->getFinishMaintenanceday()));
				}
				}

				while (!temp.isEmpty()&& !found)    //if we didn't find emergency rover we search for Mountainous rover
				{
					temp.remove(R);
				Mountainousrovers* R2 = dynamic_cast<Mountainousrovers*>(R);
				if(R2){
					WEMList.remove(ME);
                       R2->setspeed(R2->getspeed()/2);         //setting the rover speed to half of the original speed
					   ME->set_R(R2);
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R2->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());
				IEList.add(ME,(1.0/(ME->get_CD())));
				found=true;
                     }     
				else
				{
					IMRList.add(R,1.0/(R->getFinishMaintenanceday()));
				}
				}
				while (!IMRList.isEmpty()&& !found)      //if we didn't find emergency rover or Mountainous rover we search for polar rover
				{
				IMRList.remove(R);
				Polarrovers* R3 = dynamic_cast<Polarrovers*>(R);
				if(R3){
					WEMList.remove(ME);
                       R3->setspeed(R3->getspeed()/2);          //setting the rover speed to half of the original speed
					   ME->set_R(R3);
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R3->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());
				IEList.add(ME,(1.0/(ME->get_CD())));
				found=true;
                     }     
				else
				{
					temp.add(R,1.0/(R->getFinishMaintenanceday()));
				}
				}
				while (!temp.isEmpty())        //return the rovers to the original maintance list
				{
					temp.remove(R);
					IMRList.add(R,(1.0/R->getFinishMaintenanceday()));
				}
				condition5=found;
			}
			else 
				condition5=false;         //there is no rovers to take the mission

		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////


		////////////////////////////////////////////////////////////////////////////////////////////////////////
		                                //  Execute the Polar Missions //
		////////////////////////////////////////////////////////////////////////////////////////////////////////

		bool condition6=true;
		while (!WPMList.isEmpty()&&condition6)         //if true : the mission will take  Polar Rover
		{
			PolarMission * ME;
			
			 if (!WPRList.isEmpty())
			{
				WPMList.dequeue(ME);
				Polarrovers * R;
				WPRList.remove(R);
				ME->set_R(R);                      // setting the Rover which will take the mission
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);                                          //setting the execution days of the mission
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());       //setting the complition day of the mission
				IEList.add(ME,(1.0/(ME->get_CD())));                 //adding the mission to in execution missions list
			}

			 else if (!IMRList.isEmpty())     //searching for a polar rover to take the mission in maintance list
			{
				LinkedPriorityQueue<Rover*>temp;         //temp of inmaintance list
				Rover * R;
				bool found=false;
				
				while (!IMRList.isEmpty()&& !found)
				{
				IMRList.remove(R);
				Polarrovers* R3 = dynamic_cast<Polarrovers*>(R);
				if(R3){
					WPMList.dequeue(ME);
                       R3->setspeed(R3->getspeed()/2);           //setting the rover speed to half of the original speed
					   ME->set_R(R3);
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R3->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());
				IEList.add(ME,(1.0/(ME->get_CD())));
				found=true;
                     }     
				else
				{
					temp.add(R,1/(R->getFinishMaintenanceday()));      //adding the nonpolar rovers in the temp
				}
				}
				while (!temp.isEmpty())          //return the rovers to the original maintance list
				{
					temp.remove(R);
					IMRList.add(R,(1.0/R->getFinishMaintenanceday()));
				}
				condition6=found;
			 }
			else 
				condition6=false;          //there is no rovers to take the mission

		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		                               //  Execute the Mountainous Missions //
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////

		bool condition7=true;
		while (!WMMList.isEmpty()&&condition7)
		{
			MountainousMission * ME;
			if (!WMRList.isEmpty())          //if true : the mission will take an Mountainous Rover
			{
				WMMList.remove(0,ME);
				Mountainousrovers * R;
				WMRList.remove(R);
				ME->set_R(R);                          // setting the Rover which will take the mission
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);                                        //setting the execution days of the mission
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());     //setting the complition day of the mission
				IEList.add(ME,(1.0/(ME->get_CD())));                  //adding the mission to in execution missions list
			}

			else if (!WERList.isEmpty())           //if true : the mission will take an Emergency Rover
			{
				WMMList.remove(0,ME);
				Emergencyrovers * R;
				WERList.remove(R);
				ME->set_R(R);                         // setting the Rover which will take the mission
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);                                         //setting the execution days of the mission
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());     //setting the complition day of the mission
				IEList.add(ME,(1.0/(ME->get_CD())));                  //adding the mission to in execution missions list
			}

			else if (!IMRList.isEmpty())             //if true : the mission will take Rover from the in maintance list
			{
				LinkedPriorityQueue<Rover*>temp;          //temp of inmaintance list
				Rover * R;
				bool found=false;
				while (!IMRList.isEmpty()&& !found)   //searching for Mountainous rover in inmaintance list
				{
				IMRList.remove(R);
				Mountainousrovers* R2 = dynamic_cast<Mountainousrovers*>(R);
				if(R2){
					WMMList.remove(0,ME);
                       R2->setspeed(R2->getspeed()/2);           //setting the rover speed to half of the original speed
					   ME->set_R(R2);                  // setting the Rover which will take the mission
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R2->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);                                      //setting the execution days of the mission
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());        //setting the complition day of the mission
				IEList.add(ME,(1.0/(ME->get_CD())));                   //adding the mission to in execution missions list
				found=true;
                     }     
				else
				{
					temp.add(R,1.0/(R->getFinishMaintenanceday()));     //adding the nonMountainous rovers in the temp
				}
				}

				while (!temp.isEmpty()&& !found)      //if we didn't find Mountainous rover in inmaintance list we search for emergency rover
				{
					temp.remove(R);
				Emergencyrovers* R1 = dynamic_cast<Emergencyrovers*>(R);
				if(R1){
					WMMList.remove(0,ME);
                       R1->setspeed(R1->getspeed()/2);          //setting the rover speed to half of the original speed
					   ME->set_R(R1);                   // setting the Rover which will take the mission
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R1->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);                                       //setting the execution days of the mission
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());      //setting the complition day of the mission
				IEList.add(ME,(1.0/(ME->get_CD())));
				found=true;
                     }     
				else
				{
					IMRList.add(R,1.0/(R->getFinishMaintenanceday()));   //return the rovers to the original maintance list
				}
				}
				condition7=found;
			}
		
			else 
				condition7=false;       //there is no rovers to take the mission
			

		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(modeOfSim == 1){
			ui->printDataOfDay(Day);
			ui->waitEnter();
		}else if(modeOfSim == 2){
			ui->printDataOfDay(Day);
			ui->waitSecond();
		}
		Day++;
	}
	ui->createOutputFile();
}

void MarsStation::ReadInput(){
	ui->loadInputFile();
}

void MarsStation::createMrovers(int n, double* speed, int nom, int checkUp){
	for(int i = 0; i < n; i++){
		Mountainousrovers* newMrover = new Mountainousrovers(speed[i], nom, checkUp);
		WMRList.add(newMrover, speed[i]);
	}
}

void MarsStation::createProvers(int n, double* speed, int nom, int checkUp){
	for(int i = 0; i < n; i++){
		Polarrovers* newMrover = new Polarrovers(speed[i], nom, checkUp);
		WPRList.add(newMrover, speed[i]);
	}
}

void MarsStation::createErovers(int n, double* speed, int nom, int checkUp){
	for(int i = 0; i < n; i++){
		Emergencyrovers* newMrover = new Emergencyrovers(speed[i], nom, checkUp);
		WERList.add(newMrover, speed[i]);
	}
}

void MarsStation::setAutoP(int n){
	autoP = n;
}

void MarsStation::addFEvent(MissionType type, int ed, int id, int tloc, int mdur, int sig){
	FormulationEvent* fEvent = new FormulationEvent(type, ed, id, tloc, mdur, sig);
	EventList.add(fEvent, 10.0/ed);
}

void MarsStation::addXEvent(int ed, int id){
	CancellationEvent* xEvent = new CancellationEvent(ed, id);
	EventList.add(xEvent, 10.0/ed);
}

void MarsStation::addPEvent(int ed, int id){
	PromotionEvent* pEvent = new PromotionEvent(ed, id);
	EventList.add(pEvent, 10.0/ed);
}

LinkedPriorityQueue<Mission*>* MarsStation::completedMissions(){
	return &CMList;
}

LinkedPriorityQueue<Polarrovers*>* MarsStation::polarRovers(){
	return &WPRList;
}

LinkedPriorityQueue<Mountainousrovers*>* MarsStation::mountRovers(){
	return &WMRList;
}

LinkedPriorityQueue<Emergencyrovers*>* MarsStation::emergRovers(){
	return &WERList;
}

LinkedQueue<PolarMission*>* MarsStation::polarMissions(){
	return  &WPMList;
}

LinkedList<MountainousMission*>* MarsStation::mountMissions(){
	return &WMMList;
}

LinkedPriorityQueue<EmergencyMission*>* MarsStation::emergMissions(){
	return &WEMList;
}

LinkedPriorityQueue<Mission*>* MarsStation::inExec(){
	return &IEList;
}

LinkedPriorityQueue<Rover*>* MarsStation::inCheck(){
	return &ICURList;
}

LinkedPriorityQueue<Rover*>* MarsStation::inMaint(){
	return &IMRList;
}

void MarsStation::setMode(int mode){
	modeOfSim = mode;
}

int MarsStation::getMode(){
	return modeOfSim;
}

int MarsStation::getAutoPromoted(){
	return auto_promoted;
}

void MarsStation::failed_func(LinkedPriorityQueue<Mission*>& ine_M)
{
	Mission* m;
	if(ine_M.isEmpty())
		return;
	ine_M.remove(m);

	failed_func(ine_M);  //recursive call to get whole mission in the list

	if(m->get_sprob()<=Day)  // check if rovers arrive to the target location and execute the mission
	{
		ine_M.add(m,(1.0/(m->get_CD())));
		return;
	}
	else if(m->get_fprob()<=0 && m->get_R()->getNomdone()!=0)  // check if the mission failed
	{
		if(modeOfSim != 3)
			ui->printFailedMission(m->get_id());

		///////////////////////////////////////////////////////////////
		//////////// send rover to be checked up  /////////////////////
		///////////////////////////////////////////////////////////////

		Rover* r;

		r=m->get_R();
		m->set_R(nullptr);

		if(m->get_td_days()>Day) // check rover if not arrive to the target location
		{
			r->setFinishcheckupday(Day+(Day-m->get_FD()-m->get_WD())+r->getCheckupDuration());
			ICURList.add(r,1.0/(r->getFinishcheckupday()));
			r->incrementNumofcheckups();
		}
		else
		{
			r->setFinishcheckupday(Day+(m->get_td_days()-m->get_FD()-m->get_WD())+r->getCheckupDuration());
			ICURList.add(r,1.0/(r->getFinishcheckupday()));
			r->incrementNumofcheckups();
		}

		/////////////////////////////////////////////////////////////////////////////////
		///////////// re-formulate the mission and add to waiting missio n///////////////
		/////////////////////////////////////////////////////////////////////////////////
		
		m->set_FD(Day);
		MountainousMission* MM=dynamic_cast<MountainousMission*>(m);
		if(MM)
			WMMList.insert(MM);
		EmergencyMission* EM=dynamic_cast<EmergencyMission*>(m);
		if(EM)
			WEMList.add(EM,EM->get_pri());
		PolarMission* PM=dynamic_cast<PolarMission*>(m);
		if(PM)
			WPMList.enqueue(PM);

		

		return;
	}

	else  // mission in-executing and changes failed probability 
	{
		m->set_fprob(m->get_fprob() - ((float) rand()/RAND_MAX));
		ine_M.add(m,(1.0/(m->get_CD())));
		return;
	}


}

MarsStation::~MarsStation(){
	delete ui;
}