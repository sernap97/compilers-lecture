#include <stdio.h>
#include <string.h>

void analizeFile(char *fileName);

int main(int argc, char **argv) {
	analizeFile(argv[1]);

	return 0;
}


void analizeFile(char *fileName) {
	FILE *fp;
	int openPar[100], 
		closePar[100], 
		openBrace[100], 
		closeBrace[100], 
		openBracket[100], 
		closeBracket[100];
	int c, 
		line = 1, 
		errors = 0,
		oPar = 0,
		cPar = 0,
		oBrace = 0,
		cBrace = 0,
		oBracket = 0,
		cBracket = 0;

	memset(openPar, 0, 100);
	memset(closePar, 0, 100);
	memset(openBrace, 0, 100);
	memset(closeBrace, 0, 100);
	memset(openBracket, 0, 100);
	memset(closeBracket, 0, 100);
	fp = fopen(fileName, "r");

	while((c = fgetc(fp)) != EOF) {
		if(c == '\n') {
			line++;
		}

		switch(c) {
			case '/':
				if((c = fgetc(fp)) == '/') {
					while((c = getc(fp)) != '\n') {
					}
					line++;
				}
				else {
					printf("There is a missing / error in this line: %d\n", line);
					if(c == '\n') {
						line ++;
					}
					errors++;
				}
				break;

			case '\"':
				c = ' ';
				while(c != '\"') {
					if(c == '\n' || c == EOF) {
						errors++;
						printf("There is a missing \" error in this line: %d\n", line);
						line++;
						break;
					}
					c = fgetc(fp);
				}
				break;

			case '\'':
				c = ' ';
				while(c != '\'') {
					if(c == '\n' || c == EOF) {
						errors++;
						printf("There is a missing \' error in this line: %d\n", line);
						line++;
						break;
					}

					c = fgetc(fp);
				}
				break;

			case '(':
				openPar[oPar] = line;
				oPar++;
				break;

			case ')':
				closePar[cPar] = line;
				cPar++;
				break;

			case '{':
				openBrace[oBrace] = line;
				oBrace++;
				break;

			case '}':
				closeBrace[cBrace] = line;
				cBrace++;
				break;

			case '[':
				openBracket[oBracket] = line;
				oBracket++;
				break;

			case ']':
				closeBracket[cBracket] = line;
				cBracket++;
				break;
		}
	}

	int subtraction = 0;
			
	if(oPar > cPar) {
		subtraction = oPar - cPar;
		for(; subtraction > 0; subtraction--) {
			printf("There is a missing ) error in this line: %d\n", openPar[oPar - subtraction]);
		}
		errors++;
	}
	else if(cPar > oPar) {
		subtraction = cPar - oPar;
		for(; subtraction > 0; subtraction--) {
			printf("There is a missing ( error in this line: %d\n", closePar[cPar - subtraction]);
		}
		errors++;
	}
	subtraction = 0;

	if(oBrace > cBrace) {
		subtraction = oBrace - cBrace;
		for(; subtraction > 0; subtraction--) {
			printf("There is a missing } error in this line: %d\n", openBrace[oBrace - subtraction]);
		}
		errors++;
	}
	else if(cBrace > oBrace) {
		subtraction = cBrace - oBrace;
		for(; subtraction > 0; subtraction--) {
			printf("There is a missing { error in this line: %d\n", closeBrace[cBrace - subtraction]);
		}
		errors++;
	}
	subtraction = 0;

	if(oBracket > cBracket) {
		subtraction = oBracket - cBracket;
		for(; subtraction > 0; subtraction--) {
			printf("There is a missing ] error in this line: %d\n", openBracket[oBracket - subtraction]);
		}
		errors++;
	}
	else if(cBracket > oBracket) {
		subtraction = cBracket - oBracket;
		for(; subtraction > 0; subtraction--) {
			printf("There is a missing [ error in this line: %d\n", closeBracket[cBracket - subtraction]);
		}
		errors++;
	}

	if(errors == 0) {
		printf("There are no errors \n");
	}
	fclose(fp);
}
