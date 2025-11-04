#include "include/test.h"
#include "../../src/include/util/hb_array.h"

TEST(test_hb_array_init)
  hb_array_T array;

  hb_array_init(&array, sizeof(uint64_t), 1024);

  ck_assert_int_eq(array.item_size, sizeof(uint64_t));
  ck_assert_int_eq(array.capacity, 1024);
  ck_assert_int_eq(array.size, 0);
  ck_assert_ptr_nonnull(array.items);

  hb_array_deinit(&array);
END

TEST(test_hb_array_pointer_init)
  hb_array_T array;

  hb_array_pointer_init(&array, 1024);

  ck_assert_int_eq(array.item_size, sizeof(void *));
  ck_assert_int_eq(array.capacity, 1024);
  ck_assert_int_eq(array.size, 0);
  ck_assert_ptr_nonnull(array.items);

  hb_array_deinit(&array);
END

TEST(test_hb_array_append)
  hb_array_T array;

  hb_array_init(&array, sizeof(uint64_t), 2);

  uint64_t number = 1;
  hb_array_append(&array, &number);
  ck_assert_int_eq(array.capacity, 2);

  number = 2;
  hb_array_append(&array, &number);
  ck_assert_int_eq(array.capacity, 2);

  number = 3;
  hb_array_append(&array, &number);
  ck_assert_int_eq(array.capacity, 4);

  ck_assert_int_eq(*(uint64_t *)hb_array_get(&array, 0), 1);
  ck_assert_int_eq(*(uint64_t *)hb_array_get(&array, 1), 2);
  ck_assert_int_eq(*(uint64_t *)hb_array_get(&array, 2), 3);

  ck_assert_int_eq(array.size, 3);

  hb_array_deinit(&array);
END

TEST(test_hb_array_first_last)
  hb_array_T array;

  hb_array_init(&array, sizeof(uint64_t), 2);

  ck_assert_ptr_null(hb_array_first(&array));
  ck_assert_ptr_null(hb_array_last(&array));

  uint64_t number = 1;
  hb_array_append(&array, &number);

  ck_assert_int_eq(*(uint64_t *)hb_array_first(&array), 1);
  ck_assert_int_eq(*(uint64_t *)hb_array_last(&array), 1);

  number = 2;
  hb_array_append(&array, &number);

  ck_assert_int_eq(*(uint64_t *)hb_array_first(&array), 1);
  ck_assert_int_eq(*(uint64_t *)hb_array_last(&array), 2);

  hb_array_deinit(&array);
END

TEST(test_hb_array_stack_behavior)
  hb_array_T array;

  hb_array_init(&array, sizeof(uint64_t), 2);

  for(uint64_t i = 0; i < 4; i++) {
    hb_array_push(&array, &i);
  }

  uint64_t number;

  ck_assert(hb_array_pop(&array, &number));
  ck_assert_int_eq(number, 3);
  ck_assert_int_eq(array.size, 3);

  ck_assert(hb_array_pop(&array, &number));
  ck_assert_int_eq(number, 2);
  ck_assert_int_eq(array.size, 2);

  ck_assert(hb_array_pop(&array, &number));
  ck_assert_int_eq(number, 1);
  ck_assert_int_eq(array.size, 1);

  ck_assert(hb_array_pop(&array, &number));
  ck_assert_int_eq(number, 0);
  ck_assert_int_eq(array.size, 0);

  ck_assert(!hb_array_pop(&array, &number));

  hb_array_deinit(&array);
END

TEST(test_hb_array_remove)
  hb_array_T array;

  hb_array_init(&array, sizeof(uint64_t), 2);

  for(uint64_t i = 0; i < 4; i++) {
    hb_array_push(&array, &i);
  }

  hb_array_remove(&array, 0);
  ck_assert_int_eq(array.size, 3);
  ck_assert_int_eq(*(uint64_t *)hb_array_get(&array, 0), 1);
  ck_assert_int_eq(*(uint64_t *)hb_array_get(&array, 1), 2);
  ck_assert_int_eq(*(uint64_t *)hb_array_get(&array, 2), 3);

  hb_array_remove(&array, 1);
  ck_assert_int_eq(array.size, 2);
  ck_assert_int_eq(*(uint64_t *)hb_array_get(&array, 0), 1);
  ck_assert_int_eq(*(uint64_t *)hb_array_get(&array, 1), 3);

  hb_array_remove(&array, 1);
  ck_assert_int_eq(array.size, 1);
  ck_assert_int_eq(*(uint64_t *)hb_array_get(&array, 0), 1);

  hb_array_remove(&array, 0);
  ck_assert_int_eq(array.size, 0);

  hb_array_deinit(&array);
END

TCase *hb_array_tests(void) {
  TCase *buffer = tcase_create("Herb (New) Array");

  tcase_add_test(buffer, test_hb_array_init);
  tcase_add_test(buffer, test_hb_array_pointer_init);
  tcase_add_test(buffer, test_hb_array_append);
  tcase_add_test(buffer, test_hb_array_first_last);
  tcase_add_test(buffer, test_hb_array_stack_behavior);
  tcase_add_test(buffer, test_hb_array_remove);

  return buffer;
}
