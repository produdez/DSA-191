/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "dbLib.h"

/* You can implement methods, functions that support your data structures here.
 * */
int TStation::max_id = 0;
void LoadData(void*& pData)
{
	TDataset* data = new TDataset();
	//? when reading, there will be the case of empty field, with two commas like ",a,,b," be careful
	//? everything loading goes here, not done !
	LoadCities(data);
	LoadLines(data);
	LoadStations(data);
	LoadTrack(data);
	LoadStationLines(data);
	LoadTrackLines(data);
	// for reading: should get_line, then read each char, add each char to a temp string and when okay, translate that string and put into dataStruct, then reset string and continue <3
	pData = data;
}

void ReleaseData(void*& pData)
{
	TDataset* data = static_cast<TDataset*> (pData);
	delete(data);
}

void LoadTrack(TDataset*& data)
{
	ifstream input;
	input.open("E:/Dev/Coding/VisualProject/Assignment1_Data/UsableMaterial/Shared_Data/tracks.csv");
	if (!input)
	{
		throw new DSAException(-2, "Fail to open tracks.csv!");
	}
	L1List<string>* strData = new L1List<string>();
	string line;
	getline(input, line);
	// iterator helps continuous push_back fast
	Iterator<TTrack> itr = *data->tracks->iterator();
	while (getline(input, line))
	{
		string temp = "";
		for (int i = 0, count = 0; count < 2; i++) //read 1 and 2 only
		{
			if (line[i] == '"')
			{
				i++;
				while (line[i] != '"')
				{
					temp.push_back(line[i++]);
				}
				i++;
			}
			if (line[i] == ',')
			{
				strData->push_back(temp);
				temp = "";
				count++;
			}
			else temp.push_back(line[i]);
		}
		// after having string format in strData
		// Format them and add to data
		int id = -1;
		if (strData->at(0) != "") id = std::stoi(strData->at(0));
		TTrack* track = new TTrack(id);

		/*changing big line string to small line strings*/
		string locations = "";
		temp = strData->at(1).substr(11);
		*(temp.end() - 1) = ',';
		for (int i = 0; i < (int)temp.size(); i++)
		{
			if (temp[i] == ',')
			{
				track->lineS->insertHead(locations);
				locations = "";
			}
			else locations.push_back(temp[i]);
		}
		track->lineS->reverse();
		/**/
		data->tracks->insertAfter(itr,*track);
		itr++;
		strData->clean();
	}

}

void LoadCities(TDataset*& data)
{
	ifstream input;
	//? MUST CHANGE FILE PATH WHEN NEED
	input.open("E:/Dev/Coding/VisualProject/Assignment1_Data/UsableMaterial/Shared_Data/cities.csv");
	if (!input)
	{
		throw new DSAException(-2, "Fail to open cities.csv!");
	}


	L1List<string>* strData = new L1List<string>();
	//holds the string format of id,name
	string line;
	getline(input, line); // skip first line
	// iterator helps continuous push_back fast
	Iterator<TCity> itr = *data->cities->iterator();
	while (getline(input, line))
	{	
		string temp="";
		for (int i=0,count=0;count<2;i++) //read 1 and 2 only
		{
			if (line[i] == '"')
			{
				i++;
				while (line[i] != '"')
				{
					temp.push_back(line[i++]);
				}
				i++;
			}
			if (line[i] == ',')
			{
				strData->push_back(temp);
				temp = "";
				count++;
			}
			else temp.push_back(line[i]);
		}
		// after having string format in strData
		// Format them and add to data
		TCity* city;
		if (strData->at(0).data() == "") city = new TCity(NULL, strData->at(1).data());
		else city = new TCity(std::stoi(strData->at(0).data()), strData->at(1).data());
		data->cities->insertAfter(itr,*city);
		itr++;
		strData->clean();
	}
	//! we add to front and reverse the data later for quicker insert, i think!
	input.close();
}

void LoadStations(TDataset*& data)
{
	ifstream input;
	input.open("E:/Dev/Coding/VisualProject/Assignment1_Data/UsableMaterial/Shared_Data/stations.csv");
	if (!input) throw new DSAException(-1, "Can't open stations.csv");

	string line;
	L1List<string>* strData = new L1List<string>();

	getline(input, line);
	// iterator helps continuous push_back fast
	Iterator<TStation> itr = *data->stations->iterator();
	while (getline(input, line))
	{
		line.push_back(',');
		int count = 0;
		string temp = "";
		for (int i = 0; i < (int)line.size(); i++)
		{
			// if found "" , take all of it
			if (line[i] == '"')
			{
				i++;
				while (line[i] != '"')
				{
					temp.push_back(line[i++]);
				}
				i++;
			}
			if (line[i] == ',')
			{
				count++;
				if(count<=3 || count ==7)strData->push_back(temp);
				temp = "";
			}
			else
			{
				temp.push_back(line[i]);
			}
		}
		//after got data in string format
		int id=-1, city_id=-1;
		string name="",location="";
		if (strData->at(0) != "") id = std::stoi(strData->at(0));
		name = strData->at(1);
		location = strData->at(2).substr(6, strData->at(2).size()-7);
		if (strData->at(3) != "") city_id= std::stoi(strData->at(3));
		
		TStation* station = new TStation(id, name,location, city_id);
		data->stations->insertAfter(itr,*station);
		itr++;
		strData->clean();
	}

	input.close();
}

