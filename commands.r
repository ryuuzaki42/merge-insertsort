
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
    ./a.out > results.txt

## Clean sanity checks from results.txt
    cat results.txt | grep -v "\-\-\-"

## Clean sanity checks from results.txt and save in resultsClean
    cat results.txt | grep -v "\-\-\-" > resultsClean
