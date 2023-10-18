#include "Jerry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int arg_num, char* arg_num_list[]) {
    int numberOfPlanets = atoi(arg_num_list[1]);
    int numberOfJerries = atoi(arg_num_list[2]);

    FILE *newfile = fopen(arg_num_list[3], "r");
    if (newfile == NULL) { //check if the file is empty
        printf("The file is empty");
        fclose(newfile); //close the file and exit from the script
        exit(1);
    }

    Planet **planet_list = (Planet **) malloc(sizeof(Planet *) * numberOfPlanets);
    if (planet_list == NULL) { //check if the planet list is empty
        printf("The planet list is empty");
        fclose(newfile); //close the file and exit from the script
        exit(1);
    }

    Jerry **jerry_list = (Jerry **) malloc(sizeof(Jerry *) * numberOfJerries);
    if (jerry_list == NULL) { //check if the jerry list is empty
        printf("The Jerry list is empty");
        fclose(newfile); //close the file and exit from the script
        exit(1);
    }

    char wordcheck[300];
    int i = 1; //number of line if file
    int jerry_find=0;
    int counterjerries=-1;
    while (fgets(wordcheck, 300, newfile) != NULL) {
        if (i==1){
            i++;
            continue;
        }
        if (strcmp(wordcheck, "Jerries\n")==0){
            jerry_find++;
            i++;
            continue;
        }
        if (jerry_find == 0){
            char* splited = strtok(wordcheck,",");
            double x=atof(strtok(NULL,","));
            double y=atof(strtok(NULL,","));
            double z=atof(strtok(NULL,","));
            Planet *newplanet=initPlanet(x,y,z,splited);
            if (newplanet == NULL){
                free_all_Planets(planet_list, numberOfPlanets);
            }
            else{
                planet_list[i-2]=newplanet;
                i++;
            }

        }
        else {
            char* splited = strtok(wordcheck, ",");
            if (splited[0] == '\t'){
                char *pcname = strtok(wordcheck,":");
                double pcvalue = atof(strtok(NULL,":"));
                char* newpcname =strtok(pcname, "\t");
                PC *mypc = initPC(newpcname, pcvalue);
                addPC(jerry_list[counterjerries], mypc);
            }
            else{
                counterjerries++;
                char *dimension = strtok(NULL,",");
                char *planet = strtok(NULL,",");
                int bliss_level = atoi(strtok(NULL,","));
                Planet *newplanet=NULL;
                for (int k=0;k<numberOfPlanets;k++){
                    if (strcmp(planet_list[k]->name, planet)==0){
                        newplanet=planet_list[k];
                        break;
                    }
                }
                Jerry *newjerry= initJerry(splited, bliss_level, newplanet, dimension);
                if (newjerry == NULL){
                    free_all_Planets(planet_list, numberOfPlanets);
                    free_all_Jerries(jerry_list, numberOfJerries);
                }
                else{
                    jerry_list[counterjerries]=newjerry;
                }
            }
        }
    }
fclose(newfile);


