/**
 * @file	main.c
 * @brief	Funkcije za upravljanje serijskim portom
 * @author	Milan Lukic
 * @date	14-04-2019
 */


#include "../usart/usart.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <string.h>

void odaberi (char c, char r [20]);
void najfrekventnijeSlovo (char r [20]);
void makni_razmake(char r [20]);
void ukloni_duplikate(char r[20]);

int main ()

{
	usartInit(9600);

	char string [50], c;

	while(1)
	{
		usartPutString_P(PSTR("\r \n"));
		usartPutString_P(PSTR("Unesite string : "));

		while(!usartAvailable());
		_delay_ms(50);

		usartGetString(string);
		usartPutString(string);
		usartPutString_P(PSTR("\r \n"));

		usartPutString_P(PSTR("Izaberite opciju za modifikaciju unetog stringa: \r \n "));
		usartPutString_P(PSTR("1. Slovo koje se najvise ponavlja? \r \n"));
		usartPutString_P(PSTR("2. Ukloni sve razmake. \r \n "));
		usartPutString_P(PSTR("3. Ukloni sve duplikate karaktera. \r \n"));

		while(!usartAvailable());

		c = usartGetChar();

		odaberi(c, string);
	}

	return 0;
}

void odaberi(char c, char primljeniString [20])
{
	switch (c)
	{
			case '1' :
				najfrekventnijeSlovo(primljeniString);
				break;
			case '2' :
				makni_razmake(primljeniString);
				break;
			case '3' :
				ukloni_duplikate(primljeniString);
				break;
			default:
				usartPutString_P("Invalid action, try again (: ");
	}
}

void najfrekventnijeSlovo(char r [20])
{
	uint8_t i=0, j, niz [20], count=1, max= 1, slovo;
	char ispis [30], c;

	c = r[i];

	while (r[i])
	{
		j=i+1;

		while (r[j])
		{
			if (r[j] == r[i])
				count++;
			j++;
		}
		if(count > max)
			c = r[i];

		count = 1;
		i++;
	}

		sprintf(ispis, "Najvise ponavljanja ima slovo : %c", c);
		usartPutString(ispis);
}

void makni_razmake(char r [20])
{
	char ispis [50], novistr [20];
	uint8_t c=0, i=0;

	while (r[c])
	{
		if(r[c] != ' ')
		{
			novistr[i] = r[c];
			i++;
		}
			c++;
	}

	novistr[i] = '\0';
	sprintf(ispis, "String bez razmaka : %s", novistr);
		usartPutString(ispis);

}

void ukloni_duplikate(char string[20])
{
	uint8_t i = 0, j, c=0, k=0,  duzina;
	char ispis [50], novistr [20];

	duzina = strlen(string);

	novistr[0] = string[0];

	for( ; i <duzina ; i++)
	{
		if(string[i])
			novistr[c++] = string[i];

		for (j=i+1 ; j < duzina; j++ )
		{
			if (string[i] == string[j])
			{
				string[j] = NULL;
			}
		}
	}

	novistr[c] = '\0';

	sprintf(ispis, "String bez duplikata : %s", novistr);
		usartPutString(ispis);
}
