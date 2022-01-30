#ifndef __CALCULATOR__
#define __CALCULATOR__

typedef enum operation {
  ADD, SUB, DIV, MUL, FAC
} op_t;

typedef struct formula {
  op_t op;
  long double val;
  struct formula *left;
  struct formula *right;
} form_t;

form_t *parse_formula(char **str);
double eval_formula(form_t *f);
char *formula_to_string(form_t *f);

#endif
