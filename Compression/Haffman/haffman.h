#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 46

typedef struct Node Node;

typedef struct RValue {
    int currPos;
    unsigned currChar;
} RValue;

struct Node{
    int Char;
    int Freq;
    Node * next, *left, *right;
};

typedef struct List {
    Node * Head;
    int Size;
} List;

void ListInsert(int Char, int Freq, Node * right, Node * left, List * list);

typedef unsigned char byte;

int Compress(char* filename, char* resultFilename);

int Decompress(char* filename, char* resultFilename);

int EvalueateFrequences(int * frequences, FILE* stream);

void MakeList(int * frequnces, List* list);

void PrintList(List * list);

void MakeTree(List * list);

void PrintTree(List * list);

void PrintNode(Node * node);

void MakeCodes(List * tree, char** codes);

void MakeCode(Node * node, char** codes, int length, char* curr);

RValue WriteChar(char* symbol, RValue curr, FILE* output);

RValue WriteBit(RValue curr, int bit, FILE* output);

