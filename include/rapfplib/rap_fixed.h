#pragma once

#include <rapfplib/config.h>

#include <cstdint>
#include <cmath>

namespace rap {

  // I - point position, means the point is located after which bit
  template <int W, int I, bool S, rap_rnd_mode_t R = RAP_RNE> class rap_fixed {
  public:
    rap_fixed();
    rap_fixed(int);
    rap_fixed(const rap_fixed& data);
    void set_data(int);
    int get_data();
    int get_bitwidth();
    int get_point_pos();

    rap_fixed<W, I, S, R> operator=(const rap_fixed& data);
    template <int W2, int I2, bool S2, rap_rnd_mode_t R2>
    rap_fixed<W, I, S, R> operator=(const rap_fixed<W2, I2, S2, R2>& data);

    rap_fixed<W, I, S, R> operator+(const rap_fixed& data);
    template <int W2, int I2, bool S2, rap_rnd_mode_t R2>
    rap_fixed<W, I, S, R> operator+(const rap_fixed<W2, I2, S2, R2>& data);

    float show_data();
    // int get_rawdata();

  private:
    int val_;
    int width_;
    int point_;
    bool signed_;
  };

  template <int W, int I, bool S, rap_rnd_mode_t R>
  rap_fixed<W, I, S, R>::rap_fixed() {
    val_ = 0;
    width_ = W;
    point_ = I;
    signed_ = S;
  }

  template <int W, int I, bool S, rap_rnd_mode_t R> rap_fixed<W, I, S, R>::rap_fixed(int data) {
    width_ = W;
    point_ = I;
    signed_ = S;
    set_data(data);
  }

  template <int W, int I, bool S, rap_rnd_mode_t R>
  rap_fixed<W, I, S, R>::rap_fixed(const rap_fixed& data) {
    width_ = data.width_;
    point_ = data.point_;
    signed_ = data.signed_;
    set_data(data);
  }

  template <int W, int I, bool S, rap_rnd_mode_t R>
  void rap_fixed<W, I, S, R>::set_data(int in_val) {
    val_ = in_val & ((1 << W) - 1);
    if (signed_) {
      if ((in_val >> (W - 1) & 0x1) == 0x1) {
        val_ = in_val & (~((1 << W) - 1));
      }
    }
  }

  template <int W, int I, bool S, rap_rnd_mode_t R> int rap_fixed<W, I, S, R>::get_data() {
    return val_;
  }

  template <int W, int I, bool S, rap_rnd_mode_t R> int rap_fixed<W, I, S, R>::get_bitwidth() {
    return width_;
  }

  template <int W, int I, bool S, rap_rnd_mode_t R> int rap_fixed<W, I, S, R>::get_point_pos() {
    return point_;
  }

  template <int W, int I, bool S, rap_rnd_mode_t R> float rap_fixed<W, I, S, R>::show_data() {
    // TODO use override * instead of math.h
    return float(val_) * pow(2, -I);
  }

  template <int W, int I, bool S, rap_rnd_mode_t R>
  rap_fixed<W, I, S, R> rap_fixed<W, I, S, R>::operator=(const rap_fixed& data) {
    width_ = data.width_;
    point_ = data.point_;
    signed_ = data.signed_;
    return rap_fixed<W, I, S, R>(data.val_);
  }

  template <int W, int I, bool S, rap_rnd_mode_t R>
  template <int W2, int I2, bool S2, rap_rnd_mode_t R2>
  rap_fixed<W, I, S, R> rap_fixed<W, I, S, R>::operator=(const rap_fixed<W2, I2, S2, R2>& data) {
    width_ = data.width_;
    point_ = data.point_;
    signed_ = data.signed_;
    return rap_fixed<W, I, S, R>(data.val_);
  }

  template <int W, int I, bool S, rap_rnd_mode_t R>
  rap_fixed<W, I, S, R> rap_fixed<W, I, S, R>::operator+(const rap_fixed<W, I, S, R>& data) {
    return rap_fixed<W, I, S, R>(this->get_data() + data.get_data());
  }

  template <int W, int I, bool S, rap_rnd_mode_t R>
  template <int W2, int I2, bool S2, rap_rnd_mode_t R2>
  rap_fixed<W, I, S, R> rap_fixed<W, I, S, R>::operator+(const rap_fixed<W2, I2, S2, R2>& data) {
    if (I > I2) {
      return rap_fixed<W, I, S, R>(this->get_data() + (data.get_data() >> (I - I2)));
    } else {
      return rap_fixed<W, I, S, R>(this->get_data() + (data.get_data() << (I - I2)));
    }
  }

}  // namespace rap