char input[300];
double val_input;
char ch = '0';
while (ch != '7') { //printing all the menu
    printf("AW JEEZ RICK, what do you want to do now ? \n");
    printf("1 : Print all Jerries \n");
    printf("2 : Print all Planets \n");
    printf("3 : Add physical characteristic to Jerry \n");
    printf("4 : Remove physical characteristic from Jerry \n");
    printf("5 : Print Jerries by a planet \n");
    printf("6 : Print Jerries by a physical characteristic \n");
    printf("7 : Go home \n");
    scanf("%s", &ch);
    switch(ch) {
    case '1':
        print_all_Jerries(numberOfJerries, jerry_list); //calling to function
        break;
    case '2':
        print_all_Planets(numberOfPlanets, planet_list); //calling to function
        break;
    case '3':
        printf("What is your Jerry's ID ? \n");
        scanf("%s", input);
        int counter = 0;
        int jerry_index = 0;
        for (int j = 0; j < numberOfJerries; j++) { //check if the Jerry is found
            if (strcmp(jerry_list[j]->id, input) == 0) { //if there is id that equal to the input
                jerry_index = j;
                counter++;
            }
        }
        if (counter == 0) { //if counter=0 there is no id that equal to the input
            printf("OH NO! I CAN'T FIND HIM RICK!\n");
            break;
        }
        else {
            printf("What physical characteristic can you add to Jerry - %s ? \n",input); //check if pcname is found
            scanf("%s", input);
            if (isPCexist((Jerry *) jerry_list[jerry_index], input) == true) { //check if pc is found
                int length = strlen(input); //find the length of the string
                for (int l = 0; l < length; l++) {
                    input[l] = toupper(input[l]); //upper every letter in the string
                }
                printf("RICK I ALREADY KNOW HIS %s ! \n",input);
                break;
            }
            else {
                printf("What is the value of his %s ? \n", input); //check if pcvalue is found
                scanf("%lf", &val_input);
                PC *newpc= initPC(input,val_input);
                addPC(jerry_list[jerry_index], newpc); //if the pc is not found add it
                printJerry(jerry_list[jerry_index]); //print the jerry with the new pc
                break;
            }

            }


    case '4':
        printf("What is your Jerry's ID ? \n");
        scanf("%s", input);
        int counter1 = 0;
        int jerry_index1 = 0;
        for (int j = 0; j < numberOfJerries; j++) { //check if the Jerry is found
            if (strcmp(jerry_list[j]->id, input) == 0) { //if there is jerry with equal id to the input
                jerry_index1 = j;
                counter1++;
            }
        }
        if (counter1 == 0) { //that means the pc not found in the pc list to remove
            printf("OH NO! I CAN'T FIND HIM RICK!\n");
            break;}
        else {
            printf("What physical characteristic do you want to remove from Jerry - %s ? \n",input);
            scanf("%s", input);
            if (isPCexist((Jerry *) jerry_list[jerry_index1], input) == false) {
                int length = strlen(input); //find the length of the string
                for (int l = 0; l < length; l++) {
                    input[l] = toupper(input[l]); //upper every letter in the string
                }
                printf("RICK I DON'T KNOW HIS %s ! \n", input);
                break;
            }
            else {
                deletePC(jerry_list[jerry_index1], input); //delete the pc with the function
                printJerry(jerry_list[jerry_index1]); //return the jerry without the removed pc
                break;
            }

            }


    case '5':
        printf("What planet is your Jerry from ? \n");
        scanf("%s", input);
        int counter2 = 0;
        for (int j = 0; j < numberOfPlanets; j++) { //check if the planet is found
            if (strcmp(planet_list[j]->name, input) == 0) {
                counter2++;
            }
        }
        if (counter2 == 0) { //the planet does not found in the planet list
            int length = strlen(input); //find the length of the string
            for (int l = 0; l < length; l++) {
                    input[l] = toupper(input[l]); //upper every letter in the string
                }
            printf("RICK I NEVER HEARD ABOUT %s !\n",input);
            break;
        } else {
            int jerry_counter = 0;
            for (int x = 0; x < numberOfJerries; x++) { //loop to check if there is planet
                if (strcmp(jerry_list[x]->origin->planet->name, input) == 0) {
                    printJerry(jerry_list[x]); //print the jerry that from this origin
                    jerry_counter++;
                }
            }
            if (jerry_counter == 0) { //if counter=0 there is not jerries in this planet
                int length = strlen(input); //find the length of the string
                for (int l = 0; l < length; l++) {
                    input[l] = toupper(input[l]); //upper every letter in the string
                }
                printf("OH NO! I DON'T KNOW ANY JERRIES FROM %s ! \n", input);
                break;
            }
            break;
        }

    case '6':
        printf("What do you know about your jerry ? \n");
        scanf("%s", input);
        int jerry_counter = 0;
        for (int a = 0; a < numberOfJerries; a++) {
            for (int b=0; b<jerry_list[a]->val_num;b++) { //loop that run on the pc arr on the jerry
                if (strcmp(jerry_list[a]->physchar_arr[b]->name, input) == 0) { //check if the jerry have the pc
                    printJerry(jerry_list[a]); //print the jerry that has this pc
                    jerry_counter++;
                }}}
        if (jerry_counter == 0) {
            int length = strlen(input); //find the length of the string
            for (int l = 0; l < length; l++) {
                input[l] = toupper(input[l]); //upper every letter in the string
            }
            printf("OH NO! I DON'T KNOW ANY JERRY'S %s ! \n", input);
            break;
        }
        break;


    case '7':
        free_all_Jerries(jerry_list, numberOfJerries); //free all the jerries that found
        free_all_Planets(planet_list, numberOfPlanets);
        printf("AW JEEZ RICK, ALL THE JERRIES GOT FREE ! \n");
        break;

    default:
        printf("RICK WE DON'T HAVE TIME FOR YOUR GAMES ! \n"); //if the input now between 1-7
        break;

    }


}



}

