/*
	Challenge-Response (Online) Authentication
*/

#include <stdlib.h>

int main(){
	//user sends userid to server

	//server sends client a random 32-bit integer r

	//user computes r XOR h where
	//r is the random int
	//h is the hashed password from user
	//send result to server

	//server computes r XOR pwh where
	//r is the same random int
	//pwh is the "correct" password hash for the userID
	//if match print "access granted"
	//else print "access denied" to user
}
