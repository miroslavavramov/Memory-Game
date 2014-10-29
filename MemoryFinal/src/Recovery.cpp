/*
 * Recovery.cpp
 *
 *  Created on: Oct 2, 2014
 *      Author: User
 */

#include "Recovery.h"

// default Recovery constructor
Recovery::Recovery() {
	m_RecoverCredit = 0;
	m_RecoverState = RECOVERY;
	m_RecoverLevel = 0;

} //end Recovery constructor

// default Recovery destructor stub
Recovery::~Recovery() {

}

//Create recovery file function.
void Recovery::createRecoverFile() {

	//Create fstream File to open recover.dat for input in binary mode
	fstream File("files/recover.dat", ios::in | ios::binary);

	// exit program if fstream cannot open file
	if (!File) {
		cerr << "File could not be opened." << endl;
		exit(1);
	} // end if
} // end function createRecoverFile

void Recovery::saveRecoverFile(int level, int credit, gameStates state) {
	//Save temporary level, credit, state.
	m_RecoverLevel = level;
	m_RecoverCredit = credit;
	m_RecoverState = state;

	// Open file for writing.
	ofstream newFile("files/recover.dat", ios::binary | ios::out);

	// Insert record in file.
	if (newFile.is_open()) {
		newFile.write(reinterpret_cast<char*>(this), sizeof(Recovery));
	} else {
		// show message:
		std::cout << "Error opening file";
	}

	newFile.close();
}

void Recovery::LoadRecoverFile() {

	// Open file for reading.
	fstream File("files/recover.dat", ios::in | ios::binary);
	if (File.is_open()) {

		// Read file contents (until eof).
		while (!File.eof()) {
			// read next record from record file
			File.read(reinterpret_cast<char*>(this), sizeof(Recovery));
		}
	} else {
		// show message:
		std::cout << "Error opening file";
	}
	File.close();
}

//Get credit value.
int Recovery::getRecoverCredit() const {
	return m_RecoverCredit;
}

//Get level value.
int Recovery::getRecoverLevel() const {
	return m_RecoverLevel;
}

//Get state value.
gameStates Recovery::getRecoverState() const {
	return m_RecoverState;
}


