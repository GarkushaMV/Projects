//
// Stack Calculator (non-graphic version)
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "RealStack.h"

static void onAdd();
static void onSub();
static void onMul();
static void onDiv();
static void onPush(const char* line);
static void onPop();
static void onInit();
static void display();
static void printHelp();
static void onShow();

static RealStack *stack = 0;

int main() {
    printHelp();

    char line[256];
    stack = new RealStack();

    // gets(line);
    scanf("%s", line);
    while (*line != 0) {
        int linelen = strlen(line);
        try {
            if (strcmp(line, "+") == 0)
                onAdd();
            else if (strcmp(line, "-") == 0)
                onSub();
            else if (strcmp(line, "*") == 0)
                onMul();
            else if (strcmp(line, "/") == 0)
                onDiv();
            else if (strcmp(line, "=") == 0)
                display();
            else if (
                (linelen > 0 && isdigit(line[0])) ||
                (linelen > 1 && (line[0] == '-' || line[0] == '+') &&
                    isdigit(line[1]))
            )
                onPush(line);
            else if (strcmp(line, "pop") == 0)
                onPop();
            else if (strcmp(line, "init") == 0)
                onInit();
            else if (strcmp(line, "show") == 0)
                onShow();
            else if (
                strcmp(line, "") == 0 ||
                (linelen > 0 && (line[0] == 'q' || line[0] == 'Q'))
            )
                break;
            else
                printHelp();
        } catch (StackException& e) {
            printf("Stack Exception: %s\n", e.reason);
        }
        // gets(line);
        scanf("%s", line);
    }
    return 0;
}

static void onAdd() {
    double y = stack->pop();
    double x = stack->pop();
    stack->push(x + y);
    display();
}

static void onSub() {
    double y = stack->pop();
    double x = stack->pop();
    stack->push(x - y);
    display();
}

static void onMul() {
    double y = stack->pop();
    double x = stack->pop();
    stack->push(x * y);
    display();
}

static void onDiv() {
    double y = stack->pop();
    double x = stack->pop();
    stack->push(x / y);
    display();
}

static void onPush(const char* line) {
    double x = atof(line);
    stack->push(x);
}

static void onPop() {
    stack->pop();
}

static void onInit() {
    stack->init();
}

static void display() {
    if (!stack->empty()) {
        printf("=%lf\n", stack->top());
    } else {
        printf("stack empty\n");
    }
}

static void onShow() {
    int d = stack->depth();
    printf("Depth of stack = %d.", d);
    if (d > 0)
        printf(" Stack elements:\n");
    else
        printf("\n");

    for (int i = 0; i < d; i++) {
        printf("\t%lf\n", stack->elementAt(i));
    }
}

static void printHelp() {
    printf(
        "Stack Calculator commands:\n"
        "\t<number>\tPush to stack\n"
        "\t+, -, *, /\tAriphmetic operations\n"
        "\t=\t\tDisplay the stack top\n"
        "\tpop\t\tRemove the stack top\n"
        "\tshow\t\tShow the stack\n"
        "\tinit\t\tErase the stack\n"
        "\tquit\t\tEnd the program\n"
    );
}