void LoadLines(TDataset*& data)
{
	ifstream input;
	input.open("E:/Dev/Coding/VisualProject/Assignment1_Data/UsableMaterial/Shared_Data/lines.csv");

	if (!input) throw new DSAException(-1, "Can't open lines.csv");

	string line;
	L1List<string>* strData = new L1List<string>();
	getline(input, line);
	// iterator helps continuous push_back fast
	Iterator<TLine> itr = *data->lines->iterator();
	while (getline(input, line))
	{
		string temp = "";
		for (int i = 0, count = 0; count < 2; i++) // get 1, 2 col only
		{
			if (line[i] == '"')
			{
				i++;
				while (line[i] != '"')
				{
					temp.push_back(line[i++]);
				}
			}
			if (line[i] == ',')
			{
				strData->push_back(temp);
				temp = "";
				count++;
			}
			else
			{
				temp.push_back(line[i]);
			}
		}
		
		int id = -1, city_id = -1;
		if (strData->at(0) != "") id = std::stoi(strData->at(0));
		if (strData->at(1) != "") city_id = std::stoi(strData->at(1));
		TLine* line = new TLine(id, city_id);
		data->lines->insertAfter(itr,*line);
		itr++;
		strData->clean();
	}

	input.close();
}

void LoadTrackLines(TDataset*& data)
{
	ifstream input;
	input.open("E:/Dev/Coding/VisualProject/Assignment1_Data/UsableMaterial/Shared_Data/track_lines.csv");

	if (!input) throw new DSAException(-1, "Can't open track_lines.csv");

	string line;
	L1List<string>* strData = new L1List<string>();
	getline(input, line);
	// iterator helps continuous push_back fast
	Iterator<CTrack_Line> itr = *data->track_lines->iterator();
	while (getline(input, line))
	{
		string temp = "";
		for (int i = 0, count = 0; count < 3; i++) // get 1, 3 col only
		{
			if (line[i] == '"')
			{
				i++;
				while (line[i] != '"')
				{
					temp.push_back(line[i++]);
				}
			}
			if (line[i] == ',')
			{
				if(count != 1)
				strData->push_back(temp);
				temp = "";
				count++;
			}
			else
			{
				temp.push_back(line[i]);
			}
		}

		int track_id = -1, line_id = -1;
		if (strData->at(0) != "") track_id = std::stoi(strData->at(0));
		if (strData->at(1) != "") line_id = std::stoi(strData->at(1));
		CTrack_Line* track_line = new CTrack_Line(track_id, line_id);
		data->track_lines->insertAfter(itr,*track_line);
		itr++;
		strData->clean();
	}
	input.close();
}

void LoadStationLines(TDataset*& data)
{
	ifstream input;
	input.open("E:/Dev/Coding/VisualProject/Assignment1_Data/UsableMaterial/Shared_Data/station_lines.csv");

	if (!input) throw new DSAException(-1, "Can't open station_lines.csv");

	string line;
	L1List<string>* strData = new L1List<string>();
	getline(input, line);
	// iterator helps continuous push_back fast
	Iterator<CStation_Line> itr = *data->station_lines->iterator();
	while (getline(input, line))
	{
		string temp = "";
		for (int i = 0, count = 0; count < 3; i++) // get 2, 3 col only
		{
			if (line[i] == '"')
			{
				i++;
				while (line[i] != '"')
				{
					temp.push_back(line[i++]);
				}
			}
			if (line[i] == ',')
			{
				if (count != 0)
					strData->push_back(temp);
				temp = "";
				count++;
			}
			else
			{
				temp.push_back(line[i]);
			}
		}

		int station_id = -1, line_id = -1;
		if (strData->at(0) != "") station_id = std::stoi(strData->at(0));
		if (strData->at(1) != "") line_id = std::stoi(strData->at(1));
		CStation_Line* station_line = new CStation_Line(station_id, line_id);
		data->station_lines->insertAfter(itr, *station_line);
		itr++;
		strData->clean();
	}

	input.close();
}
