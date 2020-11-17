/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DBLIB_H
#define DSA191_A1_DBLIB_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"

/*Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
class Point2D
{
private:
	double x;
	double y;
public:
	Point2D() : x(0), y(0) {}
	Point2D(double a, double b) : x(a), y(b) {}
	bool operator==(const Point2D& a)
	{
		return x == a.x && y == a.y;
	}
	void operator=(const Point2D& a)
	{
		x = a.x;
		y = a.y;
	}
};
struct TCity {
    // The structure to store city information
	int id;
	string name;
	TCity(int i, string n) : id(i), name(n) {}
};

struct TLine {
	int id;
	int city_id;
	TLine(int i,int c) : id(i),city_id(c) {}
    // The structure to store line information
};

struct TTrack {
	int id;
	L1List<string> *lineS;
	TTrack(int i) : id(i), lineS(new L1List<string>()) {}
	~TTrack() { lineS->clean(); }
    // The structure to store track information
};

struct TStation {
	static int max_id;
	int id;
	string name;
	string location;
	int city_id;
	TStation():id(-1),city_id(-1){}
	TStation(int i, string n, string l, int c) : id(i), name(n), location(l), city_id(c) { if (i > max_id) max_id = i; }
	// The structure to store station information
};

struct CTrack_Line {
	int track_id;
	int line_id;
	CTrack_Line(int t, int l) : track_id(t), line_id(l) {}
	// Track line connection
};
struct CStation_Line {
	int station_id;
	int line_id;
	CStation_Line(int s, int l) : station_id(s), line_id(l) {}
	// Station line connection
};

class TDataset {
public:
	L1List<TTrack>* tracks; // has getSize()
	L1List<TCity>* cities;
	L1List<TStation>* stations; // contains TStation::max_id
	L1List<TLine> *lines;
	L1List<CTrack_Line>* track_lines;
	L1List<CStation_Line>* station_lines;

	TDataset()
	{
		tracks = new L1List<TTrack>();
		cities = new L1List<TCity>();
		stations = new L1List<TStation>();
		lines = new L1List<TLine>();
		track_lines = new L1List<CTrack_Line>();
		station_lines = new L1List<CStation_Line>();
	}
	~TDataset()
	{
		delete tracks;
		delete cities;
		delete stations;
		delete lines;
		delete track_lines;
		delete station_lines;
	}
    // This class can be a container that help you manage your tables
};

// Please add more or modify as needed

void LoadData(void* &); //! data goes in and out as the void pointer
void ReleaseData(void* &); // just delete TDataSet and viola, we done

void LoadTrack(TDataset*&); // 1 and 2 coll
void LoadCities(TDataset*&); // 1 and 2 coll
void LoadStations(TDataset*&); // 1,2,3 and 7 (end) coll
void LoadLines(TDataset*&); // 1 and 2 coll
void LoadTrackLines(TDataset*&);//1 and 3 coll
void LoadStationLines(TDataset*&); // 2 and 3 coll

#endif //DSA191_A1_DBLIB_H
