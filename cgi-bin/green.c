#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	FILE *f=fopen("web.csv", "rt");
	char st[256];
	int i=0;
	double totMatch=0;
	int tot=0;

	printf("Content-Type:text/html\n\n");
	printf("<html>");

	if(f==NULL)
	{
		printf("<head><title> ERROR </title></head>");
		printf("<body><p> Unable to open file! </p></body>");
	}
	else
	{
		printf("Enter a token: ");
		scanf("%s", st);
		while(!feof(f))
		{
			for(i=0; i < sizeof(st)/sizeof(st[0]);i++)
			{
				if(fgetc(f)==st[0])
				{
					totMatch++;
					tot++;
				}
				else
					tot++;			

				if(fgetc(f)=='\n')
				{
					printf(".%3f", totMatch/tot);
					totMatch=0;
					tot=0;
				}
			}

		}
	}
}
