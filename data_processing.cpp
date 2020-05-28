#include "data_processing.h"
void int_to_char_array(int value, char* destination)
{
    int i=0;
    if(value == 0)
    {
        destination[i++]='0';
        destination[i]=0;
        return;
    }

    while(value != 0)
    {
        int temp = value % 10;
        destination[i++] = temp + '0';
        value /= 10;
    }
    destination[i] = 0;
    int start = 0;
    i--;
    while(start < i)
    {
        char temp = *(destination+start);
        *(destination + start) = *(destination + i);
        *(destination + i) = temp;
        start++;
        i--;
    }
}
