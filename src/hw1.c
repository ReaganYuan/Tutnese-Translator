#include "../include/hw1.h"
#include "../include/const.h"
#include "../include/info.h"

#define iv "Invalid Parameters\n"
// For your helper functions (you may add additional files also)
// DO NOT define a main function here!

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')


int check_h(int number_of_arguments, char** argv_h){
	int returnValue = 0;
	argv_h++;
	char *pointer = &**argv_h;
		if(*pointer++ == 45){
			if(*pointer++ == 104){
				if(*pointer == 0){
					returnValue = 1;
				}
			}
		}
	return returnValue;
}

char validargs(int argc, char** argv, FILE** in, FILE** out) {

	char** temp_argv = argv;
	char ret = 0;
	int check_h_result = 0;
	char* alphabet_pointer = NULL;

	if(argc == 1 ){
		return ret;
	}

	if(argc > 1){
		check_h_result = check_h(argc,argv);
	}
	else{
		ret = 0 ;
		printf(iv);
		return ret;
	}
	if(check_h_result == 1){
		ret ^= (-1 ^ ret) & (1 << 7);		// toggling the  bit
		return ret;
	}

	if ((argc > 6 && check_h_result == 0) || ( argc < 5 && check_h_result == 0 ) ){
		ret = 0;
		return ret;
	}

	temp_argv = argv;
	char *ptr = &*(*(++temp_argv));

	// Checks if argument one is either -s/-t/
	if(*ptr== 45){
		ptr = ptr + 1;
		if(*ptr== 115 || *ptr == 116){
			ptr = ptr + 1;
			if(*ptr == 0){
				ptr = ptr -1;
				if(*ptr == 115 ){
					ret ^= (-1 ^ ret) & (1 << 6);
				}
				else{
					if(*ptr == 116 && argc == 6){
						ret = 0;
						return ret;
					}
				}
			}
			else{
				ret = 0;
				return ret;
			}
		}
		else{
			ret = 0 ;;
			return ret;
			}
	}
	else{
		ret = 0;
		return ret;
		}
	// Checks if argument two is either -e or -d

	if(argc > 2){
	temp_argv = temp_argv +1;
	ptr = &**temp_argv; // uses ptr instead of ptr* because is for declaration
	if(*(ptr) == 45){
		ptr = ptr + 1;
		if(*ptr == 100 || *ptr == 101){
			ptr = ptr + 1;
			if(*ptr == 0){
				ptr = ptr -1;
				if(*ptr == 100){
					ret ^= (-1 ^ ret) & (1 << 5);
				}
			}
			else{
				ret = 0;
				return ret;
			}
		}
		else{
			ret = 0;
			return ret;
		}
	}
	else{
		ret = 0;
		return ret;
	}
}

	int counter_to_decrement = 0;
// checking if an example like bin/hw1 -s -e - - 79
	if(argc == 6){
		temp_argv = temp_argv + 3;
		while(**temp_argv != '\0'){
			if(**temp_argv < 47 || **temp_argv > 58){
				ret = 0 ;
				return ret;
			}
				*temp_argv = *temp_argv + 1;
				counter_to_decrement += 1;
		}
			while(counter_to_decrement != 0 ){
				*temp_argv = *temp_argv -1;
				counter_to_decrement = counter_to_decrement - 1;
			}
			temp_argv = temp_argv - 3;
	}

	temp_argv = temp_argv + 1;
	char **temp_argv_2 = temp_argv + 1;

	if(fopen(*temp_argv,"r") == 0 && **temp_argv != 45){
		ret = 0;
		return ret;
	}


	if(**temp_argv == 45 && **temp_argv_2 == 45){
		*temp_argv += 1;
		if(**temp_argv != 0){
			ret = 0 ;
			return ret;
		}
		*temp_argv += -1;
		*in = stdin;
		*out = stdout;	
	}

	if (**temp_argv == 45 && **temp_argv_2 != 45){

		*temp_argv += 1;
		if(**temp_argv != 0){
			ret = 0;
			return ret;
		}
		*temp_argv += -1;
		*in = stdin;
		*out = fopen(*(temp_argv_2),"w");
	}

	if(**temp_argv != 45 && **temp_argv_2 == 45){
		*in = fopen(*(temp_argv),"r");
		*out = stdout;
	}

	if(**temp_argv != 45 && **temp_argv_2 != 45){
		*in = fopen(*(temp_argv),"r");
		*out = fopen(*(temp_argv_2),"w");
   	}

    alphabet_pointer = NULL;
   	int alphabet_counter = 0;
   	int atoi_int = 0;

   //	if(((ret >> 6 ) & 1) == 1 || ((ret >> 6) & 1) == 0){					// checks the 6th bit
   		alphabet_pointer = Alphabet;
   		temp_argv = temp_argv + 2;
   		if(argc == 6 && **temp_argv > 47 && **temp_argv < 58){			// check if there is n
   			while(*alphabet_pointer != 0){
   				alphabet_counter += 1;
   				alphabet_pointer += 1;
   			}
   			while(**temp_argv != '\0'){
   				atoi_int = atoi_int * 10  + **temp_argv - 48;
   				*temp_argv = *temp_argv + 1;
   			}
   			ret = ret + (atoi_int % alphabet_counter);
   		}

   		if(argc == 5 ){
   			while(*alphabet_pointer != 0 ){
   				alphabet_counter += 1;
   				alphabet_pointer += 1;
   			}
   			temp_argv = temp_argv + 2;
   			ret = ret + (320 % alphabet_counter);
   		}
   		int some_int = (ret >> 6) & 1;
   		if(argc == 6 && some_int == 0){
   			ret = 0;
   			return ret;
   		}
	return ret;
}

	void s_cipher(FILE** file_in, FILE** file_out,int mode_byte, char** argv_s){

 		char* alpha_pointer = Alphabet;
 		int alpha_counter = 0;
 		char fgetc_char;
 		int msb = 4;
 		int lsb = 0;
 		int shift_position = 0;
 		int temp_counter = 0;
 		int is_inside_alphabet = 0;
 		int d_or_c = 0;

 		// finds the length of the alphabet
 		while(*alpha_pointer != 0){
 			alpha_counter += 1;
 			alpha_pointer += 1;
 		}
 		alpha_pointer = Alphabet;

 		// getting the 5 lsb
 		int lsb_5bits = ((mode_byte) >> lsb) & ~(~0 << (msb-lsb+1));

 		temp_counter = alpha_counter;

 		// Changing whole alphabet to capital letters
 		while(temp_counter != 0){
 			temp_counter += -1;
 				if(*alpha_pointer < 123 && *alpha_pointer > 96){
 					*alpha_pointer = *alpha_pointer - 32;
				}
 				alpha_pointer += 1;
 			}
 		alpha_pointer += -alpha_counter;

 		//printf("%d\n",*alpha_pointer);
 		while((fgetc_char = fgetc(*file_in)) != EOF ){
 			is_inside_alphabet = 0;
 			alpha_pointer = Alphabet;

       		if(fgetc_char > 96 && fgetc_char < 123 && fgetc_char != 10){
 				fgetc_char = fgetc_char - 32;
 			}

 			// Check if the fgetc_char is inside the alphabet
  			temp_counter = alpha_counter;
 			while( temp_counter != 0 && alpha_pointer != 0){
 				if(fgetc_char == *alpha_pointer){
 					is_inside_alphabet = 1;
 				}
 				alpha_pointer += 1;
 				temp_counter += -1;
 			}

 			alpha_pointer += -alpha_counter;
 			temp_counter = 0;
 			if(is_inside_alphabet == 1){
 				while(fgetc_char != *alpha_pointer){
 					alpha_pointer += 1;
 					temp_counter += 1;
 				}
 				alpha_pointer += -temp_counter;
 				d_or_c = mode_byte >> 5 & 1;

 					if(d_or_c == 0){
 						shift_position = (temp_counter + lsb_5bits) % alpha_counter;
       					alpha_pointer = alpha_pointer + shift_position;
       					fgetc_char = *alpha_pointer;
       				}
       				else{
						shift_position =  (alpha_counter -(alpha_counter - ( temp_counter - lsb_5bits))) % alpha_counter;

      				if(shift_position < 0){
      						shift_position= alpha_counter - (-1 * shift_position);
						}
       					alpha_pointer = alpha_pointer + shift_position;
       					fgetc_char = *alpha_pointer;
       				}
       		}
       		//printf("%c",fgetc_char);
       		fputc(fgetc_char,*file_out);
        }


    	char** in_file = argv_s + 2;
    	char** out_file = argv_s + 3;
    	in_file += 1;
    	out_file += 1;

 
      	info();

}

