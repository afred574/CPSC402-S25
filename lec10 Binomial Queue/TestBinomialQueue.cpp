#include <iostream>
#include "BinomialQueue.h"

int main() {
    try {
        BinomialQueue<int> bq;

        int inputSequence[] = {7, 5, 10, 12, 3, 11, 13, 2};
        int n = sizeof(inputSequence) / sizeof(inputSequence[0]);

        std::cout << "=== Inserting elements into Binomial Queue ===\n";

        for (int i = 0; i < n; ++i) {
            std::cout << "Inserting: " << inputSequence[i] << std::endl;
            bq.insert(inputSequence[i]);

            std::cout << "Current Min: " << bq.findMin() << std::endl;

            bq.printTrees();
            std::cout << "============================\n";
        }

        std::cout << "\n=== Deleting all elements in order ===\n";
        while (!bq.isEmpty()) {
            int minVal;
            bq.deleteMin(minVal);
            std::cout << "Deleted Min: " << minVal << std::endl;
        }

    } catch (const UnderflowException& e) {
        std::cerr << "Error: Queue is empty.\n";
    }

    return 0;
}
