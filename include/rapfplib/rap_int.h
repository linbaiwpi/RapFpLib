#pragma once
#include <cstdint>
#include <iostream>

namespace rap {

  template <int W, bool S> class rap_int {
  public:
    rap_int();
    rap_int(const rap_int& data);
    rap_int(const int data);
    template <int W2, bool S2> rap_int(const rap_int<W2, S2>& data);

    void set_data(int);
    void set_data(float);
    void set_data(double);
    void set_bitwidth(int);
    void set_sign(int);
    int get_data() const;
    int get_bitwidth() const;
    int get_sign() const;
    uint get_rawdata();

    // operator =
    rap_int<W, S>& operator=(const rap_int& data);
    template <int W2, bool S2> void operator=(rap_int<W2, S2>& data);
    // operator +
    rap_int operator+(const rap_int& data);
    template <int W2, bool S2> rap_int operator+(const rap_int<W2, S2>& data);
    // operator -
    rap_int operator-(const rap_int& data);
    template <int W2, bool S2> rap_int operator-(const rap_int<W2, S2>& data);
    // operator *
    rap_int operator*(const rap_int& data);
    template <int W2, bool S2> rap_int operator*(const rap_int<W2, S2>& data);
    // operator <<
    rap_int operator<<(const int shift_bit);
    // operator >>
    rap_int operator>>(const int shift_bit);

  private:
    int val_;
    int width_;
    bool signed_;
  };

  template <int W, bool S> rap_int<W, S>::rap_int() {
    val_ = 0;
    width_ = W;
    signed_ = S;
  }

  template <int W, bool S> rap_int<W, S>::rap_int(const rap_int& data) {
    val_ = data.val_;
    width_ = data.width_;
    signed_ = data.signed_;
  }

  // copy constructor
  template <int W, bool S> rap_int<W, S>::rap_int(const int data) {
    width_ = W;
    signed_ = S;
    set_data(data);
  }

  template <int W, bool S> template <int W2, bool S2>
  rap_int<W, S>::rap_int(const rap_int<W2, S2>& data) {
    // FIXME
    set_data(data.get_data());
  }

  template <int W, bool S> void rap_int<W, S>::set_data(int in_val) {
    // sign extension
    if (signed_) {
      if ((in_val >> (width_ - 1)) & 0x1)
        val_ = in_val | (~((1 << width_) - 1));
      else
        val_ = in_val & ((1 << width_) - 1);
    } else {
      val_ = in_val & ((1 << width_) - 1);
    }

#ifdef OVERFLOW_MODE_SATURATE
    int max_val_s_ = (1 << (width_ - 1)) - 1;
    int min_val_s_ = -(1 << (width_ - 1));
    int max_val_u_ = (1 << (width_)) - 1;
    int bias_ = (1 << (width_ - 1));
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
#endif
  }

  template <int W, bool S> void rap_int<W, S>::set_data(float in_val) {
    // truncate, round toward 0
    set_data(int(in_val));
    // TODO: support more rounding modes
  }

  template <int W, bool S> void rap_int<W, S>::set_data(double in_val) {
    // truncate, round toward 0
    set_data(int(in_val));
    // TODO: support more rounding modes
  }

  template <int W, bool S> void rap_int<W, S>::set_bitwidth(int bitwidth) { width_ = bitwidth; };
  template <int W, bool S> void rap_int<W, S>::set_sign(int sign) { signed_ = sign; };

  template <int W, bool S> int rap_int<W, S>::get_data() const { return val_; };
  template <int W, bool S> int rap_int<W, S>::get_bitwidth() const { return width_; };
  template <int W, bool S> int rap_int<W, S>::get_sign() const { return signed_; };
  template <int W, bool S> uint rap_int<W, S>::get_rawdata() {
    return (val_ & ((1 << width_) - 1));
  }

  // override =
  // template <int W, bool S> rap_int<W, S>& rap_int<W, S>::operator=(const int& data) {
  //  set_data(data);
  //  return *this;
  //};

  template <int W, bool S> rap_int<W, S>& rap_int<W, S>::operator=(const rap_int& data) {
    set_data(data.get_data());
    set_bitwidth(data.get_bitwidth());
    set_sign(data.get_sign());
    return *this;
  }

  template <int W, bool S> template <int W2, bool S2>
  void rap_int<W, S>::operator=(rap_int<W2, S2>& data) {
    // FIXME
    set_data(data.get_data());
  }

  // override +
  template <int W, bool S> rap_int<W, S> rap_int<W, S>::operator+(const rap_int& data) {
    return rap_int<W, S>(get_data() + data.get_data());
  }

  template <int W, bool S> template <int W2, bool S2>
  rap_int<W, S> rap_int<W, S>::operator+(const rap_int<W2, S2>& data) {
    // FIXME
    set_data(get_data() + data.get_data());
  }

  // override -
  template <int W, bool S> rap_int<W, S> rap_int<W, S>::operator-(const rap_int& data) {
    return rap_int<W, S>(get_data() - data.get_data());
  }

  template <int W, bool S> template <int W2, bool S2>
  rap_int<W, S> rap_int<W, S>::operator-(const rap_int<W2, S2>& data) {
    // FIXME
    set_data(get_data() - data.get_data());
  }

  // override *
  template <int W, bool S> rap_int<W, S> rap_int<W, S>::operator*(const rap_int& data) {
    int prod = this->get_data() * data.get_data();
    prod &= (1 << W) - 1;
    return rap_int<W, S>(prod);
  }

  template <int W, bool S> template <int W2, bool S2>
  rap_int<W, S> rap_int<W, S>::operator*(const rap_int<W2, S2>& data) {
    int prod = this->get_data() * data.get_data();
    prod &= (1 << W) - 1;
    return rap_int<W, S>(prod);
  }

  // override <<
  template <int W, bool S> rap_int<W, S> rap_int<W, S>::operator<<(const int shift_bit) {
    return rap_int<W, S>(this->get_data() << shift_bit);
  }

  // override >>
  template <int W, bool S> rap_int<W, S> rap_int<W, S>::operator>>(const int shift_bit) {
    return rap_int<W, S>(this->get_data() >> shift_bit);
  }

}  // namespace rap
