/*ram.c*/

//
// << This file implements a simple RAM (Random Access Memory) system for storing variables and their values >>
//
// << Hajo Wolfram >>
//
// Template: Prof. Joe Hummel
// Northwestern University
// CS 211
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // true, false
#include <string.h>
#include <assert.h>

#include "ram.h"


//
// Public functions:
//

//
// ram_init
//
// Returns a pointer to a dynamically-allocated memory
// for storing nuPython variables and their values. All
// memory cells are initialized to the value None.
//
struct RAM* ram_init(void) {
  struct RAM* ram = (struct RAM*)malloc(sizeof(struct RAM));
  
  ram->cells = (struct RAM_CELL*)malloc(sizeof(struct RAM_CELL) * 4);
  ram->num_values = 0;
  ram->capacity = 4;

  for (int i = 0; i < ram->capacity; i++) {
    ram->cells[i].value.value_type = RAM_TYPE_NONE; 
    ram->cells[i].value.types.i = 0;
    ram->cells[i].identifier = NULL; 
  }
  
  return ram;
}


//
// ram_destroy
//
// Frees the dynamically-allocated memory associated with
// the given memory. After the call returns, you cannot
// use the memory.
//
void ram_destroy(struct RAM* memory)
{
  // Free individual cell values
  for (int i = 0; i < memory->num_values; i++) {
    free(memory->cells[i].identifier);
    // Free string value if it exists
    if (memory->cells[i].value.value_type == RAM_TYPE_STR) {
      free(memory->cells[i].value.types.s);
    }
  }

  // Free the array of cells
  free(memory->cells);
  // Free the memory structure itself
  free(memory);
}

//
// ram_get_addr
// 
// If the given identifier (e.g. "x") has been written to 
// memory, returns the address of this value --- an integer
// in the range 0..N-1 where N is the number of values currently 
// stored in memory. Returns -1 if no such identifier exists 
// in memory. 
// 
// NOTE: a variable has to be written to memory before you can
// get its address. Once a variable is written to memory, its
// address never changes.
//
int ram_get_addr(struct RAM* memory, char* identifier) {
  
  for (int i = 0; i < memory->num_values; i++) {
    if (strcmp(memory->cells[i].identifier, identifier) == 0) {
      return i;
    }
  }
  return -1;
}


//
// ram_read_cell_by_addr
//
// Given a memory address (an integer in the range 0..N-1), 
// returns a COPY of the value contained in that memory cell.
// Returns NULL if the address is not valid.
//
// NOTE: this function allocates memory for the value that
// is returned. The caller takes ownership of the copy and 
// must eventually free this memory via ram_free_value().
//
// NOTE: a variable has to be written to memory before its
// address becomes valid. Once a variable is written to memory,
// its address never changes.
//
struct RAM_VALUE* ram_read_cell_by_addr(struct RAM* memory, int address) {

  // Handle the case when malloc fails (value is NULL)
  // You might want to add further error handling or return NULL in case of malloc failure.
  if (address >= memory->num_values || address < 0) {
    return NULL;
  }
  
  else {
    struct RAM_VALUE* value = (struct RAM_VALUE*)malloc(sizeof(struct RAM_VALUE));
    if (memory->cells[address].value.value_type == RAM_TYPE_STR) {
      value->value_type = RAM_TYPE_STR;
      value->types.s = strdup(memory->cells[address].value.types.s);
      return value;
    }
    *value = memory->cells[address].value;
    return value;
  }
}


// 
// ram_read_cell_by_id
//
// If the given identifier (e.g. "x") has been written to 
// memory, returns a COPY of the value contained in memory.
// Returns NULL if no such identifier exists in memory.
//
// NOTE: this function allocates memory for the value that
// is returned. The caller takes ownership of the copy and 
// must eventually free this memory via ram_free_value().
//
struct RAM_VALUE* ram_read_cell_by_id(struct RAM* memory, char* identifier) {

  return ram_read_cell_by_addr(memory, ram_get_addr(memory, identifier));
}

//
// ram_free_value
//
// Frees the memory value returned by ram_read_cell_by_id and
// ram_read_cell_by_addr.
//
void ram_free_value(struct RAM_VALUE* value)
{
  if (value->value_type == RAM_TYPE_STR) {
    free(value->types.s);
  }
  free(value);
}


//
// ram_write_cell_by_addr
//
// Writes the given value to the memory cell at the given 
// address. If a value already exists at this address, that
// value is overwritten by this new value. Returns true if 
// the value was successfully written, false if not (which 
// implies the memory address is invalid).
// 
// NOTE: if the value being written is a string, it will
// be duplicated and stored.
// 
// NOTE: a variable has to be written to memory before its
// address becomes valid. Once a variable is written to memory,
// its address never changes.
//
bool ram_write_cell_by_addr(struct RAM* memory, struct RAM_VALUE value, int address)
{
  
  if (address < 0  || address >= memory->num_values){
    return false; 
  }
  else {
    if (memory->cells[address].value.value_type == RAM_TYPE_STR) {
      free(memory->cells[address].value.types.s);
    }
    if (value.value_type == RAM_TYPE_STR) {
      memory->cells[address].value.types.s = strdup(value.types.s);
      memory->cells[address].value.value_type = RAM_TYPE_STR;
      return true;
    }
    else {
      memory->cells[address].value = value;
      return true;
    }
    // value.types.s != NULL TBC..
  }
}


//
// ram_write_cell_by_id
//
// Writes the given value to a memory cell named by the given
// identifier. If a memory cell already exists with this name,
// the existing value is overwritten by the given value. Returns
// true since this operation always succeeds.
// 
// NOTE: if the value being written is a string, it will
// be duplicated and stored.
// 
// NOTE: a variable has to be written to memory before its
// address becomes valid. Once a variable is written to memory,
// its address never changes.
//
bool ram_write_cell_by_id(struct RAM* memory, struct RAM_VALUE value, char* identifier)
{

  int address = ram_get_addr(memory, identifier);

  if (address >= 0) {
    return ram_write_cell_by_addr(memory, value, address);
  }

  else {
    if (memory->capacity == memory->num_values) {
      memory->capacity *= 2;
      struct RAM_CELL* temp = (struct RAM_CELL*)realloc(memory->cells, sizeof(struct RAM_CELL) * memory->capacity);

      memory->cells = temp;
    }

    if (value.value_type == RAM_TYPE_STR) {
      memory->cells[memory->num_values].value.types.s = strdup(value.types.s);
      memory->cells[memory->num_values].value.value_type = value.value_type;
    }
    else {
      memory->cells[memory->num_values].value = value;
      memory->cells[memory->num_values].value.value_type = value.value_type;
    }

    memory->cells[memory->num_values].identifier = strdup(identifier);
    memory->num_values++;
    return true;

  }
}


//
// ram_print
//
// Prints the contents of memory to the console.
//
void ram_print(struct RAM* memory)
{
  printf("**MEMORY PRINT**\n");

  printf("Capacity: %d\n", memory->capacity);
  printf("Num values: %d\n", memory->num_values);
  printf("Contents:\n");

  for (int i = 0; i < memory->num_values; i++)
  {
      printf(" %d: %s, ", i, memory->cells[i].identifier);

      printf("int, %d", memory->cells[i].value.types.i);
      printf("real, %lf", memory->cells[i].value.types.d);
      printf("str, '%s'", memory->cells[i].value.types.s);
      printf("ptr, %d", memory->cells[i].value.types.i);
      printf("boolean, False");
      printf("boolean, True");
      printf("none, None");

    printf("\n");
  }

  printf("**END PRINT**\n");
}
