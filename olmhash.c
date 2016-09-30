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

char *getUserInfo(char *userID){
 	struct nlist info = lookup(userID);
	if (info != NULL){
		//if the table entry is not null
		//return the password hash
		return info->defn;
	}
	return NULL;
}

char *getPassword(char *passHash){
	char password[12];
	int counter = 0;
	while(1){
		printf("Enter in your password: ");
		fgets(password, 11, stdin);

	}
}

char *fillChar(char *password){
	
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



/*
	Beginning of dictionary definition
*/


struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};

//Note that hashtab will become what holds our user-pass info
#define HASHSIZE 128
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
          return np; /* found */
    return NULL; /* not found */
}

char *strdup(char *);
/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
          return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else /* already there */
        free((void *) np->defn); /*free previous defn */
    if ((np->defn = strdup(defn)) == NULL)
       return NULL;
    return np;
}

char *strdup(char *s) /* make a duplicate of s */
{
    char *p;
    p = (char *) malloc(strlen(s)+1); /* +1 for ’\0’ */
    if (p != NULL)
       strcpy(p, s);
    return p;
}


/*
	End of dictionary definition - taken from
	section 6.6 of "The C Programming Language"
*/
