#include "header.h"



typedef struct Node
{
    int zipcode;
    char cityname[20];
    long position;

} datanode;

datanode list[1000];

int comp_name(const void *a, const void *b){
    datanode *c1 = (datanode *) a;
    datanode *c2 = (datanode *) b;

    return strcmp(c1->cityname, c2->cityname);
}
int comp_zip(const void *a, const void *b){

    datanode *z1 = (datanode *) a;
    datanode *z2 = (datanode *) b;

    

    return z1->zipcode - z2->zipcode;
        
}

void sortbycity(datanode list[], int numEntries){

    qsort(list, numEntries, sizeof(*list), comp_name);

}

void sortbyzip(datanode list[], int numEntries){

    qsort(list, numEntries, sizeof(*list), comp_zip);

}

/*
* takes user input from command line to make file containing 
* city-zip pairs
*/

int main(int argc, char* argv[]){
    
    int numEntries;
    char city[20], mode[3], argstr[10];
    int zip, index;
    char filename[30];
    long cityftell; //, zipftell;

    

    FILE * fp, * cities,  * zips, * cityzip;

    numEntries = 0;

    //get file path from command line
    if(argc > 1){
        strcpy(filename, argv[1]);
    }
    
    
    //check to make sure filepath is good
    while( !(fp = fopen(filename, "r")) ){
        printf("File not found, please enter valid filepath: ");
        if( scanf("%s", filename) < 1){
            printf(" bad file path ");
        }
    }

    //check to make sure "mode" is good----------------------------------------------
    if(argc < 3 ){//not detected

        printf("No file mode detected, enter 'new' or 'append': ");
        if( scanf("%s", argstr) < 1 ){
            printf("No file mode detected, program may not execute correctly\n");
        }

    }else{//detected, prepare for processing
        strcpy(argstr, argv[2]);
    }
    
    //check proper syntax
    while( strcmp(argstr, "new") != 0 && strcmp(argstr, "append") != 0){

        printf("No VALID file mode detected, enter 'new' or 'append': ");
        if( scanf("%s", argstr) < 1 ){
            printf("No file mode detected, program may not execute correctly\n");
        }

    }
    
    //set mode
    if(strcmp(argstr, "new") == 0){
        strcpy(mode, "w+");
        printf("Running in 'new' mode\n");
    }else{
        strcpy(mode,"a");
        printf("Running in 'append' mode\n");
    }
    

    //create and open output files
    cityzip = fopen("output/cityzip.txt", mode);
    cities = fopen("output/cities.txt", "w+");
    zips = fopen("output/zips.txt", "w+");

     //loop putting pairs into array
    while( !feof(fp )){
        //read pair
        if( (fscanf(fp, "%s %d", city, &zip)) < 2 ){
            //printf("Data is not being read correctly, please make sure your input file is correctly formatted\nUsing this data will likely result in errors\n");
        }
        else{
            
        //get location where going to write using ftell
        cityftell = ftell(cityzip);
        //zipftell = ftell(cities);

        //write using fprintf
            //one file with city-zip, another with keys
        //cityzip
        fprintf(cityzip,"%s %d\n", city, zip);
        
        
        //create list entry
        //list[numEntries].cityname = city;
        strcpy(list[numEntries].cityname, city);
        list[numEntries].zipcode = zip;
        list[numEntries].position = cityftell;

        numEntries++;

        } 
        
    }
    //success!
    printf("%d entries successfully read from %s\n", numEntries, filename);

    //-----------------------------------IF append mode, need to load in the pre-existing info!!!!!!!!--------------------------------------
    if(strcmp(argstr, "append") == 0){
        //go to beginning of output datafile
        //rewind(cityzip); idk why this doesnt work
        fclose(cityzip);
        cityzip = fopen("output/cityzip.txt", "r");

        numEntries = 0;

        while( !feof(cityzip)){
            cityftell = ftell(cityzip);
            if( fscanf(cityzip, "%s %d", city, &zip) > 0){
                //fscanf(cityzip, "%s %d", city, &zip);
                strcpy(list[numEntries].cityname, city);
                list[numEntries].zipcode = zip;
                list[numEntries].position = cityftell;

                //printf("in full file: %s %d at %ld\n",list[numEntries].cityname, list[numEntries].zipcode, list[numEntries].position);

                numEntries++;
            }
            
        }
    }

    //insert *key* into array (sorted) with start location in output file (result of ftell)
            //sort on city
    sortbycity(list, numEntries);
            //fprintf to city index
    for(index = 0; index < numEntries; index++){

        fprintf(cities, "%s %ld\n", list[index].cityname, list[index].position);
    }
    printf("Wrote %d to city index at output/cities.txt\n", numEntries);
    

            //sort on zip
    sortbyzip(list, numEntries);
            //fprintf to zip index
    for(index = 0; index < numEntries; index++){
        fprintf(zips, "%d %ld\n", list[index].zipcode, list[index].position);
    }
    printf("Wrote %d to zip index at output/zips.txt\n", numEntries);

    //close files
    fclose(fp);
    fclose(cityzip);
    fclose(cities);
    fclose(zips);

    return 0;
}