#include "pbm_natural.h"
#include "pbm_types.h"
#include <stdlib.h>

void _pbm_natural_normalization(pbm_Natural_ptr _inatural)
{
    size_t s = _inatural->_size;
    while(s > 1 && _inatural->digits[s - 1] == 0) {
        --s;
    }
    if(s != _inatural->_size) {
        pbm_digit_t* digits = _pbm_digit_copy(_inatural->digits, s);
        __pbm_natural_stack_delete(_inatural);
        __pbm_natural_custom_init(_inatural, digits, s);
    }
}


bool _pbm_natural__bool(const pbm_Natural_ptr _inatural)
{
    return (bool)(_inatural->_size > 1 || (*_inatural->digits != (pbm_digit_t)0));
}


bool _pbm_natural_equal(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2)
{
    bool _ret = false;
    if (_inatural_1->_size == _inatural_2->_size) {
        for(size_t i = 0; i < _inatural_1->_size; ++i) {
            if (_inatural_1->digits[i] == _inatural_2->digits[i])
                _ret = true;
            else { _ret = false; break; }
        }
    }
    return _ret;
}

bool _pbm_natural_not_equal(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2)
{
    #ifdef ____PBM_inline
        bool _ret = true;
        if (_inatural_1->_size == _inatural_2->_size) {
            for(size_t i = 0; i < _inatural_1->_size; ++i) {
                if(_inatural_1->digits[i] == _inatural_2->digits[i]) {
                    _ret = false;
                    break;
                }
            }
        }
        return _ret;
    #else 
        return !(_pbm_natural_equal(_inatural_1, _inatural_2));
    #endif
}

bool _pbm_natural_more(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2)
{
    bool _ret = true;
    if (_inatural_1->_size > _inatural_2->_size)
        return _ret;
    if (_inatural_1->_size == _inatural_2->_size) {
        size_t i = _inatural_1->_size;
        while(i-- > 0) {
            if(_inatural_1->digits[i] <= _inatural_2->digits[i]) {
                _ret = false;
                break;
            }
        }
    }
    return _ret;
}

bool _pbm_natural_less(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2)
{
    bool _ret = true;
    if (_inatural_1->_size < _inatural_2->_size)
        return _ret;
    if (_inatural_1->_size == _inatural_2->_size) {
        size_t i = _inatural_1->_size;
        while(i-- > 0) {
            if(_inatural_1->digits[i] >= _inatural_2->digits[i]) {
                _ret = false;
                break;
            }
        }
    }
    return _ret;
}

bool _pbm_natural_more_or_equal(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2)
{
    #ifdef ____PBM_inline
        bool _ret = true;
        if (_inatural_1->_size > _inatural_2->_size)
            return _ret;
        if (_inatural_1->_size == _inatural_2->_size) {
            size_t i = _inatural_1->_size;
            while(i-- > 0) {
                if(_inatural_1->digits[i] < _inatural_2->digits[i]) {
                    _ret = false;
                    break;
                }
            }
        }
        return _ret;
    #else
        return _pbm_natural_more(_inatural_1, _inatural_2) || _pbm_natural_equal(_inatural_1, _inatural_2);
    #endif
}

bool _pbm_natural_less_or_equal(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2)
{
    #ifdef ____PBM_inline
        bool _ret = true;
        if (_inatural_1->_size , _inatural_2->_size)
            return _ret;
        if (_inatural_1->_size == _inatural_2->_size) {
            size_t i = _inatural_1->_size;
            while(i-- > 0) {
                if(_inatural_1->digits[i] > _inatural_2->digits[i]) {
                    _ret = false;
                    break;
                }
            }
        }
        return _ret;
    #else
        return _pbm_natural_less(_inatural_1, _inatural_2) || _pbm_natural_equal(_inatural_1, _inatural_2);
    #endif
}


#if defined(____PBM_bit_not)
void _pbm_natural_bit_not(pbm_Natural_ptr _inatural)
{
    for(size_t i = 0; i < _inatural->_size; ++i) {
        _inatural->digits[i] = ~(_inatural->digits[i]);
    }
    _pbm_natural_normalization(_inatural);
}
#endif

void _pbm_natural_bit_and__int(pbm_Natural_ptr _inatural, const pbm_digit_t _inum)
{
    _inatural->digits[0] &= _inum;
    _pbm_natural_normalization(_inatural);
}

#define MIN(_1, _2) ((_1 < _2) ? (_1) : (_2))
#define MAX(_1, _2) ((_1 > _2) ? (_1) : (_2))

pbm_Natural_ptr _pbm_natural_bit_and(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2)
{
    pbm_Natural_ptr _ret = NULL;
    size_t min_p;
    {
        size_t max_p;
        if (_inatural_1->_size < _inatural_2->_size) {
            min_p = _inatural_1->_size;
            max_p = _inatural_2->_size;
        } else {min_p = _inatural_2->_size; max_p = _inatural_1->_size;}
        _ret = __pbm_natural_size_create(max_p);
    }
    if (_ret) {
        for (size_t i = 0; i < min_p; ++i) {
            _ret->digits[i] = _inatural_1->digits[i] & _inatural_2->digits[i];
        }

        _pbm_natural_normalization(_ret);
    }
    return _ret;
}


