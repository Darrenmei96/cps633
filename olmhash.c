/*
        OLMHash Password Scheme
*/

#include "olmhash.h"
#include "hash.h"
#include "userio.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int olmHash(){
    ioInit();
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
