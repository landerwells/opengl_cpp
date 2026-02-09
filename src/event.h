#pragma once

#include <any>
#include <cstdint>
#include <unordered_map>

using EventId = std::uint32_t;
using ParamId = std::uint32_t;

class Event
{
  public:
  Event() = delete;

  explicit Event(EventId type) : mType(type) {}

  template <typename T>
  void SetParam(EventId id, T value)
  {
    mData[id] = value;
  }

  template <typename T>
  T GetParam(EventId id)
  {
    return std::any_cast<T>(mData[id]);
  }

  EventId GetType() const { return mType; }

  private:
  EventId mType{};
  std::unordered_map<EventId, std::any> mData{};
};
