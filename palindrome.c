#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "stack.h"
#include "ctype.h"

#define MAX_STR_LEN 256

/*
 * This function prompts the user for input and stores a maximum of `n`
 * characters of the string they enter into `dest`.  Any trailing line ending
 * characters are removed from the input string.  Returns 1 if a string was
 * successfully read from the user or 0 otherwise.
 */
int get_user_str(char* dest, int n) {
  printf("\nEnter a string, and we'll check whether it's a palindrome:\n");
  if (fgets(dest, MAX_STR_LEN, stdin) != NULL) {
    /*
     * If a string was successfully read from the user, remove any trailing
     * line ending characters.  Here's some documentation on strcspn() to help
     * understand how this works:
     *
     * https://en.cppreference.com/w/c/string/byte/strcspn
     */
    dest[strcspn(dest, "\r\n")] = '\0';
    return 1;
  } else {
    return 0;
  }
}

int main(int argc, char const *argv[]) {
  char* in = malloc(MAX_STR_LEN * sizeof(char));
  char *c;
  char *v;
  int n=0;
  int m=0;
  int queueSize=0;
  struct stack* s;
  struct queue* q;

  char* stackString = malloc(MAX_STR_LEN * sizeof(char));
  char* queueString = malloc(MAX_STR_LEN * sizeof(char));


  while (get_user_str(in, MAX_STR_LEN)) {
    /*
     * Inside this loop body, you'll have an input string from the user in `in`.
     * You should use your stack and your queue to test whether that string is
     * a palindrome (i.e. a string that reads the same backward as forward, e.g.
     * "ABCBA" or "Madam, I'm Adam").  For each string input by the user,
     * print a message letting the user know whether or not their string is
     * is a palindrome.
     *
     * When you test whether the user's string is a palindrome, you should
     * ignore any non-letter characters (e.g. spaces, numbers, punctuation,
     * etc.), and you should ignore the case of letters (e.g. the characters
     * 'a' and 'A' should be considered as equal).  The C functions isalpha()
     * and tolower() from ctype.h might help with this.
     */
      s=stack_create();
   q=queue_create();

      n=strlen(in);
 //     printf("length of string: %d",n);
      
      for(int i=0; i<n; i++){
        if(isalpha(in[i])>0){
          in[i]=tolower(in[i]);
          stack_push(s,&in[i]);
          c = (char *)stack_top(s);
  //        printf("\n topstack = %s\n ", c);
          queue_enqueue(q,&in[i]);
          v = (char *)queue_front(q);
  //        printf("\n endqueue = %s\n ", v);
  //        printf("\nvalue added to both stack and queue: %c",in[i]);
        }
        else{
  //        printf("\nnon alphabet detected skipping...");
        }
      }

  //    printf("\n size of queue: %d",queueSize);

      while(queue_isempty(q)==0){
        stackString=stack_pop(s);
        queueString=queue_dequeue(q);
 //       printf("\n stackpop: %s",stackString);
 //       printf("\n queuedq: %s",queueString);
        m=strncmp(stackString, queueString, 1);

      if(m!=0){
        printf("\n It is not a palindrome");
        break;
      }

        }
      if(m==0){
        printf("\n It is a palindrome");

      }
  free(s);
  free(q);

  }
  
  free(in);
  return 0;
}