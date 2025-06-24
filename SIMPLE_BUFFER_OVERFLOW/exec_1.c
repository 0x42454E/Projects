#include <stdio.h>
#include <string.h>

int IsAllowedUser(char* name)
{}

void PrivilegedActions()
{
	printf("Allow changed!\n");
}


int main()
{
	char username[8];
	int allow = 0;
	
	printf("Enter your username, please: ");
	gets(username);
	
	if (IsAllowedUser(username))
	{
		allow = 1;
	}	
	
	if (allow)
	{
		PrivilegedActions();
	}
	
	return 0;
}
