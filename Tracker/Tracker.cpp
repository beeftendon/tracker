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

String^ TalkToArduino(SerialPort^ arduino)
{
	// TODO Error handling 
	String^ response;
	String^ main_response;
	do
	{
		response = arduino->ReadLine();
		if (String::IsNullOrEmpty(main_response))
		{
			main_response = response;
		}

	} while (!response->Equals("ok\r") && !response->Contains("error:"));

	return main_response;
}

void ClearArduinoSerialBuf(SerialPort^ arduino)
{
	// TODO Error handling 
	String^ response;
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
	String^ portName;
	String^ response;

	SerialPort^ arduino;
	int baudRate = 115200;
	portName = "com5";
	arduino = gcnew SerialPort(portName, baudRate);
	arduino->Open();

	// Set status report mask
	arduino->WriteLine("$10=2");
	ClearArduinoSerialBuf(arduino);

	String^ input;
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

