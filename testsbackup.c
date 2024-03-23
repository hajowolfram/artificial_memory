TEST(memory_module, write_one_string) {
  struct RAM *memory = ram_init();

  ASSERT_TRUE(memory != NULL);
  ASSERT_TRUE(memory->cells != NULL);
  ASSERT_TRUE(memory->num_values == 0);
  ASSERT_TRUE(memory->capacity == 4);

  struct RAM_VALUE i;
  struct RAM_VALUE i2;
  i2.value_type = RAM_TYPE_INT;
  i2.types.i = 123;
  bool success = ram_write_cell_by_id(memory, i2, "x");
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_INT);
  ASSERT_TRUE(memory->cells[0].value.types.i == 123);
  ASSERT_TRUE(strcmp(memory->cells[0].identifier, "x") == 0);


  i.value_type = RAM_TYPE_STR;
  i.types.s = "i love cs";


  success = ram_write_cell_by_addr(memory, i, 0);
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(memory->cells[0].value.types.s, "i love cs") == 0);
  ram_destroy(memory);
}

TEST(memory_module, write_one_real) {
  struct RAM *memory = ram_init();

  ASSERT_TRUE(memory != NULL);
  ASSERT_TRUE(memory->cells != NULL);
  ASSERT_TRUE(memory->num_values == 0);
  ASSERT_TRUE(memory->capacity == 4);
  struct RAM_VALUE i2;
  i2.value_type = RAM_TYPE_INT;
  i2.types.i = 123;
  bool success = ram_write_cell_by_id(memory, i2, "x");
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_INT);
  ASSERT_TRUE(memory->cells[0].value.types.i == 123);
  ASSERT_TRUE(strcmp(memory->cells[0].identifier, "x") == 0);

  struct RAM_VALUE i;

  i.value_type = RAM_TYPE_REAL;
  i.types.d = 3.24552;

  success = ram_write_cell_by_addr(memory, i, 0);
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_REAL);
  ASSERT_TRUE(memory->cells[0].value.types.d == 3.24552);
  ram_destroy(memory);
}

TEST(memory_module, write_one_true) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i2;
  i2.value_type = RAM_TYPE_INT;
  i2.types.i = 123;
  bool success = ram_write_cell_by_id(memory, i2, "x");
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_INT);
  ASSERT_TRUE(memory->cells[0].value.types.i == 123);
  ASSERT_TRUE(strcmp(memory->cells[0].identifier, "x") == 0);

  struct RAM_VALUE i;

  i.value_type = RAM_TYPE_BOOLEAN;
  i.types.i = true;

  success = ram_write_cell_by_addr(memory, i, 0);
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_BOOLEAN);
  ASSERT_TRUE(memory->cells[0].value.types.i == true);
  ram_destroy(memory);
}

TEST(memory_module, write_one_false) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i2;
  i2.value_type = RAM_TYPE_INT;
  i2.types.i = 123;
  bool success = ram_write_cell_by_id(memory, i2, "x");
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_INT);
  ASSERT_TRUE(memory->cells[0].value.types.i == 123);
  ASSERT_TRUE(strcmp(memory->cells[0].identifier, "x") == 0);

  struct RAM_VALUE i;

  i.value_type = RAM_TYPE_BOOLEAN;
  i.types.i = false;

  success = ram_write_cell_by_addr(memory, i, 0);
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_BOOLEAN);
  ASSERT_TRUE(memory->cells[0].value.types.i == false);
  ram_destroy(memory);
}

