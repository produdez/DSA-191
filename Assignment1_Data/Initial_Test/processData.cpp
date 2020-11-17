/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "processData.h"

/* You can implement methods, functions that support your data structures here.
 * */
using namespace std;

void Initialization() {
    // If you use global variables, please initialize them explicitly in this function.
}

void Finalization() {
    // Release your data before exiting
}

void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &N) {
	stringstream ss(pRequest);
	string request = "";
	ss >> request;

	if (request == "CL") { // 2 cases, count lines or lines in a city
		CL(pRequest, pData, pOutput, N);
	}
	else if (request == "LSC") { //list stations city
		LSC(pRequest, pData, pOutput, N);
	}
	else if (request == "LLC") { //list lines city
		LLC(pRequest, pData, pOutput, N);
	}
	else if (request == "LSL") { // list stations line
		LSL(pRequest, pData, pOutput, N);
	}
	else if (request == "FC") { // find city
		FC(pRequest, pData, pOutput, N);
	}
	else if (request == "FS") { // find station
		FS(pRequest, pData, pOutput, N);
	}
	else if (request == "SLP") { // station line_string position
		SLP(pRequest, pData, pOutput, N);
	}
	else if (request == "IS") { // insert station
		IS(pRequest, pData, pOutput, N);
	}
	else if (request == "RS") { // remove station
		RS(pRequest, pData, pOutput, N);
	}
	else if (request == "US") { // update station
		US(pRequest, pData, pOutput, N);
	}
	else if (request == "ISL") { // insert station_line
		ISL(pRequest, pData, pOutput, N);
	}
	else if (request == "RSL") { // remove station_line
		RSL(pRequest, pData, pOutput, N);
	}
	//Test function
	else if (request == "PRINT")
	{
		request = pRequest;
		int data_N = std::stoi(request.substr(request.find(' ') + 1));
		PrintData(pData, data_N);
	}
	//Test function
	else { // Wrong choice !! 
		cout << "Wrong request" << endl;
		return;
	}




    //  Implement this function for processing a request
    // NOTE: You can add other functions to support this main process.
    //       pData is a pointer to a data structure that manages the dataset
    //       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
    //       N is the size of output, must be a non-negative number
}

void CL(const char* pRequest, void* pData, void*& pOutput, int& N)
{
	TDataset* data = static_cast<TDataset*>(pData);
	int* line_count= new int[1];
	string request = pRequest;
	if (request == "CL") *line_count = data->lines->getSize();
	else
	{
		string city_name = request.substr(request.find(' ')+1);
		int city_id=-1;
		Iterator<TCity> iCity = *data->cities->iterator();
		while (!iCity.atEnd())
		{
			if ((*iCity).data.name == city_name)
			{
				city_id = (*iCity).data.id;
				break;
			}
			iCity++;
		}
		if (city_id == -1) // no found city, fail
		{
			N = 1;
			*line_count = -1;
			pOutput = line_count;
			line_count = nullptr;
			return;
		}
		Iterator<TLine> iLine = *data->lines->iterator();
		*line_count = 0;
		while (!iLine.atEnd())
		{
			if ((*iLine).data.city_id == city_id)
			{
				(*line_count)++;
			}
			iLine++;
		}
	}
	N = 1;
	pOutput = line_count;
	line_count = nullptr;
}

void LSC(const char* pRequest, void* pData, void*& pOutput, int& N)
{
	//TODO: For LSC,LLC and LSL, is there a fail case when city/line not found?
	// Or do we just output nothing like this: "LSC Wrong_city_name: ...(nothing)"?
	TDataset* data = static_cast<TDataset*>(pData);
	string request = pRequest;
	string city_name = request.substr(request.find(' ') + 1);
	int city_id = -1;
	Iterator<TCity> iCity = *data->cities->iterator();
	while (!iCity.atEnd())
	{
		if ((*iCity).data.name == city_name)
		{
			city_id = (*iCity).data.id;
			break;
		}
		iCity++;
	}
	// after the above we have the city id
	// the station ids are in list below
	L1List<int>* id_list = new L1List<int>();
	//iterator for id list (output) ..
	Iterator<int> iID = *id_list->iterator();
	// ..and station list (data)
	Iterator<TStation> iStation = *data->stations->iterator();
	while (!iStation.atEnd()) 
	{
		if ((*iStation).data.city_id == city_id)
		{
			id_list->insertAfter(iID, (*iStation).data.id);
			iID++;
		}
		iStation++;
	}
	// format the id_list to pointer and done!
	N = id_list->getSize();
	int* station_ids = new int[N];

	//copy the linked_list's data to the pointer and delete the link_list
	// Can't have the pointer point to each element in linked list? :<
	iID = *id_list->iterator();
	for (int i = 0; i < N; i++)
	{
		station_ids[i] = (*iID).data;
		iID++;
	}
	pOutput = station_ids;
	station_ids = nullptr;
	id_list->clean();
}

