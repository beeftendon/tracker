// Tracker.cpp : main project file.

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <Windows.h>

using namespace System;
using namespace System::IO::Ports;
using namespace std;
using namespace cv;
using SysString = System::String;

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

SysString^ TellArduino(SerialPort^ arduino, SysString^ message)
{
	// Writes message to serial port and returns the response. Clears serial buffer of subsequent "ok" or "errors" (for now)

	// TODO Error handling 

	SysString^ response;
	SysString^ mainResponse; // This will be the one actually returned. Won't bother returning "ok"
	do
	{
		response = arduino->ReadLine();
		if (SysString::IsNullOrEmpty(mainResponse))
		{
			mainResponse = response;
		}

	} while (!response->Equals("ok\r") && !response->Contains("error:"));

	return mainResponse;
}

void ClearArduinoSerialBuf(SerialPort^ arduino)
{
	SysString^ response;
	do
	{
		response = arduino->ReadLine();
	} while (!response->Equals("ok\r") && !response->Contains("error:"));
}

int main(array<System::String ^> ^args)
{
	// Set up files for testing and loggin
	ofstream timefile;
	timefile.open("timefile.txt");
	ofstream serialfile;
	serialfile.open("serialfile.txt");

	// Configure serial comms for Arduino
	SysString^ portName;
	SysString^ response;

	SerialPort^ arduino;
	int baudRate = 115200;
	portName = "com5";
	arduino = gcnew SerialPort(portName, baudRate);
	arduino->Open();

	// Set up image capture and processing
	vector<vector<Point>> contours;
	vector<Vec4i> heirarchy; // Not sure what this is for, but it makes findContours work

	VideoCapture vidCap(CV_CAP_ANY);
	vidCap.set(CV_CAP_PROP_FPS, 240); // Need to set the exposure time to appropriate value in Pylon Viewer as well
	vidCap.set(CV_CAP_PROP_FRAME_HEIGHT, 200); // 200x200 window
	vidCap.set(CV_CAP_PROP_FRAME_WIDTH, 200); 

	// Set status report mask
	arduino->WriteLine("$10=2");
	ClearArduinoSerialBuf(arduino);

	// @@@@@@ MAIN LOOP @@@@@
	while (true)
	{

	}

	SysString^ input;
	while (true)
	{
		StartCounter();
		//input = Console::ReadLine();
		input = "?";

		if (input->Equals("exit")) break;

		arduino->WriteLine(input);

		do
		{
			response = arduino->ReadLine();
			//Console::WriteLine(response);
		} while (!response->Equals("ok\r") && !response->Contains("error:"));

		timefile << GetCounter() << "\n";
	}

	timefile.close();
	Console::Clear();

	arduino->Close();

	return 0;
}

