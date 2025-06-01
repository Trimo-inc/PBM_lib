#include "pbm_natural.h"
#include "pbm_types.h"

bool _pbm_natural__bool(const pbm_Natural_ptr _inatural)
{
    return (char*)*_inatural->digits;
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