
#include <iostream>
#include <random>
#include <chrono>

// #define vetSize 50000
#define vetSize 50000
#define THRESHOLD 640

using namespace std;

// v : vetor sendo ordenado, aux : vetor auxiliar
// inf : posicao inferior sendo trabalhada
// med : posicao mediana, sup : posicao superior
void merge(int *v, int *aux , int inf , int med, int sup) {
    for (int k = inf; k <= sup; k++){
        aux [k] = v [k]; // copia dos valores para auxiliar
    }

    int i = inf, j = med + 1;
    for ( int k = inf; k <= sup ; k++) {
        if (i > med) { // se sub vetor da direita terminou
            v [k] = aux [j++];
        } else if (j > sup) { // se sub vetor da esquerda terminou
            v[k] = aux [i++];
        } else { // senão, compara e copia o menor valor
            if (aux[j] < aux [i]) {
                v [k] = aux[j++];
            } else {
                v [k] = aux [i++];
            }
        }
    }
}

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

void sort(int *v, int *aux, int inf, int sup){
    if (sup <= inf)
        return;

    int med = inf + (sup - inf) / 2;

    sort(v, aux, inf, med);
    sort(v, aux, med + 1, sup);
    merge(v, aux, inf, med, sup);
}

void mergesort(int * v) {
    int aux[vetSize];

    sort(v, aux, 0, vetSize - 1);
}

void insertionSortM(int *vetor, int low, int high) {
//     int n = vetSize;
    high++;

//     cout << "\n insertionSortM low " << low << " high " << high << "\n";
    for(int j = low; j < high; j++) {
        int chave = vetor[j];
        int i = j - 1;

        // procura lugar de insercao e desloca numero
        while(i >= low && vetor[i] > chave) {
            vetor[i + 1] = vetor[i];
            i = i - 1;
        }

        vetor[i + 1] = chave;
    }
}

void sortI(int *v, int *aux, int inf, int sup){
    if (sup <= inf)
        return;

//     cout << "\nsortI\n";
//     vetPrint(v);
//     cout << "\n-A-\n";

    if ((sup - inf) > THRESHOLD){
//         cout << "\n-mergesortI-\n";
        int med = inf + (sup - inf) / 2;

        sortI(v, aux, inf, med);
        sortI(v, aux, med + 1, sup);

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
        insertionSortM(v, inf, sup);
//         cout << "\nDepois\n";
//         vetPrint(v);
//         cout << "\n-----------------------------------------------------------------------\n";
    }
}


void mergesortI(int * v) {
    int aux[vetSize];

    sortI(v, aux, 0, vetSize - 1);
}


void insertionSort (int *vetor) {
    int n = vetSize;
    for(int j = 1; j < n; j++) {
        int chave = vetor[j];
        int i = j - 1;

        // procura lugar de insercao e desloca numero
        while(i >= 0 && vetor[i] > chave) {
            vetor[i + 1] = vetor[i];
            i = i - 1;
        }

        vetor[i + 1] = chave;
    }
}

