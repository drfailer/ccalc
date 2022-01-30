#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calculator.h"


/* (op left right) */

/******************************************************************************
 * UTILS:
 *****************************************************************************/

int is_operator(char c) {
  return (c == '+' || c == '-' || c == '/' || c == '*');
}

op_t operator(char c) {
  op_t output = -1;

  switch (c) {
    case '+':
      output = 0;
      break;
    case '-':
      output = 1;
      break;
    case '/':
      output = 2;
      break;
    case '*':
      output = 3;
      break;
  }
  return output;
}

/* return the symbol corresponding to the operator */
char operator_symbol(op_t op) {
  char ops[] = "+-/*_";
  return ops[op];
}

/* print formula in postfix convention */
void print_formula(form_t *f) {
  printf("(%c %LF %LF)\n", operator_symbol(f->op), f->left->val, f->right->val);
}

/* allocate and initialise a new node of a formula */
form_t *creat_form() {
  form_t *f = (form_t*) malloc(sizeof(form_t));
  if (f) {
    f->op = -1;
    f->val = 0;
    f->left = NULL;
    f->right = NULL;
  }
  return f;
}

/* free the memory dynamicaly allcated during the creation of the formula */
void free_formula(form_t *f) {
  if (f) {
    free_formula(f->left);
    free_formula(f->right);
    free(f);
  }
}


/******************************************************************************
 * PARSEURS:
 *****************************************************************************/

/* parse a number and return a double */
long double parse_number(char **s) {
  long double nb = 0;
  long double weight = 10;
  char *ss = *s;

  // parse the int part of the number
  while (*s && *ss >= '0' && *ss <= '9') {
    nb = 10*nb + (*ss - '0');
    ss++;
  }
  // if we find a '.' we can parse the floatting part of the number
  if (*ss == '.') {
    ss++;
    while (*ss && *ss >= '0' && *ss <= '9') {
      nb = nb +  (*ss - '0')/weight;
      weight *= 10;
      ss++;
    }
  }
  // update s
  *s = ss;
  return nb;
}

/* consume the given string to parse a formula */
form_t *parse_formula(char **str) {
  form_t *f = NULL;
  char *s = *str;

  f = creat_form();
  if (f) {
    if (*s == '(') {
      /* parse a formula: */
      // skip everything until the operator
      while (*s && !is_operator(*s))
        s++;
      if (*s) {
        f->left = creat_form();
        f->right = creat_form();
        if (f->left && f->right) {
          f->op = operator(*s++);
          while (*s && *s == ' ' && s++); // skip spaces
          f->val = 0;
          printf("s: %s\n", s);
          f->left->val = parse_number(&s);
          while (*s && *s == ' ' && s++); // skip spaces
          f->right->val = parse_number(&s);
          while (*s && *s++ != ')');
        } else {
          fprintf(stderr, "Error: can't allocate new form_t.\n");
          free(f->left);
          free(f->right);
        }
      }
    } else {
      f->op = FAC;
      f->val = atol(s);
      f->left = NULL;
      f->right = NULL;
    }
  }
  *str = s;
  return f;
}
