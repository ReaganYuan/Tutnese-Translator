#include "../include/hw1.h"

int main(int argc, char **argv) {
    FILE* in;
    FILE* out;

    /* Note: create a variable to assign the result of validargs! */
    int validargs_return = validargs(argc, argv, &in, &out);

    if((validargs_return >> 7) & 1){
      USAGE(validargs_return);
      return EXIT_SUCCESS;
    }

    /* invalid argument case*/
    if(validargs_return == 0){
      USAGE(validargs_return);
  		return EXIT_FAILURE;
  	}
  	else{
      if((validargs_return >> 6) & 1){
        s_cipher(&in , &out,validargs_return, argv);
        return EXIT_SUCCESS;
      }
      else{
        tut_cipher(&in, &out,validargs_return, argv);
        return EXIT_SUCCESS;
      }
  	}

    return EXIT_SUCCESS;
}