TEST(memory_module, write_multiple) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i1;
  struct RAM_VALUE i2;
  struct RAM_VALUE i3;
  struct RAM_VALUE i4;
  i1.value_type = RAM_TYPE_INT;
  i1.types.i = 355;
  i2.value_type = RAM_TYPE_STR;
  i2.types.s = "lol";
  i3.value_type = RAM_TYPE_REAL;
  i3.types.d = 24.4342;
  i4.value_type = RAM_TYPE_BOOLEAN;
  i4.types.i = true;
  ram_write_cell_by_id(memory, i4, "i4");
  ram_write_cell_by_id(memory, i3, "i3");
  ram_write_cell_by_id(memory, i2, "i2");
  ram_write_cell_by_id(memory, i1, "i1");
  bool success = ram_write_cell_by_addr(memory, i1, 0);
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 4);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_INT);
  ASSERT_TRUE(memory->cells[0].value.types.i == 355);

  success = ram_write_cell_by_addr(memory, i2, 1);
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 4);
  ASSERT_TRUE(memory->cells[1].value.value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(memory->cells[1].value.types.s, "lol") == 0);

  success = ram_write_cell_by_addr(memory, i3, 2);
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 4);
  ASSERT_TRUE(memory->cells[2].value.value_type == RAM_TYPE_REAL);
  ASSERT_TRUE(memory->cells[2].value.types.d == 24.4342);

  success = ram_write_cell_by_addr(memory, i4, 3);
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 4);
  ASSERT_TRUE(memory->cells[3].value.value_type == RAM_TYPE_BOOLEAN);
  ASSERT_TRUE(memory->cells[3].value.types.i == true);
  ram_destroy(memory);
}

TEST(memory_module, write_override) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i1;
  struct RAM_VALUE i2;
  struct RAM_VALUE i3;

  i1.value_type = RAM_TYPE_BOOLEAN;
  i1.types.i = false;

  i2.value_type = RAM_TYPE_REAL;
  i2.types.d = 2351.43;

  i3.value_type = RAM_TYPE_STR;
  i3.types.s = "lol";

  ram_write_cell_by_id(memory, i2, "i2");
  ram_write_cell_by_id(memory, i3, "i3");

  bool success = ram_write_cell_by_addr(memory, i1, 0);
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 2);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_BOOLEAN);
  ASSERT_TRUE(memory->cells[0].value.types.i == false);
  success = ram_write_cell_by_addr(memory, i2, 0);
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 2);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_REAL);
  ASSERT_TRUE(memory->cells[0].value.types.d == 2351.43);
  success = ram_write_cell_by_addr(memory, i3, 1);
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 2);
  ASSERT_TRUE(memory->cells[1].value.value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(memory->cells[1].value.types.s, "lol") == 0);
  success = ram_write_cell_by_addr(memory, i2, 1);
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 2);
  ASSERT_TRUE(memory->cells[1].value.value_type == RAM_TYPE_REAL);
  ASSERT_TRUE(memory->cells[1].value.types.d == 2351.43);
  ram_destroy(memory);
}

TEST(memory_module, write_fail) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i1;
  struct RAM_VALUE i2;
  struct RAM_VALUE i3;

  i1.value_type = RAM_TYPE_BOOLEAN;
  i1.types.i = false;

  i2.value_type = RAM_TYPE_REAL;
  i2.types.d = 2351.43;

  i3.value_type = RAM_TYPE_STR;
  i3.types.s = "lol";
  printf("TEST 1\n");
  ram_write_cell_by_id(memory, i3, "i3");
  ram_write_cell_by_id(memory, i2, "i2");
  ram_write_cell_by_id(memory, i1, "i1");
  printf("TEST 2\n");
  bool success = ram_write_cell_by_addr(memory, i1, 4);

  ASSERT_FALSE(success);
  success = ram_write_cell_by_addr(memory, i1, -1);
  ASSERT_FALSE(success);
  success = ram_write_cell_by_addr(memory, i1, 0);
  ASSERT_TRUE(success);
  success = ram_write_cell_by_addr(memory, i2, 1);
  ASSERT_TRUE(success);
  success = ram_write_cell_by_addr(memory, i3, 2);
  ASSERT_TRUE(success);
  success = ram_write_cell_by_addr(memory, i1, 3);
  ASSERT_FALSE(success);
  printf("TEST 3\n");

  ram_destroy(memory);
  printf("TEST 4\n");

}

