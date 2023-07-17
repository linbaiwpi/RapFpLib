#pragma once

#include <cstdint>

namespace rap {

  template <int W, int I, bool S> class rap_fixed {
  public:
    rap_fixed();
    void set_data(uint32_t);
    double get_data();
    uint32_t get_rawdata();

  private:
    double val_;
    int32_t width_;
    int32_t point_;
    bool signed_;
  };

  template <int W, int I, bool S> rap_fixed<W, I, S>::rap_fixed() {
    val = 0;
    width_ = W + I;
    point_ = I;
    signed_ = S;
  };

  template <int W, int I, bool S> void rap_fixed<W, I, S>::set_data(uint32_t in_val){

  };

}  // namespace rap
