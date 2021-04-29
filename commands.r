
## To compile
    g++ code.cpp

    # or
    g++ code.cpp -Wall -Wextra -Wpedantic

    # or
    g++ code.cpp -fsanitize=address

    # or
    g++ code.cpp -Wall -Wextra -Wpedantic -fsanitize=address

## Run:
    ./a.out

## Run and save results
    ./a.out > results/resultsAll

## Clean sanity checks from resultsAll
    cat results/resultsAll | grep -v "\-\-\-"