void _pbm_natural_bit_or__int(pbm_Natural_ptr _inatural, const pbm_digit_t _inum)
{
    _inatural->digits[0] |= _inum;
    _pbm_natural_normalization(_inatural);
}

pbm_Natural_ptr _pbm_natural_bit_or(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2)
{
    size_t i = 0, max_size;
    pbm_digit_t* digits;
    if (_inatural_1->_size > _inatural_2->_size) {
        max_size = _inatural_1->_size;
        digits   = _inatural_1->digits;
    } else {
        max_size = _inatural_2->_size;
        digits   = _inatural_2->digits;
    }
    pbm_Natural_ptr _ret    = __pbm_natural_size_create(max_size);
    if (_ret) {
        while (i < _inatural_1->_size && i < _inatural_2->_size) {
            _ret->digits[i] = _inatural_1->digits[i] | _inatural_2->digits[i];
            ++i;
        }
        while (i < max_size) {
            _ret->digits[i] = digits[i];
            ++i;
        }
    
    }
    return _ret;
}


void _pbm_natural_bit_xor__int(pbm_Natural_ptr _inatural, const pbm_digit_t _inum)
{
    _inatural->digits[0] ^= _inum;
}

pbm_Natural_ptr _pbm_natural_bit_xor(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2)
{
    size_t i = 0, max_size;
    pbm_digit_t* digits;
    if (_inatural_1->_size > _inatural_2->_size) {
        max_size = _inatural_1->_size;
        digits   = _inatural_1->digits;
    } else {
        max_size = _inatural_2->_size;
        digits   = _inatural_2->digits;
    }
    pbm_Natural_ptr _ret    = __pbm_natural_size_create(max_size);
    if (_ret) {
        while (i < _inatural_1->_size && i < _inatural_2->_size) {
            _ret->digits[i] = _inatural_1->digits[i] ^ _inatural_2->digits[i];
            ++i;
        }
        while (i < max_size) {
            _ret->digits[i] = digits[i];
            ++i;
        }

        _pbm_natural_normalization(_ret);
    
    }
    return _ret;
}


void _pbm_natural_bit_logic_lshift__int(pbm_Natural_ptr _inatural, const pbm_digit_t shift_bits)
{
    if (shift_bits == 0) return;
    const pbm_digit_t full_digits    = shift_bits / PBM_digit_bits;
    const pbm_digit_t shift_in_digit = shift_bits % PBM_digit_bits;

    size_t __size = _inatural->_size + full_digits;
    if (shift_in_digit > 0) {
        // Будет ли перенос в новую цифру
        if (_inatural->_size && (_inatural->digits[_inatural->_size - 1] >> (PBM_digit_bits - shift_in_digit)) != 0)
            ++__size;
    }

    pbm_digit_t* const digits = (pbm_digit_t*)calloc(__size, sizeof(pbm_digit_t));
    if (digits) {
        pbm_digit_t carry = 0;
        for (size_t i = 0; i < _inatural->_size; ++i) {
            if (shift_in_digit > 0) {
                digits[full_digits + i] = (pbm_digit_t)((_inatural->digits[i] << shift_in_digit) | carry);
                carry = _inatural->digits[i] >> (PBM_digit_bits - shift_in_digit);
            } else digits[full_digits + i] = _inatural->digits[i];
        }

        if (shift_in_digit > 0 && carry != 0) {
            digits[full_digits + _inatural->_size] = carry;
        }
        __pbm_natural_custom_init_s(_inatural, digits, __size);
        
    }
}


void _pbm_natural_bit_logic_rshift__int(pbm_Natural_ptr _inatural, const pbm_digit_t shift_bits)
{
    if (shift_bits == 0) return;

    const pbm_digit_t full_digits    = shift_bits / PBM_digit_bits;
    if (full_digits >= _inatural->_size) {
        __pbm_natural_custom_init_s(_inatural, (pbm_digit_t*)calloc(1, sizeof(pbm_digit_t)), 1);
    }
    const pbm_digit_t shift_in_digit = shift_bits % PBM_digit_bits;

    const size_t __size = _inatural->_size - full_digits;
    pbm_digit_t* const digits = (pbm_digit_t*)calloc(__size, sizeof(pbm_digit_t));
    if (digits) {
        pbm_digit_t carry = 0;
        for (size_t i = _inatural->_size - 1; i >= full_digits && i != (size_t)-1; --i) {
            if (shift_in_digit > 0) {
                digits[i - full_digits] = (pbm_digit_t)((_inatural->digits[i] >> shift_in_digit) | carry);
                carry = _inatural->digits[i] << (PBM_digit_bits - shift_in_digit);
            } else digits[i - full_digits] = _inatural->digits[i]; 
        }
        __pbm_natural_custom_init_s(_inatural, digits, __size);
        _pbm_natural_normalization(_inatural);
    }
}


