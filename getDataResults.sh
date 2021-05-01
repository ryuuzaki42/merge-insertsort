#!/bin/bash
# Get the clean and selected results
cd results/

cat resultsAll | grep -v "\-\-\-" > resultsClean

cat resultsClean | grep -E "run of mergesortTopDown " > mergesortTopDown

cat resultsClean | grep "run of mergesortBottomUp " > mergesortBottomUp

cat resultsClean | grep "run of mergesortTopDownInsertionSort_X_10 " > mergesortTopDownInsertionSort_X_010
cat resultsClean | grep "run of mergesortTopDownInsertionSort_X_20 " > mergesortTopDownInsertionSort_X_020
cat resultsClean | grep "run of mergesortTopDownInsertionSort_X_40 " > mergesortTopDownInsertionSort_X_040
cat resultsClean | grep "run of mergesortTopDownInsertionSort_X_80 " > mergesortTopDownInsertionSort_X_080
cat resultsClean | grep "run of mergesortTopDownInsertionSort_X_160 " > mergesortTopDownInsertionSort_X_160
cat resultsClean | grep "run of mergesortTopDownInsertionSort_X_320 " > mergesortTopDownInsertionSort_X_320
cat resultsClean | grep "run of mergesortTopDownInsertionSort_X_640 " > mergesortTopDownInsertionSort_X_640

cat resultsClean | grep "run of insertionSort " > insertionSort

cat mergesortTopDown > resultsFinal
echo "" >>  resultsFinal
cat mergesortBottomUp >> resultsFinal
echo "" >>  resultsFinal
cat mergesortTopDownInsertionSort_X_010 >> resultsFinal
echo "" >>  resultsFinal
cat mergesortTopDownInsertionSort_X_020 >> resultsFinal
echo "" >>  resultsFinal
cat mergesortTopDownInsertionSort_X_040 >> resultsFinal
echo "" >>  resultsFinal
cat mergesortTopDownInsertionSort_X_080 >> resultsFinal
echo "" >>  resultsFinal
cat mergesortTopDownInsertionSort_X_160 >> resultsFinal
echo "" >>  resultsFinal
cat mergesortTopDownInsertionSort_X_320 >> resultsFinal
echo "" >>  resultsFinal
cat mergesortTopDownInsertionSort_X_640 >> resultsFinal
echo "" >>  resultsFinal
cat insertionSort >> resultsFinal

cat resultsFinal | grep -E " random|$^" > resultsFinalRandom
cat resultsFinal | grep -E " crescent|$^" > resultsFinalCrescent
cat resultsFinal | grep -E " decrescent|$^" > resultsFinalDecrescent
