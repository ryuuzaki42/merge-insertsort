void insertionSort(int *vet, int size) {
    for(int j = 1; j < size; j++) {
        int chave = vet[j];
        int i = j - 1;

        // procura lugar de insercao e desloca numero
        while(i >= 0 && vet[i] > chave) {
            vet[i + 1] = vet[i];
            i--;
        }

        vet[i + 1] = chave;
    }
}

void sort(int *vet, int *aux, int inf, int sup) {
    if (sup <= inf) {
        return;
    }

    int med = inf + (sup - inf) / 2;

    sort(vet, aux, inf, med);
    sort(vet, aux, med + 1, sup);
    merge(vet, aux, inf, med, sup);
}

void mergesortTopDown(int *vet, int size) {
    int *aux = new int[size];

    sort(vet, aux, 0, size - 1);

    delete []aux;
}
