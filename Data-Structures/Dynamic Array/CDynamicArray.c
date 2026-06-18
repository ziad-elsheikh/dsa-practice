#include <stdio.h>
#include <stdlib.h>
#define NEW_INT(val) ((object_t){.type = INTEGER, .data.v_int = val})
#define NEW_CHAR(val) ((object_t){.type = CHAR, .data.v_char = val})
#define NEW_FLOAT(val) ((object_t){.type = FLOAT, .data.v_float = val})
#define NEW_STRING(val) ((object_t){.type = STRING, .data.v_string = val})

typedef union{
	int v_int;
	float v_float;
	char v_char;
	char *v_string;
} object_data_t;

typedef enum{
	INTEGER,
	FLOAT,
	CHAR,
    STRING
} object_type_t;

typedef struct{
	object_data_t data;
	object_type_t type;
} object_t;

typedef struct DynamicArray{
    size_t size;
    size_t capacity;
    object_t *data;
} DynamicArray;


void reallocate(DynamicArray *array);
void append(DynamicArray *array, object_t value);
void printArray(DynamicArray *array);
DynamicArray initalizeDA();
void printStatus(DynamicArray *array);


int main(){
    DynamicArray A = initalizeDA();
    printStatus(&A);

    append(&A, NEW_INT(10));
    append(&A, NEW_INT(50));
    append(&A, NEW_INT(105));
    append(&A, NEW_CHAR('a'));
    append(&A, NEW_FLOAT(.05));
    append(&A, NEW_STRING("ziad"));

    printf("\nArray contents:\n");
    printArray(&A);
    
    printStatus(&A);

    free(A.data);
    return 0;
}
void menu(){
    printf("==========DYNAMIC ARRAY==========\n"); 
    printf("1. DISPLAY STATUS\n"); 
    printf("2. ADD AN ITEM TO THE LIST\n"); 
    printf("3. REMOVE AN ITEM FROM THE LIST\n"); 
    printf("4. EXIT\n"); 
}

void printStatus(DynamicArray *array){
    printf("==================\n");
    printf("current capacity: %d\n", array->capacity);
    printf("current usage: %d\n", array->size);
    printf("==================\n");
}

void reallocate(DynamicArray *array){   
    DynamicArray temp = {array->capacity, array->size, array->data};
    
    // reallocate
    array->capacity *= 2;
    // array->size += 1;
    array->data = (object_t *)malloc(array->capacity * sizeof(object_t));

    // move data
    for (int i = 0; i < temp.size; i++){
        array->data[i] = temp.data[i];
    }
    // free old array
    free(temp.data);
}

bool isAvailable(DynamicArray *array){
    return array->size < array->capacity;
}

void append(DynamicArray *array, object_t value){
    if (!isAvailable(array)){
        reallocate(array);
    }
    array->data[array->size] = value;
    array->size++;
}

void printArray(DynamicArray *array){
    for (int i =0; i < array->size; i++){
        switch(array->data[i].type){
            case INTEGER:
                printf("element-%d is %d\n",i, array->data[i].data.v_int);
                break;
            case FLOAT:
                printf("element-%i is %.f\n",i, array->data[i].data.v_float);
                break;
            case CHAR:
                printf("element-%i is %c\n",i, array->data[i].data.v_char);
                break;
            case STRING:
                printf("element-%i is %s\n",i, array->data[i].data.v_string);
                break;
        }
    }
}

DynamicArray initalizeDA(){
    DynamicArray A;
    A.size = 0;
    A.capacity = 5;
    A.data = (object_t *)malloc(A.capacity * sizeof(object_t));
    return A;
}