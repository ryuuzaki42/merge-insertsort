#include <iostream> // cout
#include <random> // random device
#include <chrono> // time chrono

using namespace std;

int vetCountL; // Count of "vectors"
int vetSizeC; // Size of each vector
int numTest; // Number of tests

// general purpose functions //---------------------------------------------------------------------

void vetPrint(int *vet) {
    for (int i = 0; i < vetSizeC; i++) {
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
    for (int i = 0; i < vetCountL; i++) {
        printf("\n");
        for (int j = 0; j < vetSizeC; j++ ) {
            printf("i %d j %d vet[i][j] %d\n", i, j, mat[i][j]);
        }
    }
}

void checkIsSorted (int *vet, int vetNum) {
    bool check = true;
    for(int i = 0; i < vetSizeC - 1; i++) {
        if (vet[i] > vet[i+1]) {
            printf("\nvet[%d] > vet[%d] - %d > %d\n", i, i+1, vet[i], vet[i+1]);
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

    for (int i = 0; i < vetCountL; i++) {
        checkIsSorted(mat[i], i);
//         printf("\ni %d mat[i] %d &mat[i][0] %d",i , mat[i], &mat[i][0]);
    }
    cout << "\n---";
}

void sanityCheckVetEqual(int *vetA, int *vetAux, int vetNum) {
    for (int i = 0; i < vetSizeC; i++) {
        if (vetA[i] != vetAux[i]) {
            printf("\nvetA%d != vetAux%d", vetNum, vetNum);
            return;
        }
    }

    printf("\n---vetA%d == vetAux%d", vetNum, vetNum);
}

// Type num random
void fillVetsRandom(int** mat) {
    const int range_from = 1;
//     const int range_to = 100;
    const int range_to = 2147483647;

    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution <int> distr(range_from, range_to);
//     cout << distr(generator) << '\n';

    for (int i = 0; i < vetCountL; i++) {
        for (int j = 0; j < vetSizeC; j++) {
            mat[i][j] = distr(generator);
        }

//         cout << "\nmat[i]" << i<< "\n";
//         vetPrint(mat[i]);
    }

//     matPrint(mat);
}

// Type num crescent
void fillVetsCrescent(int** mat) {
    int tmp = 1;
    for (int i = 0; i < vetCountL; i++) {
        for (int j = 0; j < vetSizeC; j++) {
            mat[i][j] = tmp;
            tmp++; // < INT_MAX, 6500000 * 10
        }

//         cout << "\nmat[i]" << i<< "\n";
//         vetPrint(mat[i]);
    }

//     matPrint(mat);
}

// Type num decrescent
void fillVetsDecrescent(int** mat) {
    int tmp = 2147483647;
    for (int i = 0; i < vetCountL; i++) {
        for (int j = 0; j < vetSizeC; j++) {
            mat[i][j] = tmp;
            tmp--; // > 0, 6500000 * 10
        }

//         cout << "\nmat[i]" << i<< "\n";
//         vetPrint(mat[i]);
    }

//     matPrint(mat);
}

void copyArg1toArg2(int **mat1, int **mat2) {
    for (int i = 0; i < vetCountL; i++) {
        for (int j = 0; j < vetSizeC; j++) {
            mat2[i][j] = mat1[i][j];
        }
    }

    for (int i = 0; i < vetCountL; i++) {
        sanityCheckVetEqual(mat1[i], mat2[i], i);
    }
    cout << "\n---";
}

// mergesort top-down //----------------------------------------------------------------------------

// v: vetor sendo ordenado, aux: vetor auxiliar
// inf: posicao inferior sendo trabalhada
// med: posicao mediana, sup: posicao superior
void merge(int *vet, int *aux, int inf, int med, int sup) {
    for (int k = inf; k <= sup; k++) {
        aux[k] = vet[k]; // copia dos valores para auxiliar
    }

    int i = inf, j = med + 1;
    for (int k = inf; k <= sup; k++) {
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

void mergesortTopDown(int *vet, int size) {
    int *aux = new int[size];

    sort(vet, aux, 0, size - 1);

    delete []aux;
}

// insertionSort //---------------------------------------------------------------------------------

// Estilo ordenar cartas de baralho na mão
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

// mergesort top-down + insertionSort //------------------------------------------------------------

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

// mergesort bottom-up //---------------------------------------------------------------------------

void mergesortBottomUp(int *vet, int size) {
    int *aux = new int[size];

    // tamanho dobra a cada iteração
    for (int tam = 1; tam < size; tam = tam + tam) {
        for (int inf = 0; inf < size - tam; inf += tam + tam) {
            // sub vetor à esquerda em [inf, inf + tam - 1]
            // sub vetor à direita em [inf + tam, inf + tam + tam - 1]
            // ou , se necessário , em [inf + tam, size - 1]

            merge(vet, aux, inf, inf + tam - 1, min(inf + tam + tam - 1, size - 1));
        }
    }

    delete[] aux;
}

// run <sort algoritm> //---------------------------------------------------------------------------

// 1 run mergeSort
// 2 run mergesortBottomUp
// 3 run mergesortTpInsertionSort with X as threshold
void runAlgoritms(int **mat, int threshold, int typeSort, int test, string typeNumString) {
    string algoritm;
    switch(typeSort) {
      case 1:
         cout << "\n# mergesortTopDown";
         algoritm = "mergesortTopDown";
         break;
      case 2:
         cout << "\n# mergesortBottomUp";
         algoritm = "mergesortBottomUp";
         break;
      case 3:
         cout << "\n# mergesortTopDownInsertionSort with X as " << threshold;
         algoritm = "mergesortTopDownInsertionSort_X_" + to_string(threshold);
         break;
      case 4:
         cout << "\n# insertionSort";
         algoritm = "insertionSort";
         break;
    }

    auto start = chrono::steady_clock::now();
    for (int i = 0; i < vetCountL; i++) {
        switch(typeSort) {
        case 1:
            mergesortTopDown(mat[i], vetSizeC);
            break;
        case 2:
            mergesortBottomUp(mat[i], vetSizeC);
            break;
        case 3:
            mergesortTopDownInsertionSort(mat[i], vetSizeC, threshold);
            break;
        case 4:
            insertionSort(mat[i], vetSizeC);
            break;
        }
    }
    auto end = chrono::steady_clock::now();

//  runCheckIsSorted(int** mat)
    runCheckIsSorted(mat);

    cout << "\n"<< test << " " << typeNumString << " run of " << algoritm << " elapsed time in ms: "
        << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "\n";
}

// run tests of sorting //--------------------------------------------------------------------------

void runTestTmp(int **matA, int** matAux, int test, int typeNum) {
    int valueX[] = {10, 20, 40, 80, 160, 320, 640};
    int countValuesX = 7;

    string typeNumString;
    cout << "\n---Fill the matrix A\n---";
    if (typeNum == 1) {
        cout << "\nFill with random numbers";
        typeNumString = "random";
        fillVetsRandom(matA);

    } else if (typeNum == 2) {
        cout << "\nFill with decrescent numbers";
        typeNumString = "decrescent";
        fillVetsDecrescent(matA);

    } else if (typeNum == 3) {
        cout << "\nFill with crescent numbers";
        typeNumString = "crescent";
        fillVetsCrescent(matA);
    }

    cout << "\n---Copy matA to matAux\n---";
    copyArg1toArg2(matA, matAux);

//  runAlgoritms(int **mat, int threshold, int typeSort)
    runAlgoritms(matA, 0, 1, test, typeNumString); // run mergesortTopDown

    cout << "\n---Copy matAux to matA\n---";
    copyArg1toArg2(matAux, matA);

    runAlgoritms(matA, 0, 2, test, typeNumString); // run mergesortBottomUp

    for (int i = 0; i < countValuesX; i++) {
        cout << "\n---Copy matAux to matA\n---";
        copyArg1toArg2(matAux, matA);

        // run mergesortTpInsertionSort with threshold valueX[i]
        runAlgoritms(matA, valueX[i], 3, test, typeNumString);
    }

//------------------------------------------------------------------------//
    cout << "\n---Copy matAux to matA\n---";
    copyArg1toArg2(matAux, matA);

    // Warning sort large vectors with insertionSort can take long time
    runAlgoritms(matA, 0, 4, test, typeNumString); // run insertionSort
//------------------------------------------------------------------------//
}

int** createMat(int** mat) {
    mat = new int* [vetCountL];
    for(int i = 0; i < vetCountL; i++){
        mat[i] = new int[vetSizeC];
    }

    return mat;
}

int** deleteMat(int** mat) {
    for(int i = 0; i < vetCountL; i++) {
        delete[] mat[i];
    }
    delete[] mat;

    return mat;
}

void runTest(int typeNum) {
    cout << "\nCount of vector to sort (vetCountL): " << vetCountL;
    cout << "\nSize of each vector to sort (vetSizeC): " << vetSizeC;
    cout << "\nNumber of tests (numTest): " << numTest << "\n";

    int **matA; // mat[vetCountL][vetSizeC]
    matA = createMat(matA);

//  mat[vetCountL][vetSizeC] => mat[10][5000000]
//
//  col    1 2 3  ... vetSizeC
//  row 1 |X|X|X| ...
//  row 2 |X|X|X| ...
//  row 3 |X|X|X| ...
//  ...
//   vetCountL

    int **matAux;
    matAux = createMat(matA);

    cout << "\n# Starting tests\n";
    for(int test = 1; test <= numTest; test++) {
        printf("\n# Running test %d of %d\n", test, numTest);
        runTestTmp(matA, matAux, test, typeNum);
    }
    cout << "\n# End of tests\n";

    matA = deleteMat(matA);
    matAux = deleteMat(matAux);
}

int main(int argc, char** argv) {
//     ./a.out 10 6500000 10 > results/resultsAll

    if (argc < 4) {
        cout << "\nNeed 3 parameters\n";
        cout << argv[0] << " a b c";

        cout << "\n\nExample:";
        cout << "\n" << argv[0] << " 10 6500000 10";
        cout << "\nCount of vector to sort (vetCountL): 10";
        cout << "\nSize of each vector to sort (vetSizeC): 65000";
        cout << "\nNumber of tests (numTest): 10\n\n";
    } else {
        vetCountL = stoi(argv[1]);
        vetSizeC =  stoi(argv[2]);
        numTest =  stoi(argv[3]);

//         cout << "\nvetCountL " << vetCountL;
//         cout << "\nvetSizeC " << vetSizeC;
//         cout << "\nnumTest " << numTest;

        runTest(1); // typeNum 1 random numbers
        runTest(2); // typeNum 2 decrescent numbers
        runTest(3); // typeNum 3 crescent numbers
    }

    return 0;
}