TEST(memory_module, write_one_int) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i;
  i.value_type = RAM_TYPE_INT;
  i.types.i = 123;
  struct RAM_VALUE i2;
  i2.value_type = RAM_TYPE_INT;
  i2.types.i = 123;

  ram_write_cell_by_id(memory, i2, "i2");
  bool success = ram_write_cell_by_addr(memory, i, 0);
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_INT);
  ASSERT_TRUE(memory->cells[0].value.types.i == 123);
  ram_destroy(memory);
}

TEST(memory_module, write_real) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i;
  i.value_type = RAM_TYPE_REAL;
  i.types.d = 34.1344;
  bool success = ram_write_cell_by_id(memory, i, "id");
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(strcmp(memory->cells[0].identifier, "id") == 0);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_REAL);
  ASSERT_TRUE(memory->cells[0].value.types.d == 34.1344);
  success = ram_write_cell_by_addr(memory, i, 'u');
  ASSERT_FALSE(success);
  ram_destroy(memory);
}

TEST(memory_module, write_str) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i;
  i.value_type = RAM_TYPE_STR;
  i.types.s = "3.42";
  bool success = ram_write_cell_by_id(memory, i, "id");
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->cells[0].value.types.s != i.types.s);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(strcmp(memory->cells[0].identifier, "id") == 0);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(memory->cells[0].value.types.s, "3.42") == 0);
  ram_destroy(memory);
}
TEST(memory_module, write_str_override) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i1;
  struct RAM_VALUE i2;
  i1.value_type = RAM_TYPE_STR;
  i1.types.s = "3.42";
  i2.value_type = RAM_TYPE_STR;
  i2.types.s = "hello";
  bool success = ram_write_cell_by_id(memory, i1, "id");
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(memory->capacity == 4);
  ASSERT_TRUE(strcmp(memory->cells[0].identifier, "id") == 0);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(memory->cells[0].value.types.s, "3.42") == 0);

  success = ram_write_cell_by_id(memory, i2, "id");
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(strcmp(memory->cells[0].identifier, "id") == 0);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(memory->cells[0].value.types.s, "hello") == 0);
  ram_destroy(memory);
}

TEST(memory_module, write_bool) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i1;
  struct RAM_VALUE i2;
  i1.value_type = RAM_TYPE_BOOLEAN;
  i1.types.i = true;
  i2.value_type = RAM_TYPE_BOOLEAN;
  i2.types.i = false;
  bool success = ram_write_cell_by_id(memory, i1, "idi1");
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(strcmp(memory->cells[0].identifier, "idi1") == 0);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_BOOLEAN);
  ASSERT_TRUE(memory->cells[0].value.types.i == true);
  success = ram_write_cell_by_id(memory, i2, "idi2");
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 2);
  ASSERT_TRUE(strcmp(memory->cells[1].identifier, "idi2") == 0);
  ASSERT_TRUE(memory->cells[1].value.value_type == RAM_TYPE_BOOLEAN);
  ASSERT_TRUE(memory->cells[1].value.types.i == false);
  ram_destroy(memory);
}

TEST(memory_module, write_duplicate) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i1;
  struct RAM_VALUE i2;
  i1.value_type = RAM_TYPE_STR;
  i1.types.s = "true";
  i2.value_type = RAM_TYPE_INT;
  i2.types.i = 342;
  bool success = ram_write_cell_by_id(memory, i1, "first");
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(strcmp(memory->cells[0].identifier, "first") == 0);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(memory->cells[0].value.types.s, "true") == 0);
  success = ram_write_cell_by_id(memory, i2, "first");
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(strcmp(memory->cells[0].identifier, "first") == 0);
  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_INT);
  ASSERT_TRUE(memory->cells[0].value.types.i == 342);
  ram_destroy(memory);
}

