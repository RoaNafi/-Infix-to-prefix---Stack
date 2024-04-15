#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define StackSize  20
#define ArraySize  10
#define equationSize  50



//typedef int ptr;
//node nidification and operations
struct node {
    char equation[equationSize];
    char prefix[equationSize];
    char InvalidityReason[50];
    double result;
    int valid ;
    //ptr next;
};

struct node array[ArraySize];
int stack[equationSize],top = -1;

void push(char x)
{
    if( top >= StackSize-1)
    {
        printf("\nSTACK is over flow\n");

    }
    else
    {
        top++;
        stack[top]=x;
    }
}

char pop()
{
    if(top <= -1)
    {
        printf("\n\t Stack is under flow");
    }
    else
    {
        top--;
        return stack[top+1];
    }
}

void reverseString_null(char num2[]) {
    int length = strlen(num2);
    int start = 0;
    int end = length - 1;

    while (start < end) {
        char temp = num2[start];
        num2[start] = num2[end];
        num2[end] = temp;

        start++;
        end--;
    }

    // Replace '0' with '\0'
    for (int i = 0; i < length; i++) {
        if (num2[i] == '0') {
            num2[i] = '\0';
        }
    }
}


void reverseString(char num2[]) {
    int length = strlen(num2);
    int start = 0;
    int end = length - 1;

    while (start < end) {
        char temp = num2[start];
        num2[start] = num2[end];
        num2[end] = temp;

        start++;
        end--;
    }

}
int isOperation(char ch) {
    if (ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == '^')
        return 1 ;
    return 0;
}

void isValid (){
    char eq[equationSize];

    int j =0;
    //printf("%s\n", eq);
    while (array[j].equation[0] != '\0'){
        int count1 = 0;
        int count2 = 0;
        strcpy(eq , array[j].equation);
        int i =0;
        while (array[j].equation[i] != '\0') { //go through one eq
            //printf("ch = %c\n", eq[i]);
            char nextCharacter = eq[i+1];
            //printf("next = %c\n", nextCharacter);
            char previousCharacter;
            if (i > 0) {
                previousCharacter = eq[i - 1];
            }

            if (isOperation(eq[0]))
            {
                array[j].valid = 0;
                strcpy(array[j].InvalidityReason , "equation must start with number\n" );
                break;
            }

//unknown character
            if (eq[i] != '(' && eq[i] != ')' && eq[i] != '[' && eq[i] != ']'&& !isOperation(eq[i]) && eq[i] != '.' && !isdigit(eq[i]) && eq[i] != '^'){
                array[j].valid = 0;
                strcpy(array[j].InvalidityReason , "unknown character\n" );
                break;
            }

            if (eq[i] == '(')
                count1++;
            if (eq[i] == ')')
                count1--;


            if (eq[i] == '[')
                count2++;
            if (eq[i] == ']')
                count2--;

//two Parentheses with nothing between them
            if ( eq[i] == '(' && nextCharacter == ')' ){
                array[j].valid = 0;
                strcpy(array[j].InvalidityReason , "two parentheses without an operator between them \n" );
                break;
            }

//two opposite Parentheses without an operator between them )(
            if ( (eq[i] == ')' || isdigit(eq[i]) )&& nextCharacter == '(' ){
                array[j].valid = 0;
                strcpy(array[j].InvalidityReason , "two opposite parentheses without an operator between them  \n" );
                break;
            }

//two Square brackets without an operator between them
            if ( eq[i] == '[' && nextCharacter == ']' ){
                array[j].valid = 0;
                strcpy(array[j].InvalidityReason , "two Square brackets without an operator between them  \n" );
                break;
            }
//two opposite Square brackets without an operator between them
            if ( eq[i] == ']' && nextCharacter == '[' ){
                array[j].valid = 0;
                strcpy(array[j].InvalidityReason , "two opposite Square brackets  without an operator between them  \n" );
                break;
            }

// number ... [
            if ( isdigit(eq[i])  && nextCharacter == '[' ){
                array[j].valid = 0;
                strcpy(array[j].InvalidityReason , "missed operator between number and Square brackets \n" );
                break;
            }

//imbalanced parentheses
            if( nextCharacter == '\0'){
                if(count1 != 0 && count2 != 0){
                    array[j].valid = 0;
                    strcpy(array[j].InvalidityReason , "imbalance of the number of open & close parentheses and Square brackets\n");
                    break;
                }
                else if (count1 != 0){
                    array[j].valid = 0;
                    strcpy(array[j].InvalidityReason , "imbalance of the number of open & close parentheses\n");
                    break;
                }
                else if (count2 != 0){
                    array[j].valid = 0;
                    strcpy(array[j].InvalidityReason , "imbalance of the number of open & close Square brackets \n");
                    break;
                }
                else
                    array[j].valid = 1;

            }


// " . " & "  ^ " must be between two numbers
            if ( (eq[i] == '.' || eq[i] == '^') && ( !isdigit(nextCharacter) || !isdigit(previousCharacter))){
                array[j].valid = 0;
                strcpy(array[j].InvalidityReason , ". or ^ must be between two numbers\n" );
                break;
            }


            //a number with more than one sign
            if (isOperation(eq[i]) && isOperation(nextCharacter)){

                array[j].valid = 0;
                strcpy(array[j].InvalidityReason , "more than one Operation\n" );

                break;
                    }

            if (eq[i] == '/' && nextCharacter == '0'){

                array[j].valid = 0;
                strcpy(array[j].InvalidityReason , "div by zero\n" );
                break;
            }

            i++;
        }
        j++;
    }

}

