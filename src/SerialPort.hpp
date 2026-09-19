// Modified version of the SerialPort library by Manash Kumar Mandal

#pragma once
#pragma comment( lib, "setupapi" )

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include <windows.h>
#include <SetupAPI.h>
#include <tchar.h>
#include <iostream>
#include <vector>

using namespace std;

class SerialPort
{
private:
	HANDLE handler;
	bool connected;
	COMSTAT status;
	DWORD errors;
public:
	explicit SerialPort( const char *portName, DWORD baudrate );
	~SerialPort();

	static vector<string> ListPorts( void );
	int readSerialPort( const char *buffer, unsigned int buf_size );
	bool writeSerialPort( const char *buffer, unsigned int buf_size );
	bool isConnected();
	void closeSerial();

	double InputDelay;
	double InputCooldown;
	double OutputDelay;
	double OutputCooldown;
};
