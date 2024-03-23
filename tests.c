#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ram.h"
#include "gtest/gtest.h"
// TEST CASES FOR RAM.c
// NORTHWESTERN UNIVERSITY
// CS211
// HAJO WOLFRAM

//
// Test: writing an int value
//
TEST(memory_module, write_int) {
  bool success;
  struct RAM *memory = ram_init();
  ASSERT_TRUE(memory != NULL);ASSERT_TRUE(memory->cells != NULL);
  ASSERT_TRUE(memory->num_values == 0);
  ASSERT_TRUE(memory->capacity == 4);

  struct RAM_VALUE ram1; 
  ram1.value_type = RAM_TYPE_INT;
  ram1.types.i = 1;

  success = ram_write_cell_by_id(memory, ram1, "x");
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_INT);
  ASSERT_TRUE(memory->cells[0].value.types.i == 1);
  ram_destroy(memory);
}

//
// Test: writing a string
//
TEST(memory_module, write_str) {
  bool success;
  struct RAM *memory = ram_init();
  ASSERT_TRUE(memory != NULL);ASSERT_TRUE(memory->cells != NULL);
  ASSERT_TRUE(memory->num_values == 0);
  ASSERT_TRUE(memory->capacity == 4);

  struct RAM_VALUE ram1; 
  ram1.value_type = RAM_TYPE_STR;
  ram1.types.s = "hello";

  success = ram_write_cell_by_id(memory, ram1, "x");
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(memory->cells[0].value.types.s, "hello") == 0);
  ASSERT_TRUE(memory->cells[0].value.types.s != ram1.types.s);
  ram_destroy(memory);
}

//
// checking for errors what happen when your overwrite something 
//
TEST(memory_module, overwrite_different) {
  bool success;
  struct RAM *memory = ram_init();
  ASSERT_TRUE(memory != NULL); ASSERT_TRUE(memory->cells != NULL);
  ASSERT_TRUE(memory->num_values == 0);
  ASSERT_TRUE(memory->capacity == 4);

  struct RAM_VALUE ram1, ram2, ram3;

  ram1.value_type = RAM_TYPE_INT;
  ram1.types.i = 1;
  ram2.value_type = RAM_TYPE_STR;
  ram2.types.s = "hello";
  ram3.value_type = RAM_TYPE_REAL;
  ram3.types.d = 1.1;

  ASSERT_TRUE(ram_write_cell_by_id(memory, ram1, "x"));
  ASSERT_TRUE(ram_write_cell_by_id(memory, ram2, "x"));
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(memory->cells[0].value.types.s, "hello") == 0);
  ASSERT_TRUE(ram_write_cell_by_id(memory, ram3, "x"));
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_REAL);
  ASSERT_TRUE(memory->cells[0].value.types.d == 1.1);
  
  ram_write_cell_by_id(memory, ram1, "a");
  ram_write_cell_by_id(memory, ram1, "b");
  ram_write_cell_by_id(memory, ram1, "c");
  
  ASSERT_TRUE(ram_read_cell_by_addr(memory, 4) == NULL);

  ram_destroy(memory);
}

//
// Test case: writing multiple cells
//
TEST(memory_module, write_multiple_cells) {
  bool success;
  struct RAM *memory = ram_init();
  ASSERT_TRUE(memory != NULL); ASSERT_TRUE(memory->cells != NULL);
  ASSERT_TRUE(memory->num_values == 0);
  ASSERT_TRUE(memory->capacity == 4);

  struct RAM_VALUE ram1, ram2;
  ram1.value_type = RAM_TYPE_INT;
  ram1.types.i = 10;
  ram2.value_type = RAM_TYPE_STR;
  ram2.types.s = "world";

  success = ram_write_cell_by_id(memory, ram1, "x");
  ASSERT_TRUE(success);
  success = ram_write_cell_by_id(memory, ram2, "y");
  ASSERT_TRUE(success);

  ASSERT_TRUE(memory->num_values == 2);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_INT);
  ASSERT_TRUE(memory->cells[0].value.types.i == 10);
  ASSERT_TRUE(strcmp(memory->cells[1].value.types.s, "world") == 0);

  ram_destroy(memory);
}

//
// Test case: overwriting
//
TEST(memory_module, overwrite_cell) {
  bool success;
  struct RAM *memory = ram_init();
  ASSERT_TRUE(memory != NULL); ASSERT_TRUE(memory->cells != NULL);
  ASSERT_TRUE(memory->num_values == 0);
  ASSERT_TRUE(memory->capacity == 4);

  struct RAM_VALUE ram1;
  ram1.value_type = RAM_TYPE_INT;
  ram1.types.i = 5;

  success = ram_write_cell_by_id(memory, ram1, "x");
  ASSERT_TRUE(success);
  success = ram_write_cell_by_id(memory, ram1, "a");
  ASSERT_TRUE(success);
  success = ram_write_cell_by_id(memory, ram1, "b");
  ASSERT_TRUE(success);
  success = ram_write_cell_by_id(memory, ram1, "c");
  ASSERT_TRUE(success);

  struct RAM_VALUE ram2;
  ram2.value_type = RAM_TYPE_STR;
  ram2.types.s = "hello";

  success = ram_write_cell_by_id(memory, ram2, "x");
  ASSERT_TRUE(success);
  

  struct RAM_VALUE ram3;
  ram3.value_type = RAM_TYPE_INT;
  ram3.types.i = 34;

  ASSERT_TRUE(ram_write_cell_by_addr(memory, ram3, 0));
  ASSERT_TRUE(ram_write_cell_by_addr(memory, ram2, 1));
  ASSERT_TRUE(ram_write_cell_by_addr(memory, ram3, 2));
  ASSERT_TRUE(ram_write_cell_by_addr(memory, ram3, 3));
  
  ASSERT_TRUE(memory->num_values == 4);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_INT);
  ASSERT_TRUE(memory->cells[0].value.types.i == 34);

  ASSERT_TRUE(memory->cells[1].value.value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(memory->cells[1].value.types.s, "hello") == 0);

  ASSERT_TRUE(memory->cells[2].value.value_type == RAM_TYPE_INT);
  ASSERT_TRUE(memory->cells[2].value.types.i == 34);

  ASSERT_TRUE(memory->cells[3].value.value_type == RAM_TYPE_INT);
  ASSERT_TRUE(memory->cells[3].value.types.i == 34);
  
  ram_destroy(memory);
}

