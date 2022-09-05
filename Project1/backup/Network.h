#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

using namespace std;

char EstablishConnection(sf::TcpSocket& socket)
{
	/// A function that establishes a connection between 2 Players over local network.
	sf::IpAddress ip = sf::IpAddress::getLocalAddress(); //Local IP Address of the machine.
	char connectionType;                                 //Connection Type can be 'H' for Host or 'C' for client. 
	char buffer[1000];									 //A character array to recieve the data over network.
	size_t recieved;									 //Size of recieved data in bytes.

	cout << "Enter Connection Type: ";
	cin >> connectionType;
	if (connectionType == 'H') {
		cout << "Type this ip on the client machine: " << ip.toString() << endl;

		//Wait for a connection from client on port 2000.
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
	}
	else if (connectionType == 'C') {
		sf::IpAddress ip;
		cout << "Enter host ip: ";
		cin >> ip;

		//Connect to a host with given IP on port 2000.
		socket.connect(ip, 2000);
	}

	string test = "Connected";

	// send text over network to verify connection.
	socket.send(test.c_str(), test.size() + 1);
	socket.receive(buffer, sizeof(buffer), recieved);
	cout << buffer << endl;
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
