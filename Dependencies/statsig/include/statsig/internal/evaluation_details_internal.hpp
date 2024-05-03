#pragma once

#include "../evaluation_details.h"

namespace statsig::internal::evaluation_details {

String GetValueSourceString(const ValueSource &source) {
  switch (source) {
    case ValueSource::Uninitialized:return "Uninitialized";
    case ValueSource::Loading:return "Loading";
    case ValueSource::NoValues:return "NoValues";
    case ValueSource::Cache:return "Cache";
    case ValueSource::Network:return "Network";
    case ValueSource::NetworkNotModified:return "NetworkNotModified";
    case ValueSource::Bootstrap:return "Bootstrap";
  }

  return "";
}

struct SourceInfo {
  ValueSource source;
  time_t lcut;
  time_t received_at;
};

EvaluationDetails Uninitialized() {
  return {"Uninitialized", 0, 0};
}

EvaluationDetails UnrecognizedFromSourceInfo(SourceInfo info) {
  auto result = GetValueSourceString(info.source);

  if (info.source == ValueSource::Uninitialized || info.source == ValueSource::NoValues) {
    return {result, 0, 0};
  }

  return {result + ":Unrecognized", info.lcut, info.received_at};
}

EvaluationDetails RecognizedFromSourceInfo(SourceInfo info) {
  auto result = GetValueSourceString(info.source);
  return {result + ":Recognized", info.lcut, info.received_at};
}

}