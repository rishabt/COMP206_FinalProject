#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

int main(void)
{
	FILE *in;
	char site[256], desc[256];
	char *data;

	/* print to webserver */
	printf("Content-type: text/html\n\n");
	printf("<!doctype html>\n\n");
	printf("<html><head><title>Search</title></head><body>\n");

	/* open web.csv */
	in=fopen("web.csv", "rt");
	if(in == NULL) {
		printf("<p>Error.</p>");
	} else {
		data = getenv("QUERY_STRING");
		printf("<p>%s</p>\n", data);
		while(fscanf(in, "%s, %s\n", site, desc) == 2) {
			printf("<p>%s! (%s)</p>\n", site, desc);
		}
		fclose(in);
	}

	printf("</body></head>\n");

	return 0;
}
