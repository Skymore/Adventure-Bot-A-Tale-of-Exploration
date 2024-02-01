#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static DynamicArray **globalArrayTracker = NULL;
static int globalArrayCount = 0;

/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;
    globalArrayTracker = (DynamicArray **) realloc(globalArrayTracker, (globalArrayCount + 1) * sizeof(DynamicArray *));
    globalArrayTracker[globalArrayCount++] = da;

    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    return;
}

int DynamicArray_num_arrays(void) {
    return globalArrayCount;
}

void DynamicArray_destroy_all(void) {
    for (int i = 0; i < globalArrayCount; i++) {
        if (globalArrayTracker[i] != NULL) {
            DynamicArray_destroy(globalArrayTracker[i]);
        }
    }
    free(globalArrayTracker);
    globalArrayTracker = NULL;
    globalArrayCount = 0;
}

int DynamicArray_is_valid(const DynamicArray * da) {
    for (int i = 0; i < globalArrayCount; i++) {
        if (globalArrayTracker[i] == da) {
            return da->buffer != NULL? 1 : 0;
        }
    }
    return 0;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;

    for (int i = 0; i < globalArrayCount; i++) {
        if (globalArrayTracker[i] == da) {
            globalArrayTracker[i] = NULL;
            break;
        }
    }
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, DynamicArray_size(da)-1);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, 0);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_new();
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(da, i)));
    }
    return result;
}

DynamicArray * DynamicArray_subarray(DynamicArray * da, int a, int b) {

  assert(da->buffer != NULL);
  assert(b >= a);

  DynamicArray * result = DynamicArray_new();

  for (int i=a; i<b; i++) {
      DynamicArray_push(result,DynamicArray_get(da, i));
  }

  return result;

}

double DynamicArray_min(const DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double min_val = da->buffer[da->origin];
    for (int i = 1; i < DynamicArray_size(da); i++) {
        double val = DynamicArray_get(da, i);
        if (val < min_val) {
            min_val = val;
        }
    }
    return min_val;
}

double DynamicArray_max(const DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double max_val = da->buffer[da->origin];
    for (int i = 1; i < DynamicArray_size(da); i++) {
        double val = DynamicArray_get(da, i);
        if (val > max_val) {
            max_val = val;
        }
    }
    return max_val;
}

double DynamicArray_mean(const DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double sum = 0;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        sum += DynamicArray_get(da, i);
    }
    return sum / DynamicArray_size(da);
}

int compare(const void * a, const void * b) {
    double diff = *(double*)a - *(double*)b;
    return (diff > 0) - (diff < 0);
}

double DynamicArray_median(const DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double *sorted = (double*) malloc(DynamicArray_size(da) * sizeof(double));
    for (int i = 0; i < DynamicArray_size(da); i++) {
        sorted[i] = DynamicArray_get(da, i);
    }
    qsort(sorted, DynamicArray_size(da), sizeof(double), compare);
    double median;
    if (DynamicArray_size(da) % 2 == 0) {
        median = (sorted[DynamicArray_size(da) / 2 - 1] + sorted[DynamicArray_size(da) / 2]) / 2;
    } else {
        median = sorted[DynamicArray_size(da) / 2];
    }
    free(sorted);
    return median;
}

double DynamicArray_sum(const DynamicArray * da) {
    double sum = 0;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        sum += DynamicArray_get(da, i);
    }
    return sum;
}

double DynamicArray_first(const DynamicArray * da) {
    assert(DynamicArray_size(da) > 0); 
    return DynamicArray_get(da, 0); 
}

double DynamicArray_last(const DynamicArray * da) {
    assert(DynamicArray_size(da) > 0); 
    return DynamicArray_get(da, DynamicArray_size(da) - 1); 
}

DynamicArray * DynamicArray_copy(const DynamicArray * da) {
    assert(da != NULL);

    DynamicArray * copy = DynamicArray_new(); 
    assert(copy != NULL);

    copy->capacity = da->capacity;
    copy->origin = da->origin;
    copy->end = da->end;

    copy->buffer = (double *) calloc(copy->capacity, sizeof(double));
    assert(copy->buffer != NULL);

    for (int i = 0; i < DynamicArray_size(da); i++) {
        copy->buffer[index_to_offset(copy, i)] = DynamicArray_get(da, i);
    }

    return copy;
}

DynamicArray * DynamicArray_range(double start, double end, double step) {
    assert(step != 0);

    DynamicArray * rangeArray = DynamicArray_new();
    assert(rangeArray != NULL);

    if (step > 0) { // Handle positive step
        for (double i = start; i < end; i += step) {
            DynamicArray_push(rangeArray, i);
        }
    } else { // Handle negative step
        for (double i = start; i > end; i += step) {
            DynamicArray_push(rangeArray, i);
        }
    }

    return rangeArray;
}

DynamicArray * DynamicArray_concat(const DynamicArray * da1, const DynamicArray * da2) {
    assert(da1 != NULL && da2 != NULL);

    DynamicArray * concatenated = DynamicArray_new();
    assert(concatenated != NULL);

    for (int i = 0; i < DynamicArray_size(da1); i++) {
        DynamicArray_push(concatenated, DynamicArray_get(da1, i));
    }

    for (int i = 0; i < DynamicArray_size(da2); i++) {
        DynamicArray_push(concatenated, DynamicArray_get(da2, i));
    }

    return concatenated;
}

DynamicArray * DynamicArray_take(const DynamicArray * da, int n) {
    assert(da != NULL);

    DynamicArray * subArray = DynamicArray_new();
    int size = DynamicArray_size(da);
    int actualSize = (abs(n) < size) ? abs(n) : size;
    int startIndex = (n > 0) ? 0 : size - actualSize;

    for (int i = 0; i < actualSize; i++) {
        DynamicArray_push(subArray, DynamicArray_get(da, startIndex + i));
    }

    for (int i = actualSize; i < abs(n); i++) {
        DynamicArray_push(subArray, 0.0);
    }

    return subArray;
}
