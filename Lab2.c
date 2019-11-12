/*
READ ME
cc Lab2.c
./a.out
then enter the commands as many times as desired
or "Quit" to quit
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int getword(char *word, int lim);
int getch(void);
void ungetch(int c);

struct node2d;
struct node2d * new2Dnode(char *name);
struct node1d;
struct node1d * new1Dnode(char *name);
struct node2d * insert2Dnode(struct node2d *head, char *name);
struct node2d * append2Dnode(struct node2d *head, char *name);
struct node2d * find2Dnode(struct node2d *head, char *afterName);
struct node2d * appendAfter2Dnode(char *name, char *afterName);
struct node2d * insert1Dnode(char *name, char *name2d);
void print2Dnode(struct node2d *target);
void print1Dnode(struct node1d *target);
void printAll(struct node2d *head);
void print1Dlist(char *name2d);

//the unseen start pointer
struct node2d *head = NULL;

int main() {
    printf("Enter your command here or enter or enter QUIT to quit:\n");
    char command[20];
    getword(command, 20);
    //printf("%s is your command\n", command);
    //user can do multiple things untill they want to end the project
    while (strcasecmp(command, "QUIT") != 0) {
        if (strcasecmp(command, "insert2d") == 0) {
            char name[20];
            getword(name, 20);
            //printf("%s is your name\n", name);
            head = insert2Dnode(head, name);
        }

        else if (strcasecmp(command, "append2d") == 0) {
            char name[20];
            getword(name, 20);
            //printf("%s is your name\n", name);
            head = append2Dnode(head, name);
        }

        else if (strcasecmp(command, "appendAfter2d") == 0) {
            char name[20];
            getword(name, 20);
            char afterName[20];
            getword(afterName, 20);
            //printf("%s is your name\n", name);
            //printf("%s is your afterName\n", afterName);
            head = appendAfter2Dnode(name, afterName);
        }

        else if (strcasecmp(command, "insert1d") == 0) {
            char name[20];
            getword(name, 20);
            char name2d[20];
            getword(name2d, 20);
            //printf("%s is your name\n", name);
            //printf("%s is your name2d\n", name2d);
            head = insert1Dnode(name, name2d);
        }

        else if (strcasecmp(command, "printAll") == 0) {
            printAll(head);
        }

        else if (strcasecmp(command, "print1dList") == 0) {
            char name2d[20];
            getword(name2d, 20);
            //printf("%s is your name2d\n", name2d);
            print1Dlist(name2d);
        }
        else {
            printf("No such command, sorry\n");
        }
        
        printf("Done with the previous command!\n");
        printf("Enter your command here or enter or enter QUIT to quit:\n");
        getword(command, 20);
        //printf("%s is your command\n", command);
    }
    printf("Thank you and goodbye!\n");
    return 1;
}

//1D node structure
struct node1d {
    struct node1d *next;
    char *name;
};
//2D node structure
struct node2d {
    struct node1d *first;
    char *name;
    struct node2d *down;
};
//create a 2D node
struct node2d * new2Dnode(char *name) {
    struct node2d *temp;
    temp = (struct node2d *) malloc(sizeof(struct node2d));
    temp->name = (char *) malloc(strlen(name)*sizeof(char));
    strcpy(temp->name, name);
    temp->down = NULL;
    temp->first = NULL;
    return temp;
}

//create a 1D node
struct node1d * new1Dnode(char *name) {
    struct node1d *temp;
    temp = (struct node1d *) malloc(sizeof(struct node1d));
    temp->name = (char *) malloc(strlen(name)*sizeof(char));
    strcpy(temp->name, name);
    temp->next = NULL;
    return temp;
}

//insert 2D node
struct node2d * insert2Dnode(struct node2d *head, char *name) {
    struct node2d *temp;
    temp = new2Dnode(name);
    if (head == NULL) {
        head = temp;
    }
    else {
        temp->down = head;
        head = temp;
    }
    return head;
}
//append 2D node
struct node2d * append2Dnode(struct node2d *head, char *name) {
    struct node2d *temp;
    temp = new2Dnode(name);
    if (head == NULL) {
        head = temp;
    }
    if (head->down == NULL) {
        head->down = temp;
    }
    else {
        struct node2d *p;
        p = head;
        while (p->down != NULL) {
            p = p->down;
        }
        p->down = temp;
    }
    return head;
}

//find 2D node
struct node2d * find2Dnode(struct node2d *head, char *afterName) {
    //if the linked list itself is empty
    if (head == NULL) {
        fprintf(stderr, "Nothing to be searched, goodbye!\n");
        exit(-1);
    }

    struct node2d *p;
    p = head;
    while (p->down != NULL) {
        if (strcmp(p->name, afterName) == 0) {
            return p;
        }
        p = p->down;
    }
    if (strcmp(p->name, afterName) == 0) {
        return p;
    }
    fprintf(stderr, "Can't find the intended node, goodbye!\n");
    exit(-1);
}

//append after 2D node
struct node2d * appendAfter2Dnode(char *name, char *afterName) {
    struct node2d *afterNode, *temp;
    afterNode = find2Dnode(head, afterName);
    temp = new2Dnode(name);
    temp->down = afterNode->down;
    afterNode->down = temp;
    return head;
}

//insert 1D node
struct node2d * insert1Dnode(char *name, char *name2d) {
    struct node2d *afterNode;
    struct node1d *temp;
    temp = new1Dnode(name);
    afterNode = find2Dnode(head, name2d);
    if (afterNode->first == NULL) {
        afterNode->first = temp;
    }
    else {
        temp->next = afterNode->first;
        afterNode->first = temp;
    }
    return head;
}

//print all
void printAll(struct node2d *head) {
    if (head == NULL) {
        fprintf(stderr, "Nothing is here, goodbye!\n");
        exit(-1);
    }
    struct node2d *p;
    p = head;
    while (p->down != NULL) {
        print1Dlist(p->name);
        p = p->down;
    }
    print1Dlist(p->name);
}

//print 1D list
void print1Dlist(char *name2d) {
    struct node2d *afterNode;
    afterNode = find2Dnode(head, name2d);
    print2Dnode(afterNode);
    if (afterNode->first != NULL) {
        struct node1d *temp;
        temp = afterNode->first;
        while (temp->next != NULL) {
            print1Dnode(temp);
            temp = temp->next;
        }
        print1Dnode(temp);
    }
}

//print 2D node
void print2Dnode(struct node2d *target) {
    printf("2d node name = %s\n", target->name);
}

//print 1D node
void print1Dnode(struct node1d *target) {
    printf("    1d node name = %s\n", target->name);
}

//This part is from the textbook inorder to read in word
int getch(void) /*geta(possiblypushed-back)character*/ {
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) /*pushcharacterbackoninput*/ {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

// getword: get next word or character from input
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}