#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <memory>
#include <mutex>

template <typename T> class Singleton
{
public:
  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;

  static T &get_instace()
  {
    static T instance;
    return instance;
  }

protected:
  Singleton() = default;
  virtual ~Singleton() = default;
};
#endif