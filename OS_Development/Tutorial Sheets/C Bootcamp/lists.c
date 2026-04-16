#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stud_type {
    int id;
    char firstname[20];
    char lastname[20];
    struct stud_type *next;
} stud_type;


/* Is the database empty? */
bool is_empty(stud_type const* list) {
    return !list;
}


/* Insert an element
 * 
 * Gets a pointer to a pointer, which points to the 1. element of the list
 * Gets ID, first name and last name of the student to be inserted
 *
 * Returns true if successful
 * Returns false to indicate an error
 */
bool enqueue(stud_type** students_list, int id, char const firstname[20], char const lastname[20]) {
    /* Get dynamic memory for the new list entry */
    
    /* Fill the memory (beware of buffer overflows!) */
    
    /* Insert the new element into the list */
        /* Is the list empty? */

        /* Sort the student into the right position by ascending ID number */
}

/* Remove an element
 * 
 * Gets a pointer to a pointer, which points to the 1. element of the list
 * Gets the ID of the student to be deleted
 *
 * Returns true if successful
 * Returns false to indicate an error
 */
bool dequeue(stud_type** students_list, int id) {
    /* Check edge cases */
    
    /* Find the student */
    
    /* Remove the student and free memory */
    
    /* What must happen if the 1. element of the list is removed? */
    /* What if the ID can't be found in the list? */
    /* ... */
    
}

/* Read an element 
 *
 * Gets a pointer to the list type
 * Gets the ID of the student whose data is to be read
 *
 * Writes first and last name into firstname and lastname, respectively
 */
bool get_student(stud_type const* students_list, int id, char firstname[20], char lastname[20]) {
    /* Search the DB */
    stud_type const* curr = students_list;
    while (curr && curr->id < id) {
        curr = curr->next;
    }

    if (!curr || curr->id != id) {
        /* Return value: Error */
        return false;
    } else {
        strncpy(firstname, curr->firstname, 19);
        firstname[19] = '\0';
        strncpy(lastname, curr->lastname, 19);
        lastname[19] = '\0';
        /* Return value: OK */
        return true;
    }
}

static void test_empty(stud_type const* list) {
    printf(">>> Testing whether the student list is empty ...\n");

    if(is_empty(list)) {
        printf("    The student list is empty \n");
    } else {
        printf("    The student list is not empty \n");
    }
}

static void test_get(stud_type const* list, int id) {
    printf(">>> Testing, whether the ID %4i exists ...\n", id);

    char firstname[20];
    char lastname[20];
    if(get_student(list, id, firstname, lastname)) {
        printf("    ID %4i: %s %s\n", id, firstname, lastname);
    } else {
        printf("    ID %4i is not known\n", id);
    }
}

static void test_enqueue(stud_type** list, int id, char const* firstname, char const* lastname) {
    printf(">>> Inserting the new student into the list: %s %s [%4i] ...\n", firstname, lastname, id);
    if(enqueue(list, id, firstname, lastname)) {
        printf("    ID %4i inserted\n", id);
    } else {
        printf("    ID %4i couldn't be inserted\n", id);
    }
}

static void test_dequeue(stud_type** list, int id) {
    printf(">>> Removing ID %4i ...\n", id);

    if(dequeue(list, id)) {
        printf("    ID %4i removed\n", id);
    } else {
        printf("    ID %4i is not known\n", id);
    }
}

static void test_dump(stud_type const* list) {
    printf(">>> Printing all known students ...\n");
    for(stud_type const* curr = list; curr; curr = curr->next) {
        printf("    ID %4i: %s %s\n", curr->id, curr->firstname, curr->lastname);
    }
}

/* Test all the list functions  */
int main(void) {
    /* Initialize database */
    stud_type* students_list = NULL;

    test_empty(students_list);
    test_enqueue(&students_list, 1234, "Eddard", "Stark");
    test_get(students_list, 1234);
    test_enqueue(&students_list, 5678, "Jon", "Snow");
    test_get(students_list, 1234);
    test_enqueue(&students_list, 9999, "Tyrion", "Lannister");
    test_get(students_list, 1235);
    test_enqueue(&students_list, 1289, "Daenerys", "Targaryen");
    test_dequeue(&students_list, 1234);
    test_empty(students_list);
    test_get(students_list, 5678);
    test_dequeue(&students_list, 9998);
    test_enqueue(&students_list, 1289, "Viserys", "Targaryen");
    test_dequeue(&students_list, 5678);
    test_enqueue(&students_list, 1, "Tywin", "Lannister");
    test_dump(students_list);

    {
        /* Generate list sorted by first name */
        /* Print list */
        /* Delete list */
    }

    {
        /* Generate list sorted by last name */
        /* Print list */
        /* Delete list */
    }

    /* Delete students_list */

    return 0;
}
