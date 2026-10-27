#ifndef __HELPER_FUNCTIONS_H_INCLUDED__
#define __HELPER_FUNCTIONS_H_INCLUDED__

/* Just some helper functions -- the interfaces
 */

 #include "sort.h"

// this struct holds the input arguments
typedef struct _InputArgs
{
    enum sort_base _base ; // sort by "name" or "id"
    FILE* _input_file ;
    FILE* _output_file ;
} InputArgs;

InputArgs* parse_input_args( int argc, char* argv[] ) ;
int read_records( FILE* inputFile, struct student*** student_records ) ;
int print_records( FILE* output, struct student** student_records, int count ) ;
int free_student_records( struct student*** student_records, int count ) ;


#endif // __HELPER_FUNCTIONS_H_INCLUDED__