void LLC(const char* pRequest, void* pData, void*& pOutput, int& N)
{
	TDataset* data = static_cast<TDataset*>(pData);
	string request = pRequest;
	string city_name = request.substr(request.find(' ') + 1);
	
	Iterator<TCity> iCity = *data->cities->iterator();
	int city_id = -1;
	while (!iCity.atEnd())
	{
		if ((*iCity).data.name == city_name)
		{
			city_id = (*iCity).data.id;
			break;
		}
		iCity++;
	}

	L1List<int> *id_list = new L1List<int>();
	Iterator<int> iID = *id_list->iterator();
	Iterator<TLine> iLine = *data->lines->iterator();
	while (!iLine.atEnd())
	{
		if ((*iLine).data.city_id == city_id)
		{
			id_list->insertAfter(iID,(*iLine).data.id);
			iID++;
		}
		iLine++;
	}

	N = id_list->getSize();
	int* line_ids = new int[N];
	iID = *id_list->iterator();

	for (int i = 0; i < N; i++)
	{
		line_ids[i] = (*iID).data;
		iID++;
	}
	pOutput = line_ids;
	line_ids = nullptr;
	id_list->clean();
}

void LSL(const char* pRequest, void* pData, void*& pOutput, int& N)
{
	TDataset* data = static_cast<TDataset*>(pData);
	string request = pRequest;
	int line_id = std::stoi(request.substr(request.find(' ') + 1));

	L1List<int>* id_list = new L1List<int>();
	Iterator<int> iID = *id_list->iterator();
	Iterator<CStation_Line> iLS = *data->station_lines->iterator();
	while (!iLS.atEnd())
	{
		if ((*iLS).data.line_id == line_id)
		{
			id_list->insertAfter(iID, (*iLS).data.station_id);
			iID++;
		}
		iLS++;
	}

	N = id_list->getSize();
	int* station_ids = new int[N];
	iID = *id_list->iterator();

	for (int i = 0; i < N; i++)
	{
		station_ids[i] = (*iID).data;
		iID++;
	}
	pOutput = station_ids;
	station_ids = nullptr;
	id_list->clean();
}

void FC(const char* pRequest, void* pData, void*& pOutput, int& N)
{
	TDataset* data = static_cast<TDataset*>(pData);
	string request = pRequest;
	string city_name = request.substr(request.find(' ')+1);
	int city_id=-1;
	Iterator<TCity> iCity = *data->cities->iterator();
	while (!iCity.atEnd())
	{
		if ((*iCity).data.name == city_name)
		{
			city_id = (*iCity).data.id;
			break;
		}
		iCity++;
	}
	int* found_index = new int[1];
	*found_index = city_id;

	N = 1;
	pOutput = found_index;
	found_index = nullptr;
}

void FS(const char* pRequest, void* pData, void*& pOutput, int& N)
{
	TDataset* data = static_cast<TDataset*>(pData);
	string request = pRequest;
	string station_name = request.substr(request.find(' ') + 1);
	int station_id = -1;
	Iterator<TStation> iStation = *data->stations->iterator();
	while (!iStation.atEnd())
	{
		if ((*iStation).data.name == station_name)
		{
			station_id = (*iStation).data.id;
			break;
		}
		iStation++;
	}
	int* found_index = new int[1];
	*found_index = station_id;

	N = 1;
	pOutput = found_index;
	found_index = nullptr;
}

void SLP(const char* pRequest, void* pData, void*& pOutput, int& N)
{
	TDataset* data = static_cast<TDataset*> (pData);
	string request = pRequest;
	int station_id = std::stoi(request.substr(request.find(' ') + 1));
	int track_id = std::stoi(request.substr(request.find_last_of(' ') + 1));
	
	Iterator<TStation> iStation = *data->stations->iterator();
	string station_loc = "";
	while (!iStation.atEnd())
	{
		if ((*iStation).data.id == station_id)
		{
			station_loc = (*iStation).data.location;
			break;
		}
		iStation++;
	}
	// Got the station location string

	Iterator<TTrack> iTrack = *data->tracks->iterator();
	Iterator<string> iLineS; // Iterator to the first location in LINESTRING of needed track
	while (!iTrack.atEnd())
	{
		if ((*iTrack).data.id == track_id)
		{
			iLineS = *(*iTrack).data.lineS->iterator();
			break;
		}
		iTrack++;
	}
	// Got the Iterator pointing to #1 of LINESTRING

	// then count for the first index that match in the LINESTRING
	int* idx_output = new int[1];
	*idx_output = -1;
	int i = 0;
	while (!iLineS.atEnd())
	{
		if ((*iLineS).data == station_loc)
		{
			*idx_output = i;
			break;
		}
		iLineS++;
		i++;
	}

	N = 1;
	pOutput = idx_output;
	idx_output = nullptr;
	
}

