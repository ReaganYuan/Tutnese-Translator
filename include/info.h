#ifndef INFO_H
#define INFO_H
#include <stdlib.h>
#include <stdio.h>

#ifdef INFO
	#define info() {\
		fprintf(stderr,"\nINFO: shifted alphabet: ");\
		alpha_pointer = Alphabet + lsb_5bits;\
			while(alpha_counter != 0){\
				alpha_counter += -1;\
				if(*alpha_pointer == 0){\
					alpha_pointer = Alphabet;\
				}\
				fprintf(stderr,"%c",*alpha_pointer);\
				alpha_pointer += 1;\
			}\
\
		fprintf(stderr,"\nINFO: shift amount: %d\n",lsb_5bits);\
		if(**in_file == '-'){\
			fprintf(stderr,"INFO: input file: STDIN\n");\
		}\
		else{\
			fprintf(stderr,"INFO: input file: %s\n",*in_file);\
		}\
\
		if(**out_file == '-'){\
			fprintf(stderr,"INFO: output file: STDOUT\n");\
		}\
		else{\
			fprintf(stderr,"INFO: output file: %s\n",*out_file);\
		}\
		if(d_or_c == 1){\
			fprintf(stderr,"INFO: operation: decryption\n");\
		}\
		else{\
			fprintf(stderr,"INFO: operation: encryption\n");\
		}\
}
#else
	#define info()
#endif

#endif /* DEBUG_H */

