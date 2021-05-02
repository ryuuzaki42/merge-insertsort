void insertionSortM(int *vet, int low, int high) {
//     int size;

    for(int j = low + 1; j < high; j++) {
        int chave = vet[j];
        int i = j - 1;

        // procura lugar de insercao e desloca numero
        while(i >= low && vet[i] > chave) {
            vet[i + 1] = vet[i];
            i--;
        }

        vet[i + 1] = chave;
    }
}

void sortMI(int *vet, int *aux, int inf, int sup, int threshold) {
    if (sup <= inf) {
        return;
    }

    if ((sup - inf) >= threshold) {
        int med = inf + (sup - inf) / 2;

        sortMI(vet, aux, inf, med, threshold);
        sortMI(vet, aux, med + 1, sup, threshold);

        merge(vet, aux, inf, med, sup);
    } else {
        insertionSortM(vet, inf, sup + 1);
    }
}

void mergesortTopDownInsertionSort(int *vet, int size, int threshold) {
    int *aux = new int[size];

    sortMI(vet, aux, 0, size - 1, threshold);

    delete []aux;
}
