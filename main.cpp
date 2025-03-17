#include <torch/csrc/jit/python/python_ivalue.h>

int main() {
  // using torch::autograd::AutogradContext;
  using torch::autograd::variable_list;

  auto vl = variable_list();
  // auto ac = AutogradContext();

  (void)vl;
  // (void)ac;
  
  return 0;
}
