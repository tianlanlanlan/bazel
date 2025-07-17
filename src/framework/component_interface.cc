#include "component_interface.h"

// 获取单例实例
ComFactory *ComFactory::Instance() {
  static ComFactory instance;
  return &instance;
}

// 注册组件创建函数
void ComFactory::RegisterComponent(
    const std::string &name,
    std::function<std::unique_ptr<ComponentInterface>()> creator) {
  creators_[name] = std::move(creator);
}

// 创建组件实例
std::unique_ptr<ComponentInterface>
ComFactory::Create(const std::string &name) {
  auto it = creators_.find(name);
  if (it != creators_.end()) {
    return it->second(); // 调用创建函数
  }
  return nullptr; // 未找到组件
}