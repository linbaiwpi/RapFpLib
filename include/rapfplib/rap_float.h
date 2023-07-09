#include <cstdint>

// consider special case
// consider HW limitation
// optional: inf, nan, subnorm

class rap_float {

public:
    uint32_t get_rawdata();
    void set_data(uint32_t, bool);
    void set_data(double);
    void set_exponent(int32_t);
    void set_mantissa(rap_int);
    void set_mantissa(double);
    void set_mantissa(rap_fixed);
    void normalize();

private:
    double mant;
    int exp;

};
