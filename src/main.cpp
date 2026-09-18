#include "serial_cpp/serial.h"
#include "GarrysMod/Lua/Interface.h"

#define GMMODULE
#define PRINT( STRING ) \
	LUA->PushSpecial( SPECIAL_GLOB ); \
	LUA->GetField( -1, "print" ); \
	LUA->PushString( STRING ); \
	LUA->Call( 1, 0 ); \
	LUA->Pop();

using namespace GarrysMod::Lua;
using namespace serial_cpp;
using namespace std;

int SerialTable;

LUA_FUNCTION( Begin )
{
	LUA->CheckType( 1, Type::String );
	LUA->CheckType( 2, Type::Number );
	auto port = LUA->GetString( 1 );
	auto baud = LUA->GetNumber( 2 );
	try
	{
		Serial *serial;
		serial = new Serial( port, baud );
		LUA->PushUserType( serial, SerialTable );
		return 1;
	}
	catch ( exception& e )
	{
		PRINT( e.what() );
	}
	LUA->PushNil();
	return 1;
}

LUA_FUNCTION( ListDevices )
{
	vector<PortInfo> devices = list_ports();
	LUA->CreateTable();
	for ( auto d : devices )
	{
		LUA->PushString( d.description.c_str() );
		LUA->SetField( -2, "description" );
		LUA->PushString( d.hardware_id.c_str() );
		LUA->SetField( -2, "hardware_id" );
		LUA->PushString( d.port.c_str() );
		LUA->SetField( -2, "port" );
	}
	return 1;
}

LUA_FUNCTION( SetTimeout )
{
	LUA->CheckType( 2, Type::Number );
	auto serial = LUA->GetUserType<Serial>( 1, SerialTable );
	if ( serial->isOpen() )
	{
		auto timeout = Timeout::simpleTimeout( LUA->GetNumber( 2 ) );
		serial->setTimeout( timeout );
	}
	return 0;
}

LUA_FUNCTION( WriteString )
{
	LUA->CheckType( 2, Type::String );
	auto serial = LUA->GetUserType<Serial>( 1, SerialTable );
	auto str = LUA->GetString( 2 );
	if ( serial->isOpen() )
	{
		auto written = serial->write( str );
		LUA->PushNumber( written );
		return 1;
	}
	LUA->PushNumber( 0 );
	return 1;
}

LUA_FUNCTION( ReadString )
{
	auto serial = LUA->GetUserType<Serial>( 1, SerialTable );
	auto size = LUA->GetNumber( 2 );
	auto eol = LUA->GetString( 3 );
	if ( serial->isOpen() )
	{
		if ( size <= 0 )
			size = 65536;
		if ( eol == NULL )
			eol = "\n";

		auto str = serial->readline( ( size_t ) size, eol );
		LUA->PushString( str.c_str() );
		return 1;
	}
	LUA->PushString( "" );
	return 1;
}

LUA_FUNCTION( IsConnected )
{
	auto serial = LUA->GetUserType<Serial>( 1, SerialTable );
	LUA->PushBool( serial->isOpen() );
	return 1;
}

LUA_FUNCTION( Close )
{
	auto serial = LUA->GetUserType<Serial>( 1, SerialTable );
	if ( serial->isOpen() )
	{
		serial->close();
		delete serial;
	}
	return 0;
}

GMOD_MODULE_OPEN()
{
	SerialTable = LUA->CreateMetaTable( "Serial" );
	LUA->Push( -1 );
		LUA->SetField( -2, "__index" );
		LUA->PushCFunction( SetTimeout );
		LUA->SetField( -2, "SetTimeout" );
		LUA->PushCFunction( WriteString );
		LUA->SetField( -2, "WriteString" );
		LUA->PushCFunction( ReadString );
		LUA->SetField( -2, "ReadString" );
		LUA->PushCFunction( IsConnected );
		LUA->SetField( -2, "IsConnected" );
		LUA->PushCFunction( Close );
		LUA->SetField( -2, "Close" );
	LUA->Pop();

	LUA->PushSpecial( SPECIAL_GLOB );
		LUA->CreateTable();
			LUA->PushCFunction( Begin );
			LUA->SetField( -2, "Begin" );
			LUA->PushCFunction( ListDevices );
			LUA->SetField( -2, "ListDevices" );
		LUA->SetField( -2,  "gmserial" );
	LUA->Pop();
	return 0;
}

GMOD_MODULE_CLOSE()
{
	return 0;
}
