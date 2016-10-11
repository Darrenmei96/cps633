/*
	Contains all the functions
	handling user io
*/

#include "userio.h"
#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

userhash **accountList;
int currentIndex = 0;

void ioInit(){
	printf("Initializing the user list!\n");
	*accountList = malloc(sizeof(userhash*) * MAX_USERS);
}

char *getUser(){
    char *userID = malloc(sizeof(char) * 33);
	while(1){
    	printf("Enter in your user ID: ");
    	fgets(userID, 32, stdin);
		if (strlen(userID) > 4){
			break;
		}
		printf("Minimum userID length: 4 characters!\n");
	}
	return userID;
}

char *getHashedPassword(){
	char *password = malloc(sizeof(char) * 13);
    printf("Enter in a password: ");
    fgets(password, 12, stdin);
    if (!checkPasswordFormat(password)){
        return getHashedPassword();
    }
    return passToHash(password);
}

char *getUserInfo(char *userID){
 	int i = 0;
    for(; i < MAX_USERS ; i++){
        if (accountList[i]->name == NULL){
            break;
        }else if (strcmp(accountList[i]->name,userID)==0){
            return accountList[i]->hash;
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
            return 1;
            break;
        }
	}
    //if password cannot be retrieved and authenticated given
    //a reasonable amount of tries, exit
    return 0;
}

int registerAccount(char *userID){
    if(currentIndex >= MAX_USERS){
        return 0;
    }
    printf("userID: %s not found! ", userID);
    accountList[currentIndex]->name = userID;
    accountList[currentIndex]->hash = getHashedPassword();
    printf("Account created!\n");
    return 1;
}
