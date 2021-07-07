# city/zip search
C program for indexing and searching big data file

City/Zip Search
By Matthew Davis 2020

Description:
    This program reads in text files of cities and zip codes and allows user to search master file (output/cityzip.txt) by city or zip and get the entry's exact
byte position in the master file. To do this the program creates two files, one that is sorted alphabetically for cities and one that is sorted numerically for zip.
Binary search of either of these files returns the byte position of the entry in the master file.
    While most computers can easily handle storing this amount of records in memory, this program illustrates a way to handle datasets so large they can only be stored
in files on a drive.

To run from scratch:
    make run

To append more city/zip records:
    ./createfile [path to txt file] append

to run with with existing dataset
    ./searchfiles
