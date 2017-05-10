#include "inventory.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct inventory {
  int len;
  int *qty;
  char **item;
};

struct inventory *inventory_create(void) {
  struct inventory *i = malloc(sizeof(struct inventory));
  i->len = 0;
  i->qty = NULL;
  i->item = NULL;
  return i;
}

void inventory_destroy(struct inventory *inv) {
  assert(inv != NULL);
  for(int i = 0; i < inv->len; ++i) {
    free(inv->item[i]);
  }
  free(inv->qty);
  free(inv->item);
  free(inv);
}


int inventory_lookup(const struct inventory *inv, const char *item) {
  assert(inv != NULL);
  assert(item != NULL);
  int low = 0;
  int high = inv->len - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (strcmp(inv->item[mid], item) == 0) {
      return inv->qty[mid];
    } else if (strcmp(inv->item[mid], item) > 0) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return -1;
}

void inventory_add(struct inventory *inv, const char *item, int qty) {
  assert(inv != NULL);
  assert(item != NULL);
  assert(qty >= 0);
  int low = 0;
  int high = inv->len - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (mid > inv->len - 1 || mid < 0) break;
    if (strcmp(inv->item[mid], item) == 0) {
      inv->qty[mid] += qty;
      return;
    } else if (strcmp(inv->item[mid], item) > 0) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  inv->len += 1;
  inv->item = realloc(inv->item, inv->len * sizeof(char *));
  inv->qty = realloc(inv->qty, inv->len * sizeof(int));
  int k = inv->len - 1;
  while (k && strcmp(inv->item[k - 1], item) > 0) {
    inv->item[k] = inv->item[k - 1];
    inv->qty[k] = inv->qty[k - 1];
    --k;
  }
  int item_len = strlen(item);
  inv->item[k] = malloc((item_len + 1) * sizeof(char));
  strcpy(inv->item[k], item);
  inv->qty[k] = qty;
}

void inventory_remove(struct inventory *inv, const char *item, int qty) {
  assert(inv != NULL);
  assert(item != NULL);
  assert(qty > 0 && qty <= inventory_lookup(inv, item));
  int low = 0;
  int high = inv->len - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (strcmp(inv->item[mid], item) == 0) {
      inv->qty[mid] -= qty;
      break;
    } else if (strcmp(inv->item[mid], item) > 0) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
}



