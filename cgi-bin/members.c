#include <string.h>
#include <stdio.h>

int main(void)
{
	FILE *f = fopen("members.csv","rt");
	char [256];

	printf("Content-Type:text/html\n\n");
	printf("<html>");

	if (f==NULL)
	{
		printf("<head><title>ERROR</title></head>");
		printf("<body><p>Unable to open file!</p></body>");
	}
	else
	{
	//	fgets(ch, 256, f);
		while((ch=fgetc(f)) != EOF) putchar(ch);
		fclose(f);		
	
	}
	printf("</html>");
	return 0;
}
