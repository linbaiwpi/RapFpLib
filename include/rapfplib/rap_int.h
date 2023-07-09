#pragma once
#include <cstdint>

namespace rap {

  template <int W, bool S> class rap_int {
  public:
    rap_int();
    void set_data(int32_t);
    void set_data(float);
    void set_data(double);
    int32_t get_data();
    uint32_t get_rawdata();

  private:
    int32_t val_;
    int32_t width_;
    bool signed_;
  };

  template <int W, bool S> rap_int<W, S>::rap_int() {
    val_ = 0;
    width_ = W;
    signed_ = S;
  }

  template <int W, bool S> void rap_int<W, S>::set_data(int32_t in_val) {
    int32_t max_val_s_ = (1 << (width_ - 1)) - 1;
    int32_t min_val_s_ = -(1 << (width_ - 1));
    int32_t max_val_u_ = (1 << (width_));

    if (signed_) {  // signed
      if (in_val > max_val_s_) {
        val_ = max_val_s_;
      } else if (in_val < min_val_s_) {
        val_ = min_val_s_;
      } else {
        val_ = in_val;
      }
    } else {  // unsigned
      if (in_val > max_val_u_) {
        val_ = max_val_u_;
      } else if (in_val < 0) {
        val_ = 0;
      } else {
        val_ = in_val;
      }
    }
  };

  template <int W, bool S> void rap_int<W, S>::set_data(float in_val) {
    // truncate, round toward 0
    set_data(int32_t(in_val));
    // TODO: support more rounding modes
  };

  template <int W, bool S> void rap_int<W, S>::set_data(double in_val) {
    // truncate, round toward 0
    set_data(int(in_val));
    // TODO: support more rounding modes
  };

  template <int W, bool S> int32_t rap_int<W, S>::get_data() { return val_; };
  template <int W, bool S> uint32_t rap_int<W, S>::get_rawdata() { return (val_ & ((1 << W) - 1)); };

}  // namespace rap
