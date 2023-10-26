#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VAL 100

struct Node
{
    int data;
    struct Node *next;
};

typedef struct BigInteger
{
    struct Node *L;
    int length;
}SBI;

struct BigInteger initialize(char*);
void display(struct BigInteger);
struct BigInteger reverse(struct BigInteger);
struct BigInteger insert(struct BigInteger, int);
struct BigInteger add(struct BigInteger, struct BigInteger);
int compare(struct BigInteger, struct BigInteger);
struct BigInteger sub(struct BigInteger, struct BigInteger);
struct BigInteger insert_head(struct BigInteger, int);
struct BigInteger mul(struct BigInteger, struct BigInteger);
struct BigInteger div1(struct BigInteger, struct BigInteger);
struct BigInteger mod(struct BigInteger, struct BigInteger);
int length(struct BigInteger);
#endif