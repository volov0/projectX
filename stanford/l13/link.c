/**
 * @file link.c
 * @author volovo
 * @date 23.12.2014
 * @brief Sample na linkovani.
 * @detail
 *
 * Kdyz zakomentuju #include <stdio.h> kompilace a linkovani projde,
 * gcc hodi nejake warningy a pouzije implicitni deklaraci printf,
 * coz znamena, ze automaticky da retrun typ int a typy parametru podle
 * volani... v tomto pripade jeden parametr char *. .o soubor bude vypadat 
 * uplne stejne jako s #include, protoze printf ma shodou okolnosti
 * navratovy typ int (teoreticky... ve skutecnosti si gcc stezuje jeste na
 * "incompatible implicit declaration").
 * #include je jenom pro kompilator, ne pro linker. Kompilator diky tomu
 * kontroluje spravnost volani. .h soubory nerikaji nic o tom, kde se kod
 * nachazi, nejsou tam ani zadne jine informace uzitecne pro linker.
 * Smyslem deklaraci funkci je to, aby se volajici a volany shodli na tom
 * jak funkce vypada (jake bere parametry, jakou ma navratovou hodnotu) - 
 * - kompilator to muze kontrolovat. 
 * Linker o #includech nema poneti. Linker automaticky prohledava standartni 
 * knihovnu a tam printf najde, takze to zavola tak jak je to nakodovano, 
 * coz je v tomto pripade spravne.
 *
 * Kdyz zakomentuju #include <stdlib.h> opet vse projde a dostanu warningy 
 * kompilatoru. Jeden z nich je protoze navratovou hodnotu prirazuju do
 * pointeru void * - kompilator nevi, ze to ma byt void *. .o soubor bude
 * opet vypadat uplne stejne.
 *
 * Kdyz zakomentuju #include <assert.h> kompilace projde (hodi warning,
 * ze pouzije implicitni deklaraci), ale linkovani zfailuje, protoze
 * ve standartnich knihovnach nenajde funkci assert(). Kompilator tedy 
 * vygeneruje v .o souboru instrukci CALL <assert>, coz by delat nemel.
 * Dusledek je chyba linkeru.
 * Pozn.: assert() je #define.
 */

#include <stdio.h>      // obsahuje printf definici
#include <stdlib.h>     // obsahuje malloc a free definice
#include <assert.h>     // obsahuje assert #define



/**
 * Function main
 * -------------
 * -
 */
int main(int argc, char *argv[]) {
	void *mem = malloc(400);
	assert(mem != NULL);
	printf("chrrrrr...\n");
	free(mem);
	return 0;
}
