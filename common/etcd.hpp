#include "logger.hpp"
#include <etcd/Client.hpp>
#include <etcd/KeepAlive.hpp>
#include <etcd/Response.hpp>
#include <etcd/Watcher.hpp>
#include <memory>
#include <string>

namespace milestone {

// 服务注册客户端
class Registrant {
public:
  using ptr = std::shared_ptr<Registrant>;
  Registrant(const std::string &host)
      : _clinet(std::make_shared<etcd::Client>(host)),
        _keep_alive(_clinet->leasekeepalive(3).get()),
        _lease_id(_keep_alive->Lease()) {}
  ~Registrant() { _keep_alive->Cancel(); }
  bool register_key(const std::string &key, const std::string &value) {
    auto resp = _clinet->put(key, value, _lease_id).get();
    if (resp.is_ok() == false) {
      std::cerr << "注册" << key << "-" << value << ",失败" << std::endl;
      return false;
    }
    return true;
  }

private:
  // 注意,顺序不能反,他们是有前面的,才有后面的
  std ::shared_ptr<etcd::Client> _clinet;
  std::shared_ptr<etcd::KeepAlive> _keep_alive;
  uint64_t _lease_id;
};

// 服务发现客户端
class Discovery {
  using NotifyCallback = std::function<void(std::string, std::string)>;

public:
  using ptr = std::shared_ptr<Discovery>;
  Discovery(const std::string &host, const std::string &basedir,
            const NotifyCallback &put_cb,
            const NotifyCallback &del_cb)
      : _clinet(std::make_shared<etcd::Client>(host)), // basedir--根目录
        _put_cb(put_cb), _del_cb(del_cb) {
    _watcher = std::make_shared<etcd::Watcher>(
        *_clinet.get(), basedir,
        std::bind(&Discovery::callback, this, std::placeholders::_1));
  }

private:
  void callback(const etcd::Response &resp) {
    if (resp.is_ok() == false) {
      std::cout << "收到一个错误的事件通知:" << resp.error_message()
                << std::endl;
      return;
    }
    for (auto const &ev : resp.events()) {
      if (ev.event_type() == etcd::Event::EventType::PUT) {
        std::cout << "原来的值" << ev.prev_kv().key() << "-"
                  << ev.prev_kv().as_string() << std::endl;
        if (_put_cb)
          _put_cb(ev.kv().key(), ev.kv().as_string());
        LOG_DEBUG("新增服务:{} - {}", ev.kv().key(),
                             ev.kv().as_string());
      } else if (ev.event_type() == etcd::Event::EventType::DELETE_) {
        if (_del_cb) _del_cb(ev.kv().key(), ev.kv().as_string());
        LOG_DEBUG("服务被删除下线:{} - {}", ev.kv().key(), ev.kv().as_string());
      }
    }
  }

private:
std ::shared_ptr<etcd::Client> _clinet;
  NotifyCallback _put_cb;
  NotifyCallback _del_cb;
  // watcher对象
  std::shared_ptr<etcd::Watcher> _watcher;
};}//end
