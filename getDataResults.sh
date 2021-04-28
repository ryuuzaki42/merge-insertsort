#!/bin/bash
# Get the clean and selected results

cat results.txt | grep -v "\-\-\-" > res/resultsClean

cd res/

cat resultsClean | grep -E "run of mergesortTopDown" > mergesortTopDown

cat resultsClean | grep "run of mergesortBottomUp" > mergesortBottomUp

cat resultsClean | grep "run of mergesortTpInsertionSort_X_10" > mergesortTpInsertionSort_X_010
cat resultsClean | grep "run of mergesortTpInsertionSort_X_20" > mergesortTpInsertionSort_X_020
cat resultsClean | grep "run of mergesortTpInsertionSort_X_40" > mergesortTpInsertionSort_X_040
cat resultsClean | grep "run of mergesortTpInsertionSort_X_80" > mergesortTpInsertionSort_X_080
cat resultsClean | grep "run of mergesortTpInsertionSort_X_160" > mergesortTpInsertionSort_X_160
cat resultsClean | grep "run of mergesortTpInsertionSort_X_320" > mergesortTpInsertionSort_X_320
cat resultsClean | grep "run of mergesortTpInsertionSort_X_640" > mergesortTpInsertionSort_X_640

cat mergesortTopDown > resultsFinal
echo "" >>  resultsFinal
cat mergesortBottomUp >> resultsFinal
echo "" >>  resultsFinal
cat mergesortTpInsertionSort_X_010 >> resultsFinal
echo "" >>  resultsFinal
cat mergesortTpInsertionSort_X_020 >> resultsFinal
echo "" >>  resultsFinal
cat mergesortTpInsertionSort_X_040 >> resultsFinal
echo "" >>  resultsFinal
cat mergesortTpInsertionSort_X_080 >> resultsFinal
echo "" >>  resultsFinal
cat mergesortTpInsertionSort_X_160 >> resultsFinal
echo "" >>  resultsFinal
cat mergesortTpInsertionSort_X_320 >> resultsFinal
echo "" >>  resultsFinal
cat mergesortTpInsertionSort_X_640 >> resultsFinal

cat resultsFinal | grep -E "random|$^" > resultsFinalRandom
cat resultsFinal | grep -E " crescent|$^" > resultsFinalCrescent
cat resultsFinal | grep -E " decrescent|$^" > resultsFinalDecrescent
