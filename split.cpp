/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
#include <cstddef>

/* Add a prototype for a helper function here if you need */
static void splitHelper(Node* in, Node** oddsTail, Node** evensTail);

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */
  splitHelper(in, &odds, &evens);
  in = NULL;
// WRITE YOUR CODE HERE
}

/* If you needed a helper function, write it here */
static void splitHelper(Node* in, Node** oddsTail, Node** evensTail)
{
  if (in == NULL) {
    *oddsTail = NULL;
    *evensTail = NULL;
    return;
  }

  Node* rest = in->next;   // save before we touch in->next
  in->next = NULL;         // detach this node from the rest

  if (in->value % 2 != 0) {
    *oddsTail = in;                              // attach here
    splitHelper(rest, &(in->next), evensTail);    // next odd attaches after this node
  } else {
    *evensTail = in;
    splitHelper(rest, oddsTail, &(in->next));
  }
}