TEST(memory_module, write_capacity_fail) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i1;
  struct RAM_VALUE i2;
  struct RAM_VALUE i3;
  struct RAM_VALUE i4;
  struct RAM_VALUE i5;

  i1.value_type = RAM_TYPE_BOOLEAN;
  i1.types.i = false;

  i2.value_type = RAM_TYPE_REAL;
  i2.types.d = 2351.43;

  i3.value_type = RAM_TYPE_STR;
  i3.types.s = "lol";

  i4.value_type = RAM_TYPE_INT;
  i4.types.i = 1234;

  i4.value_type = RAM_TYPE_BOOLEAN;
  i4.types.i = true;

  bool success = ram_write_cell_by_id(memory, i1, "first");
  ASSERT_TRUE(memory->num_values == 1);
  ASSERT_TRUE(success);
  success = ram_write_cell_by_id(memory, i2, "second");
  ASSERT_TRUE(memory->num_values == 2);
  ASSERT_TRUE(success);
  success = ram_write_cell_by_id(memory, i3, "third");
  ASSERT_TRUE(memory->num_values == 3);
  ASSERT_TRUE(success);
  success = ram_write_cell_by_id(memory, i4, "fourth");
  ASSERT_TRUE(memory->num_values == 4);
  ASSERT_TRUE(success);
  success = ram_write_cell_by_id(memory, i5, "fifth");
  ASSERT_TRUE(memory->num_values == 5);
  success = ram_write_cell_by_id(memory, i5, "sixth");
  ASSERT_TRUE(memory->num_values == 6);
  ASSERT_TRUE(success);
  ram_destroy(memory);
}

TEST(memory_module, read_id) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i1;
  struct RAM_VALUE i2;
  struct RAM_VALUE i3;
  struct RAM_VALUE i4;
  i1.value_type = RAM_TYPE_BOOLEAN;
  i1.types.i = false;
  i2.value_type = RAM_TYPE_REAL;
  i2.types.d = 2351.43;
  i3.value_type = RAM_TYPE_STR;
  i3.types.s = "lol";
  i4.value_type = RAM_TYPE_INT;
  i4.types.i = 1234;
  bool success = ram_write_cell_by_id(memory, i1, "first");
  success = ram_write_cell_by_id(memory, i2, "second");
  success = ram_write_cell_by_id(memory, i3, "third");
  success = ram_write_cell_by_id(memory, i4, "fourth");

  ASSERT_TRUE(strcmp(memory->cells[0].identifier, "first") == 0);
  ASSERT_TRUE(strcmp(memory->cells[1].identifier, "second") == 0);
  ASSERT_TRUE(strcmp(memory->cells[2].identifier, "third") == 0);
  ASSERT_TRUE(strcmp(memory->cells[3].identifier, "fourth") == 0);

  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_BOOLEAN);
  ASSERT_TRUE(memory->cells[1].value.value_type == RAM_TYPE_REAL);
  ASSERT_TRUE(memory->cells[2].value.value_type == RAM_TYPE_STR);
  ASSERT_TRUE(memory->cells[3].value.value_type == RAM_TYPE_INT);
  ASSERT_TRUE(success);

  struct RAM_VALUE *value1 = ram_read_cell_by_id(memory, "first");
  ASSERT_TRUE(value1->types.i == false);
  ASSERT_TRUE(value1->value_type == RAM_TYPE_BOOLEAN);
  ram_free_value(value1);
  ram_destroy(memory);
}

