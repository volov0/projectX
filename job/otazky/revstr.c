/**
 * @file revstr.c
 * @author Vaclav Koudelka
 * @date 19.10.2015
 * @brief prevrati retezec
 */

#include <stdio.h>
#include <string.h>

/**
 * @param str string which will be reverted
 */
void revstr(char *str) {
	/*char tmp;*/
	int i, j;
	for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
		/*tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;*/
		str[i] ^= str[j];
		str[j] ^= str[i];
		str[i] ^= str[j];
	}
}

int main(int argc, char **argv) {
	char *s = strdup("abcdefghijklmnopq");

	revstr(s);
	printf("Reverted string: %s\n", s);
	/*free(s);*/
	return 0;
}
