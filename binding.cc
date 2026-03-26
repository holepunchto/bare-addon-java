#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <jstl.h>

static inline std::string
bare_addon_hello(js_env_t *env, js_receiver_t) {
  auto vm = java_vm_t::get_created().value();

  auto java = vm.get_env().value();

  auto addon = java_class_t<"to/holepunch/bare/Addon">(java);

  auto hello = addon.get_static_method<std::string()>("hello");

  return hello();
}

static js_value_t *
bare_addon_exports(js_env_t *env, js_value_t *exports) {
  int err;

  err = js_set_property<bare_addon_hello>(env, exports, "hello");
  assert(err == 0);

  return exports;
}

BARE_MODULE(bare_addon, bare_addon_exports)
