int main() {
    char inputValueA[309], inputValueB[309], input[11];
    struct uint1024_t A, B, C, D, E;

    for (int i = 0; i < 309; ++i) {
        inputValueA[i] = 'f';
        inputValueB[i] = 'f';
    }

    printf("input А:");
    scanf("%s", inputValueA);
    scanfValue(inputValueA, &A);
    printf("input B:");
    scanf("%s", inputValueB);
    scanfValue(inputValueB, &B);
    printf("Available commands: '+', '-', '*', 'generate()', 'exit()'\n");
    scanf("%s", input);

    while (strcmp("exit()", input) != 0) {
        if (strcmp("generate()", input) == 0) {
            unsigned int x;
            printf("input x:");
            scanf("%u", &x);
            D = fromUint(x);
            printf("select operation for A and x: '+', '-', '*'\n");
            char operation[2];
            scanf("%s", operation);
            if (strcmp("+", operation) == 0) {
                C = addOp(A, D);
                printfValue(&C);
            } else if (strcmp("-", operation) == 0) {
                C = SubtrOp(A, D);
                printfValue(&C);
            } else if (strcmp("*", operation) == 0) {
                C = MultOp(A, D);
                printfValue(&C);
            }
            printf("select operation for A and B: '+', '-', '*'\n");
        } else if (strcmp("+", input) == 0) {
            C = addOp(A, B);
            printfValue(&C);
        } else if (strcmp("-", input) == 0) {
            C = SubtrOp(A, B);
            printfValue(&C);
        } else if (strcmp("*", input) == 0) {
            C = MultOp(A, B);
            printfValue(&C);
        }
        scanf("%s", input);
    }

    return 0;
}