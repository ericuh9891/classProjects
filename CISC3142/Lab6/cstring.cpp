
namespace mystring{
#ifndef CSTRING_H
#define CSTRING_H
#endif
	char *strcpy(char *dest, const char *src){
		char *temp = dest;
		while(*dest++ = *src++);
		return temp;
	}
	int strlen(const char *str){
		if(*(str)){
			return strlen(++str) + 1;
		}
		else return 0;
	}
	char *strcat(char *dest, const char *src){
		char *temp = dest;		
		int dest_len = strlen(dest);
		dest = dest+dest_len;
		strcpy(dest,src);
		return temp;
	}
	int strcmp(const char *str1, const char *str2){
		if(*str1 == *str2 && (*str1 != '\0' && *str2 != '\0'))
			return strcmp(++str1,++str2);
		else if(*str1 == '\0' && *str2 != '\0')
			return -1;
		else if(*str2 == '\0' && *str1 != '\0')
			return 1;
		else if(*str1 - *str2 < 0)
			return -1;
		else if(*str1 - *str2 > 0)
			return 1;
		else return 0;
	}
	char *strchr(char *str, int c){
		if(*str == c)
			return str;
		else if(*str == '\0')
			return nullptr;
		else
			return strchr(++str,c);
	}
	char *strrchr(char *str, int c){
		int str_len = strlen(str);	
		str = str+str_len;
		for(int i = str_len; i != 0; --i,--str){
			if(*str == c)
				return str;
		}
		return nullptr;
	}
}
