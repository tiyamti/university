TIMAP Tool for Network Scanning

This project is a simple implementation of some core functionalities of the Nmap network scanning tool. It allows users to perform network scanning tasks, such as checking online status of hosts, scanning specific or all ports on a host, measuring response latency, and simulating HTTP GET and POST requests.

Features

Host Online Status: Check if a host is online by attempting to establish a connection.
Port Scanning: Scan a range of ports on a given host to identify which are open.
Latency Measurement: Calculate the average response time for a port.
HTTP Method Simulation: Simulate HTTP GET and POST methods to interact with a server that maintains user data.

Usage

The tool can be run with various commands to perform different network-related tasks:

Commands:

 - -h: Displays help information about the tool.

 - -sS: Checks if a host is online.

 - -r: Tests all ports of a specified IP address to determine whether they are open or closed.

 - -p: Scans selected ports. After using this command, specify the port numbers, followed by the IP address.

 - -sp: Selects the type of HTTP request to use.

 - -sp GET: Use the GET request type. Requires user ID.

 - -sp POST: Use the POST request type. Requires user name and age.

 - -sN: trace ping of IP, U can send hole part of IP xxx.xxx.xxx.xxx or xxx.xxx.xxx. if you send like that it trace of all ranges of xxx.xxx.xxx.1 to 254

Project Structure

src/: Source code for the application.

README.md: Project documentation (this file).

Makefile: To compile the project (if using Make).

Contribution

Feel free to fork the project and submit pull requests. Please ensure your code adheres to the project's style guidelines and passes any unit tests before submitting.



Acknowledgements

The original Nmap tool for inspiration.
Qt framework for cross-platform development.