TEST(memory_module, read_add) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i1;
  struct RAM_VALUE i2;
  struct RAM_VALUE i3;
  struct RAM_VALUE i4;
  i1.value_type = RAM_TYPE_BOOLEAN;
  i1.types.i = false;
  i2.value_type = RAM_TYPE_REAL;
  i2.types.d = 2351.43;
  i3.value_type = RAM_TYPE_STR;
  i3.types.s = "lol";
  i4.value_type = RAM_TYPE_INT;
  i4.types.i = 1234;
  ram_write_cell_by_id(memory, i1, "first");
  ram_write_cell_by_id(memory, i2, "second");
  ram_write_cell_by_id(memory, i3, "third");
  ram_write_cell_by_id(memory, i4, "fourth");

  struct RAM_VALUE *value1 = ram_read_cell_by_addr(memory, 1);
  ASSERT_TRUE(value1->types.d = 2351.43);
  ASSERT_TRUE(value1->value_type == RAM_TYPE_REAL);

  ram_free_value(value1);
  ram_destroy(memory);
}

TEST(memory_module, strings) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i1;
  struct RAM_VALUE i2;
  struct RAM_VALUE i3;
  struct RAM_VALUE i4;
  i1.value_type = RAM_TYPE_STR;
  i1.types.s = "cs";
  i2.value_type = RAM_TYPE_STR;
  i2.types.s = "is";
  i3.value_type = RAM_TYPE_STR;
  i3.types.s = "so";
  i4.value_type = RAM_TYPE_STR;
  i4.types.s = "fun";

  ram_write_cell_by_id(memory, i1, "first");
  ASSERT_TRUE(strcmp(memory->cells[0].identifier, "first") == 0);
  ram_write_cell_by_id(memory, i2, "second");
  ram_write_cell_by_id(memory, i3, "third");
  ram_write_cell_by_id(memory, i4, "fourth");

  ASSERT_TRUE(ram_get_addr(memory, "first") == 0);
  ASSERT_TRUE(ram_get_addr(memory, "second") == 1);
  ASSERT_TRUE(ram_get_addr(memory, "third") == 2);
  ASSERT_TRUE(ram_get_addr(memory, "fourth") == 3);
  ASSERT_TRUE(ram_get_addr(memory, "hi") == -1);

  struct RAM_VALUE *value1 = ram_read_cell_by_id(memory, "first");
  ASSERT_TRUE(value1->types.s != i1.types.s);
  struct RAM_VALUE *value2 = ram_read_cell_by_id(memory, "second");
  ASSERT_TRUE(value2->types.s != i2.types.s);
  struct RAM_VALUE *value3 = ram_read_cell_by_id(memory, "third");
  ASSERT_TRUE(value3->types.s != i3.types.s);
  struct RAM_VALUE *value4 = ram_read_cell_by_id(memory, "fourth");
  ASSERT_TRUE(value4->types.s != i4.types.s);

  struct RAM_VALUE *v1 = ram_read_cell_by_addr(memory, 0);
  ASSERT_TRUE(v1->types.s != i1.types.s);
  struct RAM_VALUE *v2 = ram_read_cell_by_addr(memory, 1);
  ASSERT_TRUE(v2->types.s != i2.types.s);
  struct RAM_VALUE *v3 = ram_read_cell_by_addr(memory, 2);
  ASSERT_TRUE(v3->types.s != i3.types.s);
  struct RAM_VALUE *v4 = ram_read_cell_by_addr(memory, 3);
  ASSERT_TRUE(v4->types.s != i4.types.s);

  ASSERT_TRUE(strcmp(value1->types.s, "cs") == 0);
  ASSERT_TRUE(value1->value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(value2->types.s, "is") == 0);
  ASSERT_TRUE(value2->value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(value3->types.s, "so") == 0);
  ASSERT_TRUE(value3->value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(value4->types.s, "fun") == 0);
  ASSERT_TRUE(value4->value_type == RAM_TYPE_STR);

  ASSERT_TRUE(strcmp(v1->types.s, "cs") == 0);
  ASSERT_TRUE(v1->value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(v2->types.s, "is") == 0);
  ASSERT_TRUE(v2->value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(v3->types.s, "so") == 0);
  ASSERT_TRUE(v3->value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(v4->types.s, "fun") == 0);
  ASSERT_TRUE(v4->value_type == RAM_TYPE_STR);

  ram_free_value(value1);
  ram_free_value(value2);
  ram_free_value(value3);
  ram_free_value(value4);
  ram_free_value(v1);
  ram_free_value(v2);
  ram_free_value(v3);
  ram_free_value(v4);
  ram_destroy(memory);
}

