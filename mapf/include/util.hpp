#pragma once
#include <random>
#include <chrono>


static void halt(const std::string& msg,
                 const char* caller=__builtin_FUNCTION())
{
  std::cout << "error@" << caller << ": ";
  std::cout << msg << std::endl;
  std::exit(1);
}

static void warn(const std::string& msg,
                 const char* caller=__builtin_FUNCTION())
{
  std::cout << "warn@" << caller << ": ";
  std::cout << msg << std::endl;
}

template <typename T>
static bool inArray(const T a, const std::vector<T> &arr) {
  auto itr = std::find(arr.begin(), arr.end(), a);
  return itr != arr.end();
}

static bool getRandomBoolean(std::mt19937* MT) {
  std::uniform_int_distribution<int> r(0, 1);
  return r(*MT);
}

static int getRandomInt(int from, int to, std::mt19937* MT) {
  // [from, to]
  std::uniform_int_distribution<int> r(from, to);
  return r(*MT);
}

static float getRandomFloat(float from, float to, std::mt19937* MT) {
  // [from, to)
  std::uniform_real_distribution<float> r(from, to);
  return r(*MT);
}

template <typename T>
static T randomChoose(std::vector<T> &arr, std::mt19937* MT) {
  return arr[getRandomInt(0, arr.size()-1, MT)];
}

using Time = std::chrono::system_clock;
static double getElapsedTime(const std::chrono::system_clock::time_point&
                             t_start)
{
  Time::time_point t_end = Time::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>
    (t_end-t_start).count();
}
