#include "haffman.h"



int EvalueateFrequences(int * frequences, FILE* stream) {
    int b;
    while((b = fgetc(stream)) != EOF) {
        frequences[b]++;
    }
    return 0;
}



int Compress(char *filename, char *resultFilename) {
    int frequences[256] = {0};
    FILE * input = fopen(filename, "rb");
    List * list = (List*)malloc(sizeof (list));
    if (input == NULL) {
        return 1;
    }
    int res = EvalueateFrequences(frequences, input);
    if (res) {
        return res;
    }
    list->Size = 0;
    MakeList(frequences, list);
    PrintList(list);
    MakeTree(list);
    char ** codes = (char**)malloc(256*sizeof (char*));
    MakeCodes(list, codes);
    int i = 0;
    for (; i < 256; i++) {
        if (codes[i] != NULL) {
            printf("%s\n", codes[i]);
        }
    }

    FILE * output = fopen(resultFilename, "wb");
    if (output == NULL) {
        return 2;
    }
    fwrite(frequences, 4, 256, output);
    PrintTree(list);
    //PrintList(list);

    rewind(input);

    int ch = 0;
    RValue result;
    result.currPos = 7;
    result.currChar = 0;
    while ((ch = fgetc(input)) != EOF) {
        result = WriteChar(codes[ch], result, output);
    }
    WriteChar("", result, output);
    fclose(output);
    fclose(input);

    DeleteList(list);
    free(list);
    for (i = 0; i < 256; i++) {
        free(codes[i]);
    }
    free(codes);

    return 0;
}

void ListInsert(int Char, int Freq, Node* right, Node* left, List* list) {
    list->Size++;
    Node * newNode = (Node*)malloc(sizeof (Node));
    newNode->Char = Char;
    newNode->Freq = Freq;
    newNode->next = NULL;
    newNode->left = left;
    newNode->right = right;
    if (list->Head == NULL) {
        list->Head = newNode;
    } else {
        Node * ptr = NULL;
        if (list->Head->Freq >= newNode->Freq) {
            Node * nextNode = list->Head;
            list->Head = newNode;
            newNode->next = nextNode;
            return;
        }
        for (ptr = list->Head; ptr->next != NULL; ptr = ptr->next) {
            if (ptr->next->Freq >= newNode->Freq) {
                break;
            }
        }
        Node * nextNode = ptr->next;
        ptr->next = newNode;
        newNode->next = nextNode;
    }
}

void MakeList(int *frequnces, List *list) {
    int i = 0;
    for (i = 0; i < 256; i++) {
        if (frequnces[i]) {
            ListInsert(i, frequnces[i], NULL, NULL, list);
        }
    }
}

void PrintList(List *list) {
    Node * ptr = NULL;
    for (ptr = list->Head; ptr; ptr = ptr->next) {
        printf("%d -- %d,  ", ptr->Char, ptr->Freq);
    }
    printf("\n");
}

void MakeTree(List *list) {
    if (list->Head) {
        while (list->Size > 2) {
            list->Size-=2;
            Node * TwoLast = list->Head;
            list->Head = TwoLast->next->next;
            Node * right = TwoLast; //less
            Node * left = TwoLast->next;
            int Char = -1;
            int Freq = left->Freq+right->Freq;
            ListInsert(Char, Freq, right, left, list);
            //PrintList(list);
        }
        if (list->Size == 1) {
            Node* newNode = (Node*)malloc(sizeof (Node));
            newNode->left = list->Head;
            list->Head = newNode;
            return;
        } else {
            list->Size--;
            Node * TwoLast = list->Head;
            Node * right = TwoLast; //less
            Node * left = TwoLast->next;
            int Char = -1;
            int Freq = left->Freq+right->Freq;
            list->Head = NULL;
            ListInsert(Char, Freq, right, left, list);
        }
    }
}

void PrintTree(List *list) {
    PrintNode(list->Head);
}

void PrintNode(Node *node) {
    printf("Current node: %d, its frequency: %d, ", node->Char, node->Freq);
    if (node->left) {
        printf("left: %d", node->left->Freq);
    } else {
        printf("left: NULL, ");
    }
    if (node->right) {
        printf("right: %d.\n", node->right->Freq);
    } else {
        printf("right: NULL.\n");
    }
    if (node->left) {
        PrintNode(node->left);
    }
    if (node->right) {
        PrintNode(node->right);
    }
}



