#include <stdio.h>
#include <ctype.h>
//from textbook
#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
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
    if (c != '\0')
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

int main() {
    printf("enter something:\n");
    char word[20];
    getword(word, 20);
    printf("%s is your input\n", word);

    char w[20];
    getword(w, 20);
    printf("%s is your 2 input\n", w);
    return 1;
}