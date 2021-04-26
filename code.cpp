#include <iostream> // cout
#include <random> // random device
#include <chrono> // time chrono

// #define vetSize 5000000 // "vetor" size
#define vetCount 10 // count of "vectors"

#define vetSize 1000
// #define vetCount 4

using namespace std;

// general purpose functions //---------------------------------------------------------------------

void vetPrint(int *vet) {
    for (int i = 0; i < vetSize; i++) {
        if (i < 10) {
            cout << "0000";
        } else if (i < 100) {
            cout << "000";
        } else if (i < 1000) {
            cout << "00";
        } else if (i < 10000) {
            cout << "0";
        }

        cout << i << " " << vet[i] << "\n";
    }
}

void matPrint(int **mat) {
    for (int i = 0; i < vetCount; i++) {
        printf("\n");
        for (int j = 0; j < vetSize; j++ ) {
            printf("i %d j %d vet[i][j] %d\n", i , j, mat[i][j]);
        }
    }
}

void checkIsSorted (int *vet, int vetNum) {
    bool check = true;
    for(int i = 0; i < vetSize - 1; i++) {
        if (vet[i] > vet[i+1]) {
            printf("\nvet[%d] > vet[%d] - %d > %d\n",i, i+1, vet[i], vet[i+1]);
            check = false;
            break;
        }
    }

    if (check) {
        printf("\n---vetA%d is sorted", vetNum);
    } else {
        printf("\nvetA%d is not sorted", vetNum);
//         vetPrint(vet);
        exit(1);
    }
}

void runCheckIsSorted(int** mat) {
    cout << "\n---Checking if is sorted";

    for (int i = 0; i < vetCount; i++) {
        checkIsSorted(mat[i], i);
//         printf("\ni %d mat[i] %d &mat[i][0] %d",i , mat[i], &mat[i][0]);
    }
    cout << "\n---";
}

void sanityCheckVetEqual(int *vetA, int *vetAux, int vetNum) {
    for (int i = 0; i < vetSize; i++) {
        if (vetA[i] != vetAux[i]) {
            printf("\nvetA%d != vetAux%d", vetNum, vetNum);
            return;
        }
    }

    printf("\n---vetA%d == vetAux%d", vetNum, vetNum);
}

// TODO type 1 crescent, 2 decrescent and 3 random
void fillVets(int** mat) {
    const int range_from = 1;
    const int range_to = 2147483647;
//     const int range_to = 100;

    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(range_from, range_to);
//     cout << distr(generator) << '\n';

//     printf("\n vetSize %d vetCount %d", vetSize, vetCount);
    for (int i = 0; i < vetCount; i++) {
        for (int j = 0; j < vetSize; j++) {
            mat[i][j] = distr(generator);
        }

//         cout << "\nmat[i]" << i<< "\n";
//         vetPrint(mat[i]);
    }

//     matPrint(mat);
}

void copyArg1toArg2(int **mat1, int **mat2) {
    for (int i = 0; i < vetCount; i++) {
        for (int j = 0; j < vetSize; j++) {
            mat2[i][j] = mat1[i][j];
        }
    }

    for (int i = 0; i < vetCount; i++) {
        sanityCheckVetEqual(mat1[i], mat2[i], i);
    }

    cout << "\n---";
}

// mergesort top-down //----------------------------------------------------------------------------

