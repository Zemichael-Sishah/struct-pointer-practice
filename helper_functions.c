
/* Implementation of helper functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "helper_functions.h"

int free_student_records( struct student*** student_records, int count ) 
{
    /* Free the memory allocated for the array of student records
     * Returns 0 on success, -1 on failure
     */

    // sanity check
    if ( student_records == NULL || *student_records == NULL )
    {
        return -1 ;
    }

    // free each student record
    // call the function to free each student struct
    for ( int i = 0 ; i < count ; i++ )
        free_student( (*student_records)[i] ) ;

    // free the array itself
    free( *student_records ) ;
    *student_records = NULL ;

    return 0 ;
}

InputArgs* parse_input_args( int argc, char* argv[] )
{
    /* Parse the input arguments
     * The function allocates memory for the InputArgs struct
     * (caller -- main -- is responsible for freeing the memory)
     * Returns NULL on failure
     * Expected usage: <program name> <name/id> <input file> <output file>
     * where `a` or `d` stand for ascending/descending
     */

    // Check if the number of arguments is correct
    if ( argc != 4)
    {
        printf( "Usage: %s <name/id> <input file> <output file>\n\n"
                "where `name` or `id` stand for sort based on name of ID of student\n", argv[0] ) ;
        
        exit(1) ;
    }

    // allocate memory for the InputArgs struct
    InputArgs* args = (InputArgs*) malloc( sizeof(InputArgs) ) ;

    // get the strings for each of the command line arguments
    char* base = argv[1] ;
    char* input_file_name = argv[2] ;
    char* output_file_name = argv[3] ;

    // are we sorting based on name or id?
    if( strcmp( base, "name" ) == 0 )
    {
        args->_base = name ;
    }
    else if ( strcmp( base, "id" ) == 0 )
    {
        args->_base = id ;
    }
    else
    {
        // always check for error conditions in your code!

        printf( "First argument must be either `name` or `id` \n" ) ;
        return NULL ;
    }

    // open the input and output files
    args->_input_file = fopen(input_file_name, "r");
    if (args->_input_file == NULL)
    {
        // failed to open the input file -- close it and return an error (NULL)
        // note we can free the args struct since the input file was never opened

        printf("Could not open input file %s \n", input_file_name );
        fclose(args->_input_file);
        free(args);

        return NULL;
    }

    args->_output_file = fopen(output_file_name, "w");
    if (args->_output_file == NULL)
    {
        // failed to open the input file -- close it and return an error (NULL)
        // note we can free the args struct since the input file was never opened

        printf("Could not open output file %s \n", output_file_name);
        fclose(args->_input_file);
        fclose(args->_output_file);
        free(args);

        return NULL;
    }

    return args ;
}

int read_records( FILE* inputFile, struct student** student_records[] )
{
    /* Read in the array from the input file
     * The function allocates memory for the array
     * The caller is responsible for freeing the memory
     * Returns the number of elements read, or -1 on failure
     */

    // sanity checks
    // make sure the input file and the array pointer exist (i.e., are not NULL)
    if ( inputFile == NULL || student_records == NULL )
    {
        return -1 ;
    }

    // read in the number of elements
    int count = 0 ;
    if ( fscanf( inputFile, "%d", &count ) != 1 )
    {
        return -1 ;
    }

    // allocate memory for the input array
    *student_records = (struct student**) malloc( sizeof(struct student*) * count ) ;
    if ( *student_records == NULL )
    {
        return -1 ;
    }

    // Read one line at at time -- check if we encountered an error
    for ( int i = 0 ; i < count ; i++ )
    {
        int id ;
        char name[MAX_NAME_LENGTH] ;

        // Read one line from the file
        if ( fscanf( inputFile, "%d %[^\n]", &id, name ) != 2 )
        {
            // error reading the input file
            if( free_student_records(student_records, i) )
                printf( "Error while free-ing student records!\n" ) ;

            return -1 ;
        }

        // Remove trailing newline character from the name if present
        size_t len = strlen(name);
        if (len > 0 && name[len - 1] == '\n') {
            name[len - 1] = '\0';
        }

        // create a student struct and add it to the array
        struct student* s = create_student( id, name ) ;
        if ( s == NULL )
        {
            // error allocating memory for the student struct
            //release previously allocated memory
            if( free_student_records(student_records, i) )
                printf( "Error while free-ing student records!\n" ) ;

            return -1 ;
        }

        // add the student struct to the array
        (*student_records)[i] = s ; 
    }

    // return how many elements we read
    return count ;
}

int print_records( FILE* output, struct student** student_records, int count )
{
    /* Print the array to the output file
     * Returns -1 on error, number of records printed on success
     */

    // sanity checks
    if ( output == NULL || student_records == NULL )
    {
        return -1 ;
    }

    // print each element in the array
    int i ;
    for ( i = 0 ; i < count ; i++ )
    {
        fprintf( output, "id = %d\t name = %s\n", student_records[i]->_id, student_records[i]->_name ) ;
    }

    return i ;
}