void _pbm_natural_add__int(pbm_Natural_ptr _inatural, const pbm_digit_t _inum)
{
    pbm_digit_t carry = (_inum);
    size_t i = 0;
    while (carry && i < _inatural->_size) {
        pbm_digit_t sum = _inatural->digits[i] + carry;
        carry = (sum < _inatural->digits[i]);
        _inatural->digits[i] = sum;
        ++i;
    }

    if (carry) {
        i = _inatural->_size + 1; // Оптимизация: size_t __size = _inatural->_size + 1;
        pbm_digit_t* digits = (pbm_digit_t*)_pbm_digit_copy(_inatural->digits, i);
        if (digits) {
            digits[_inatural->_size] = carry;
            __pbm_natural_custom_init_s(_inatural, digits, i);
        }
    }
}

pbm_Natural_ptr _pbm_natural_add(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2)
{
    const size_t max_size = (_inatural_1->_size > _inatural_2->_size) ? _inatural_1->_size : _inatural_2->_size;
    const size_t min_size = (_inatural_1->_size < _inatural_2->_size) ? _inatural_1->_size : _inatural_2->_size;

    pbm_Natural_ptr _ret = __pbm_natural_size_create(max_size + 1); // Для запаса
    if (_ret) {
        pbm_digit_t carry = 0;
        {
            pbm_digit_t sum;
            for (size_t i = 0; i < min_size; ++i) {
                sum   = _inatural_1->digits[i] + _inatural_2->digits[i] + carry;
                carry = (sum < _inatural_1->_size || sum < _inatural_2->_size);
                _ret->digits[i] = sum;
            }
            {
                pbm_digit_t* larger = ((_inatural_1->_size > _inatural_2->_size) ? (_inatural_1->digits) : (_inatural_2->digits));
                for (size_t i = min_size; i < max_size; ++i) {
                    sum   = larger[i] + carry;
                    carry = (sum < larger[i]);
                    _ret->digits[i] = sum;
                }
            }
        }
        _pbm_natural_normalization(_ret);
    }
    return _ret;
}


void _pbm_natural_mul__int(pbm_Natural_ptr _inatural, const pbm_digit_t _inum)
{
    if (_inum == 1) return;
    if (_inum == 0) {
        __pbm_natural_custom_init_s(_inatural, (pbm_digit_t*)calloc(1, sizeof(pbm_digit_t)), 1);
        return;
    }
    pbm_digit_t carry = 0;
    {
        for (size_t i = 0; i < _inatural->_size; ++i) {
            // Не константы (для оптимизации памяти)
            pbm_digit_t low_1  = _inatural->digits[i] & PBM_low_mask;
            pbm_digit_t low_2  = _inum & PBM_low_mask;
            // high_1 в дальнейшим выступает в роли low
            pbm_digit_t high_1 = _inatural->digits[i] >> PBM_half_bits;
            pbm_digit_t high_2 = _inum >> PBM_half_bits;
            {
                const pbm_digit_t p0 = low_1 * low_2;
                const pbm_digit_t p1 = low_1 * high_2;
                const pbm_digit_t p2 = high_1 * low_2;
                const pbm_digit_t p3 = high_1 * high_2;
                {
                    low_1  = p1 + p2;
                    low_2  = p3 + (low_1 >> PBM_half_bits) + ((low_1 < p1) ? ((pbm_digit_t)1 << PBM_half_bits) : 0);

                    high_1 = p0 + (low_1 << PBM_half_bits);
                    high_2 = low_2 + (high_1 < p0);
                }
                high_1 += carry;
                carry  = high_2 + (high_1 < carry);
                _inatural->digits[i] = high_1;
            }
        }
    }
    if (carry) {
        size_t __size = _inatural->_size + 1;
        pbm_digit_t* digits = (pbm_digit_t*)_pbm_digit_copy(_inatural->digits, __size);
        if (digits) {
            digits[_inatural->_size] = carry;
            __pbm_natural_custom_init_s(_inatural, digits, __size);
        }
    }
}

pbm_Natural_ptr __pbm_natural_base_mul(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2)
{
    size_t __size = _inatural_1->_size + _inatural_2->_size;
    pbm_Natural_ptr _ret = __pbm_natural_size_create(__size);
    if (_ret) {
        pbm_digit_t carry;
        size_t k;
        for (size_t i = 0; i < _inatural_1->_size; ++i) {
            carry = 0;
            pbm_digit_t prod, sum;
            for (size_t j = 0; j < _inatural_2->_size; ++j) {
                k = i + j;
                prod = _inatural_1->digits[i] * _inatural_2->digits[j];
                sum = _ret->digits[k] + prod + carry;
                _ret->digits[k] = sum;
                carry = ((sum < prod) || sum < _ret->digits[k]);
            }
            k = i + _inatural_2->_size;
            while (carry && k < _ret->_size) {
                sum = _ret->digits[k] + carry;
                _ret->digits[k] = sum;
                carry = (sum < carry);
                ++k;
            }
        }
        _pbm_natural_normalization(_ret);
    }
    return _ret;
}