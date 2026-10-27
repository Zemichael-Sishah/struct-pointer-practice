#ifndef __SORT_H_INCLUDED__
#define __SORT_H_INCLUDED__

// Header file for the structure to be sorted

#define MAX_NAME_LENGTH 256

enum sort_base { name, id } ;

struct student
{
    int _id ;
    char _name[MAX_NAME_LENGTH] ;
} ;

struct student* create_student( int id, const char* name ) ;
void free_student( struct student* s ) ;

#endif // __SORT_H_INCLUDED__