// v: vetor sendo ordenado, aux: vetor auxiliar
// inf: posicao inferior sendo trabalhada
// med: posicao mediana, sup: posicao superior
void merge(int *vet, int *aux , int inf , int med, int sup) {
    for (int k = inf; k <= sup; k++) {
        aux[k] = vet[k]; // copia dos valores para auxiliar
    }

    int i = inf, j = med + 1;
    for ( int k = inf; k <= sup ; k++) {
        if (i > med) { // se sub vetor da direita terminou
            vet[k] = aux[j++];
        } else if (j > sup) { // se sub vetor da esquerda terminou
            vet[k] = aux[i++];
        } else { // senão, compara e copia o menor valor
            if (aux[j] < aux [i]) {
                vet[k] = aux[j++];
            } else {
                vet[k] = aux[i++];
            }
        }
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

void mergesort(int *vet) {
    int *aux = new int[vetSize];

    sort(vet, aux, 0, vetSize - 1);

    delete []aux;
}

// insertionSort //---------------------------------------------------------------------------------
void insertionSort(int *vet) {
//     int n = vetSize;
    for(int j = 1; j < vetSize; j++) {
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

// mergesort top-down + insertionSort //------------------------------------------------------------

void insertionSortM(int *vet, int low, int high) {
//     int n = vetSize;

//     cout << "\n insertionSortM low " << low << " high " << high << "\n";
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

void sortI(int *vet, int *aux, int inf, int sup, int threshold) {
    if (sup <= inf) {
        return;
    }

    if ((sup - inf) > threshold) {
        int med = inf + (sup - inf) / 2;

        sortI(vet, aux, inf, med, threshold);
        sortI(vet, aux, med + 1, sup, threshold);

        merge(vet, aux, inf, med, sup);
    } else {
        insertionSortM(vet, inf, sup + 1);
    }
}

void mergesortTpInsertionSort(int *vet, int threshold) {
    int *aux = new int[vetSize];

    sortI(vet, aux, 0, vetSize - 1, threshold);
//   sort(vet, aux, 0, vetSize - 1);

    delete []aux;
}

// mergesort bottom-up //---------------------------------------------------------------------------

void mergesortBottomUp(int *vet) {
    int n = vetSize;
//     int aux[vetSize];
//     TODO
    int *aux = new int[vetSize];

    // tamanho dobra a cada iteração
    for (int tam = 1; tam < n; tam = tam + tam) {
        for (int inf = 0; inf < n - tam; inf += tam + tam) {
            // sub vetor à esquerda em [inf, inf + tam - 1]
            // sub vetor à direita em [inf + tam, inf + tam + tam - 1]
            // ou , se necessário , em [inf + tam, n - 1]

            merge (vet, aux, inf, inf + tam - 1, min(inf + tam + tam - 1, n - 1));
        }
    }

    delete[] aux;
}

// run<sort algoritm> //----------------------------------------------------------------------------

// 1 run mergeSort
// 2 run mergesortBottomUp
// 3 run mergesortTpInsertionSort with X as threshold
void runAlgoritms(int **mat, int threshold, int typeSort) {
    switch(typeSort) {
      case 1:
         cout << "\n# mergesort top-down";
         break;
      case 2:
         cout << "\n# mergesortBottomUp";
         break;
      case 3:
         cout << "\n# mergesortTpInsertionSort with X as " << threshold;
         break;
    }

    auto start = chrono::steady_clock::now();
    for (int i = 0; i < vetCount; i++) {
        switch(typeSort) {
        case 1:
            mergesort(mat[i]);
            break;
        case 2:
            mergesortBottomUp(mat[i]);
            break;
        case 3:
            mergesortTpInsertionSort(mat[i], threshold);
            break;
        }

    }
    auto end = chrono::steady_clock::now();

    runCheckIsSorted(mat);
    cout << "\nElapsed time in ms: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "\n";
}

// run tests of sorting //--------------------------------------------------------------------------

void runTest(int **matA, int** matAux) {
    int valueX[] = {10, 20, 40, 80, 160, 320, 640};
//     int valueX[] = {100, 200, 400, 800, 1600, 3200, 6400};
//     int valueX[] = {1000, 2000, 4000, 8000, 16000, 32000, 64000};
//     int valueX[] = {49999, 49999, 49999, 49999, 49999, 49999, 49999};
    int countValuesX = 7;

    cout << "\n---Fill the matrix A\n---";
    fillVets(matA);

    cout << "\n---Copy matA to matAux\n---";
    copyArg1toArg2(matA, matAux);

//  runAlgoritms(int **mat, int threshold, int typeSort)
    runAlgoritms(matA, 0, 1); // run mergeSort

    cout << "\n---Copy matAux to matA\n---";
    copyArg1toArg2(matAux, matA);

    runAlgoritms(matA, 0, 2); // run mergesortBottomUp

    for (int i = 0; i < countValuesX; i++) {
        cout << "\n---Copy matAux to matA\n---";
        copyArg1toArg2(matAux, matA);

        runAlgoritms(matA, valueX[i], 3); // run mergesortTpInsertionSort with threshold valueX[i]
    }

}

void compareMergexInsert() {

    int vet1[1000];
    int vet2[1000];

    cout << "\n\n--Copy matAux to matA";
//     copyAtoB2(matAux, matA);

    cout << "\n# insertionSort for one vet only\n";
    auto start = chrono::steady_clock::now();

//     insertionSort(matA[1]);

    auto end = chrono::steady_clock::now();
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
}

int main(){
//     int numT = 10;
    int numT = 1;

    int **matA; // mat[vetCount][vetSize]
    matA = new int* [vetCount];
    for(int i = 0; i < vetCount; i++){
        matA[i] = new int[vetSize];
    }

//  mat[vetCount][vetSize] => mat[10][5000000]
//
//  col    1 2 3  ... vetCount
//  row 1 |X|X|X| ...
//  row 2 |X|X|X| ...
//  row 3 |X|X|X| ...
//  ...
//   vetCount

    int **matAux;
    matAux = new int* [vetCount];
    for(int i = 0; i < vetCount; i++){
        matAux[i] = new int[vetSize];
    }

    cout << "\n# Starting tests\n";
    for(int t =0; t < numT; t++) {
        printf("\n# Running test %d of %d\n", t+1, numT);
        runTest(matA, matAux);
    }
    cout << "\n# End of tests\n";

    for(int i = 0; i < vetCount; i++){
        delete[] matA[i];
    }
    delete[] matA;

    for(int i = 0; i < vetCount; i++){
        delete[] matAux[i];
    }
    delete[] matAux;

    return 0;
}
