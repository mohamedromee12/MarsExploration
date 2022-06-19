#include "UI.h"
#include "MarsStation.h"
#include <iostream>
#include <fstream>
#include<direct.h>
#include<Windows.h>
using namespace std;

UI::UI(MarsStation* st){		//	constructor
	station = st;
	inputfile = "";
}

void UI::loadInputFile(){						//	loading input file

	ifstream inputFile;							//	creating input file stream
	do {
		std::cout << "Please enter the name of the input file" << endl;
		cin >> inputfile;
		cin.ignore();
		inputFile.open("Input\\" + inputfile + ".txt", ios::in);		
	} while (!inputFile.is_open());				//Checking if the file is open		
	int M, P, E, N, CM, CP, CE;
	double* SM;
	double* SP;
	double* SE;
	char eventType;
	int ed, id;

	if(inputFile.is_open()){
		inputFile >> M >> P >> E;			//	num of each type of rovers
		SM = new double[M];
		SP = new double[P];
		SE = new double[E];
		//	speed of each rover
		for(int i = 0; i < M; i++)
			inputFile >> SM[i];
		for(int i = 0; i < P; i++)
			inputFile >> SP[i];
		for(int i = 0; i < E; i++)
			inputFile >> SE[i];
		
		inputFile >> N >> CM >> CP >> CE;	//	num of missions before checkup and the checkup durations

		//	creating rovers
		station->createMrovers(M, SM, N, CM);
		station->createProvers(P, SP, N, CP);
		station->createErovers(E, SE, N, CE);

		inputFile >> N;						//	autoP
		station->setAutoP(N);

		inputFile >> N;						//	num of evevts
		for(int i = 1; i <= N; i++){
			inputFile >> eventType;
			//	formulation event
			if(eventType == 'F'){
				char mType;
				inputFile >> mType;
				//	type of the mission
				MissionType type = (mType == 'E')? MissionType::E : ((mType == 'P')? MissionType::P : MissionType::M);
				int tloc, mdur, sig;
				inputFile >> ed >> id >> tloc >> mdur >> sig;
				station->addFEvent(type, ed, id, tloc, mdur, sig);		//	creating formulation event
			//	promotion event
			}else if(eventType == 'P'){
				inputFile >> ed >> id;
				station->addPEvent(ed, id);		//	creating promotion event
			//	cancellation event
			}else if(eventType == 'X'){
				inputFile >> ed >> id;
				station->addXEvent(ed, id);		//	creating cancellation event
			//	nothing
			}else{
				//	skip this incorrect line
			}
		}
		inputFile.close();		//	closing input file
		delete[]SM;
		delete[]SP;
		delete[]SE;
	}
	
}

void UI::createOutputFile(){
	LinkedPriorityQueue<Mission*> *CM = station->completedMissions();		//	address of CMList
	LinkedPriorityQueue<Polarrovers*>* P = station->polarRovers();			//	address of WPRList
	LinkedPriorityQueue<Mountainousrovers*>* M = station->mountRovers();	//	address of WMRList
	LinkedPriorityQueue<Emergencyrovers*>* E = station->emergRovers();		//	address of WERList

	ofstream outputFile("Output\\" + inputfile + "_Output.txt", ios::out);			//	creating output file stream

	if(outputFile.is_open())
	{ }
	else if(_mkdir("Output") == 0) //create the Save Directory and check if created successfully
	{		
		outputFile.open("Output\\" + inputfile + "_Output.txt", ios::out);
	}
	if(outputFile.is_open()){
		outputFile << "CD" << "\t" << "ID" << "\t" << "FD" << "\t" << "WD" << "\t" << "ED\n";
		Mission* mission;
		Polarrovers* pRoverPtr;
		Mountainousrovers* mRoverPtr;
		Emergencyrovers* eRoverPtr;

		int totalWait = 0, totalExecution = 0, totalMissions = 0, Emission = 0, Pmission = 0, Mmission = 0;
		int Erovers = 0, Mrovers = 0, Provers = 0;

		//	count num of polar rovers
		while(P->remove(pRoverPtr))
			Provers++;
		//	count num of mount rovers
		while(M->remove(mRoverPtr))
			Mrovers++;
		//	count num of emerg rovers
		while(E->remove(eRoverPtr))
			Erovers++;
		//	count num of missions
		while(CM->remove(mission)){
			totalMissions++;
			if(dynamic_cast<EmergencyMission*>(mission))
				Emission++;
			else if(dynamic_cast<PolarMission*>(mission))
				Pmission++;
			else if(dynamic_cast<MountainousMission*>(mission))
				Mmission++;

			totalWait += mission->get_WD();
			totalExecution += mission->get_ED();

			outputFile << mission->get_CD() << "\t" << mission->get_id() << "\t" << mission->get_FD() << "\t" << mission->get_WD() << "\t" << mission->get_ED() << "\n";
		}

		outputFile << "....................................................\n....................................................\n";
		//	statistics of the system
		outputFile << "Missions: " << totalMissions << " [M: " << Mmission << ", P: " << Pmission << ", E: " << Emission << "]\n";

		outputFile << "Rovers: " << Provers+Mrovers+Erovers << "[M: " << Mrovers << ", P: " << Provers << ", E: " << Erovers << "]\n";
		if(!totalMissions){
			outputFile << "Avg Wait= " << 0 << ", Avg Exec = " << 0 << "\n";

			outputFile << "Auto-Promoted: " << 0 << "%\n"; 
		}else if(!(Mmission + station->getAutoPromoted())){
			outputFile << "Avg Wait= " << 1.0*totalWait/totalMissions << ", Avg Exec = " << 1.0*totalExecution/totalMissions << "\n";

			outputFile << "Auto-Promoted: " << 0 << "%\n";
		}else{
			outputFile << "Avg Wait= " << 1.0*totalWait/totalMissions << ", Avg Exec = " << 1.0*totalExecution/totalMissions << "\n";

			outputFile << "Auto-Promoted: " << 100.0*station->getAutoPromoted()/(Mmission + station->getAutoPromoted()) << "%\n"; 
		}
		
	}
	outputFile.close();		//	closing output file
	std::cout << "Simulation ends, Output file created\n";
}

