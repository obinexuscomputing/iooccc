#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../quparser.h"

// State-based control flow transformation patterns
typedef enum {
    NORMAL_FLOW = 0,
    GOTO_FLOW = 1,
    SWITCH_FLOW = 2,
    COMPUTED_GOTO = 3
} FlowState;

typedef struct {
    char *original;
    char *transformed;
    FlowState state;
} ControlTransform;

// Transform if-else to state machine
char* transform_if_else(const char *code) {
    char *result = malloc(strlen(code) * 2 + 100);
    sprintf(result, 
        "int _s=0;while(_s<2){switch(_s){case 0:if(%s){_s=1;}else{_s=2;}break;"
        "case 1:%s;_s=2;break;case 2:%s;_s=2;break;}}",
        strchr(code, '(') + 1,
        strstr(code, "{") + 1,
        strstr(code, "else") + 5
    );
    return result;
}

// Transform while to computed goto
char* transform_while(const char *code) {
    char *result = malloc(strlen(code) * 2 + 100);
    sprintf(result,
        "void *_s[]={&&start,&&body,&&end};goto *_s[0];start:if(!(%s))goto *_s[2];"
        "body:%s;goto *_s[0];end:;",
        strchr(code, '(') + 1,
        strstr(code, "{") + 1
    );
    return result;
}

// Main transformation function
char* obfuscate_control_flow(const char *src) {
    QuToken **tokens;
    int index = 0;
    
    // Tokenize source
    Qu_tokenize(src);
    QuASTNode *ast = Qu_parseProgram(tokens, &index);
    
    // Transform control structures based on state patterns
    char *result = malloc(strlen(src) * 3);
    strcpy(result, "");
    
    // Walk AST and apply transformations
    QuASTNode *current = ast;
    while (current) {
        if (strstr(current->value, "if")) {
            char *transformed = transform_if_else(current->value);
            strcat(result, transformed);
            free(transformed);
        } else if (strstr(current->value, "while")) {
            char *transformed = transform_while(current->value);
            strcat(result, transformed);
            free(transformed);
        } else {
            strcat(result, current->value);
        }
        current = current->right;
    }
    
    Qu_freeAST(ast);
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <source_file>\n", argv[0]);
        return 1;
    }
    
    // Read source file
    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;
    
    char src[10000];
    size_t n = fread(src, 1, 9999, src);
    src[n] = 0;
    fclose(f);
    
    // Obfuscate
    char *obfuscated = obfuscate_control_flow(src);
    printf("%s\n", obfuscated);
    free(obfuscated);
    
    return 0;
}