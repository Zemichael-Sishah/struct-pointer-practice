/* CSCI 2410
 * Homework 0.5
 * Compound types and Pointers
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helper_functions.h"
#include "sorting_function.h"
#include "sort.h"

struct student* create_student( int id, const char* name ) 
{
    /* Allocate memory for a student struct and initialize it
     */

    struct student* s = (struct student*) malloc( sizeof(struct student) ) ;

    // check if malloc succeeded
    if ( s == NULL )
    {
        return NULL ;
    }

    // initialize the fields
    s->_id = id ;
    strncpy( s->_name, name, MAX_NAME_LENGTH ) ;
    s->_name[MAX_NAME_LENGTH - 1] = '\0' ; // ensure null termination

    return s ;
}

void free_student( struct student* s ) 
{
    // free the memory allocated for a student struct
    if ( s != NULL )
    {
        free( s ) ;
    }
}

int main( int argc, char* argv[] )
{
    // first, call the function to parse the input arguments 
    // from the command line 
    InputArgs* input_args = parse_input_args( argc, argv ) ;

    // did it fail? 
    // if so, print an error message and exit the program
    if ( input_args == NULL )
    {
        printf("Failed to parse input arguments\n");
        return -1 ;
    }

    // an array to store the input
    struct student** student_records = NULL ;
    int count = read_records( input_args->_input_file, &student_records ) ;

    // call the SORTING function -- YOUR CODE!
    int status = sorting_function( student_records, count, input_args->_base ) ;

    // did the sorting function fail?
    if( status )
    {
        printf(" Sorting function failed!!!\n ") ;

        fclose( input_args->_input_file ) ;
        fclose( input_args->_output_file ) ;
 
        free_student_records( &student_records, count ) ;
        free( input_args ) ; 

        exit(-1) ;
    }

    // verify
    int sorted = is_sorted( student_records, count, input_args->_base ) ;

    if( sorted == 1 )
        fprintf( input_args->_output_file, " The array is sorted by the ") ;
    else if ( sorted == 0 )
        fprintf( input_args->_output_file, " The array is NOT sorted by the ") ;
    else 
    {
        printf(" ERROR while checking if the array is sorted!!!\n") ;

        // release memory, close files
        // ALWAYS "clean up" after yourself!
        fclose(input_args->_input_file);
        fclose(input_args->_output_file);
        free_student_records(&student_records, count);
        free(input_args);

        exit(-1) ; // quit the program with an error code
    }

    fprintf( input_args->_output_file, "%s base!\n\n", 
        ( input_args->_base ? "ID" : "NAME" ) ) ;

    print_records( input_args->_output_file, student_records, count ) ;

    // release memory at the end, close files
    // ALWAYS "clean up" after yourself!
    fclose( input_args->_input_file ) ;
    fclose( input_args->_output_file ) ;
    free_student_records( &student_records, count ) ;
    free( input_args ) ;
    
    return 0 ;
}