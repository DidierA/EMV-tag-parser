#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tlv.h"
#include "hashtable.h"
#include "emvTagList.h"

# define MAXSIZE 4096

int is_hex_char (char c) {
    c=tolower(c) ;
    char * allowed_chars="0123456789abcdef" ;
    for (int i=0; i<strlen(allowed_chars); i++) {
        if (c == allowed_chars[i]) return 1 ;
    }
    return 0 ;
}

int main(int ac, char *av[]) {
    dict_t *dict[HASHSIZE];
	memset(dict, 0, sizeof(dict));
	emvInit(dict);
	// displayTable(dict);
    int i ;
    unsigned char input[MAXSIZE+1] ;

    char s[MAXSIZE+1] ;

    unsigned short size=0 ;

    while (fgets(s, MAXSIZE, stdin) != NULL){

        for (i=0; i<strlen(s); i++) {
            if (
                !(is_hex_char(s[i]) && is_hex_char(s[i+1]))
                ) continue ;  
            char b[3] ;
            b[0]=s[i]; b[1]=s[i+1]; b[2]='\0' ;
            sscanf(b, "%x", input+size) ;
            size++; i++;
        }
    }
	
    tlvInfo_t *t=malloc(sizeof(tlvInfo_t)*size);
	memset(t,0,size);
	tlvInfo_init(t);
	int tindex =0;
	emvparse(input, size, t, &tindex , 0, dict);
	emvPrint_result(t, tindex);

	return 0;
}