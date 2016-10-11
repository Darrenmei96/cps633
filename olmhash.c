/*
        OLMHash Password Scheme
*/

#include "olmhash.h"
#include "hash.h"
#include "userio.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void generateAccounts(){
    registerAccount("darren",passToHash("password123"));
    registerAccount("nam",passToHash("nopassword"));
    registerAccount("raymon",passToHash("sober4ever"));
    registerAccount("mustafa",passToHash("b1essedfeet"));
}

int olmHash(){
    ioInit();
    generateAccounts();
    printList();
    char *userid, *userpwhash;
    while(1){
        userid = getUser();
        userpwhash = getUserInfo(userid);
        if (userpwhash == 0){
            registerAccount(userid, getHashedPassword());
        }else{
            checkPassword(userpwhash);
            break;
        }
    }
    ioDestroy();
}
