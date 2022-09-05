#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/// A function that establishes a connection between 2 Players over local network.
char EstablishConnection(sf::TcpSocket& socket, char connectionType, string ip)
{
	char buffer[1000];									 //A character array to recieve the data over network.
	size_t recieved;									 //Size of recieved data in bytes.

	if (connectionType == 'H') {
		//Wait for a connection from client on port 2000.
		sf::TcpListener listener;
		listener.listen(2000);
		sf::SocketSelector selector;
		selector.add(listener);
		if (selector.wait(sf::seconds(1.0f))) {
			sf::Socket::Status status = listener.accept(socket);
		}
	
	}
	else if (connectionType == 'C') {
		sf::IpAddress hostIP;
		stringstream ss;
		ss << ip;
		ss >> hostIP;

		//Connect to a host with given IP on port 2000.
		socket.connect(hostIP, 2000);
	}

	string test = "Connected";

	// send text over network to verify connection.
	socket.send(test.c_str(), test.size() + 1);
	socket.receive(buffer, sizeof(buffer), recieved);
	if ((string)buffer == "Connected")
		return connectionType;
	return 'n';
}

void send_over_network(sf::TcpSocket& socket, string data) {
	socket.send(data.c_str(), data.size() + 1);
}

string wait_for_data(sf::TcpSocket& socket) {
	char buffer[2000];
	size_t recieved;
	sf::SocketSelector selector;
	selector.add(socket);
	if (selector.wait(sf::seconds(0.5f))) {
		socket.receive(buffer, sizeof(buffer), recieved);
		return (string)buffer;
	}
	else {
		return "NULL";
	}
}
