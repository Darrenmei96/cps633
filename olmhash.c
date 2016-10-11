/*
        OLMHash Password Scheme
*/

#include "olmhash.h"
#include "hash.h"
#include "userio.h"
#include <stdlib.h>
#include <stdio.h>

int olmHash(){
    ioInit();
    char *userid, *userpwhash;
    while(1){
        userid = getUser();
        userpwhash = getUserInfo(userid);
        if (userpwhash == 0){
            registerAccount(userid);
        }else{
            checkPassword(userpwhash);
            break;
        }
    }
    ioDestroy();
}
