
#include <iostream>
#include <random>
#include <chrono>

// #define vetSize 50000
#define vetSize 10
// #define vetCount 10
#define vetCount 4

using namespace std;

//--------------------------------------------------------------------------------------------------------
// Funções gerais

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



void vetMat(int vet[vetSize][vetCount]) {
    for (int i = 0; i < vetSize; i++) {
        printf("\n");
        for ( int j = 0; j < vetCount; j++ ) {

//             if (j < 10) {
//                 cout << "0000";
//             } else if (j < 100) {
//                 cout << "000";
//             } else if (j < 1000) {
//                 cout << "00";
//             } else if (j < 10000) {
//                 cout << "0";
//             }

            printf("i %d j %d vet[i][j] %d\n", i , j, vet[i][j]);
        }
    }
}

void checkIsSorted (int *vet, int vetNum) {
    bool check = true;
    for(int i = 0; i < vetSize - 1; i++) {
        if (vet[i] > vet[i+1]) {
            printf("\nvet[i] > vet[i+1] - vet[%d] > vet[%d] - %d > %d\n",i, i+1, vet[i], vet[i+1]);

            check = false;
            break;
        }
    }

    if (check) {
        printf("---VetA%d is sorted\n", vetNum);
    } else {
        printf("VetA%d is not sorted\n", vetNum);
        vetPrint(vet);
        exit(0);
    }
}

void runCheckIsSorted(int vet[vetSize][vetCount]) {
    cout << "---Checking if is sorterd\n";

    for (int i = 0; i < vetCount; i++) {
        checkIsSorted(vet[i], i);
    }

    cout << "---\n";
}

void TesteSanidadeVetIgual(int *vetA, int *vetAux, int vetNum) {
    for (int i = 0; i < vetSize; i++) {
        if (vetA[i] != vetAux[i]) {
            printf("VetA%d != VetAux%d\n", vetNum, vetNum);
            return;
        }
    }

    printf("---VetA%d == VetAux%d\n", vetNum, vetNum);
}

void fillVets(int vetA[vetSize][vetCount]) {
    const int range_from = 1;
//     const int range_to = 2147483647;
    const int range_to = 100;
//     const int range_to = 9;

    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(range_from, range_to);

//   cout << distr(generator) << '\n';

    printf("\n vetSize %d vetCount %d", vetSize, vetCount);
    for (int i = 0; i < vetSize; i++) {
        for (int j = 0; j < vetCount; j++) {
            printf("\ni %d j %d", i, j);
            int a = distr(generator);
            vetA[i][j] = a;

            cout << "\ndistr(generator) " << a;
//             vetA[i][j] = distr(generator);
        }

        cout << "\nvetA[i]" << i<< "\n";
        vetPrint(vetA[i]);
    }

    vetMat(vetA);
}

void copyArg1toArg2(int vet1[vetSize][vetCount], int vet2[vetSize][vetCount]) {
    for (int i = 0; i < vetSize; i++) {
        for (int j = 0; j < vetCount; j++) {
            vet2[i][j] = vet1[i][j];
        }
    }

    for (int i = 0; i < vetCount; i++) {
        TesteSanidadeVetIgual(vet1[i], vet2[i], i);
    }
}

void vetwPrint(chrono::duration<double> start, chrono::duration<double> end) {
    chrono::duration<double> elapsed_seconds = end - start;
    cout << "Tempo gasto: " << elapsed_seconds.count() << " s\n";

    cout << "Elapsed time in nanoseconds: "
        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
        << " ns" << endl;

    cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;

    cout << "Elapsed time in milliseconds: "
        << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << " ms" << endl;

    cout << "Elapsed time in seconds: "
        << chrono::duration_cast<chrono::seconds>(end - start).count()
        << " sec";
}

//////////////
void merge2(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // Create temp arrays
    int L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r]
 
    // Initial index of first subarray
    int i = 0;
 
    // Initial index of second subarray
    int j = 0;
 
    // Initial index of merged subarray
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
void mergeSort2(int arr[],int l,int r){
    if(l>=r){
        return;//returns recursively
    }
    int m =l+ (r-l)/2;
    mergeSort2(arr,l,m);
    mergeSort2(arr,m+1,r);
    merge2(arr,l,m,r);
}
//////////////

//--------------------------------------------------------------------------------------------------------
// mergesort top-down

