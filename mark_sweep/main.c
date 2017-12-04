#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX 256

typedef enum{
    OBJ_INT,
    OBJ_PAIR
} ObjectType;

typedef struct _Object{
    ObjectType type;
    unsigned char marked;
    struct _Object *next;
    union {
        int value;
        struct {
            struct _Object *head;
            struct _Object *tail;
        };
    };
} Object;

typedef struct {
    Object *stack[STACK_MAX];
    Object *firstObject;
    int numObjects;
    int maxObjects;
    int stackSize;
} VM;

void assert(int condition, const char *message){
    if (!condition) {
        printf("%s\n", message);
        exit(1);
    }
}

VM *newVM(){
    VM *vm = malloc(sizeof(VM));
    vm->stackSize   = 0;
    vm->firstObject = NULL;
    vm->numObjects  = 0;
    vm->maxObjects  = 16;
    return vm;
}

void push(VM *vm, Object *value){
    assert(vm->stackSize < STACK_MAX, "stack overflow");
    vm->stack[vm->stackSize++] = value;
}

Object *pop(VM *vm){
    assert(vm->stackSize > 0, "stack underflow");
    return vm->stack[--vm->stackSize];
}

void mark(Object *object){
    if (object->marked) {
        return;
    }
    object->marked = 1;
    if (object->type == OBJ_PAIR) {
        mark(object->head);
        mark(object->tail);
    }
}

void markAll(VM *vm){
    for(int i = 0; i < vm->stackSize; i++){
        mark(vm->stack[i]);
    }
}

void sweep(VM *vm){
    Object **o = &vm->firstObject;
    while (*o) {
        if (!(*o)->marked) {
            Object *unreached = *o;
            *o = unreached->next;
            free(unreached);
            vm->numObjects--;
        } else {
            (*o)->marked = 0;
            o = &(*o)->next;
        }
    }
}

void gc(VM *vm){
    int numObjects = vm->numObjects;
    markAll(vm);
    sweep(vm);
    vm->maxObjects = vm->numObjects * 2;
    printf("Collected %d objects, %d remaining.\n",
            numObjects - vm->numObjects, vm->numObjects);   
}

Object *newObject(VM *vm, ObjectType type){
    if (vm->numObjects == vm->maxObjects) {
        gc(vm);
    }
    Object *object  = malloc(sizeof(Object));
    object->type    = type;
    object->marked  = 0;
    object->next    = vm->firstObject;
    vm->firstObject = object;
    vm->numObjects++;
    return object;
}

void pushInt(VM *vm, int value){
    Object *o = newObject(vm, OBJ_INT);
    o->value = value;
    push(vm, o);
}

Object *pushPair(VM *vm){
    Object *o = newObject(vm, OBJ_PAIR);
    o->tail = pop(vm);
    o->head = pop(vm);
    push(vm, o);
    return o;
}

void objectPrint(Object *object){
    switch (object->type) {
        case OBJ_INT:
            printf("%d", object->value);
            break;
        case OBJ_PAIR:
            printf("()");
            objectPrint(object->head);
            printf(", ");
            objectPrint(object->tail);
            break;

    }
}

void test1() {
    printf("Test 1: Objects on stack are preserved.\n");
    VM* vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);

    gc(vm);
    assert(vm->numObjects == 2, "Should have preserved objects.");
}

void test2() {
    printf("Test 2: Unreached objects are collected.\n");
    VM* vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);
    pop(vm);
    pop(vm);

    gc(vm);
    assert(vm->numObjects == 0, "Should have collected objects.");
}

void test3() {
    printf("Test 3: Reach nested objects.\n");
    VM* vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);
    pushPair(vm);
    pushInt(vm, 3);
    pushInt(vm, 4);
    pushPair(vm);
    pushPair(vm);

    gc(vm);
    assert(vm->numObjects == 7, "Should have reached objects.");
}

void test4() {
    printf("Test 4: Handle cycles.\n");
    VM* vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);
    Object* a = pushPair(vm);
    pushInt(vm, 3);
    pushInt(vm, 4);
    Object* b = pushPair(vm);

    a->tail = b;
    b->tail = a;

    gc(vm);
    assert(vm->numObjects == 4, "Should have collected objects.");
}

int main(int argc, const char * argv[]) {
    printf("begin\n");
    test1();
    test2();
    test3();
    test4();
    printf("end\n");
    return 0;
}
