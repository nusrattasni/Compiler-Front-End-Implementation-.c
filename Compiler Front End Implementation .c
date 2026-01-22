#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
int tempCount=1;
typedef struct{
    char result[10];
    char arg1[10];
    char arg2[10];
    char op;
    }
     TAC;
TAC tac[20];
int tacIndex = 0;
void generateTAC(char *a, char op, char *b)
{
    sprintf(tac[tacIndex].result, "t%d", tempCount++);
    strcpy(tac[tacIndex].arg1, a);
    strcpy(tac[tacIndex].arg2, b);
    tac[tacIndex].op = op;
    tacIndex++;
}
void printTAC(){
  printf("\n--- INTERMEDIATE CODE (TAC) ---\n");
  for (int i = 0; i < tacIndex; i++){
     printf("%s = %s %c %s\n",
               tac[i].result,
               tac[i].arg1,
               tac[i].op,
               tac[i].arg2);
  }
}
void lexicalAnalysis(char expr[]){
printf("\n--- LEXICAL ANALYSIS (TOKENS) ---\n");
  for (int i = 0; expr[i] != '\0'; i++){
    if (isalpha(expr[i]))
            printf("IDENTIFIER (%c)\n", expr[i]);
        else if (isdigit(expr[i]))
            printf("NUMBER (%c)\n", expr[i]);
        else
            printf("OPERATOR (%c)\n", expr[i]);
  }
}
int syntaxAnalysis(char expr[]){
if (!isalpha(expr[0]) || expr[1] != '=')
        return 0;
    return 1;

}
int semanticAnalysis(char expr[]){
  for (int i = 2; expr[i] != '\0'; i++){
    if (!isalpha(expr[i]) && !isdigit(expr[i]) &&
            expr[i] != '+' && expr[i] != '-' &&
            expr[i] != '*' && expr[i] != '/')
            return 0;
  }
  return 1;
}
int main()
{
    char expr[30];
    char lhs[10], op1[10], op2[10], op3[10];
    printf("Enter expression (example: a=b+2*3): ");
    scanf("%s", expr);
    lexicalAnalysis(expr);
    if (!syntaxAnalysis(expr)) {
        printf("\nSyntax Error ❌\n");
        return 0;
}
  printf("\nSyntax Analysis Passed ✅\n");
   if (!semanticAnalysis(expr)){
    printf("\nSemantic Error ❌\n");
    return 0;
   }
   printf("Semantic Analysis Passed ✅\n");
    lhs[0] = expr[0]; lhs[1] = '\0';
    op1[0] = expr[2]; op1[1] = '\0';
    op2[0] = expr[4]; op2[1] = '\0';
    op3[0] = expr[6]; op3[1] = '\0';
      printf("\nGenerating Intermediate Code...\n");
       if (expr[5] == '*' || expr[5] == '/'){
         generateTAC(op2, expr[5], op3);
        generateTAC(op1, expr[3], tac[0].result);
       }else{
       generateTAC(op1, expr[3], op2);
        generateTAC(tac[0].result, expr[5], op3);
       }
      printTAC();
    printf("\n%s = %s\n", lhs, tac[tacIndex - 1].result);
     printf("\nCompilation Successful ✅\n");
     return 0;
}
