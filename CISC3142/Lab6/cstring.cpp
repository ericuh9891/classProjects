#ifndef CSTRING_H
#define CSTRING_H

char *strcpy(char *dest, const char *src){
	while(*dest){
		*dest++ = *src++;
	}
	return dest;
} 


#endif
