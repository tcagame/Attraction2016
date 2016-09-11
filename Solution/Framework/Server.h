#pragma once

#include "Task.h"
#include "smart_ptr.h"
#include "Network.h"
#include "DxLib.h"
#include <array>

PTR( Server );

class Server : public Task {
public:
	static std::string getTag( ) { return "SERVER"; }
	static ServerPtr getTask( );
public:
	Server( );
	virtual ~Server( );
public:
	virtual void update( );
	void saveIP( );
	std::string getMachineIPStr( int index );
	void sendStatus( const CLIENTDATA& data );
	void setConecting( int index, int device );
	CLIENTDATA getData( );
	void updateOriginal( );
private:
	void listenForAcceptNewClient( );
	void listenForPackets( );
	void sendCondition( );
	void showTheReceivedLog( int index, const SERVERDATA& data );
	void executeNetData( const SERVERDATA& data );
	void resetDevice( int index = 0 );
	void sendData( );
	void resetState( );
private:
	std::array< int, MAX_MACHINE > _machine;
	int _udp_handle;
	int _network_state_time;
	int _send_network_condition_num;
	int _count;
	CLIENTDATA _data;
};