TEST(memory_module, replace_strings) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i1;
  struct RAM_VALUE i2;
  i1.value_type = RAM_TYPE_STR;
  i1.types.s = "cs";
  i2.value_type = RAM_TYPE_INT;
  i2.types.i = 123;

  bool success = ram_write_cell_by_id(memory, i1, "first");
  ASSERT_TRUE(success);
  struct RAM_VALUE *value1 = ram_read_cell_by_id(memory, "first");
  ASSERT_TRUE(value1->value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(value1->types.s, "cs") == 0);
  ASSERT_TRUE(memory->num_values == 1);

  success = ram_write_cell_by_id(memory, i2, "second");
  ASSERT_TRUE(success);
  struct RAM_VALUE *value2 = ram_read_cell_by_id(memory, "second");
  ASSERT_TRUE(ram_read_cell_by_id(memory, "hi") == NULL);
  ASSERT_TRUE(value2->value_type == RAM_TYPE_INT);
  ASSERT_TRUE(value2->types.i == 123);
  ASSERT_TRUE(memory->num_values == 2);

  success = ram_write_cell_by_addr(memory, i2, 0);
  ASSERT_TRUE(success);
  struct RAM_VALUE *v1 = ram_read_cell_by_addr(memory, 0);
  ASSERT_TRUE(ram_read_cell_by_addr(memory, 2) == NULL);
  ASSERT_TRUE(v1->value_type == RAM_TYPE_INT);
  ASSERT_TRUE(v1->types.i == 123);
  ASSERT_TRUE(memory->num_values == 2);

  success = ram_write_cell_by_addr(memory, i1, 1);
  ASSERT_TRUE(success);
  struct RAM_VALUE *v2 = ram_read_cell_by_addr(memory, 1);
  ASSERT_TRUE(v2->value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(v2->types.s, "cs") == 0);
  ASSERT_TRUE(memory->num_values == 2);

  ram_free_value(v1);
  ram_free_value(v2);
  ram_free_value(value1);
  ram_free_value(value2);
  ram_destroy(memory);
}


TEST(memory_module, empty_RAM) {
  struct RAM *memory = ram_init();
  ASSERT_TRUE(memory->capacity == 4);
  ASSERT_TRUE(memory->num_values == 0);
  ASSERT_TRUE(memory->cells[3].identifier == NULL);
  ram_read_cell_by_addr(memory, 0);
  ASSERT_TRUE(ram_read_cell_by_addr(memory, 0) == NULL);
  ASSERT_TRUE(ram_read_cell_by_id(memory, "cssss") == NULL);
  ram_destroy(memory);
}

