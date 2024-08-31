#include "priorityqueue.h"
#include "lander.h"
#include <iostream>
#include <fstream>
using namespace std;

// Function to print out details of lander
void printLander(lander l){
        cout << "Rocket " << l.get_id();
        cout <<"\nFuel: " << l.get_fuel_amount();
        cout << "\nAltitude: " << l.get_altitude();
        cout << "\nVelocity: " << l.get_velocity()
            << "\n\n";
}

int main(){

    // getting input file and error checking
    ifstream inFile;
    string userInput;
    priorityQ<lander> pq;
    lander l;
    double mass, thrust, fuelRate, altitude, fuelAmt, flowRate;
    int id;
    do{
        cout << "Enter lander file: ";
        cin >> userInput;
        inFile.open(userInput);
    }while(!inFile);

    // reading in the info
    while(inFile >> mass >> thrust >> fuelRate >> altitude >> fuelAmt >> id){
        if(inFile.eof())
            break;
        lander l(mass, thrust, fuelRate, altitude, fuelAmt, id);
        pq.insert(l);
    }

    
    inFile.close();

    // read in simulation file of flow rate numbers between 0 and 1
    do{
        cout << "Enter simulation file: ";
        cin >> userInput;
        inFile.open(userInput);
    }while(!inFile);

    while (inFile >> flowRate ) {
        // if it is not a double
        if(inFile.fail())
            continue;
        
        // Check if value is between 0 and 1
        // simulate if it is
        if(flowRate>=0 && flowRate <=1){
            l = pq.getHighestPriority();
            printLander(l);
            pq.deleteHighestPriority();
            l.change_flow_rate(flowRate);
            l.simulate();
            if(l.get_status() == 'a'){
                pq.insert(l);
            }
            if(l.get_status() == 'c'){
                cout << "Rocket ID: " << l.get_id() <<
                    " has crashed :( At least nobody was on board\n\n";
            }
            if(l.get_status() == 'l'){
                cout << "Rocket ID: " << l.get_id() <<
                    " has landed :) Hurray!\n\n";
            }
        }
    }
    
   
    l = pq.getHighestPriority();
    printLander(l);
    pq.deleteHighestPriority();

    //if it reaches end of file, print what is in priorityQ
    if(!pq.isEmpty()){
        cout << "\nThere are landers still trying to land...\n";
        while(!pq.isEmpty()){
            l = pq.getHighestPriority();
            cout << "Lander ID: " << l.get_id();
            cout << " Altitude: " << l.get_altitude();
            cout << " mission aborted.\n";
            pq.deleteHighestPriority();
        } 
    }


    inFile.close();

    return 0;
}
