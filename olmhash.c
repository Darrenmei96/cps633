/*
        OLMHash Password Scheme
*/

#include "olmhash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void E(char *in, char *out);
char *getUserInfo(char *userid);
char *getUser();
char *getPasswordHashed();

userhash **accountList;
int currentIndex = 0;

int main(void){
    ;
}

int olmHash(){

    *accountList = malloc(sizeof(userhash) * MAX_USERS);

    char *userid, *userpwhash;
    while(1){
        userid = getUser();
        userpwhash = getUserInfo(userid);
        if (!userpwhash){
            registerAccount(userid);
        }else{
            checkPassword(userid);
        }
    }
}

char *passToHash(char *pass){
    char *hash = malloc(sizeof(char)*13);
    int i = 0;
    for(; i < 3; ++i){
        E(&pass[4*i], &hash[4*i]);
    }
    return hash;
}

/*
	Get the userID
*/
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
        if (strcmp(getPasswordHashed(), passHash) == 0){
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
    accountList[currentIndex]->hash = getPasswordHashed();
    printf("Account created!\n");
    return 1;
}

char *getPasswordHashed(){
    char *password = malloc(sizeof(char) * 13);
    printf("Enter in a password: ");
    fgets(password, 12, stdin);
    if (!checkPasswordFormat(password)){
        return getPasswordHashed();
    }
    return passToHash(password);
}

int checkPasswordFormat(char *pass){
    int i = 0;
    for(;i<13; ++i){
        //if it is neither a letter or a digit, password
        //format is incorrect
        if(!isalpha(pass[i]) || !isdigit(pass[i])){
            return 0;
        }
    }
    return 1;
}

char *fillChar(char *password){
	int zeroesNeeded = 12 - strlen(password);
	while (zeroesNeeded != 0){
	  //add zero to the end of password
		password[strlen(password) - 1 - zeroesNeeded] = '\0';
	  //zeroesNeeded - 1
		--zeroesNeeded;
	}
	return password;
}



/********************* E function *************************/
// DES replacement cipher
// The function E takes 4 bytes from *in as input
// after a conversion to uppercase and
// writes 4 bytes to *out
void E(char *in, char *out){
    char in0 = toupper(in[0]);
    char in1 = toupper(in[1]);
    char in2 = toupper(in[2]);
    char in3 = toupper(in[3]);

	out[0]=(in0&0x80)^(((in0>>1)&0x7F)^((in0)&0x7F));
	out[1]=((in1&0x80)^((in0<<7)&0x80))^(((in1>>1)&0x7F)^((in1)&0x7F));
	out[2]=((in2&0x80)^((in1<<7)&0x80))^(((in2>>1)&0x7F)^((in2)&0x7F));
	out[3]=((in3&0x80)^((in2<<7)&0x80))^(((in3>>1)&0x7F)^((in3)&0x7F));
}
