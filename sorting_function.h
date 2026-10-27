#ifndef __SORTING_FUNCTION_H_INCLUDED__
#define __SORTING_FUNCTION_H_INCLUDED__

/* CSCI 2410 
 * Homework 0.25
 * Sorting algorithm interface
 */

struct student ;

int sorting_function( struct student* student_records[], int count, enum sort_base base ) ;
int is_sorted( struct student* student_records[], int count, enum sort_base base ) ;

#endif // __SORTING_FUNCTION_H_INCLUDED__