/*
 * Project1.cpp
 * 
 * Name: Deepanshi Sharma
 * EE312 Fall 2019
 * SpellCheck
 */

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types
#include <string.h>
#include <stdlib.h>

/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
 *
 * Many students find it helpful to declare global variables (often arrays). You are welcome to use
 * globals if you find them helpful. Global variables are by no means necessary for this project.
 */

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I *insist* that you indent
 * reasonably and consistently in your code. I strongly encourage you to avoid big functions
 * So, plan on implementing spellCheck by writing two or three other "support functions" that
 * help make the actual spell checking easier for you.
 * There are no explicit restrictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard library. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */

char one_word[30] = {0};
char words[50000*8];
void PrintWord(char one_word[]){                    //this function prints the words not found in dictionary
        printf("%s", one_word);
}

void LowerCase(char dictionary[]){                  //this function converts the dictionary to lowercase
    int d=0;
    while(dictionary[d]) {
        for (; dictionary[d] != '\n'; d++) {
            if (('A' <= dictionary[d]) && (dictionary[d] <= 'Z')) {
                dictionary[d] = (dictionary[d] + ' ');
            }
        }
        if(dictionary[d] == '\n'){
            d++;
        }
    }
}

void printArticle(char article[]){                  //this function stores all the "words" in the article in words[]

    int i = 0;                                      //initializing counters
    int j=0;
    int x=0;
    int words_i=0;
    int save_x = 0;

    while(article[i]) {                             //while the character is a letter, increment count
        int count = 0;
        while ((('A'<=article[i])&&(article[i]<='Z'))||(('a'<=article[i])&&(article[i]<='z'))){
            count++;
            i++;                                                        //i is the index for article[]
        }
        if (count > 1) {                                                //word length greater than 1
            for (x = 0; x < count; x++) {
                words[x + words_i] = article[j];                        //x is the index for words[]
                j++;                                                    //j points to the next word in article[]
            }
            words[x + words_i] = '\n';
            save_x = x+words_i;
        }
        if((('A' > article[i]) || (article[i] > 'z'))  || (('Z' <= article[i]) && (article[i] <= 'a'))){        //if the char is not a letter, go to the next char
            j++;
        }
        i=j;
        if(article[i] == 0){
            words[save_x] = '\n';                                      //append word with new line and null termination
            words[save_x+1] = 0;
        }
        if(count > 1) {
            words_i += count;                                          //words_i points to the next word in words[]
            words_i++;
        }
    }
}
void spellCheck(char article[], char dictionary[]) {

    printArticle(article);                                             //find all the words in the article
    LowerCase(dictionary);                                             //convert dictionary to lowercase
    int i=0;
    int x=0;
    char* is_word = 0;                                                 //pointer to word in dictionary or null
    while(words[i]) {
            x=0;
        for (; words[i] != '\n'; x++) {                                //isolate one word to search for in the dictionary
            if (('A' <= words[i]) && (words[i] <= 'Z')) {              //if char is capital, make lowercase
                one_word[x] = (words[i] + ' ');
                i++;
            } else {
                one_word[x] = words[i];
                i++;
            }
        }
        one_word[x] = '\n';
        one_word[x+1] = 0;
        x=0;
        SEARCH: is_word = strstr(dictionary, one_word);                //search for "word/n" within dictionary
            while (is_word) {
                if(dictionary == is_word){                             //skip this step for first word
                    break;
                }
                if(*(is_word-1) != '\n') {                             //make sure word is not contained within another
                    char *temp = is_word + 1;
                    is_word = strstr(temp, one_word);
                }else{
                    break;
            }
        }

     PRINT:   if (is_word == 0) {                                      //if word wasn't found in dictionary, print to console
            PrintWord(one_word);
        }
        i++;                                                           //check next word in words[]
    }
}



