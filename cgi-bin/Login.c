#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DATAFILE "../data/members.csv"
#define MAXLEN 80
#define EXTRA 5
#define MAXINPUT MAXLEN+EXTRA+2

const char* getfield(char* line, int num)
{
		const char* token;
		for (token = strtok(line, " ");
			token && *token;
			token = strtok(NULL, " \n"))
		{
			if (!--num)
				return token;
		}

		return NULL;
}


void unencode(char *src, char *last, char *dest)
{
	 for(; src != last; src++, dest++)
		    if(*src == '&' || *src == '=')
			         *dest = ' ';
	    else if(*src == '%') {
		         int code;
			      if(sscanf(src+1, "%2x", &code) != 1) code = '?';
			           *dest = code;
				        src +=2; }     
	    else
		         *dest = *src;
	  *dest = '\n';
	   *++dest = '\0';
}


int main(void)
{
	    char *lenstr;
	    char input[MAXINPUT], data[MAXINPUT];
	    long len;
	    const char* uname;

	    printf("%s%c%c\n",
			    "Content-Type:text/html;charset=iso-8859-1",13,10);
	    printf("<TITLE>Response</TITLE>\n");

	    lenstr = getenv("CONTENT_LENGTH");
	    if(lenstr == NULL || sscanf(lenstr,"%ld",&len)!=1 || len > MAXLEN)
		      printf("<P>Error in invocation - wrong FORM probably.");
	    else {
		fgets(input, len+1, stdin);
		unencode(input+EXTRA, input+len, data);
		const char* in_pass = getfield(&data[0], 3);
		const char* in_user = getfield(&data[0], 1);
		uname = in_user;
		int found = 0;

		FILE* file = fopen(DATAFILE, "r");
		char line[256];
            	while (fgets(line, sizeof(line), file)) {

			char* tmp1 = strdup(line);
			const char* pass = getfield(line, 3);

			const char* user = getfield(tmp1, 2);

			if(strcmp(user, in_user) == 0){
				if(strcmp(pass, in_pass) == 0){
					found = 1;
					break;
				}
			}
	    	}

		fclose(file);

		if(found == 1){
			printf("<p>Logged in!");
			printf("<form action=\"http://cgi.cs.mcgill.ca/~rtando1/cgi-bin/MyFacebookPage.py\" METHOD=\"POST\"><input type=\"hidden\" name=\"username\" value=\"%s\"><INPUT TYPE=\"SUBMIT\" VALUE=\"Go to your profile\" NAME=\"pass\"></form>", uname);	
		}
	    }

            return 0;
}