void MakeCodes(List *tree, char **codes) {
    char a[MAXLEN] = "";
    MakeCode(tree->Head, codes, 0, a);
}

void MakeCode(Node *node, char **codes, int length, char * curr) {
    if (node->left) {
        char a[MAXLEN];
        strcpy(a, curr);
        a[length] = '1';
        MakeCode(node->left, codes, length+1, a);
    }
    if (node->right) {
        char a[MAXLEN];
        strcpy(a, curr);
        a[length] = '0';
        MakeCode(node->right, codes, length+1, a);
    }
    if (node->left == NULL && node->right == NULL) {
        codes[node->Char] = (char*)malloc(MAXLEN*sizeof (char));
        char a[MAXLEN];
        strcpy(a, curr);
        a[length] = '\0';
        strcpy(codes[node->Char], a);
    }

}

RValue WriteChar(char* symbol, RValue curr, FILE* output) {
    RValue result = curr;
    if (strcmp(symbol, "") == 0) {//if end of string
        WriteBit(result, -1, output);
    } else {
        int i = 0;
        for (; symbol[i]; i++) {
            result = WriteBit(result, symbol[i] == '1' ? 1 : 0, output);
        }
    }
    return result;
}

RValue WriteBit(RValue curr, int bit, FILE* output) { //returns current char
    if (bit == -1) {
        if (curr.currPos != 0) {
            int i = 0;
            for (; i < curr.currPos; i++) {
                unsigned d = 1;
                d <<= i;
                curr.currChar |= d;
            }
            fputc(curr.currChar, output);
        }
        return curr;
    }
    RValue result;    
    int add = 1 << curr.currPos;
    result.currPos = (curr.currPos - 1 < 0) ? 7 : curr.currPos-1;
    result.currChar = curr.currChar;
    if (bit == 1) {
        result.currChar |= add;
    }
    if (curr.currPos == 0) {
        fputc(result.currChar, output);
        result.currPos = 7;
        result.currChar = 0;
    }
    return result;
}

int Decompress(char *filename, char *resultFilename) {
    int frequences[256] = {0};
    FILE * input = fopen(filename, "rb");
    List * list = (List*)malloc(sizeof (list));
    if (input == NULL) {
        return 1;
    }

    FILE* output = fopen(resultFilename, "wb");
    if (output == NULL) {
        return 2;
    }

    fread(frequences, 4, 256, input);

    list->Size = 0;
    MakeList(frequences, list);
    PrintList(list);
    MakeTree(list);
//    char ** codes = (char**)malloc(256*sizeof (char*));
//    MakeCodes(list, codes);
//    int i = 0;
//    for (; i < 256; i++) {
//        if (codes[i] != NULL) {
//            printf("%s\n", codes[i]);
//        }
//    }

    ProcessDecomression(input, output, list);


    fclose(input);
    fclose(output);
    DeleteList(list);
    free(list);

    return 0;
}

void DeleteList(List *list) {
    if (list->Head) {
        if (list->Head->left || list->Head->right) {
            DeleteNode(list->Head);
        } else {
            free(list->Head);
        }
    }
}

void DeleteNode(Node *node) {
    if (node->left) {
        if (node->left->left || node->left->right) {
            DeleteNode(node->left);
        } else {
            free(node->left);
        }
    }
    if (node->right) {
        if (node->right->left || node->right->right) {
            DeleteNode(node->right);
        } else {
            free(node->right);
        }
    }
}

void ProcessDecomression(FILE *input, FILE *output, List *list){
    int ch = 0;
    int pos = 0;
    Node * ptr = list->Head;
    if (ptr) {
        while((ch = fgetc(input)) != EOF) {
            for (pos = 0; pos < 8; pos++) {
                unsigned curr = 1;
                curr <<= (7-pos);
                int res = ch & curr;
                if (res) { //left
                    if (ptr->left) {
                        ptr = ptr->left;
                        if (ptr->left == NULL && ptr->right == NULL) {//means that ptr is a symbol
                            fputc(ptr->Char, output);
                            ptr = list->Head;
                        }
                    }
                } else {
                    if (ptr->right) {
                        ptr = ptr->right;
                        if (ptr->left == NULL && ptr->right == NULL) {//means that ptr is a symbol
                            fputc(ptr->Char, output);
                            ptr = list->Head;
                        }
                    }
                }

            }

        }

    }
}
