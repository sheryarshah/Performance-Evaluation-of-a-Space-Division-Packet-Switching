/****************************************************************************************
* Author: Sheyar Shah
* Last updated: 4-09-15
* Compiler Used: Microsoft Visual Studio 2013 Professional.
* Program Description: Program written in C/C++.
* The program produces a discrete event simulation of a 3x3, 4x4, and 5x5 cross bar 
* switches. The program mimics the operation of the network and collects statistics. The
* program records the total number of packets, across all outputs, that are successes and
* dropped. The program generates an excel file for each size crossbar where the user can 
* graph for the plots.
*****************************************************************************************/

#define _CRT_SECURE_NO_DEPRECATE		//needed for this specific complier, ignores unnessary warnings
#define SLOTS 5000						//number of times the simulation will run for each slot

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

int crossbar_selection(); /*function for allowing user to select the type of crossbar*/

int main(){

	ofstream excelFile;
	ofstream excelFile1;
	ofstream excelFile2;

	int output1 = 0;
	int output2 = 0;
	int output3 = 0;
	int output4 = 0;
	int output5 = 0;

	double throughPut[100], dropPacket[100];
	double totalDropped3x3, totalOutput3x3;	/*for 3x3 crossbar*/
	double totalDropped4x4, totalOutput4x4; /*for 4x4 crossbar*/
	double totalDropped5x5, totalOutput5x5; /*for 5x5 crossbar*/

	double p1 = 0.01;

	int index = 0;

	srand(time(NULL));

	while (1){
		int selection = crossbar_selection();
		/*the switch statement allows the user to select the type of crossbar*/
		switch (selection){
		case (0) :
			excelFile.open("result.csv");	//data being saved for 3x3

			/*loop of probability that increment by .01 up to 1*/
			for (double p = 0.01; p < 1; p+= 0.01, index++){
				totalOutput3x3 = 0;
				totalDropped3x3 = 0;
				/*loop for number of slots it will run for each switch*/
				for (int i = 0; i < SLOTS; i++){
					int inputCounter = 0;
					bool inputSwitch[3] = { 0 };
					/*this loop generates packets for each input*/
					for (int j = 0; j < 3; j++){
						double checkOutput = ((double)rand() * (1 - 0)) / ((double)RAND_MAX + 0);
						if (checkOutput <= p){
							inputSwitch[j] = true;
							inputCounter++;
						}
						else{
							inputSwitch[j] = false;
						}
					}
					/*After recieving packets from input, check which output
					the packet will go to*/
					int outputDest[3] = { 0 };
					for (int j = 0; j < 3; j++){
						/*if there was a packet at that input then proceed on 
						determing which ouput the packet will go to*/
						if (inputSwitch[j] == true){
							/*generate random number which will determine which output line
							the packet will go to*/
							double checkOutput = ((double)rand() * (1 - 0)) / ((double)RAND_MAX + 0);
							if (checkOutput < 0.33){
								output1++;
								outputDest[0] = output1;
							}

							else if (checkOutput > 0.33 && checkOutput < 0.66){
								output2++;
								outputDest[1] = output2;
							}

							else if (checkOutput > 0.66){
								output3++;
								outputDest[2] = output3;
							}

						}

					}
					/*reset the values of output*/
					output1 = 0; output2 = 0; output3 = 0;

					/*After getting output, check which needs to be dropped.
					If the ouput line has more than 1 packet drop rest of packets
					and store in it a variable "dropped*/
					int dropped = 0;
					for (int j = 0; j < 3; j++){
						if (outputDest[j] > 1){
							dropped += outputDest[j] - 1;
						}
					}
					
					/*packets that were passed through the ouput line*/
					int passed = inputCounter - dropped;
					
					totalOutput3x3 += passed;
					totalDropped3x3 += dropped;	

				}
				/*calculate the throughput and dropped packets*/
				throughPut[index] = (totalOutput3x3 * 1.0) / (3.0 * 5000.0);
				dropPacket[index] = (totalDropped3x3 * 1.0) / (3.0 * 5000.0);
			}

			/*importing to excel file "result1" which is for 3x3 crossbar*/
			for (int j = 0; j < 99; j++){
				excelFile << p1 << "," << throughPut[j] << "," << dropPacket[j] << endl;
				p1 += 0.01;
			}

			excelFile.close();
			break;
		
			/*this case is 4x4 crossbar*/
		case (1) :
			excelFile1.open("result1.csv");	//data being saved for 4x4
			/*reset the values of throughput and dropPacket and output counters*/
			output1 = 0; output2 = 0; output3 = 0;
			throughPut[index] = { 0 };
			dropPacket[index] = { 0 };
			/*loop of probability that increment by .01 up to 1*/
			for (double p = 0.01; p < 1; p += 0.01, index++){
				totalOutput4x4 = 0;
				totalDropped4x4 = 0;
				/*loop for number of slots it will run for each switch*/
				for (int i = 0; i < SLOTS; i++){
					int inputCounter = 0;
					bool inputSwitch[4] = { 0 };
					/*this loop generates packets for each input*/
					for (int j = 0; j < 4; j++){
						double checkOutput = ((double)rand() * (1 - 0)) / ((double)RAND_MAX + 0);
						if (checkOutput <= p){
							inputSwitch[j] = true;
							inputCounter++;
						}
						else{
							inputSwitch[j] = false;
						}
					}
					/*After recieving packets from input, check which output
					the packet will go to*/
					int outputDest[4] = { 0 };
					for (int j = 0; j < 4; j++){
						/*if there was a packet at that input then proceed on
						determing which ouput the packet will go to*/
						if (inputSwitch[j]){
							/*generate random number which will determine which output line
							the packet will go to*/
							double checkOutput = ((double)rand() * (1 - 0)) / ((double)RAND_MAX + 0);
							if (checkOutput < 0.25){
								output1++;
								outputDest[0] = output1;
							}

							else if (checkOutput > 0.25 && checkOutput < 0.50){
								output2++;
								outputDest[1] = output2;
							}

							else if (checkOutput >  0.50 && checkOutput < 0.75){
								output3++;
								outputDest[2] = output3;
							}

							else if (checkOutput > 0.75){
								output4++;
								outputDest[3] = output4;
							}

						}

					}
					/*reset the values of output*/
					output1 = 0; output2 = 0; output3 = 0; output4 = 0;

					/*After getting output, check which needs to be dropped.
					If the ouput line has more than 1 packet drop rest of packets
					and store in it a variable "dropped*/
					int dropped = 0;
					for (int j = 0; j < 4; j++){
						if (outputDest[j] > 1){
							dropped += outputDest[j] - 1;
						}
					}

					/*packets that were passed through the ouput line*/
					int passed = inputCounter - dropped;

					totalOutput4x4 += passed;
					totalDropped4x4 += dropped;

				}

				/*calculate the throughput and dropped packets*/
				throughPut[index] = (totalOutput4x4 * 1.0) / (4.0 * 5000.0);
				dropPacket[index] = (totalDropped4x4 * 1.0) / (4.0 * 5000.0);
	
			}

			/*importing to excel file "result1" which is for 4x4 crossbar*/
			for (int j = 0; j < 99; j++){
				excelFile1 << p1 << "," << throughPut[j] << "," << dropPacket[j] << endl;
				p1 += 0.01;
			}
			excelFile1.close();
			break;

			/*this case is 5x5 crossbar*/
		case(2) :
			excelFile2.open("result2.csv");
			output1 = 0; output2 = 0; output3 = 0; output4 = 0;
			throughPut[index] = { 0 };
			dropPacket[index] = { 0 };
			/*loop of probability that increment by .01 up to 1*/
			for (double p = 0.01; p < 1; p += 0.01, index++){
				totalOutput5x5 = 0;
				totalDropped5x5 = 0;
				/*loop for number of slots it will run for each switch*/
				for (int i = 0; i < SLOTS; i++){
					int inputCounter = 0;
					bool inputSwitch[5] = { 0 };
					/*this loop generates packets for each input*/
					for (int j = 0; j < 5; j++){
						double checkOutput = ((double)rand() * (1 - 0)) / ((double)RAND_MAX + 0);
						if (checkOutput <= p){
							inputSwitch[j] = true;
							inputCounter++;
						}
						else{
							inputSwitch[j] = false;
						}
					}
					/*After recieving packets from input, check which output
					the packet will go to*/
					int outputDest[5] = { 0 };
					for (int j = 0; j < 5; j++){
						/*if there was a packet at that input then proceed on
						determing which ouput the packet will go to*/
						if (inputSwitch[j]){
							/*generate random number which will determine which output line
							the packet will go to*/
							double checkOutput = ((double)rand() * (1 - 0)) / ((double)RAND_MAX + 0);
							if (checkOutput < 0.20){
								output1++;
								outputDest[0] = output1;
							}

							else if (checkOutput > 0.20 && checkOutput < 0.40){
								output2++;
								outputDest[1] = output2;
							}

							else if (checkOutput >  0.40 && checkOutput < 0.60){
								output3++;
								outputDest[2] = output3;
							}

							else if (checkOutput >  0.60 && checkOutput < 0.80){
								output4++;
								outputDest[3] = output4;
							}

							else if (checkOutput > 0.80){
								output5++;
								outputDest[4] = output5;
							}

						}

					}
					/*reset the values of output*/
					output1 = 0; output2 = 0; output3 = 0; output4 = 0; output5 = 0;

					/*After getting output, check which needs to be dropped.
					If the ouput line has more than 1 packet drop rest of packets
					and store in it a variable "dropped*/
					int dropped = 0;
					for (int j = 0; j < 5; j++){
						if (outputDest[j] > 1){
							dropped += outputDest[j] - 1;
						}
					}
					/*packets that were passed through the ouput line*/
					int passed = inputCounter - dropped;

					totalOutput5x5 += passed;
					totalDropped5x5 += dropped;

				}
				/*calculate the throughput and dropped packets*/
				throughPut[index] = (totalOutput5x5 * 1.0) / (5.0 * 5000.0);
				dropPacket[index] = (totalDropped5x5 * 1.0) / (5.0 * 5000.0);
			}
			/*importing to excel file "result2" which is for 5x5 crossbar*/
			for (int j = 0; j < 99; j++){
				excelFile2 << p1 << "," << throughPut[j] << "," << dropPacket[j] << endl;
				p1 += 0.01;
			}

			excelFile2.close();
			break;

		case (-1) :

			cout << "\nSystem exiting..." << endl;
			exit(0);

		default:

			cout << "Wrong entry" << endl;
			break;
		}
	}
	
	
	getchar();
	getchar();

	return 0;
}

/*Function which returns the selection the user makes
for selecting the type of crossbar*/
int crossbar_selection(){

	int select;
	cout << "Enter 0 for 3x3 crossbar" << endl;
	cout << "Enter 1 for 4x4 crossbar" << endl;
	cout << "Enter 2 for 5x5 crossbar" << endl;
	cout << "Enter -1 to exit\n" << endl;
	cout << "\nPlease choose an option: ";
	cin >> select;
	cout << "\n" << endl;
	

	return select;
}
