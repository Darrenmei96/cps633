/*
        OLMHash Password Scheme
*/

#include "olmhash.h"
#include "hash.h"
#include "userio.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void generateAccount(char *name, char *pass){
    char *n = calloc(sizeof(char), 33);
    char *p = calloc(sizeof(char), 13);
    strcpy(n,name);
    strcpy(p,pass);
    registerAccount(n,passToHash(p));
}

void generateAccounts(){
    generateAccount("darren\n","1234\n");
    generateAccount("namm\n","n0p3\n");
    generateAccount("raymon\n","j4d3\n");
    generateAccount("mustafa\n","f33t\n");
}

int olmHash(){
    ioInit();
    generateAccounts();
    printList();
    char *userid, *userpwhash;
    while(1){
        userid = getUser();
        if (userid == 0){
            break;
        }
        userpwhash = getUserInfo(userid);
        if (userpwhash == 0){
            registerAccount(userid, getHashedPassword());
        }else{
            if(!checkPassword(userpwhash)){
                break;
            }
        }
    }
    ioDestroy();
}
