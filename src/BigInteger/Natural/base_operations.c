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
    return (bool)*_inatural->digits;
}


bool _pbm_natural_equal(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2)
{
    bool _ret = false;
    if (_inatural_1->_size == _inatural_2->_size) {
        for(size_t i = 0; i < _inatural_1->_size; ++i) {
            if (_inatural_1->digits[i] == _inatural_2->digits[i])
                _ret = true;
            else break;
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

        _pbm_natural_normalization(_ret);
    
    }
    return _ret;
}

#undef MIN
#undef MAX