// v: vetor sendo ordenado, aux: vetor auxiliar
// inf: posicao inferior sendo trabalhada
// med: posicao mediana, sup: posicao superior
void merge(int *v, int *aux , int inf , int med, int sup) {
    for (int k = inf; k <= sup; k++) {
        aux[k] = v[k]; // copia dos valores para auxiliar
    }

    int i = inf, j = med + 1;
    for ( int k = inf; k <= sup ; k++) {
        if (i > med) { // se sub vetor da direita terminou
            v[k] = aux[j++];
        } else if (j > sup) { // se sub vetor da esquerda terminou
            v[k] = aux[i++];
        } else { // senão, compara e copia o menor valor
            if (aux[j] < aux [i]) {
                v[k] = aux[j++];
            } else {
                v[k] = aux[i++];
            }
        }
    }
}

void sort(int *v, int *aux, int inf, int sup){
    if (sup <= inf) {
        return;
    }

    int med = inf + (sup - inf) / 2;

    sort(v, aux, inf, med);
    sort(v, aux, med + 1, sup);
    merge(v, aux, inf, med, sup);
}

void mergesort(int * v) {
    int aux[vetSize];

    sort(v, aux, 0, vetSize - 1);
}
//--------------------------------------------------------------------------------------------------------
// insertionSort

void insertionSort(int *vetor) {
//     int n = vetSize;
    for(int j = 1; j < vetSize; j++) {
        int chave = vetor[j];
        int i = j - 1;

        // procura lugar de insercao e desloca numero
        while(i >= 0 && vetor[i] > chave) {
            vetor[i + 1] = vetor[i];
            i--;
        }

        vetor[i + 1] = chave;
    }
}

//--------------------------------------------------------------------------------------------------------
// mergesort top-down + insertionSort

void insertionSortM(int *vetor, int low, int high) {
//     int n = vetSize;
//     high++;

//     cout << "\n insertionSortM low " << low << " high " << high << "\n";
    for(int j = low + 1; j < high; j++) {
        int chave = vetor[j];
        int i = j - 1;

        // procura lugar de insercao e desloca numero
        while(i >= low && vetor[i] > chave) {
            vetor[i + 1] = vetor[i];
            i--;
        }

        vetor[i + 1] = chave;
    }
}

void sortI(int *v, int *aux, int inf, int sup, int threshold){
    if (sup <= inf)
        return;

//     cout << "\nsortI\n";
//     vetPrint(v);
//     cout << "\n-A-\n";

    if ((sup - inf) > threshold){
//         cout << "\n-mergesortI-\n";
        int med = inf + (sup - inf) / 2;

        sortI(v, aux, inf, med, threshold);
        sortI(v, aux, med + 1, sup, threshold);

        merge(v, aux, inf, med, sup);
    } else {
//         cout << "\n-insertionSortM-\n";
//         sortI(v, aux, inf, med);
//         sortI(v, aux, med + 1, sup);
//         merge(v, aux, inf, med, sup);

//         cout << "\n-----------------------------------------------------------------------\n";
//         cout << "\nANTES\n";
//         vetPrint(v);
//         cout << "inf " << inf << " sup " << sup << "\n";
        insertionSortM(v, inf, sup + 1);
//         cout << "\nDepois\n";
//         vetPrint(v);
//         cout << "\n-----------------------------------------------------------------------\n";
    }
}

void mergesortI(int * v, int threshold) {
    int aux[vetSize];

    sortI(v, aux, 0, vetSize - 1, threshold);
}

//--------------------------------------------------------------------------------------------------------
// mergesort bottom-up

void mergesortBottomUp(int * v) {
    int n = vetSize;
    int aux[vetSize];

    // tamanho dobra a cada iteração
    for (int tam = 1; tam < n; tam = tam + tam) {
        for (int inf = 0; inf < n - tam; inf += tam + tam) {
            // sub vetor à esquerda em [inf, inf + tam - 1]
            // sub vetor à direita em [inf + tam, inf + tam + tam - 1]
            // ou , se necessário , em [inf + tam, n - 1]

            // TODO
            merge (v, aux, inf, inf + tam - 1, min(inf + tam + tam - 1, n - 1));
//             void merge(int *v, int *aux , int inf , int med, int sup) {
        }
    }
}
//--------------------------------------------------------------------------------------------------------

void runMergeSort(int vet[vetSize][vetCount]) {
    for (int i = 0; i < vetCount; i++) {
        mergesort(vet[i]);

//         mergeSort2(vet[i], 0, vetSize - 1);
    }
}

void runmergesortBottomUp(int vet[vetSize][vetCount]) {
    for (int i = 0; i < vetCount; i++) {
        mergesortBottomUp(vet[i]);
    }
}

void runmergesortInsertionSort(int vet[vetSize][vetCount], int threshold) {
    for (int i = 0; i < vetCount; i++) {
        mergesortI(vet[i], threshold);
    }
}