void tut_cipher(FILE** in_tut, FILE** out_tut, int mode_byte_t, char** argv_t){
	char** tut_pointer = Tutnese;
	//char storage;
	int tut_size = 0;
	int tut_size_holder = 0;
	int index = 0;
	bool is_uppercase_1 = false;
	bool is_uppercase_2 = false;
	bool is_equal = false;
	bool first_char_exist = false;
	bool second_char_exist = false;
	int tut_pointer_counter = 0;

	if(is_uppercase_1){
		if(is_uppercase_2){}
			if(is_equal){}
	}

	char* squa_upper = "Squa";
	char* squa_lower = "squa";
	char* squat_upper = "Squat";
	char* squat_lower = "squat";

	squat_lower += 0;
	squat_upper +=0;
	squa_upper += 0;
	squa_lower += 0;
	index += 0;

	// get size of the tut alphabet
	while(*tut_pointer != NULL){
		tut_size += 1;
		tut_pointer += 1;
	}

	tut_size_holder = tut_size;
	tut_size_holder += 0;
	tut_pointer = Tutnese;


	char first_char;
	char second_char;
	int counter = 0;
	my_label_2:
	while((second_char = fgetc(*in_tut)) != EOF){
		first_char_exist = false;
		second_char_exist = false;
		is_equal = false;
		if(first_char == 10){
			goto my_label;
		}

		if(counter == 0){
			my_label:
			is_equal = false;
			first_char_exist = false;
			second_char_exist = false;
			first_char = second_char;
			counter = 1;
		}
		else{

			if(first_char > 64 && first_char < 91){
				// this means it is capital
				is_uppercase_1 = true;
				first_char += 32;
			}else{
				is_uppercase_1 = false;
			}
			if(second_char > 64 && second_char < 91){
				is_uppercase_2 = true;
				second_char += 32;
			}else{
				is_uppercase_2 = false;
			}
			//printf("initial first char = %c ,",first_char);
			if(second_char == first_char ){
				is_equal = true;
				//printf("is_equal\n");
			}
			while(tut_size_holder != 0){
				if(first_char == **tut_pointer){
					first_char_exist = true;
				}
				tut_pointer++;
				tut_size_holder--;
			}
			tut_pointer = Tutnese;
			tut_size_holder = tut_size;

			while(tut_size_holder != 0){
				if(second_char == **tut_pointer){
					second_char_exist = true;
				}
				tut_pointer++;
				tut_size_holder--;
			}

			tut_pointer = Tutnese;
			tut_size_holder = tut_size;
			if(first_char_exist){
				//printf("first char exists\n");
			}else{
			//	printf("first char does not exist\n");
			}
			if(second_char_exist){
				//printf("second char exists\n");
			}
			else{
			//	printf("second char does not exist\n");
			}
			if(is_equal){
				//printf("at is_equal");
				if( first_char == 'a' || first_char == 'e' || first_char == 'i' || first_char == 'o' || first_char == 'u'){
					if(is_uppercase_1 == true && is_uppercase_2 == true){
						fprintf(*out_tut, "%s", squat_upper);
						fprintf(*out_tut,"%c",first_char - 32);
						counter = 0;
						goto my_label_2;
					}
					if(is_uppercase_1 == true && is_uppercase_2 == false){
						fprintf(*out_tut,"%s",squat_upper);
						fprintf(*out_tut, "%c",first_char );
						counter = 0;
						goto my_label_2;
					}
					if(is_uppercase_1 == false && is_uppercase_2 == true){
						fprintf(*out_tut, "%s",squat_lower );
						fprintf(*out_tut, "%c",first_char - 32 );
						counter = 0;
						goto my_label_2;
					}
					if(is_uppercase_1 == false && is_uppercase_2 == false){
						fprintf(*out_tut, "%s",squat_lower );
						fprintf(*out_tut, "%c",first_char );
						counter = 0;
						goto my_label_2;
					}
				}
				else{
					if(is_uppercase_1 == true && is_uppercase_2 == true && first_char_exist == true){
						//SquaDud

						int capitalcounter = 0;
						int tut_pointer_counter = 0;
						tut_pointer = Tutnese;
						fprintf(*out_tut, "%s",squa_upper);
						while(first_char != **tut_pointer && tut_size_holder != 0){
							tut_pointer += 1;
							capitalcounter += 1;
							tut_size_holder -= 1;
						}
						char* first_letter = *tut_pointer;
						fprintf(*out_tut,"%c",*first_letter - 32);
						*tut_pointer += 1;
						while(**tut_pointer != 0){
							fprintf(*out_tut,"%c",**tut_pointer);
							*tut_pointer += 1;
							tut_pointer_counter += 1;
						}
						*tut_pointer -= tut_pointer_counter;
						*tut_pointer -= 1;
						tut_pointer -= capitalcounter;
						counter = 0;
						goto my_label_2;
					}
					if(is_uppercase_1 && !is_uppercase_2 && first_char_exist == true){

						fprintf(*out_tut, "%s",squa_upper);
						int capitalcounter = 0;
						tut_pointer = Tutnese;
						while(first_char != **tut_pointer){
							tut_pointer += 1;
							capitalcounter += 1;
						}
						fprintf(*out_tut, "%s",*tut_pointer );
						tut_pointer -= capitalcounter;
						counter = 0;
						goto my_label_2;
					}
					if(!is_uppercase_1 && is_uppercase_2 && first_char_exist == true){
						//squaDud
						fprintf(*out_tut, "%s",squa_lower);
						int capitalcounter = 0;
						tut_pointer = Tutnese;
						while(first_char != **tut_pointer){
							tut_pointer += 1;
							capitalcounter += 1;
						}
						char* first_letter = *tut_pointer;
						fprintf(*out_tut,"%c",*first_letter - 32);
						*tut_pointer += 1;
						while(**tut_pointer != 0){
							fprintf(*out_tut,"%c",**tut_pointer);
							*tut_pointer += 1;
							tut_pointer_counter += 1;
						}
						*tut_pointer -= tut_pointer_counter;
						*tut_pointer -= 1;
						tut_pointer -= capitalcounter;
						counter = 0;
						goto my_label_2;
					}
					if(!is_uppercase_1 && !is_uppercase_2 && first_char_exist == true){
						//squadud
						int capitalcounter = 0;
						fprintf(*out_tut, "%s", squa_lower);
						while(first_char != **tut_pointer){
							tut_pointer += 1;
							capitalcounter += 1;
						}
						fprintf(*out_tut, "%s",*tut_pointer );
						tut_pointer -= capitalcounter;
						counter = 0;
						goto my_label_2;

					}
				}
			}

			int tut_counter = 0;

		if(first_char != 'a' && first_char != 'e' && first_char != 'i' && first_char != 'o'
			&&first_char != 'u' && first_char != ' '
			&& first_char_exist == true){
			while(first_char != **tut_pointer){
				tut_pointer += 1;
				tut_counter += 1;
			}
			if(is_uppercase_1){
				// Code for printing out the first letter upper
				tut_pointer_counter = 0;
				char first_letter = **tut_pointer;
				fprintf(*out_tut,"%c",first_letter - 32);
				*tut_pointer += 1;
				while(**tut_pointer != 0){
					fprintf(*out_tut,"%c",**tut_pointer);
					*tut_pointer += 1;
					tut_pointer_counter += 1;
				}
				*tut_pointer -= tut_pointer_counter;
				*tut_pointer -= 1;
			}
			else{
				fprintf(*out_tut,"%s",*tut_pointer);
			}
		}
		else{
			if(is_uppercase_1){
			fprintf(*out_tut,"%c",first_char -32);
			}
			else{
				fprintf(*out_tut,"%c",first_char);
			}

		}



		if(is_uppercase_1){
			first_char = first_char - 32;
		}
		if(is_uppercase_2){
			second_char = second_char - 32;
		}
			tut_pointer = Tutnese;
			first_char = second_char;

		}
	}

}

