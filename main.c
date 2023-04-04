#include <stdio.h>
#include <stdbool.h>

#define LMAX 20
#define LMIN 6
//if the input string is larger than 20, we take into consideration the first 20 characters, so the rest is ignored and not considered as delete operations
//also copying the input characters and the addition of '\0' to the end of the output password are not considered(counted) as insertion changes
int main() {
    char str[40];//input

    char out[21];//out[0-20]
    //'\0' is placed at out[20] => [0-19] -> 20 positions for password characters

    printf( "Enter a password :");
    gets( str );

    printf( "\nYou entered: ");
    puts( str );


    int count = 0;//operations counter
    bool l = false;//lowercase presence
    bool L = false;//uppercase presence
    bool d = false;//digit presence
    bool maxlength = false;
    bool minlength = false;

    int digitCount = 0, lowerCount = 0, upperCount = 0;

    int index = 0;
    char c = str[index];
    char prevC;//previous character
    int consecutive = 1;//used for counting consecutive apparitions of the same character

    while(c != '\0' && index <LMAX)//start iterating through the input list, at most 20 characters
    {
        int asc = (int)c;//ASCII code of c

        if((asc >= (int)'a') && (asc <= (int)'z'))
        {
            lowerCount++;
        }

        if((asc >= (int)'A') && (asc <= (int)'Z'))
        {
            upperCount++;
        }

        if((asc >= (int)'0') && (asc <= (int)'9'))
        {
            digitCount++;
        }

        out[index] = c;
        index++;
        prevC = c;
        c = str[index];
        if(prevC == c)   //compare current char with next char
            consecutive++;
        else
            consecutive = 1;//restore initial value for consecutive

        if(consecutive==3)
        {
            //change middle character
            out[index-1] = (char)((int)c + 1);
            count++;
            //restore initial value for consecutive
            consecutive = 1;
        }
        //printf("%c %c\n", prevC, c);
    }
//WHILE EXIT
//index can't be greater than LMAX

    if(index == LMAX)
    {
        if (c =='\0')//20 characters spot on
        {
            maxlength = true;
            out[index] = '\0';
        }
    }
    if(index < LMAX)
    {
        maxlength = true;
        out[index] = '\0';//index can't be greater than LMAX
    }

    if(index >= LMIN) //index -1 for the '\0' on exit but +1 because index starts at 0
    {
        minlength = true;
        out[index] = '\0';
    }
    else
    {
        //need to add, in index we already have the correct position to start adding characters Ex: abc\0, index = 3
        while(index < LMIN)
        {
            count++;
            out[index] = (char)((int)out[index-1] + 1);//add the next character in the ascii table to the previous char from out[], so that we maintain rule 3 true
            index++;
        }
        out[index] = '\0';
    }

    //At this point we already have the length in the correct parameters
    if(digitCount==0)//count is incremented only by 1 in these 3 cases, since a replace change is enough.
        count++;
    else
        d = true;
    if(lowerCount==0)
        count++;
    else
        l = true;
    if(upperCount==0)
        count++;
    else
        L = true;

    printf("str: %s\n", str);
    printf("out: %s\n", out);
    printf("d=%d, l=%d, L=%d, minlength=%d, maxlength=%d", d,l,L,minlength,maxlength);

    return count;
}
