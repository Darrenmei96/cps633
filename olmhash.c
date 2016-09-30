/*
        OLMHash Password Scheme
*/

/*
	Get the userID
*/
char *getUser(){
    char userID[32];

	while(1){
    	printf("Enter in your user ID: ");
    	fgets(userID, 31, stdin);
		if (strlen(userID) > 4){
			break;
		}
		printf("Minimum userID length: 4 characters!\n");
	}
	return userID;
}

/********************* E function *************************/
// DES replacement cipher
// The function E takes 4 bytes from *in as input and
// writes 4 bytes to *out
void E(char *in, char *out){
	out[0]=(in[0]&0x80)^(((in[0]>>1)&0x7F)^((in[0])&0x7F));
	out[1]=((in[1]&0x80)^((in[0]<<7)&0x80))^(((in[1]>>1)&0x7F)^((in[1])&0x7F));
	out[2]=((in[2]&0x80)^((in[1]<<7)&0x80))^(((in[2]>>1)&0x7F)^((in[2])&0x7F));
	out[3]=((in[3]&0x80)^((in[2]<<7)&0x80))^(((in[3]>>1)&0x7F)^((in[3])&0x7F));
}

/*
	Call E, with uppercase input chars
*/
void ECall(char *in, char *out){
	char upperin[4];
	for (int i = 0; i < 4; i++){
		upperin[i] = toupper(in[i]);
	}
	E(upperin[i],out);
}
