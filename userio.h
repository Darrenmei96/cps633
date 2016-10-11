#define MAX_ATTEMPTS 3
#define MAX_USERS 10

typedef struct userhash{
	char *name;
	char *hash;
} userhash;

void ioInit();
void printList();
void ioDestroy();
char *getUser();
char *getHashedPassword();
char *getUserInfo();
int registerAccount();
int checkPassword();
