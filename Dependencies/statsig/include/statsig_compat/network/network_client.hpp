#pragma once

#include <functional>
#include <optional>
#include <utility>

#include "statsig/internal/constants.h"

namespace statsig::internal {

struct HttpResponse {
  const std::string text;
  const int status = -1;
  const std::string sdk_region;
  const std::optional<std::string> error;
};

struct HttpRequest {
  const std::string api;
  const std::string &path;
  const std::unordered_map<std::string, std::string> &headers;
  const std::string &body;
};

#ifndef STATSIG_TESTS

class NetworkClient {
 public:
  static void Post(
      const HttpRequest &request,
      const std::function<void(HttpResponse)> &callback
  ) {

  }
};

#else

class NetworkClient {
 public:
  static void Post(
      const HttpRequest &request,
      const std::function<void(HttpResponse)> &callback
  ) {
    GetInstance().PostImpl(request, callback);
  }

  static NetworkClient &GetInstance() {
    static NetworkClient instance;
    return instance;
  }

  std::function<HttpResponse(HttpRequest)> _test_func_;

 private:
  void PostImpl(
      const HttpRequest &request,
      const std::function<void(HttpResponse)> &callback
  ) const {
    callback(_test_func_(request));
  }
};

#endif

}



