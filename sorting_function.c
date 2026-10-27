/* CSCI 2410 
 * Homework 0.5
 * Sorting algorithm IMPLEMENTATION
 * ONLY MODIFY THE FOLLOWING FUNCTIONS:
 *  string_comparator()
 *  integer_comparator()
 *  sorting_function()
 *  is_sorted()
 * DO NOT MODIFY ANY OTHER PART OF THIS FILE or OTHER FILES
 */

#include <stdlib.h>

#include "sort.h"
#include "sorting_function.h"

int string_comparator( const char str1[], const char str2[] ) 
{
    /* Write a comparator function for strings
     * If str1 < str2, return negative value
     * If str1 > str2, return positive value
     * If str1 == str2, return 0
     * 
     * DO NOT USE strcmp or any other library function
     * Recall how strings are represented in C
     */

    // <YOUR CODE HERE>    
    
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0'){
        if(str1[i] == str2[i]){}
        else if(str1[i] < str2[i]){
            return -1;
        }
        else if(str1[i] > str2[i]){
            return 1;
        }
        i++;
    }

    if(str1[i] == '\0' && str2[i] != '\0'){
        return -1;
    }
    else if(str1[i] != '\0' && str2[i] == '\0'){
        return 1;
    }

    return 0 ;
}


int integer_comparator(int a, int b) 
{
    /* Write a comparator function for integers
     * using the same convention as above (especially for return values)
     */

    // <YOUR CODE HERE>  
    if(a < b){
        return -1;
    }  
    else if ( a == b){
        return 0;
    }
    else if(a > b){
        return 1;
    }

    return 0 ;
}

int sorting_function( struct student* student_records[], int count, enum sort_base base ) 
{
    // Implement the sorting algorithm of your choice here
    // You can use any algorithm you like (e.g., bubble sort, selection sort, insertion sort, etc.)
    // The 'sort_base' parameter indicates whether to sort by the NAME or the ID of the student
    // 
    // The function returns 0 on success (by default), You should return non-zero value on failure

    // NOTE: you should use the appropriate COMPARATOR function based on the 'base' parameter
    //
    // Recall that the input is an ARRAY of POINTERS to student structs

    // <YOUR CODE HERE>
    if( student_records == NULL || count < 0 ) 
    {
        return -1 ; // Error condition
    }

    for (int i = 0; i < count; i++){
        for(int j = 0; j < count; j++){
            if(base == 0){
                if( string_comparator( student_records[i]->_name, student_records[j]->_name ) == -1){
                    struct student *temp = student_records[i];
                    student_records[i] = student_records[j];
                    student_records[j] = temp;
                }
            }
            else if (base == 1){
                if( integer_comparator( student_records[i]->_id, student_records[j]->_id ) == -1){
                    struct student *temp = student_records[i];
                    student_records[i] = student_records[j];
                    student_records[j] = temp;
                }
            }
        }
    }

    return 0 ; // Return 0 to indicate success
}


int is_sorted( struct student* student_records[], int count, enum sort_base base ) 
{
    /* Check if the array is sorted based on the given base (name or id)
     * Returns 1 if sorted, 0 if not sorted, -1 on error
     *
     * NOTE: 
     * 1. Remember to use the appropriate COMPARATOR function based on the 'base' parameter
     * 2. 0 and 1 sized arrays are automatically "sorted"
     */

    // sanity check
    // if the student_records array is NULL or count is negative, return -1
    if( student_records == NULL || count < 0 ) 
    {
        return -1 ; // Error condition
    }

    // check if the array is sorted
    // <YOUR CODE HERE>
    for(int i = 0; i < count - 1; i++){
        if(base == 0){
            if( string_comparator( student_records[i]->_name, student_records[i + 1]->_name ) != -1 ){
                return 0;
            }

        }
        else if (base == 1){
            if( integer_comparator( student_records[i]->_id, student_records[i + 1]->_id ) != -1){
                return 0;
            }
        }
    }
    

    return 1 ; // Return 1 to indicate the array is sorted
}