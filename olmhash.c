/*
	OLMHash Password Scheme
*/

struct userhash{
	char name[32];
	char hash[32];
}

typedef struct userhash userhash

int prompt(char ){
	/*
		Get the userID
	*/
	int userIDLength = 32;
	char userID[userIDLength];
	printf("Enter in your user ID: ");
	fgets(userID, userIDLength - 1, stdin);

	int i = 1, max_attempts = 3;
	char pass[12];
	do{
		printf("Enter in your password :");
		fgets(pass, 11, stdin);


	}while (i < max_attempts);

}
