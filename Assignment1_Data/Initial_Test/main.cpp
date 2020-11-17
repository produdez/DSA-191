#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"
#include "dbLib.h"
#include "processData.h"

using namespace std;

int main() {
	//....................Test area..........

	//Load data
	//void* a = nullptr;
	//LoadData(a);
	//TDataset* data = static_cast<TDataset*>(a);
	//

	// Iterator use
	//string input ="";
	//while (1)
	//{
	//	cin >> input;
	//	if (input == "Exit") break;
	//	Iterator<TCity> iterator = *data->cities->iterator();
	//	while (iterator != nullptr)
	//		{
	//			if ((*iterator).data.name == input) {
	//				cout << (*iterator).data.id << endl;
	//			}
	//			iterator++;
	//		}
	//}
	
	
	
	//.....................Test area...................
	//? Test Linked List
	/*
		L1List<int> *myList = new L1List<int>() ;
			int n = 100;
			int temp;
			for (int i = 0; i < n; i++)
			{
				temp = rand() % 10;
				myList->insert(rand() % (myList->getSize()+1), temp);
				myList->insertHead(temp);
				myList->push_back(temp);


				//print
				myList->traverse(print);
				std::cout << std::endl;
			}
			for (int i = 0; i < n; i++)
			{
				myList->remove(rand() % myList->getSize());
				myList->removeHead();
				myList->removeLast();

				//print
				myList->traverse(print);
				std::cout << std::endl;
			}
	*/
	
	//.....................Test area...............



    Initialization();

    void*   pData = nullptr;
    void*   pOutput = nullptr;
    int     N;

    LoadData(pData);
    assert(pData != nullptr);
    cout << fixed << setprecision(8);
    string req;
    while (true) {
        req = "";
        getline(cin, req);
        if (cin.bad()) {
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
        }
        if (req == "Exit") {
            break;
        }
        ProcessRequest(req.data(), pData, pOutput, N);
        PrintReqOutput<int>(req.data(), (int*)pOutput, N);
        delete [] (int*)pOutput;
        pOutput = nullptr;
    }

    ReleaseData(pData);
    Finalization();
    return 0;
}