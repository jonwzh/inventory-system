#include <assert.h>
#include "inventory.h"

// a simple test client for inventory.c

int main(void) {
  struct inventory *inv = inventory_create();
  assert(inventory_lookup(inv, "apples") == -1);
  inventory_add(inv, "apples", 3);
  inventory_add(inv, "bananas", 6);
  inventory_add(inv, "pears", 2);
  inventory_add(inv, "coconuts", 9);
  assert(inventory_lookup(inv, "apples") == 3);
  inventory_remove(inv, "apples", 1);
  assert(inventory_lookup(inv, "apples") == 2);
  assert(inventory_lookup(inv, "bananas") == 6);
  assert(inventory_lookup(inv, "pears") == 2);
  assert(inventory_lookup(inv, "coconuts") == 9);
  inventory_remove(inv, "coconuts", 9);
  assert(inventory_lookup(inv, "coconuts") == 0);
  inventory_add(inv, "pears", 3);
  assert(inventory_lookup(inv, "pears") == 5);
  inventory_destroy(inv);
}