void IS(const char* pRequest, void* pData, void*& pOutput, int& N)
{
	TDataset* data = static_cast<TDataset*> (pData);
	string  request = pRequest;
	string	csv_station = request.substr(request.find(' ') + 1) +",";
	string strData[2]{ "" };
	// the csv_station given wont have id, new id = max_station_id +1
	// since city id is also not given, just need to read two first column of the string
	string temp = "";
	for (int i = 0, count = 0; count < 2 && i< (int)csv_station.size(); i++)
	{
		if (csv_station[i] == '"')
		{
			i++;
			while (csv_station[i] != '"')
			{
				temp.push_back(csv_station[i++]);
			}
			i++;
		}
		if (csv_station[i] == ',')
		{
			strData[count] = temp;
			count++;
			temp = "";
		}
		else
		{
			temp.push_back(csv_station[i]);
		}
	}

	int* id = new int[1];
	*id= TStation::max_id+1;
	string name = strData[0];
	string location = strData[1].substr(6, strData[1].size() - 7);
	TStation* a = new TStation(*id, name, location, NULL);
	if (data->stations->push_back(*a)==0)
	{
		N = 1;
		pOutput = id;
		id = nullptr;
	}
	a = nullptr;

}

void RS(const char* pRequest, void* pData, void*& pOutput, int& N)
{
	TDataset* data = static_cast<TDataset*> (pData);
	string  request = pRequest;
	int station_id = std::stoi(request.substr(request.find(' ') + 1));
	int* output = new int[1];
	*output = -1;

	// remove the station from stations
	Iterator<TStation> iStation = *data->stations->iterator();
	int idx=0;
	while (!iStation.atEnd())
	{
		if ((*iStation).data.id == station_id)
		{
			if (data->stations->remove(idx) == 0)
				* output = 0; // station found
			break;
		}
		iStation++;
		idx++;
	}

	// remove the station connection from station_lines
	Iterator<CStation_Line> iSLine = *data->station_lines->iterator();
	idx = 0;
	if(*output==0) // only if station found
	while (!iSLine.atEnd())
	{
		if ((*iSLine).data.station_id == station_id)
		{
			iSLine++;
			data->station_lines->remove(idx);
			idx++;
			// Not sure if a station only has one line, so has to check all
			//! BUT, must move iterator before deleting it's location (Critical)
		}
		iSLine++;
		idx++;
	}
	pOutput = output;
	N = 1;
	output = nullptr;
}

void US(const char* pRequest, void* pData, void*& pOutput, int& N)
{
	// Only change the name ,location and city_id, we know the id already
	TDataset* data = static_cast<TDataset*> (pData);
	stringstream ss(pRequest);
	string temp;
	ss >> temp; // remove US
	ss >> temp; int station_id = std::stoi(temp); // station to upload
	char skip; ss >> skip;

	string csv_station; // upload data
	getline(ss, csv_station);
	csv_station += ",";

	L1List<string> *strData = new L1List<string>();
	temp = "";
	int count = 0;
	for (int i = 0; i < csv_station.size(); i++)
	{
		if (csv_station[i] == '"')
		{
			i++;
			while (csv_station[i]!='"')
			{
				temp.push_back(csv_station[i]);
				i++;
			}
			i++;
		}
		if (csv_station[i] == ',')
		{
			count++;//(count from 1)
			if (count <= 2 || count == 6) // city_id will be at index 6 
			{
				strData->push_back(temp);
			}
			temp = "";
		}
		else
		{
			temp.push_back(csv_station[i]);
		}
	}
	string name = strData->at(0);
	string location = strData->at(1);
	int city_id = -1;
	if (strData->at(2) != "") city_id = std::stoi(strData->at(2));

	
	int* output = new int[1];
	N = 1;
	Iterator<TStation> iStation = *data->stations->iterator();
	while (!iStation.atEnd())
	{
		if ((*iStation).data.id == station_id)
		{
			(*iStation).data.name = name;
			(*iStation).data.location = location.substr(6, location.size() - 7);
			(*iStation).data.city_id = city_id;
			*output = 0;
			pOutput = output;
			output = nullptr;
			return;
		}
		iStation++;
	}
	//if cant find it , then...
	*output = -1;
	pOutput = output;
	output = nullptr;
}

