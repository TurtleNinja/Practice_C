#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// function prototype
int hash(char *);

int main(int argc, char *argv[])
{
    // get input
    if (argc != 2)
    {
        printf("Usage: ./hashtable textfile\n");
        return 1;
    }

    // open the input file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Can't access the file\n");
        return 2;
    }

    // local structs
    typedef struct node
    {
        char word[45 + 1];
        struct node *next;
    }
    node;

    // create the array of buckets
    node *buckets[26];

    // load the list
    char fruit[45 + 1] = {'a'};
    while(fscanf(input, "%s", fruit) != EOF)
    {
        node *element = malloc(sizeof(node));
        if (element == NULL)
        {
            return 3;
        }

        // obtain the hash code
        int bucket_number = hash(fruit);

        strcpy(element->word, fruit);
        buckets[bucket_number] = element;
    }

    // print out the list in reverse order
    for (int i = 25; i >= 0; --i)
    {
        printf("%s\n", buckets[i]->fruit);
    }

    return 0;
}

int hash(char *fruit)
{
    return fruit[0] - 'a';
}

