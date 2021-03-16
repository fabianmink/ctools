/*
  Copyright (c) 2020 Fabian Mink
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//usage: "hexconv <infile> <outfile>"

//Purpose: convert file into c hex array
//similar to "xxd -i <infile> <outfile>"
int main(int argc, char* argv[]) {
	FILE *fp,*fpout;
	int ch;

	char* filename = argv[1];
	char* fileout = argv[2];

	int len = strlen(filename);
	char filename_conv[len+1];

	for(int i=0; i<len; i++){
		char curChar = filename[i];
		if(isalpha(curChar)||isdigit(curChar)){
			filename_conv[i] = curChar;
		}
		else{
			filename_conv[i] = '_';
		}
	}
	filename_conv[len] = 0x00; //terminating 0

	//printf("Reading from : %s\n", filename);
	//printf("Converted to : %s\n", filename_conv);

	fp = fopen(filename, "rb");
	fpout = fopen(fileout, "w");

	fprintf(fpout, "unsigned char %s[] = {\n", filename_conv);

	int countchar = 0;

	if (fp == NULL || fpout == NULL)
	{
		printf("File not found\n");
	}
	else
	{
		while ((ch = fgetc(fp)) != EOF){
			//ch = fgetc(fp);
			//if(ch == EOF) {
			//	printf("EOF!! cnt: %i,  char: %i\n",countchar,ch);
			//	break;
			//}
			//printf("cnt: %i,  char: %i\n",countchar,ch);
			if(countchar) {
				fprintf(fpout, ","); //not for first char
				if(!(countchar%10)) {
					fprintf(fpout, "\n"); //not for first char
				}
			}
			countchar++;
			fprintf(fpout, "0x%02x", (unsigned char)ch);
		}
	}

	fprintf(fpout, "\n};\n");
	fprintf(fpout, "unsigned int %s_len = %d", filename_conv, countchar);
	fprintf(fpout, ";\n");

	fclose(fp);
	fclose(fpout);

	return 0;
}