TEST(memory_module, expand_capacity) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i1;
  i1.value_type = RAM_TYPE_STR;
  i1.types.s = "3.42";
  struct RAM_VALUE i3;
  i3.value_type = RAM_TYPE_BOOLEAN;
  i3.types.i = false;
  struct RAM_VALUE i4;
  i4.value_type = RAM_TYPE_INT;
  i4.types.i = 23;
  struct RAM_VALUE i5;
  i5.value_type = RAM_TYPE_REAL;
  i5.types.d = 3.45;
  struct RAM_VALUE i6;
   i6.value_type = RAM_TYPE_STR;
   i6.types.s = "hi";
  bool success = ram_write_cell_by_id(memory, i1, "first");
  ASSERT_TRUE(success);
  success = ram_write_cell_by_id(memory, i3, "second");
  ASSERT_TRUE(success);
  success = ram_write_cell_by_id(memory, i4, "third");
  ASSERT_TRUE(success);
  success = ram_write_cell_by_id(memory, i5, "fourth");
  ASSERT_TRUE(success);

  ASSERT_TRUE(memory->num_values == 4);
  ASSERT_TRUE(memory->capacity == 4);
  success = ram_write_cell_by_id(memory, i6, "fifth");
  ASSERT_TRUE(success);
  ASSERT_TRUE(memory->num_values == 5);
  ASSERT_TRUE(memory->capacity == 8);

  ASSERT_TRUE(strcmp(memory->cells[0].identifier, "first") == 0);
  ASSERT_TRUE(strcmp(memory->cells[1].identifier, "second") == 0);
  ASSERT_TRUE(strcmp(memory->cells[2].identifier, "third") == 0);
  ASSERT_TRUE(strcmp(memory->cells[3].identifier, "fourth") == 0);
  ASSERT_TRUE(strcmp(memory->cells[4].identifier, "fifth") == 0);

  ASSERT_TRUE(strcmp(memory->cells[0].value.types.s, "3.42") == 0);
  ASSERT_TRUE(memory->cells[1].value.types.i == false);
  ASSERT_TRUE(memory->cells[2].value.types.i == 23);
  ASSERT_TRUE(memory->cells[3].value.types.d ==  3.45);
  ASSERT_TRUE(strcmp(memory->cells[4].value.types.s, "hi") == 0);

  ASSERT_TRUE(memory->cells[0].value.value_type == RAM_TYPE_STR);
  ASSERT_TRUE(memory->cells[1].value.value_type == RAM_TYPE_BOOLEAN);
  ASSERT_TRUE(memory->cells[2].value.value_type == RAM_TYPE_INT);
  ASSERT_TRUE(memory->cells[3].value.value_type == RAM_TYPE_REAL);
  ASSERT_TRUE(memory->cells[4].value.value_type == RAM_TYPE_STR);

  struct RAM_VALUE *v1 = ram_read_cell_by_id(memory, "fifth");
  struct RAM_VALUE *v2 = ram_read_cell_by_addr(memory, 4);
  ASSERT_TRUE(v1->types.s != i6.types.s);
  ASSERT_TRUE(strcmp(v2->types.s, "hi")==0);
  ASSERT_TRUE(v1->value_type == RAM_TYPE_STR);
  ASSERT_TRUE(v2->value_type == RAM_TYPE_STR);
  ASSERT_TRUE(strcmp(v1->types.s, v2->types.s)==0);
  ASSERT_TRUE(v1->value_type == v2->value_type);
  ASSERT_TRUE(strcmp(memory->cells[4].identifier, "fifth") == 0);
  ASSERT_TRUE(strcmp(memory->cells[4].value.types.s, "hi") == 0);
  ASSERT_TRUE(memory->cells[4].value.value_type == RAM_TYPE_STR);

  success = ram_write_cell_by_id(memory, i1, "sixth");
  ASSERT_TRUE(strcmp(memory->cells[5].identifier, "sixth") == 0);
  ASSERT_TRUE(strcmp(memory->cells[5].value.types.s, "3.42") == 0);
  ASSERT_TRUE(memory->cells[5].value.value_type == RAM_TYPE_STR);
  struct RAM_VALUE *v3 = ram_read_cell_by_addr(memory, 5);
  ASSERT_TRUE(strcmp(v3->types.s, "3.42")==0);
  ASSERT_TRUE(v3->value_type == RAM_TYPE_STR);

  struct RAM_VALUE i2;
  i2.value_type = RAM_TYPE_REAL;
  i2.types.d = 3409.2;
  success = ram_write_cell_by_addr(memory, i2, 5);
  ASSERT_TRUE(memory->cells[5].value.value_type == RAM_TYPE_REAL);
  ASSERT_TRUE(memory->cells[5].value.types.d == 3409.2);
  ram_free_value(v1);
  ram_free_value(v2);
  ram_free_value(v3);
  ram_destroy(memory);
}

