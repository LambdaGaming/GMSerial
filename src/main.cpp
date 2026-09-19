#include "SerialPort.hpp"
#include "GarrysMod/Lua/Interface.h"

#define GMMODULE
#define DATA_LENGTH 255
#define PRINT( STRING ) \
	LUA->PushSpecial( SPECIAL_GLOB ); \
	LUA->GetField( -1, "print" ); \
	LUA->PushString( STRING ); \
	LUA->Call( 1, 0 ); \
	LUA->Pop();

using namespace GarrysMod::Lua;
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
		SerialPort *serial;
		serial = new SerialPort( port, baud );
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

LUA_FUNCTION( ListPorts )
{
	auto list = SerialPort::ListPorts();
	LUA->CreateTable();
	int index = LUA->Top();
	int key = 1;
	for ( auto p : list )
	{
		LUA->PushNumber( key );
		LUA->PushString( p.c_str() );
		LUA->SetTable( index );
		key++;
	}
	return 1;
}

LUA_FUNCTION( SetInputDelay )
{
	LUA->CheckType( 2, Type::Number );
	auto serial = LUA->GetUserType<SerialPort>( 1, SerialTable );
	if ( serial != nullptr && serial->isConnected() )
	{
		serial->InputDelay = LUA->GetNumber( 2 );
	}
	return 1;
}

LUA_FUNCTION( SetOutputDelay )
{
	LUA->CheckType( 2, Type::Number );
	auto serial = LUA->GetUserType<SerialPort>( 1, SerialTable );

	if ( serial != nullptr && serial->isConnected() )
	{
		serial->OutputDelay = LUA->GetNumber( 2 );
	}
	return 1;
}

LUA_FUNCTION( WriteString )
{
	LUA->CheckType( 2, Type::String );
	auto serial = LUA->GetUserType<SerialPort>( 1, SerialTable );
	auto str = LUA->GetString( 2 );

	LUA->PushSpecial( SPECIAL_GLOB );
		LUA->GetField( -1, "CurTime" );
		LUA->Call( 0, 1 );
		auto curtime = LUA->GetNumber( -1 );
	LUA->Pop( 3 );

	if ( serial != nullptr && serial->isConnected() )
	{
		if ( serial->OutputDelay && serial->OutputCooldown >= curtime )
		{
			LUA->PushBool( true );
			return 1;
		}

		auto haswritten = serial->writeSerialPort( str, DATA_LENGTH );
		if ( serial->OutputDelay )
		{
			serial->OutputCooldown = curtime + serial->OutputDelay;
		}

		if ( haswritten )
		{
			LUA->PushBool( true );
			return 1;
		}
	}
	LUA->PushBool( false );
	return 1;
}

LUA_FUNCTION( ReadString )
{
	auto serial = LUA->GetUserType<SerialPort>( 1, SerialTable );
	char received[DATA_LENGTH];

	LUA->PushSpecial( SPECIAL_GLOB );
		LUA->GetField( -1, "CurTime" );
		LUA->Call( 0, 1 );
		auto curtime = LUA->GetNumber( -1 );
	LUA->Pop( 3 );

	if ( serial != nullptr && serial->isConnected() )
	{
		if ( serial->InputDelay && serial->InputCooldown >= curtime )
		{
			LUA->PushBool( true );
			return 1;
		}

		auto hasread = serial->readSerialPort( received, DATA_LENGTH );
		if ( serial->InputDelay )
		{
			serial->InputCooldown = curtime + serial->InputDelay;
		}

		if ( hasread )
		{
			LUA->PushString( received );
			return 1;
		}
	}
	LUA->PushString( "" );
	return 1;
}

LUA_FUNCTION( IsConnected )
{
	auto serial = LUA->GetUserType<SerialPort>( 1, SerialTable );
	LUA->PushBool( serial->isConnected() );
	return 1;
}

LUA_FUNCTION( Close )
{
	auto serial = LUA->GetUserType<SerialPort>( 1, SerialTable );
	if ( serial != nullptr && serial->isConnected() )
	{
		delete serial;
	}
	return 0;
}

GMOD_MODULE_OPEN()
{
	SerialTable = LUA->CreateMetaTable( "Serial" );
	LUA->Push( -1 );
		LUA->SetField( -2, "__index" );
		LUA->PushCFunction( SetInputDelay );
		LUA->SetField( -2, "SetInputDelay" );
		LUA->PushCFunction( SetOutputDelay );
		LUA->SetField( -2, "SetOutputDelay" );
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
			LUA->PushCFunction( ListPorts );
			LUA->SetField( -2, "ListPorts" );
		LUA->SetField( -2,  "gmserial" );
	LUA->Pop();
	return 0;
}

GMOD_MODULE_CLOSE()
{
	return 0;
}
