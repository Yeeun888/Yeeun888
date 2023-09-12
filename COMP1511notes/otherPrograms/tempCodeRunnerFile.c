int size;
    printf("Enter size: ");
    scanf("%d", &size);

    //Check for odd number
    if (size % 2 == 0) {
        return -1;
    }

    for(int row = 0; row < size; ++row) {
        createLine(size,row % 4);
        printf("\n");
    }

    return 0;    