#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

// 组件抽象接口
class ComponentInterface {
public:
  virtual ~ComponentInterface() = default;
  virtual bool Init() = 0;
};

// 组件工厂类
class ComFactory {
public:
  // 获取单例实例
  static ComFactory *Instance();

  // 注册组件创建函数
  void RegisterComponent(
      const std::string &name,
      std::function<std::unique_ptr<ComponentInterface>()> creator);

  // 创建组件实例
  std::unique_ptr<ComponentInterface> Create(const std::string &name);

  // 删除拷贝构造和赋值
  ComFactory(const ComFactory &) = delete;
  ComFactory &operator=(const ComFactory &) = delete;

private:
  ComFactory() = default; // 私有构造函数

  std::unordered_map<std::string,
                     std::function<std::unique_ptr<ComponentInterface>()>>
      creators_;
};