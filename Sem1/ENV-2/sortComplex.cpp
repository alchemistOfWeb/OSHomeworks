#include "sortComplex.h"

void sortComplex(ComplexNumber* complexArray, int arraySize) {
    for (int i=0; i < arraySize; i++) {
        for (int j=0; j < arraySize-i-1; j++) {
	    if (complexArray[j] > complexArray[j+1]) {
	        ComplexNumber tmp = complexArray[j];
		complexArray[j] = complexArray[j+1];
		complexArray[j+1] = tmp;
	    }
	}
    }
}