void UI::printDataOfDay(int day){
	LinkedQueue<PolarMission*>* WPMList = station->polarMissions();					//	Pointer to the waiting polar missions
	LinkedList<MountainousMission*>* WMMList =station->mountMissions();				//	Pointer to the waiting mount missions
	LinkedPriorityQueue<EmergencyMission*>* WEMList = station->emergMissions();		//	Pointer to the waiting emerg missions
	LinkedPriorityQueue<Mission*>* inExecution = station->inExec();					//	Pointer to the in execution missions
	LinkedPriorityQueue<Polarrovers*>* WPRList = station->polarRovers();			//	Pointer to the waiting polar rovers
	LinkedPriorityQueue<Mountainousrovers*>* WMRList = station->mountRovers();		//	Pointer to the waiting mount rovers
	LinkedPriorityQueue<Emergencyrovers*>* WERList = station->emergRovers();		//	Pointer to the waiting emerg rovers
	LinkedPriorityQueue<Rover*>* ICURList = station->inCheck();						//	Pointer to the in check-up rovers
	LinkedPriorityQueue<Rover*>* IMRList = station->inMaint();						//	Pointer to the in maintainance rovers
	LinkedPriorityQueue<Mission*>* CMList = station->completedMissions();			//	Pointer to the in in completed missions
	

	LinkedQueue<Mission*> missionTemp;						//temp queue for missions
	LinkedQueue<PolarMission*> pMissionTemp;				//temp queue for polar missions
	LinkedQueue<MountainousMission*> mMissionTemp;			//temp queue for mount missions
	LinkedQueue<EmergencyMission*> eMissionTemp;			//temp queue for emerg missions
	LinkedQueue<Rover*> roverTemp;							//temp queue for rovers
	LinkedQueue<Polarrovers*> PRoverTemp;					//temp queue for polar rovers
	LinkedQueue<Mountainousrovers*> MRoverTemp;				//temp queue mount for rovers
	LinkedQueue<Emergencyrovers*> ERoverTemp;				//temp queue for emerg rovers


	PolarMission* pMissionPtr;							//	Pointer to polar mission
	MountainousMission* mMissionPtr;					//	Pointer to mount mission
	EmergencyMission* eMissionPtr;						//	Pointer to emerg mission
	Mission* mission;									//	Pointer to mission
	Polarrovers* pRoverPtr;								//	Pointer to polar rover
	Mountainousrovers* mRoverPtr;						//	Pointer to mount rover
	Emergencyrovers* eRoverPtr;							//	Pointer to emerg rover
	Rover* rover;										//	Pointer to rover

	string dayDetails = "[";
	int n = 0;

	//	std::cout << "Current day:" << day << "\n";
	
	//////////////////////////////////////////////////////////
	//	Printing waiting missions	//////////////////////////
	//////////////////////////////////////////////////////////

	//	Getting IDs of waiting emerg missions
	while(WEMList->remove(eMissionPtr)){
		n++;
		dayDetails += (to_string(eMissionPtr->get_id())+",");
		eMissionTemp.enqueue(eMissionPtr);
	}
	//returning the missions to its DS
	while (!eMissionTemp.isEmpty())
	{
		eMissionTemp.dequeue(eMissionPtr);
		WEMList->add(eMissionPtr, eMissionPtr->get_pri());
	}
	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	dayDetails += "] (";
	
	//	Getting IDs of waiting polar missions
	while(WPMList->dequeue(pMissionPtr)){
		n++;
		dayDetails += (to_string(pMissionPtr->get_id())+",");
		pMissionTemp.enqueue(pMissionPtr);
	}
	//returning the missions to its DS
	while (!pMissionTemp.isEmpty())
	{
		pMissionTemp.dequeue(pMissionPtr);
		WPMList->enqueue(pMissionPtr);
	}
	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	dayDetails += ") {";

	//	Getting IDs of waiting mount missions
	int m = 0;
	while(WMMList->remove(m ,mMissionPtr)){			//	how to remove each element in this list??
		n++;
		dayDetails += (to_string(mMissionPtr->get_id())+",");
		mMissionTemp.enqueue(mMissionPtr);
	}
	//returning the missions to its DS
	while (!mMissionTemp.isEmpty())
	{
		mMissionTemp.dequeue(mMissionPtr);
		WMMList->insert(mMissionPtr);
	}
	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	dayDetails += "}";

	std::cout << n << " Waiting Missions: " << dayDetails << endl;

	//////////////////////////////////////////////////////////
	//	Printing in execution missions	//////////////////////
	//////////////////////////////////////////////////////////
	n = 0;
	dayDetails = "[";
	string dayDetails2 = "(";
	string dayDetails3 = "{";

	while(inExecution->remove(mission)){
		n++;
		if(dynamic_cast<EmergencyMission*>(mission)){
			dayDetails += (to_string(mission->get_id()) + "/" + to_string(mission->get_R()->getid()));
			dayDetails += ",";
		}else if(dynamic_cast<PolarMission*>(mission)){
			dayDetails2 += (to_string(mission->get_id()) + "/" + to_string(mission->get_R()->getid()));
			dayDetails2 += ",";
		}else if(dynamic_cast<MountainousMission*>(mission)){
			dayDetails3 += (to_string(mission->get_id()) + "/" + to_string(mission->get_R()->getid()));
			dayDetails3 += ",";
		}
		missionTemp.enqueue(mission);
	}
	//returning the missions to its DS
	while (!missionTemp.isEmpty())
	{
		missionTemp.dequeue(mission);
		inExecution->add(mission, 100.0/(mission->get_CD()));
	}
	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	if(dayDetails2.back() == ',')
		dayDetails2.pop_back();
	if(dayDetails3.back() == ',')
		dayDetails3.pop_back();

	dayDetails += "]";
	dayDetails2 += ")";
	dayDetails3 += "}";

	std::cout << n << " In-Execution Missions/Rovers: " << dayDetails << " " << dayDetails2 << " " << dayDetails3 << endl;

	//////////////////////////////////////////////////////////
	//	printing available rovers	//////////////////////////
	//////////////////////////////////////////////////////////

	n = 0;
	dayDetails = "[";
	//	Getting IDs of waiting emerg rovers
	while(WERList->remove(eRoverPtr)){
		n++;
		dayDetails += (to_string(eRoverPtr->getid())+",");
		ERoverTemp.enqueue(eRoverPtr);
	}
	//returning the Rovers to its DS
	while (!ERoverTemp.isEmpty())
	{
		ERoverTemp.dequeue(eRoverPtr);
		WERList->add(eRoverPtr, eRoverPtr->getspeed());
	}
	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	dayDetails += "] (";
	
	//	Getting IDs of waiting polar rovers
	m = 0;
	while(WPRList->remove(pRoverPtr)){
		n++;
		dayDetails += (to_string(pRoverPtr->getid())+",");
		PRoverTemp.enqueue(pRoverPtr);
	}
	//returning the Rovers to its DS
	while (!PRoverTemp.isEmpty())
	{
		PRoverTemp.dequeue(pRoverPtr);
		WPRList->add(pRoverPtr, pRoverPtr->getspeed());
	}
	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	dayDetails += ") {";

	//	Getting IDs of waiting mount rovers
	while(WMRList->remove(mRoverPtr)){
		n++;
		dayDetails += (to_string(mRoverPtr->getid()) + ",");
		MRoverTemp.enqueue(mRoverPtr);
	}
	//returning the Rovers to its DS
	while (!MRoverTemp.isEmpty())
	{
		MRoverTemp.dequeue(mRoverPtr);
		WMRList->add(mRoverPtr, mRoverPtr->getspeed());
	}
	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	dayDetails += "}";

	std::cout << n << " Available Rovers: " << dayDetails << endl;

	//////////////////////////////////////////////////////////
	//	printing in checkup rovers	//////////////////////////
	//////////////////////////////////////////////////////////

	n = 0;
	dayDetails = "[";
	dayDetails2 = "(";
	dayDetails3 = "{";

	while(ICURList->remove(rover)){
		n++;
		if(dynamic_cast<Emergencyrovers*>(rover))
			dayDetails += (to_string(rover->getid()) + ",");
		else if(dynamic_cast<Polarrovers*>(rover))
			dayDetails2 += (to_string(rover->getid()) + ",");
		else if(dynamic_cast<Mountainousrovers*>(rover))
			dayDetails3 += (to_string(rover->getid()) + ",");
		roverTemp.enqueue(rover);
	}

	//returning the Rovers to its DS
	while (!roverTemp.isEmpty())
	{
		roverTemp.dequeue(rover);
		ICURList->add(rover, (100.0/rover->getFinishcheckupday()));
	}

	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	if(dayDetails2.back() == ',')
		dayDetails2.pop_back();
	if(dayDetails3.back() == ',')
		dayDetails3.pop_back();

	dayDetails += "]";
	dayDetails2 += ")";
	dayDetails3 += "}";

	std::cout << n << " In-Checkup Rovers: " << dayDetails << " " << dayDetails2 << " " << dayDetails3 << endl;
	
	//////////////////////////////////////////////////////////
	//	printing in maintainance rovers	//////////////////////
	//////////////////////////////////////////////////////////

	n = 0;
	dayDetails = "[";
	dayDetails2 = "(";
	dayDetails3 = "{";

	while(IMRList->remove(rover)){
		n++;
		if(dynamic_cast<Emergencyrovers*>(rover))
			dayDetails += (to_string(rover->getid()) + ",");
		else if(dynamic_cast<Polarrovers*>(rover))
			dayDetails2 += (to_string(rover->getid()) + ",");
		else if(dynamic_cast<Mountainousrovers*>(rover))
			dayDetails3 += (to_string(rover->getid()) + ",");
		roverTemp.enqueue(rover);
	}

	//returning the Rovers to its DS
	while (!roverTemp.isEmpty())
	{
		roverTemp.dequeue(rover);
		IMRList->add(rover, (100.0/rover->getFinishcheckupday()));
	}

	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	if(dayDetails2.back() == ',')
		dayDetails2.pop_back();
	if(dayDetails3.back() == ',')
		dayDetails3.pop_back();

	dayDetails += "]";
	dayDetails2 += ")";
	dayDetails3 += "}";

	std::cout << n << " In-Maintainance Rovers: " << dayDetails << " " << dayDetails2 << " " << dayDetails3 << endl;
	
	//////////////////////////////////////////////////////
	//	Printing completed missions	//////////////////////
	//////////////////////////////////////////////////////

	n = 0;
	dayDetails = "[";
	dayDetails2 = "(";
	dayDetails3 = "{";

	while(CMList->remove(mission)){
		n++;
		if(dynamic_cast<EmergencyMission*>(mission))
			dayDetails += (to_string(mission->get_id()) + ",");
		else if(dynamic_cast<PolarMission*>(mission))
			dayDetails2 += (to_string(mission->get_id()) + ",");
		else if(dynamic_cast<MountainousMission*>(mission))
			dayDetails3 += (to_string(mission->get_id()) + ",");
		missionTemp.enqueue(mission);
	}

	//returning the Missions to its DS
	while (!missionTemp.isEmpty())
	{
		missionTemp.dequeue(mission);
		CMList->add(mission, (100.0/mission->get_CD()));		//check this should it be like this or FD 
	}

	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	if(dayDetails2.back() == ',')
		dayDetails2.pop_back();
	if(dayDetails3.back() == ',')
		dayDetails3.pop_back();

	dayDetails += "]";
	dayDetails2 += ")";
	dayDetails3 += "}";

	std::cout << n << " Completed Missions: " << dayDetails << " " << dayDetails2 << " " << dayDetails3 << endl << endl << endl;

}

void UI::silentMode(){
	std::cout << "Silent Mode\n";		//	message of the silent mode
}

void UI::waitEnter(){
	while(true)
		if (cin.get() == '\n'){			//	waiting until enter is pressed
			//cin.ignore();
			break;
		}
}

void UI::waitSecond(){
	Sleep(1000);		//	waiting 1 second
}

int UI::getModeOfSim(){
	std::cout << "Select The Mode Of Simulation: \n-------------------------------\n";
	std::cout << "1) Interactive Mode\n";
	std::cout << "2) Step-By-Step Mode\n";
	std::cout << "3) Silent Mode\n";
	int mode;
	cin >> mode;
	cin.ignore();
	while(mode != 1 && mode !=  2 && mode != 3){
		std::cout << "Enter Correct Choice: ";
		cin >> mode;
		cin.ignore();
	}
	std::cout << "\nSimulation Starts...\n";
	return mode;
}

void UI::printFailedMission(int id){
	cout << "\nFAILUR: Mission #" << id << endl;
}

void UI::printDayNumber(int day){
	cout << "Current day:" << day << "\n";
}
