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
    generateAccount("darren\n","w4st3");
    generateAccount("namm\n","n0p3");
    generateAccount("raymon\n","j4d3");
    generateAccount("mustafa\n","f33t");
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
            if(!checkPassword(userpwhash)){
                break;
            }
        }
    }
    ioDestroy();
}