// Function to get the priority of operators
int getPriority(char C) // high num high priority
{
    if (C == '-' || C == '+')
        return 1;
    else if (C == '*' || C == '/')
        return 2;
    else if (C == '^')
        return 3;
    return 0;
}


void ToPrefix() {
    int a = 0;
    while (array[a].equation[0] != '\0') {
        if (array[a].valid){

            int p = 0;
            char num2[5]; // to handel num if is more than one digit
            int n2 = 0;
            memset(num2, '\0', sizeof(num2));
            memset(stack, '\0', sizeof(stack));
            memset(array[a].prefix, '\0', sizeof(array[a].prefix));

            for (int k = strlen(array[a].equation) - 1; k >= 0 ; k--){


                if ( isdigit(array[a].equation[k] ) ) {

                    num2[n2] = array[a].equation[k] ;
                    n2++;

                    if ( !isdigit(array[a].equation[k-1] )) {

                        array[a].prefix[p] = ' ';
                        p++;
                        strcat(array[a].prefix, num2);
                        p += n2;

                        memset(num2, '\0', sizeof(num2));
                        n2 = 0;

                    }

                }


                else {
                    //printf("temp_eq[k] %c\n" ,temp_eq[k]);
                    if (array[a].equation[k] == '('){  //start pop stack untill )
                        while (stack[top] != ')'){
                            if (stack[top] == ')'){
                                break;
                            }
                            //printf("stack[top] %c\n" ,stack[top]);
                            array[a].prefix[p] = ' ';
                            p++;
                            array[a].prefix[p] = pop();
                            p++;

                            //printf("pre %s\n" ,array[a].prefix);

                        }
                        pop();
                    }
                    else if (array[a].equation[k] == '['){  //start pop stack untill ]
                        while (stack[top] != ']'){
                            if (stack[top] == ']'){
                                break;
                            }
                            //printf("stack[top] %c\n" ,stack[top]);
                            array[a].prefix[p] = ' ';
                            p++;
                            array[a].prefix[p] = pop();
                            p++;

                            // printf("pre %s\n" ,array[a].prefix);

                        }
                        pop();
                    }

                    else if(array[a].equation[k] == ' '){

                    }
                    else { // + - / * )



                        if(getPriority(array[a].equation[k]) >= getPriority(stack[top]) || array[a].equation[k] == ')' || array[a].equation[k] == ']' ){
                            push(array[a].equation[k]);
                        }

                        else if ((getPriority(array[a].equation[k]) < getPriority(stack[top]))){
                            while (getPriority(array[a].equation[k]) < getPriority(stack[top])){
                                if (getPriority(array[a].equation[k]) >= getPriority(stack[top])){
                                    break;
                                }
                                array[a].prefix[p] = ' ';
                                p++;
                                array[a].prefix[p] = pop();
                                p++;
                                push(array[a].equation[k]);
                                //printf(" prefix[p] %c \n", array[a].prefix[p]);

                            }
                        }
                    }
                }
            }
            while (isOperation(stack[top])){
                array[a].prefix[p] = ' ';
                p++;
                array[a].prefix[p] = pop();
                p++;

            }
            reverseString(array[a].prefix);
        }
        a++;
    }

}

int arrayToNumber(int arr[], int size) {
    int i, k = 0;
    for (i = 0; i < size; i++)
        k = 10 * k + arr[i];

    return k;
}

