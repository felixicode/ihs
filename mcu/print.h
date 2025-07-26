#ifndef PRINT_H
#define PRINT_H
void print_init(void);
void print_str(const char *str);

//#define PRINT_EXTEND

#ifdef PRINT_EXTEND
void print_num(int n);
void print_float(float n);
void print_charx(unsigned char n);
#endif
#endif