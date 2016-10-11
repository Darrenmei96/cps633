#define MAX_ATTEMPTS 3
#define MAX_USERS 10

typedef struct userhash{
	char *name;
	char *hash;
} userhash;

void ioInit();
char *getUser();
char *getHashedPassword();
char *getUserInfo();
