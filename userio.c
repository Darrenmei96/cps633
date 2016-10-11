/*
	Contains all the functions
	handling user io
*/

#include "userio.h"
#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

userhash *accountList;
int currentIndex = 0;

void printList(){
	int i = 0;
	while(i<currentIndex){
		if(accountList[i].name != NULL){
			printf("%s", accountList[i++].name);
		}
	}
}

void ioInit(){
	userhash *list = calloc(sizeof(userhash), MAX_USERS);
	accountList = list;
}

char *getUser(){
    char *userID = calloc(sizeof(char), 33);
	while(1){
    	printf("Enter in your user ID: ");
    	fgets(userID, 33, stdin);
		if (strlen(userID) > 4){
			break;
		}
		printf("Minimum userID length: 4 characters!\n");
	}
	return userID;
}

char *getHashedPassword(){
	char *password = calloc(sizeof(char), 13);
    printf("Enter in a password: ");
    fgets(password, 13, stdin);
    if (!checkPasswordFormat(password)){
		printf("Incorrect format! Alphanumeric only!\n");
        return getHashedPassword();
    }
    return passToHash(password);
}

char *getUserInfo(char *userID){
 	int i = 0;
    for(; i < currentIndex ; i++){
        if (strcmp(accountList[i].name,userID)==0){
            return accountList[i].hash;
        }
    }
    return 0;
}

int checkPassword(char *passHash){
	int counter = 0;
	while(counter++<MAX_ATTEMPTS){
        //The compared hashes are the same
        //assume that the passwords are equal
        if (strcmp(getHashedPassword(), passHash) == 0){
			printf("Login Successful!\n");
            return 1;
            break;
        }
		printf("Incorrect password!\n");
	}
    //if password cannot be retrieved and authenticated given
    //a reasonable amount of tries, exit
    return 0;
}

int registerAccount(char *userID, char *passwordhash){
    if(currentIndex >= MAX_USERS){
        return 0;
    }
    //printf("\nuserID: %s not found! ", userID);
    accountList[currentIndex].name = userID;
    accountList[currentIndex].hash = passwordhash;
    printf("Account created!\n");
	++currentIndex;
    return 1;
}

void ioDestroy(){
	int i = 0;
	for(;i<MAX_USERS;i++){
		if(accountList[i].name){
			free(accountList[i].name);
			free(accountList[i].hash);
		}
	}
	free(accountList);
}
