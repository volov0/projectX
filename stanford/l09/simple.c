/**
 * @file simple.c
 * @author volovo
 * @date 17.12.2014
 * @brief jednoduche operace, cil je ukazat jake instrukce to vygeneruje
 */


int fxn(int a);
int gxn(int b, int c, int d);

 
/**
 * Function main
 * -------------
 * - test 01 - 
 */
//int main(int argc, char *argv[]) {
int main(void) {
	int i;
	int j;
	int k;

	i = 10;
	j = i + 7;
	k = fxn(j);
	k++;
	return k;
}

/**
 * Function fxn
 * ------------
 * uplne jednoducha funkce na demonstraci stacku
 */
int fxn(int a) {
	int x;
	x = a + 9;
	x = gxn(x,4,2);
	return x;
}

/**
 * Function gxn
 * ------------
 * uplne jednoducha funkce na demonstraci stacku
 */
int gxn(int b, int c, int d) {
	int arr[4];
	int i;
	for (i = 0; i < 4; i++) {
		arr[i] = c;
	}
	i = i + d + b + arr[3];
	return i;
}