TEST(memory_module, read_addr_nots) {
  struct RAM *memory = ram_init();
  struct RAM_VALUE i1;
  i1.value_type = RAM_TYPE_STR;
  i1.types.s = "3.42";
  struct RAM_VALUE i2;
  i2.value_type = RAM_TYPE_BOOLEAN;
  i2.types.i = false;
  bool success = ram_write_cell_by_id(memory, i1, "school");
  ASSERT_TRUE(success);
  struct RAM_VALUE *v1 = ram_read_cell_by_id(memory, "school");
  ASSERT_TRUE(strcmp(v1->types.s, "3.42") == 0);
  ASSERT_TRUE(v1->value_type == RAM_TYPE_STR);
  success = ram_write_cell_by_addr(memory, i2, 0);
  ram_free_value(v1);
  v1 = ram_read_cell_by_addr(memory, 0);
  ASSERT_TRUE(success);
  ASSERT_TRUE(v1->types.i == false);
  ASSERT_TRUE(v1->value_type == RAM_TYPE_BOOLEAN);
  ASSERT_TRUE(memory->capacity == 4);
  ASSERT_TRUE(memory->num_values == 1);
  ram_free_value(v1);
  ram_destroy(memory);
}

TEST(memory_module, stringspt1){
  struct RAM *memory = ram_init();
  struct RAM_VALUE i1;
  i1.value_type = RAM_TYPE_STR;
  i1.types.s = "3.42";
  struct RAM_VALUE i2;
  i2.value_type = RAM_TYPE_STR;
  i2.types.s = "hi";

  bool success = ram_write_cell_by_id(memory, i1, "first");
  ASSERT_TRUE(success);
  success = ram_write_cell_by_id(memory, i2, "second");
  ASSERT_TRUE(success);
  struct RAM_VALUE *v1 = ram_read_cell_by_id(memory, "first");
  struct RAM_VALUE *v2 = ram_read_cell_by_id(memory, "second");
  struct RAM_VALUE *value1 = ram_read_cell_by_addr(memory, 0);
  struct RAM_VALUE *value2 = ram_read_cell_by_addr(memory, 1);
  ASSERT_TRUE(v1->types.s != i1.types.s);
  ASSERT_TRUE(v2->types.s != i2.types.s);
  ASSERT_TRUE(value1->types.s != i1.types.s);
  ASSERT_TRUE(value2->types.s != i2.types.s);

  struct RAM_VALUE i3;
  i3.value_type = RAM_TYPE_STR;
  i3.types.s = "school";
  struct RAM_VALUE i4;
  i4.value_type = RAM_TYPE_STR;
  i4.types.s = "phone";

  success = ram_write_cell_by_addr(memory, i3, 0);
  ASSERT_TRUE(success);
  success = ram_write_cell_by_addr(memory, i4, 1);
  struct RAM_VALUE *f1 = ram_read_cell_by_id(memory, "first");
  struct RAM_VALUE *f2 = ram_read_cell_by_id(memory, "second");
  struct RAM_VALUE *falue1 = ram_read_cell_by_addr(memory, 0);
  struct RAM_VALUE *falue2 = ram_read_cell_by_addr(memory, 1);
  ASSERT_TRUE(f1->types.s != i1.types.s);
  ASSERT_TRUE(f2->types.s != i2.types.s);
  ASSERT_TRUE(falue1->types.s != i1.types.s);
  ASSERT_TRUE(falue2->types.s != i2.types.s);

  ram_free_value(v1);
  ram_free_value(v2);
  ram_free_value(value1);
  ram_free_value(value2);
  ram_free_value(f1);
  ram_free_value(f2);
  ram_free_value(falue1);
  ram_free_value(falue2);
  ram_destroy(memory);