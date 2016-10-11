/*
	Contains all the functions necessary for:
	olmhash.c
	challenge-response.c
*/

#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


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

void *padChar(char *pass){
	int i = strlen(pass);
	while (i<13){
		pass[i++] = '\0';
	}
}

char *passToHash(char *pass){
	padChar(pass);
	char *hash = malloc(sizeof(char)*13);
    int i = 0;
    for(; i < 3; ++i){
        E(&pass[4*i], &hash[4*i]);
    }
    return hash;
}

int checkPasswordFormat(char *pass){
    int i = 0;
	printf("%s",pass);
    for(;i<13; ++i){
		if(pass[i] < 32){
			break;
		}

        //if it is neither a letter or a digit, password
        //format is incorrect
		if (isalpha(pass[i])){
			continue;
		}
		if (isdigit(pass[i])){
			continue;
		}
		return 0;

    }
    return 1;
}
