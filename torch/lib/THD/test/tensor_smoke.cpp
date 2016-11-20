#include <iostream>
#include <cassert>
#include <typeinfo>

#include "../base/tensors/THTensor.hpp"

using namespace std;


int main() {
  FloatTensor *tensor = new THTensor<float>();
  FloatTensor *tensor2 = new THTensor<float>();
  assert(tensor->nDim() == 0);

  tensor->resize({1, 2, 3});
  assert(tensor->nDim() == 3);
  int i = 0;
  for (auto s: tensor->sizes())
    assert(s == ++i);

  vector<long> sizes = {2, 2};
  tensor2->resize(sizes);
  tensor2->fill(4);
  tensor->add(*tensor2, 1);
  assert(tensor->nDim() == 2);

  for (auto s: tensor->sizes())
    assert(s == 2);
  for (int i = 0; i < 2; i++)
    assert(((float*)tensor->data())[i] == 5);

  bool thrown = false;
  try {
    IntTensor &a = dynamic_cast<IntTensor&>(*tensor);
  } catch(std::bad_cast &e) {
    thrown = true;
  }
  assert(thrown);

  delete tensor;
  delete tensor2;
  cout << "OK" << endl;
  return 0;
}
