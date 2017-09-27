#include "../include/defs.h"

int showMenu(void)
{
    int option = 0;
    int ret_val_sscanf = 0;
    char* char_buffer = NULL;

        char_buffer = (char*)malloc(CHAR_BUFFER_SIZE * sizeof(char));

        fprintf(stdout, "\nChoose an option (number):\n");
        fprintf(stdout, "1 - \n");
        fprintf(stdout, "2 - \n");
        fprintf(stdout, "3 - \n");
        fprintf(stdout, "4 - \n");
        fprintf(stdout, "5 - \n");
        fprintf(stdout, "6 - \n");

        fgets(char_buffer, sizeof(char_buffer), stdin);
        ret_val_sscanf = sscanf(char_buffer, "%d\n", &option);
        if(ret_val_sscanf != 1){
            fprintf(stdout, "Error reading option, try again.\n");
        }

        free(char_buffer);

    return option;
}

int main(int argc, char const *argv[]) {

    int choice = 0;

    choice = showMenu();

    switch(choice){
        case 1:{
            break;}
        case 2:
            break;
        case 3:{
            break;}
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            break;
    }

    return 0;
}
