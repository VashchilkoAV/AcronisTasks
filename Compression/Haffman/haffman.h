#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node{
    int Char;
    int Freq;
    Node * next;
};

typedef struct List {
    Node * Head;
    int Size;
} List;

typedef struct Treenode Treenode;

struct Treenode{
    int Char;
    int Freq;
    Node * right, * left;
};

typedef struct Tree {
    Treenode * root;
} Tree;

void ListInsert(int Char, int Freq, List * list);

typedef unsigned char byte;

int Compress(char* filename, char* resultFilename);

int Decompress(char* filename, char* resultFilename);

int EvalueateFrequences(int * frequences, FILE* stream);

void MakeList(int * frequnces, List* list);

void PrintList(List * list);

void MakeTree(Tree * tree, List * list);
