/*
 * main.cpp
 *
 *  Created on: 4 янв. 2021 г.
 *      Author: user
 */

#include "Comm.hpp"
Comm comm;

void Terminal(){
	comm.TerminalCommander();
};
int main(int argc, char *argv[]) {
	Terminal();
	return 0;
}