void ISL(const char* pRequest, void* pData, void*& pOutput, int& N)
{
	TDataset* data = static_cast<TDataset*> (pData);
	stringstream  ss(pRequest);
	string temp;
	ss >> temp; // Take the ISL
	ss >> temp; int station_id = std::stoi(temp);
	ss >> temp; int line_id = std::stoi(temp);
	ss >> temp; int idx_sta_line = std::stoi(temp); // index of the station in the line
	// in station_line data, one line has many stations, and we add this station at the requested index OF THAT LINE
	
	// TODO: Check for info of line and station??, what if they don't exist?
	//? Or what if they exist but, the line has no connection yet?

	//bool goodStation = false;
	//Iterator<TStation> iStation = *data->stations->iterator();
	//while (!iStation.atEnd())
	//{
	//	if ((*iStation).data.id == station_id)
	//	{
	//		goodStation = true;
	//	}
	//	iStation++;
	//}
	//Iterator<TLine> iLine = *data->lines->iterator();
	//bool goodLine = false;
	//while (!iLine.atEnd())
	//{
	//	if ((*iLine).data.id == line_id)
	//	{
	//		goodLine = true;
	//	}
	//	iLine++;
	//}
	//
	
	
	
	Iterator<CStation_Line> iSLine = *data->station_lines->iterator(); //Iterates the C_SL list
	int* output = new int[1];

	int idx = 0; // Real index of the station_line
	int ins_idx=-1; //  index to insert in the station_line dataset

	// Iterate the station_line data, find the insert index according to the order of the station of the line
	// 
	bool good_SL = true;
	while (!iSLine.atEnd())
	{
		int temp_S_id = (*iSLine).data.station_id;
		int temp_L_id = (*iSLine).data.line_id;
		
		if (temp_S_id == station_id && temp_L_id == line_id) //connection existed, no good
		{
			good_SL = false;
		}
		if (temp_L_id == line_id)
		{
			if (idx_sta_line == 0)
			{
				ins_idx = idx;
			}
			idx_sta_line--;
		}
		iSLine++;
		idx++;
	}

	// if this connection existed, fail operation
	// or if no found line 
	// or if index of insert (of station in the line) is out of range
	if (good_SL == false || ins_idx == -1 || idx_sta_line >1)
	{
		*output = -1;
		N = 1;
		pOutput = output;
		output = nullptr;
		return;
	}
	// in case we insert at end of the line, we just push back at end of station_line
	if (idx_sta_line == 1) ins_idx = data->station_lines->getSize();

	//? If the line and station doesn't exit, do we add them as new connection??
	CStation_Line* a = new CStation_Line(station_id, line_id);

	*output = data->station_lines->insert(ins_idx,*a);
	N = 1;
	pOutput = output;
	output = nullptr;
	a = nullptr;

}

void RSL(const char* pRequest, void* pData, void*& pOutput, int& N)
{
	TDataset* data = static_cast<TDataset*> (pData);
	string  request = pRequest;
	int station_id = std::stoi(request.substr(request.find(' ')+1));
	int line_id = std::stoi(request.substr(request.find_last_of(' ') + 1));

	Iterator<CStation_Line> iSLine = *data->station_lines->iterator();
	int idx = 0;
	int* output = new int[1];
	*output = -1;
	while (!iSLine.atEnd())
	{
		CStation_Line* temp = &(*iSLine).data;
		if (temp->line_id == line_id && temp->station_id == station_id)
		{
			if (data->station_lines->remove(idx) == 0)
				* output = 0;
			break;
			// only one connection between station - line, so use break
		}
		idx++;
		iSLine++;
	}
	pOutput = output;
	N = 1;
	output = nullptr;
}
// Test function
void PrintData(void* pData, int N)
{

	TDataset* data = static_cast<TDataset*>(pData);
	switch (N)
	{
	case 1:
		data->cities->traverse([](TCity& a) {
			std::cout << a.id << ' ' << a.name << std::endl;
			});
		break;
	case 2:
		data->stations->traverse([](TStation& a) {
			std::cout << a.id << ' ' << a.name << ' ' << a.location << ' '<< a.city_id << " MaxID " << TStation::max_id << std::endl;
			});
		break;
	case 3:
		data->lines->traverse([](TLine& a) {
			cout << a.id << ' ' << a.city_id << endl;
			});
		break;
	case 4:
		data->tracks->traverse([](TTrack& a) {
			std::cout << a.id << ' ' << "LINS: ";
			a.lineS->traverse([](string& b) {
				std::cout << b << "__";
				});
			std::cout << std::endl;
			});
		break;
	case 5:
		data->track_lines->traverse([](CTrack_Line& a) {
			cout << a.track_id << ' ' << a.line_id << endl;
			});
		break;
	case 6:
		data->station_lines->traverse([](CStation_Line& a) {
			cout << a.station_id << ' ' << a.line_id << endl;
			});
		break;
	default:
		cout << "Fuck" << endl;
		break;
	}
}
// test function