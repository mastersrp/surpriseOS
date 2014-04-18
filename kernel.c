/*
*	kernel.c
*
*	Variable Breakdown:
* 
*	vidptr = an array 80 * 25 * 2 bytes long.
* 		->First byte is the character to be printed
*		->Second byte is the color (See colors listed)
* 		->Supports 25 lines, each containing 80 characters
* 		->Begins at address 0xb8000
*
*	string = an array that holds the current character to be
* 			 loaded into vidptr.
*
*
*/


void clear(char *vidptr)						//clears the screen
{
	int j = 0;
	while (j < 80 * 25 * 2) {
		vidptr[j] = ' ';					//blank character
		vidptr[j+1] = 0x07;
		j = j + 2;
	}
}

void scroll(char *vidptr)
{
	char *tempstring = vidptr;				//put the contents of vidptr into a string
	int j = 0;
	while (tempstring[j + 160] != '\0') {	//repeat until the last line is reached
		vidptr[j] = tempstring[j + 160];	//shift characters into the previous line
		j++;
	} 
}


void pause(int unit)						//dirty pausing method, does a for loop
{
	int x = 0;
	while (x < (unit * 100)){
		++x;
	}
	return;
}

int linebreak (int i, int lines)
{
	i = i + (160 * lines);
	return i;
}

void printstring(char *string, char *vidptr, int i, int j, int color, int wait) 
{
	while(string[j] != '\0') {				//while string is not null, print characters
		vidptr[i] = string[j];				
		vidptr[i+1] = color;				//set attribute byte (color)
		++j;								//increase character one
		i = i + 2;							//skip to the next vidptr character input.
	}
	if (i >= 80 * 25 * 2) {
		scroll(vidptr);
	}
	if (wait == 1){							//if wait is positive, pause after displaying
		pause(5500000);
		j = 0;
	}
	return;
}

void kmain(void)
{
	//strings to print
	char *str1 = "We're no strangers to love";						//cyan
	char *str2 = "You know the rules and so do I";
	char *str3 = "A full commitment's what I'm thinking of";
	char *str4 = "You wouldn't get this from any other guy";
	char *str6 = "I just wanna tell you how I'm feeling";			//green
	char *str7 = "Gotta make you understand";
	char *str9 = "Never gonna give you up";							//red
	char *str10 = "Never gonna let you down";
	char *str11 = "Never gonna run around and desert you!";
	char *str12 = "Never gonna make you cry";
	char *str13 = "Never gonna say goodbye";
	char *str14 = "Never gonna tell a lie and hurt you!";
	char *str15 = "Surprise OS v. 1.00";							//blue
	
	//color codes
	int black = 0x00;
	int blue  = 0x01;
	int green = 0x02;
	int cyan  = 0x03;
	int red   = 0x04;
	int magnt = 0x05;
	int brown = 0x06;
	int lgrey = 0x07;
	int dgrey = 0x08;
	int lblue = 0x09;
	
	char *vidptr = (char*)0xb8000; 			//video memory begins here
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int line = 0;
	
	clear(vidptr);							//clear the screen
	
	j = 0;
	int wait = 1;
	
	// Here begins the macros!
	printstring(str1, vidptr, i, j, cyan, wait);
	i = linebreak(i, 1);
	printstring(str2, vidptr, i, j, cyan, wait);
	i = linebreak(i, 1);
	printstring(str3, vidptr, i, j, cyan, wait);
	i = linebreak(i, 1);
	printstring(str4, vidptr, i, j, cyan, wait);
	i = linebreak(i, 2);										//jump here
	printstring(str6, vidptr, i, j, green, wait);
	i = linebreak(i, 1);
	printstring(str7, vidptr, i, j, green, wait);
	i = linebreak(i, 2);										//jump here
	printstring(str9, vidptr, i, j, red, wait);
	i = linebreak(i, 1);
	printstring(str10, vidptr, i, j, red, wait);
	i = linebreak(i, 1);
	printstring(str11, vidptr, i, j, red, wait);
	i = linebreak(i, 1);
	printstring(str12, vidptr, i, j, red, wait);
	i = linebreak(i, 1);
	printstring(str13, vidptr, i, j, red, wait);
	i = linebreak(i, 1);
	printstring(str14, vidptr, i, j, red, wait);
	i = linebreak(i, 2);										//jump here
	printstring(str15, vidptr, i, j, lgrey, wait);
	
	scroll(vidptr);
	scroll(vidptr);
	scroll(vidptr);
	
	return;
}