void checkIsSorted (int *vet, char vetChar, int vetNum) {
    bool check = true;
    for(int i = 0; i < vetSize - 1; i++) {
        if (vet[i] > vet[i+1]) {
            check = false;
            break;
        }
    }

    if (check) {
        printf("Vet%c%d is sorted\n", vetChar, vetNum);
    } else {
        printf("Vet%c%d is not sorted\n", vetChar, vetNum);
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

void sanidadeVetIgual(int *vetA, int *vetB, int vetNum) {
    for (int i = 0; i < vetSize; i++) {
        if (vetA[i] != vetB[i]) {
            printf("VetA%d != VetB%d\n", vetNum, vetNum);
            return;
        }
    }

    printf("VetA%d == VetB%d\n", vetNum, vetNum);
}

void preencheVet(int *vetA, int *vetB, int vetNum) {
    const int range_from = 1;
//     const int range_to = 2147483647;
    const int range_to = 9;

    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(range_from, range_to);

//   cout << distr(generator) << '\n';

    for (int i = 0; i < vetSize; i++) {
        vetA[i] = vetB[i] = distr(generator);
    }

    sanidadeVetIgual(vetA, vetB, vetNum);
}

int main() {
    int i, vetCount;
    vetCount = 10;

//     int vetA0[vetSize], vetA1[vetSize], vetA2[vetSize], vetA3[vetSize], vetA4[vetSize];
//     int vetA5[vetSize], vetA6[vetSize], vetA7[vetSize], vetA8[vetSize], vetA9[vetSize];
// 
//     int vetB0[vetSize], vetB1[vetSize], vetB2[vetSize], vetB3[vetSize], vetB4[vetSize];
//     int vetB5[vetSize], vetB6[vetSize], vetB7[vetSize], vetB8[vetSize], vetB9[vetSize];

    int vetA[vetSize][vetCount];
    int vetB[vetSize][vetCount];

//     int aux;
//     const int range_from = 1;
// //     const int range_to = 2147483647;
//     const int range_to = 9;
//
//     random_device rand_dev;
//     mt19937 generator(rand_dev());
//     uniform_int_distribution<int> distr(range_from, range_to);
// //   cout << distr(generator) << '\n';
//
//     for (int i = 0; i < vetSize; i++) {
//         aux = distr(generator);
//         vetA1[i] = vetA2[i] = vetA3[i] = aux;
//     }

//     preencheVet(vetA0, vetB0, 0);
//     preencheVet(vetA1, vetB1, 1);
//     preencheVet(vetA2, vetB2, 2);
//     preencheVet(vetA3, vetB3, 3);
//     preencheVet(vetA4, vetB4, 4);
//     preencheVet(vetA5, vetB5, 5);
//     preencheVet(vetA6, vetB6, 6);
//     preencheVet(vetA7, vetB7, 7);
//     preencheVet(vetA8, vetB8, 8);
//     preencheVet(vetA9, vetB9, 9);

    for (i = 0; i < vetCount; i++) {
        preencheVet(vetA[i], vetB[i], i);
    }
    cout << "\n";

//     vetPrint(vetA1);
//     insertionSortM(vetA1, 5, 9);
//     vetPrint(vetA1);
//     checkIsSorted(vetA1);

//     return 0;
//     vetPrint(vetA1);

    auto start = chrono::steady_clock::now();

    for (i = 0; i < vetCount; i++) {
        mergesort(vetA[i]);
    }

//     mergesort(vetA0);
//     mergesort(vetA1);
//     mergesort(vetA2);
//     mergesort(vetA3);
//     mergesort(vetA4);
//     mergesort(vetA5);
//     mergesort(vetA6);
//     mergesort(vetA7);
//     mergesort(vetA8);
//     mergesort(vetA9);

    auto end = chrono::steady_clock::now();

    for (i = 0; i < vetCount; i++) {
        checkIsSorted(vetA[i], 'A', i);
    }


//     checkIsSorted(vetA0, 'A', 0);
//     checkIsSorted(vetA1, 'A', 1);
//     checkIsSorted(vetA2, 'A', 2);
//     checkIsSorted(vetA3, 'A', 3);
//     checkIsSorted(vetA4, 'A', 4);
//     checkIsSorted(vetA5, 'A', 5);
//     checkIsSorted(vetA6, 'A', 6);
//     checkIsSorted(vetA7, 'A', 7);
//     checkIsSorted(vetA8, 'A', 8);
//     checkIsSorted(vetA9, 'A', 9);

    cout << "\n";

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

//     start = chrono::steady_clock::now();
// 
// //     selectionSort(vetA2);
// //     insertionSort(vetA2);
// 
//     end = chrono::steady_clock::now();
//     checkIsSorted(vetA2);
// 
//     elapsed_seconds = end - start;
//     cout << "Tempo gasto: " << elapsed_seconds.count() << " s\n";
// 
//     cout << "Elapsed time in nanoseconds: "
//         << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
//         << " ns" << endl;
// 
//     cout << "Elapsed time in microseconds: "
//         << chrono::duration_cast<chrono::microseconds>(end - start).count()
//         << " µs" << endl;
// 
//     cout << "Elapsed time in milliseconds: "
//         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
//         << " ms" << endl;
// 
//     cout << "Elapsed time in seconds: "
//         << chrono::duration_cast<chrono::seconds>(end - start).count()
//         << " sec";
// 
//     cout << "\n";

    start = chrono::steady_clock::now();

    for (i = 0; i < vetCount; i++) {
        mergesortI(vetB[i]);
    }

//     mergesortI(vetB0);
//     mergesortI(vetB1);
//     mergesortI(vetB2);
//     mergesortI(vetB3);
//     mergesortI(vetB4);
//     mergesortI(vetB5);
//     mergesortI(vetB6);
//     mergesortI(vetB7);
//     mergesortI(vetB8);
//     mergesortI(vetB9);

    end = chrono::steady_clock::now();

    for (i = 0; i < vetCount; i++) {
        checkIsSorted(vetB[i], 'B', i);
    }

//     checkIsSorted(vetB0, 'B', 0);
//     checkIsSorted(vetB1, 'B', 1);
//     checkIsSorted(vetB2, 'B', 2);
//     checkIsSorted(vetB3, 'B', 3);
//     checkIsSorted(vetB4, 'B', 4);
//     checkIsSorted(vetB5, 'B', 5);
//     checkIsSorted(vetB6, 'B', 6);
//     checkIsSorted(vetB7, 'B', 7);
//     checkIsSorted(vetB8, 'B', 8);
//     checkIsSorted(vetB9, 'B', 9);

    cout << "\n";

//     vetPrint(vetA3);

    elapsed_seconds = end - start;
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

    cout << "\n";

    return 0;
}
