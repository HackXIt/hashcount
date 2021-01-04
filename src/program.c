/* About the program
 * Purpose:
 * Teaching myself the algorithmic principle of hash-tables
 * Also it helps me install the project's compiler-configs, since it's a working code-example.
 * Example Output:
 * Hash-Table of names
 * Hints:
 * https://www.youtube.com/watch?v=2Ti5yvumFTU
 */

/* KNOWLEDGE
Ideally, hash-tables help finding data in constant time, versus O(n) time for linked-lists
The constant time refers to the hash-function, 
because it is responsible for saving data, looking up data and removing data.

So this functions needs to be A) very fast and B) spread values randomly at best.
It needs to be fast, because it is defining the time-efficiency of the code.
And it needs to spread randomly at best, because if two data-inputs give the same hash-output,
then this means that A) the first data will be replaced or B) the second data will be ignored.
To work around this possible data-loss, linked-lists are used to store data-inputs with the same hash-output.

Since the linked-lists slow down the search of data, it is mandatory to keep the lists small, thus spreading the hash-value randomly at best.
*/

//-- THE CODE HERE IS FROM THE VIDEO --//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256  // bytes
#define TABLE_SIZE 10 // size of the hash-table

typedef struct
{
    char name[MAX_NAME];
    int age;
    // ... more later...
} person_t;

person_t *hash_table[TABLE_SIZE];

unsigned int hash(char *name)
{
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++)
    {
        hash_value += name[i];
        hash_value = hash_value * name[i] % TABLE_SIZE;
    }
    return hash_value; // stupid hash function
}

void init_hash_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
    // table is empty
}

void print_table()
{
    printf("---\tStart of Table\t---\n");
    for (int i = 0; i < TABLE_SIZE - 1; i++)
    {
        if (hash_table[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }
        else
        {
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }
    printf("---\tEnd of Table\t---\n");
}

bool hash_table_insert(person_t *p)
{
    if (p == NULL)
    {
        return false;
    }
    int index = hash(p->name);
    if (hash_table[index] != NULL)
    {
        return false;
    }
    hash_table[index] = p;
    return true;
}

person_t *hash_table_lookup(char *name)
{
    int index = hash(name);
    if (hash_table[index] != NULL && strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0)
    {
        return hash_table[index];
    }
    else
    {
        return NULL;
    }
}

person_t *hash_table_delete(char *name)
{
    int index = hash(name);
    if (hash_table[index] != NULL && strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0)
    {
        person_t *tmp = hash_table[index];
        hash_table[index] = NULL;
        return tmp;
    }
    else
    {
        return NULL;
    }
}

int main(int argc, char const *argv[])
{
    init_hash_table();
    print_table();

    person_t jacob = {.name = "Jacob", .age = 256};
    person_t kate = {.name = "Kate", .age = 27};
    person_t mpho = {.name = "Mpho", .age = 14};
    person_t sarah = {.name = "Sarah", .age = 54};
    person_t edna = {.name = "Edna", .age = 15};
    person_t maren = {.name = "Maren", .age = 25};
    person_t eliza = {.name = "Eliza", .age = 34};
    person_t robert = {.name = "Robert", .age = 1};
    person_t jane = {.name = "Jane", .age = 75};

    hash_table_insert(&jacob);
    hash_table_insert(&kate);
    hash_table_insert(&mpho);
    hash_table_insert(&sarah);
    hash_table_insert(&edna);
    hash_table_insert(&maren);
    hash_table_insert(&eliza);
    hash_table_insert(&robert);
    hash_table_insert(&jane);
    print_table();

    person_t *tmp = hash_table_lookup("Mpho");

    if (tmp == NULL)
    {
        printf("Not found!\n");
    }
    else
    {
        printf("Found %s.\n", tmp->name);
    }
    tmp = hash_table_lookup("George");
    if (tmp == NULL)
    {
        printf("Not found!\n");
    }
    else
    {
        printf("Found %s.\n", tmp->name);
    }

    hash_table_delete("Kate");
    print_table();

    /*
    printf("Jacob\t=> %u\n", hash("Jacob"));
    printf("Natalie\t=> %u\n", hash("Natalie"));
    printf("Sara\t=> %u\n", hash("Sara"));
    printf("Mpho\t=> %u\n", hash("Mpho"));
    printf("Tebogo\t=> %u\n", hash("Tebogo"));
    printf("Ron\t=> %u\n", hash("Ron"));
    printf("Jane\t=> %u\n", hash("Jane"));
    printf("Maren\t=> %u\n", hash("Maren"));
    printf("Bill\t=> %u\n", hash("Bill"));
    */
    return 0;
}