void runTest() {
    int i;
    int valueX[] = {10, 20, 40, 80, 160, 320, 640};
//     int valueX[] = {100, 200, 400, 800, 1600, 3200, 6400};
//     int valueX[] = {1000, 2000, 4000, 8000, 16000, 32000, 64000};
//     int valueX[] = {49999, 49999, 49999, 49999, 49999, 49999, 49999};
    int countValuesX = 7;

    int vetA[vetSize][vetCount]; // vetA[50000][10]
//     int vetB[vetSize][vetCount];
    int vetAux[vetSize][vetCount];


//     for (i = 0; i < vetCount; i++) {
//         preencheVet(vetA[i], vetB[i], i);
//     }
//     cout << "\n";

    cout << "\n---fill the vector\n";
    fillVets(vetA);
    copyArg1toArg2(vetA, vetAux);

//     cout << "\n--Copy vetB to vetAux";
//     copyAtoB2(vetA, vetAux);

//     for (i = 0; i < vetCount; i++) {
//         copyAtoB(vetB[i], vetAux[i]);
//     }

//     vetPrint(vetA1);
//     insertionSortM(vetA1, 5, 9);
//     vetPrint(vetA1);
//     checkIsSorted(vetA1);


    cout << "\n# mergesort\n";
    auto start = chrono::steady_clock::now();

//     for (i = 0; i < vetCount; i++) {
//         mergesort(vetA[i]);
//     }

//     runMergeSort(vetA);
//     runmergesortBottomUp(vetA);

    for (i = 0; i < vetCount; i++) {
        insertionSort(vetA[i]);
    }


    auto end = chrono::steady_clock::now();

//     for (i = 0; i < vetCount; i++) {
//         checkIsSorted(vetA[i], 'A', i);
//     }
//     cout << "\n";

    runCheckIsSorted(vetA);
    return;

//     chrono::duration<double> elapsed_seconds = end - start;
//     cout << "Tempo gasto: " << elapsed_seconds.count() << " s\n";

//     cout << "Elapsed time in nanoseconds: "
//         << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns\n";

//     cout << "Elapsed time in microseconds: "
//         << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs\n";

//     cout << "Elapsed time in milliseconds: "
//         << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";

    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";

//     cout << "Elapsed time in seconds: "
//         << chrono::duration_cast<chrono::seconds>(end - start).count() << " sec\n";

// //     selectionSort(vetA2);
// //     insertionSort(vetA2);


    cout << "\n---Copy vetA to vetAux\n";
    copyArg1toArg2(vetAux, vetA);

    cout << "\n# mergesortBottomUp\n";
    start = chrono::steady_clock::now();
    runmergesortBottomUp(vetA);
    end = chrono::steady_clock::now();

    runCheckIsSorted(vetA);

    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";

    for (i = 0; i < countValuesX; i++) {
//     for (i = 0; i < 1; i++) {
//         runCheckIsSorted(vetB, 'B');
//         runCheckIsSorted(vetAux, 'x');

        cout << "\n---Copy vetA to vetAux\n";
        copyArg1toArg2(vetAux, vetA);

        cout << "\n# mergesortInsertionSort with X as " << valueX[i] << "\n";
        start = chrono::steady_clock::now();

        runmergesortInsertionSort(vetA, valueX[i]);

        end = chrono::steady_clock::now();

        runCheckIsSorted(vetA);

        cout << "time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
    }

//     cout << "\n\n--Copy vetB to vetAux";
//     copyAtoB2(vetAux, vetB);
//     cout << "\n# insertionSort for one vet only\n";
//     start = chrono::steady_clock::now();
//
// //     for (i = 0; i < vetCount; i++) {
//     for (i = 0; i < 1; i++) {
// //         insertionSort(vetB[i]);
// //         insertionSortM(vetB[i], 0, vetSize - 1);
//     }
//
//     end = chrono::steady_clock::now();
//
//     runCheckIsSorted(vetB, 'B');
//
//     cout << "time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";

// no bounds check
// some help g++ a.cpp -fsanitize=address
//     for (i = 0; i < 20; i++) {
//         cout << "vetB[" << i << "] " << vetB[i] <<"\n";
//         cout << "vetB[" << i << "][0] " << &vetB[i][0] <<"\n";
//     }
}

int main(){
    int numT = 100;

    cout << "\nStrating tests";
    for(int t =0; t < numT; t++) {
        printf("\nRuning test %d of %d\n", t+1, numT);
        runTest();
    }
    cout << "\nEnd of tests\n";
}