//todo...
void evaluatePrefix()
{
    int a = 0;

    char num2[10]; // to handel num if is more than one digit
    int n2 = 0;

    while (array[a].prefix[0] != '\0'){
        memset(stack, '\0', sizeof(stack));
        top = -1;
        if (array[a].valid){

            for (int j = strlen(array[a].prefix) - 1; j >= 0; j--)
            {
                //printf("array[a].prefix : %s",array[a].prefix);
                if ( isdigit(array[a].prefix[j] ) ) {

                    num2[n2] = array[a].prefix[j] ;
                    n2++;
                   // printf("num2 %s\n",num2);
                    if ( !isdigit(array[a].prefix[j-1] )) {

                        //printf("num : %d\n",arrayToNumber(num2,n2));
                        push(arrayToNumber(num2,n2));
                        memset(num2, '\0', sizeof(num2));
                        n2 = 0;

                    }


                }else if (isOperation(array[a].prefix[j])){
                    int operand1 = pop();
                    int operand2 = pop();
                    char operator = array[a].prefix[j];
                    int result;
                    switch (operator)
                    {
                        case '+':
                            result = operand1 + operand2;
                            push(result);
                        case '-':
                            result = operand1 - operand2;
                            push(result);
                        case '*':
                            result = operand1 * operand2;
                            push(result);
                        case '/':
                            result = operand1 / operand2;
                            push(result);
                        //case '^':
                          //  result = operand1 ^ operand2;
                            //push(result);
                    }
                }
                if (top == 0){
                    printf("result :%d\n",array[a].result);
                    array[a].result = pop() ;
                }
            }
        }

    }


}
int main() {

    char msg[] ="_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n";

    //Prompt user to enter file neme
    FILE* file;
    char filename[10];

    //make sure that file opened successfully
    do{
        printf("Enter the name of the input file: ");
        scanf("%s", filename);

        //file = fopen("equations.txt", "r"); //delete
        file = fopen(filename, "r");
        if (file != NULL) {
            printf("File '%s' opened successfully.\n", filename);
            break;
        } else {
            printf("Unable to open the file '%s'. Please try again.\n", filename);
        }


    } while (1);



    //read from file and save data into array of type node
    char line[50];
    int i =0;
    while (fgets(line, sizeof(line), file) != NULL ) {
        // Remove the newline character if present
        line[strcspn(line, "\n")] = '\0';
        //printf("%s\n" , line);
        strcpy(array[i].equation , line);
        array[i].valid = 1;
        i++;
    }
    array[i].equation[0] ='\0';
    fclose(file);
    isValid ();


    //keep show the menu
    int flag = 0;
    char choice;

    do{
        printf(msg);
        printf("What can I do for you? Just enter the number:\n");
        printf("1. Check the validity\n");
        printf("2. Infix to Prefix\n");
        printf("3. Evaluate the prefix\n");
        printf("4. Print all information in file\n");
        printf("5. Exit\n");
        printf(msg);
        choice = getch();
        switch (choice) {
            case '1': {
                //print
                int j = 0;
                while (array[j].equation[0] != '\0')  {
                    if (array[j].valid == 1)
                        printf("%-20s\tValid\n" , array[j].equation);
                    if (array[j].valid == 0)
                    {
                        printf("%-20s\tnot Valid: %s" , array[j].equation , array[j].InvalidityReason);
                    }
                    j++;
                }
                break;
            }
            case '2': {
                if (!flag){
                    ToPrefix();
                    int j = 0;
                    printf("infix\t\t\t\tprefix\n");
                    while (array[j].equation[0] != '\0')  {
                        if (array[j].valid == 1)
                            printf("%-30s\t%-30s\n" , array[j].equation ,array[j].prefix);
                        j++;
                    }
                    flag = 1;
                }
                else{
                    int j = 0;
                    printf("infix\t\t\t\tprefix\n");
                    while (array[j].equation[0] != '\0')  {
                        if (array[j].valid == 1)
                            printf("%-30s\t%-30s\n" , array[j].equation ,array[j].prefix);
                        j++;
                    }
                }
                break;
            }
            case '3': {
                if(flag){
                    evaluatePrefix();

                    int j = 0;
                    printf("infix\t\t\t\tprefix\n");
                    while (array[j].equation[0] != '\0')  {
                        if (array[j].valid == 1)
                            printf("%-30s\t%-30s\n" , array[j].equation ,array[j].result);
                        j++;
                    }
                } else{
                    printf("find PREFIX first\n");
                }


                break;
            }
            case '4':{

                FILE* file;
                char output_file[] = "output_file";

                //make sure that file opened successfully
                do{


                    //file = fopen("equations.txt", "r"); //delete
                    file = fopen(output_file, "w");
                    if (file != NULL) {
                        printf("File '%s' opened successfully.\n", output_file);
                        break;
                    } else {
                        printf("Unable to open the file '%s'. Please try again.\n", output_file);
                    }

                } while (1);
                int i = 0;
                while (array[i].equation[0] != '\0')
                {

                    if(array[i].valid){
                        fprintf(file, "Equation %d: %s\n",  i + 1,array[i].equation);
                        fprintf(file, "Valid: %d\n", array[i].valid);
                        fprintf(file, "Prefix: %s\n", array[i].prefix);
                        fprintf(file, "Result: %lf\n", array[i].result);
                        fprintf(file,msg);
                    } else{
                        fprintf(file, "Equation %d: %s\n",  i + 1,array[i].equation);
                        fprintf(file, "Valid: %d\n", array[i].valid);
                        fprintf(file, "Invalidity Reason: %s", array[i].InvalidityReason);
                        fprintf(file,msg);
                    }
                    i++;
                }
                fclose(file);
                puts("Check the file\n");
                break;
            }

            case '5': {
                printf("Program exit complete, See you in the next runtime!\n");
                break;

            }
            default:
                printf("Invalid choice.\n");
                break;
        }

    }while (choice != '5');


    return 0;
}