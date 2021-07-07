#include <math.h>
#include <ctype.h>
#include "header.h"

//struct for index of cities
typedef struct lista{
    char city[20];
    long position;
}cityindex;

//struct for index of zips
typedef struct listb{
    int zip;
    long position;
}zipindex;

//declare in-memory arrays
cityindex cities[1000];
zipindex zips[1000];

/*
Function to load the index files into their appropriate structs
*/
int loadStructs(){
    FILE * cityfile, * zipfile;
    int numentries = 0;
    int ziptemp;
    long postemp;
    char citytemp[20];

    //open files
    cityfile = fopen("output/cities.txt", "r");
    zipfile = fopen("output/zips.txt", "r");

    while(!feof(cityfile) && !feof(zipfile) ){
        //grab info for cities
        if( fscanf(cityfile, "%s %ld", citytemp, &postemp) > 0){
            strcpy(cities[numentries].city, citytemp);
            cities[numentries].position = postemp;
            //printf("read: %s at %ld\n",cities[numentries].city, cities[numentries].position);
        }
        
        //grab info for zips
        if( fscanf(zipfile, "%d %ld", &ziptemp, &postemp) > 0){
            zips[numentries].zip = ziptemp;
            zips[numentries].position = postemp;
            //printf("read %d at %ld\n", zips[numentries].zip, zips[numentries].position);
        }

        numentries++;
    }

    return numentries-1;
}

/*

*/
long searchbyzip(int zip, int start, int end){
    int size = end - start;
    int midpoint = start + (int)ceil(size/2);
    //printf("checking at %d index\n", midpoint);

    if(size == 1 && zips[midpoint].zip != zip){
        printf("zip not found in index\n");
        return -1;
    }

    if( zip < zips[midpoint].zip ){
        return searchbyzip(zip, start, midpoint);
    }
    else if( zip > zips[midpoint].zip ){
        return searchbyzip(zip, midpoint, end);
    }
    //if this is the one we're looking for
    return zips[midpoint].position;
    
}

long searchbycity(char * city, int start, int end){
    int size = end - start;
    int midpoint = start + (int)ceil(size/2);

    if( size == 1 && strcmp(cities[midpoint].city, city) != 0){
        printf("%s not found in index\n", city);
        return -1;
    }

    if( strcmp(city, cities[midpoint].city) > 0 ){
        return searchbycity(city, midpoint, end);
    }
    else if( strcmp(city, cities[midpoint].city) < 0 ){
        return searchbycity(city, start, midpoint);
    }

    return cities[midpoint].position;
}


int main(int arg, char* argv[]){
    int entries, searchmode, zipsearch, getzip;
    char getcity[20], citysearch[20];
    long seekpos;
    FILE *fp;
    searchmode = 0;

    printf("Welcome to SearchFiles!\n");

    entries = loadStructs();

    printf("Loaded %d index entries into memory\n", entries);

    //open datafile
    fp = fopen("output/cityzip.txt", "r");


    printf("Enter 1 to search by zip or 2 to search by city: ");

    while( scanf("%d", &searchmode) < 1 || searchmode < 1 || searchmode > 2){
        printf("Please enter 1 to search by zip, 2 to search by city: ");
    }
    

    //search by zip
    if(searchmode == 1){
        printf("Enter zip to search or 0 to quit: ");
        //check for exit condition
        while ( scanf("%d", &zipsearch) > 0){

            if(zipsearch==0){//exit condition
                printf("Exiting program\n");
                return 0;
            }

            //get position of zip
            seekpos = searchbyzip(zipsearch, 0, entries);

            if(seekpos != -1){
                printf("%d located at %ld\n", zipsearch, seekpos);
                fseek(fp, seekpos, SEEK_SET);
                if( fscanf(fp, "%s %d", getcity, &getzip) ) {
                    printf("City: %s Zip: %d\n", getcity, getzip);
                }
                
            }
            //reprompt
            printf("Enter zip to search or 0 to quit: ");
        }//zipsearch loop
        
    }
    else{
        printf("Enter city to search or 0 to quit: ");
        while( scanf("%s", citysearch) > 0){

            if(strcmp(citysearch, "0") != 0){ //if not exit condition
                seekpos = searchbycity(citysearch, 0, entries);

                if(seekpos != -1){ //if found entry
                    printf("%s located at %ld\n", citysearch, seekpos);
                    fseek(fp, seekpos, SEEK_SET);
                    if( fscanf(fp, "%s %d", getcity, &getzip) ) {
                        printf("City: %s Zip: %d\n", getcity, getzip);
                    }
                }


            }else{
                printf("Exiting\n");
                return 0;
            }
            //reprompt
            printf("Enter city to search or 0 to quit: ");
        }//citysearch loop
    }
    

    

    return 0;
}