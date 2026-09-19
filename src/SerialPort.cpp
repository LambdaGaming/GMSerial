// Modified version of the SerialPort library by Manash Kumar Mandal

#include "SerialPort.hpp"

SerialPort::SerialPort( const char *portName, DWORD baudrate )
{
	this->connected = false;
	this->handler = CreateFileA( static_cast<LPCSTR>( portName ), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( this->handler == INVALID_HANDLE_VALUE )
	{
		if ( GetLastError() == ERROR_FILE_NOT_FOUND )
			std::cerr << "ERROR: Handle was not attached.Reason : " << portName << " not available\n";
		else
			std::cerr << "ERROR!!!\n";
	}
	else
	{
		DCB dcbSerialParameters = {0};
		if ( !GetCommState( this->handler, &dcbSerialParameters ) )
		{
			std::cerr << "Failed to get current serial parameters\n";
		}
		else
		{
			dcbSerialParameters.BaudRate = baudrate;
			dcbSerialParameters.ByteSize = 8;
			dcbSerialParameters.StopBits = ONESTOPBIT;
			dcbSerialParameters.Parity = NOPARITY;
			dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

			if ( !SetCommState( handler, &dcbSerialParameters ) )
			{
				std::cout << "ALERT: could not set serial port parameters\n";
			}
			else
			{
				this->connected = true;
				PurgeComm( this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR );
				Sleep( ARDUINO_WAIT_TIME );
			}
		}
	}
}

SerialPort::~SerialPort()
{
	if ( this->connected )
	{
		this->connected = false;
		CloseHandle( this->handler );
	}
}

// Reading bytes from serial port to buffer;
// returns read bytes count, or if error occurs, returns 0
int SerialPort::readSerialPort( const char *buffer, unsigned int buf_size )
{
	DWORD bytesRead{};
	unsigned int toRead = 0;
	ClearCommError( this->handler, &this->errors, &this->status );

	if ( this->status.cbInQue > 0 )
	{
		if ( this->status.cbInQue > buf_size )
			toRead = buf_size;
		else
			toRead = this->status.cbInQue;
	}

	memset( ( void* ) buffer, 0, buf_size );
	if ( ReadFile( this->handler, ( void* ) buffer, toRead, &bytesRead, NULL ) )
	{
		return bytesRead;
	}
	return 0;
}

// Sending provided buffer to serial port;
// returns true if succeed, false if not
bool SerialPort::writeSerialPort( const char *buffer, unsigned int buf_size )
{
	DWORD bytesSend;
	if ( !WriteFile( this->handler, ( void* ) buffer, buf_size, &bytesSend, 0 ) )
	{
		ClearCommError( this->handler, &this->errors, &this->status );
		return false;
	}
	return true;
}

// Checking if serial port is connected
bool SerialPort::isConnected()
{
	if ( !ClearCommError( this->handler, &this->errors, &this->status ) )
	{
		this->connected = false;
	}
	return this->connected;
}

void SerialPort::closeSerial()
{
	CloseHandle( this->handler );
}

// Modified version of https://github.com/gbionics/serial_cpp/blob/main/src/impl/list_ports/list_ports_win.cc
static const DWORD port_name_max_length = 256;
vector<string> SerialPort::ListPorts()
{
	vector<string> list;
	HDEVINFO device_info_set = SetupDiGetClassDevs( ( const GUID * ) &GUID_DEVINTERFACE_COMPORT, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE );
	unsigned int device_info_set_index = 0;
	SP_DEVINFO_DATA device_info_data;
	device_info_data.cbSize = sizeof( SP_DEVINFO_DATA );
	while( SetupDiEnumDeviceInfo( device_info_set, device_info_set_index, &device_info_data ) )
	{
		device_info_set_index++;

		// Get port name
		HKEY hkey = SetupDiOpenDevRegKey( device_info_set, &device_info_data, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ );
		TCHAR port_name[port_name_max_length];
		DWORD port_name_length = port_name_max_length;
		LONG return_code = RegQueryValueEx( hkey, _T("PortName"), NULL, NULL, ( LPBYTE ) port_name, &port_name_length);
		RegCloseKey( hkey );

		if( return_code != EXIT_SUCCESS )
			continue;

		if( port_name_length > 0 && port_name_length <= port_name_max_length )
			port_name[port_name_length-1] = '\0';
		else
			port_name[0] = '\0';

		// Ignore parallel ports
		if( _tcsstr( port_name, _T( "LPT" ) ) != NULL )
			continue;

		list.push_back( port_name );
	}
	return list;
}