//
// invalid address
//
TEST(memory_module, read_invalid_address) {
  struct RAM *memory = ram_init();
  ASSERT_TRUE(memory != NULL); ASSERT_TRUE(memory->cells != NULL);
  ASSERT_TRUE(memory->num_values == 0);
  ASSERT_TRUE(memory->capacity == 4);

  struct RAM_VALUE *value = ram_read_cell_by_addr(memory, 10);

  ASSERT_TRUE(value == NULL);

  ram_destroy(memory);
}

//
// double capacity, 
//

TEST(memory_moduke, expanding) {
  bool success;
  struct RAM *memory = ram_init();
  ASSERT_TRUE(memory != NULL); ASSERT_TRUE(memory->cells != NULL);
  ASSERT_TRUE(memory->num_values == 0);
  ASSERT_TRUE(memory->capacity == 4);

  struct RAM_VALUE ram1, ram2, ram3, ram4, ram5;
  ram1.value_type = RAM_TYPE_INT;
  ram1.types.i = 10;
  ram2.value_type = RAM_TYPE_STR;
  ram2.types.s = "world";
  ram3.value_type = RAM_TYPE_INT;
  ram3.types.i = 10;
  ram4.value_type = RAM_TYPE_INT;
  ram4.types.i = 10;
  ram5.value_type = RAM_TYPE_STR;
  ram5.types.s = "hello";

  success = ram_write_cell_by_id(memory, ram1, "x");
  ASSERT_TRUE(success);
  success = ram_write_cell_by_id(memory, ram2, "y");
  ASSERT_TRUE(success);
  success = ram_write_cell_by_id(memory, ram3, "a");
  ASSERT_TRUE(success);
  success = ram_write_cell_by_id(memory, ram4, "b");
  ASSERT_TRUE(success);
  success = ram_write_cell_by_id(memory, ram5, "c");
  ASSERT_TRUE(success);
  
  ASSERT_TRUE(memory->capacity == 8);
  ASSERT_TRUE(memory->num_values == 5);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_INT);
  ASSERT_TRUE(memory->cells[0].value.types.i == 10);
  ASSERT_TRUE(strcmp(memory->cells[1].value.types.s, "world") == 0);
  ASSERT_TRUE(strcmp(memory->cells[4].value.types.s, "hello") == 0); 


  ASSERT_TRUE((ram_read_cell_by_id(memory, "c")->value_type) == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(ram_read_cell_by_id(memory, "c")->types.s, "hello") == 0);
  ram_destroy(memory);
}

//
// Test case: Writing a real value
//
TEST(memory_module, write_real) {
  bool success;
  struct RAM *memory = ram_init();
  ASSERT_TRUE(memory != NULL);
  ASSERT_TRUE(memory->cells != NULL);
  ASSERT_TRUE(memory->num_values == 0);
  ASSERT_TRUE(memory->capacity == 4);

  struct RAM_VALUE ram1;
  ram1.value_type = RAM_TYPE_REAL;
  ram1.types.d = 3.14;

  success = ram_write_cell_by_id(memory, ram1, "pi");
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_REAL);
  ASSERT_TRUE(memory->cells[0].value.types.d == 3.14);
  ram_destroy(memory);
}

//
// Test case: Reading a cell by its identifier
//
TEST(memory_module, read_by_id) {
  bool success;
  struct RAM *memory = ram_init();
  ASSERT_TRUE(memory != NULL);
  ASSERT_TRUE(memory->cells != NULL);
  ASSERT_TRUE(memory->num_values == 0);
  ASSERT_TRUE(memory->capacity == 4);

  struct RAM_VALUE ram1;
  ram1.value_type = RAM_TYPE_INT;
  ram1.types.i = 42;

  success = ram_write_cell_by_id(memory, ram1, "answer");
  ASSERT_TRUE(success);

  struct RAM_VALUE *value = ram_read_cell_by_id(memory, "answer");
  ASSERT_TRUE(value != NULL);
  ASSERT_TRUE(value->value_type == RAM_TYPE_INT);
  ASSERT_TRUE(value->types.i == 42);
  ram_free_value(value);

  ram_destroy(memory);
}

//
// Test case: Attempting to read from an empty RAM
//
TEST(memory_module, read_empty_memory) {
  struct RAM *memory = ram_init();
  ASSERT_TRUE(memory != NULL);
  ASSERT_TRUE(memory->cells != NULL);
  ASSERT_TRUE(memory->num_values == 0);
  ASSERT_TRUE(memory->capacity == 4);

  struct RAM_VALUE *value = ram_read_cell_by_id(memory, "nonexistent");
  ASSERT_TRUE(value == NULL);

  ram_destroy(memory);
}



