#include <iostream>
#include "ComplexNumber.h"
#include "sortComplex.h"

int main() {
    const int ARR_SIZE = 4;
    ComplexNumber arr[ARR_SIZE];
    arr[0] = ComplexNumber(1, 3);
    arr[1] = ComplexNumber(3, 1);
    arr[2] = ComplexNumber(2, 2);
    arr[3] = ComplexNumber(1, 0);
    
    for (int i=0; i<ARR_SIZE; i++) {
        std::cout << i << " : " << arr[i] << std::endl;
    }
   
    sortComplex(arr, ARR_SIZE);
     
    for (int i=0; i<ARR_SIZE; i++) {
        std::cout << i << " : " << arr[i] << std::endl;
    }
   
    return 0;
}

