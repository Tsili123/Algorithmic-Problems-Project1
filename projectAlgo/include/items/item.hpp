#pragma once
template <typename T>
struct Item {
  // Identifier for each item
  long int id;
  // Actual data
  T* data;
  // Flag for reverse assignment
  bool staged;
  // Flag for reverse assignment
  bool marked;
  // Flag if is NULL
  bool null_flag;

  Item(){
    id = -1;
    data = NULL;
    staged = false;
    marked = false;
    null_flag = true;
  }

  Item(long int id, T* data, bool st = false, bool md = false) : id(id), data(data), staged(st), marked(md) {
    null_flag = false;
  }

  void operator = (const Item<T> &item) {
    id = item.id;
    data = item.data;
    staged = item.staged;
    marked = item.marked;
    null_flag = item.null_flag;
  }

  bool operator == (const Item<T> &item) {
    return id == item.id;
  }
};