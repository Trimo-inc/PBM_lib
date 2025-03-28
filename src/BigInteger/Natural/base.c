#include "pbm_natural.h"
#include <string.h>
#include <stdlib.h>

void _pbm_natural_default_init(pbm_Natural_ptr _inatural)
{
    _inatural->_size = 0;
    _inatural->digits = NULL;
}

void _pbm_natural_default_init_s(pbm_Natural_ptr _inatural)
{
    _pbm_natural_delete(_inatural);
    _pbm_natural_default_init(_inatural);
}


void __pbm_natural_custom_init(pbm_Natural_ptr _inatural, pbm_digit_t *const _digits, const size_t __size)
{
    _inatural->digits = _digits;
    _inatural->_size  = __size;
}

void __pbm_natural_custom_init_s(pbm_Natural_ptr _inatural, pbm_digit_t *const _digits, const size_t __size)
{
    _pbm_natural_delete(_inatural);
    __pbm_natural_custom_init(_inatural, _digits, __size);
}

void _pbm_natural_custom_init(pbm_Natural_ptr _inatural, const pbm_digit_t *_digits, const size_t __size)
{
    const size_t SIZE = __size * sizeof(pbm_digit_t);
    pbm_digit_t* _new = (pbm_digit_t*)malloc(SIZE);
    memcpy(_new, _digits, SIZE);

    __pbm_natural_custom_init(_inatural, _new, __size);
}

void _pbm_natural_custom_init_s(pbm_Natural_ptr _inatural, const pbm_digit_t *_digits, const size_t __size)
{
    _pbm_natural_delete(_inatural);
    _pbm_natural_custom_init(_inatural, _digits, __size);
}


void _pbm_natural_i_init(pbm_Natural_ptr _inatural, pbm_digit_t _number)
{
    *_inatural->digits = _number;
    _inatural->_size   = 1;
}

void _pbm_natural_i_init_s(pbm_Natural_ptr _inatural, pbm_digit_t _number)
{
    _pbm_natural_delete(_inatural);
    _pbm_natural_i_init(_inatural, _number);
}


void _pbm_natural_copy_init(pbm_Natural_ptr _inatural, const pbm_Natural_ptr _inatural_copy)
{
    _pbm_natural_custom_init(_inatural, _inatural_copy->digits, _inatural_copy->_size);
}

void _pbm_natural_copy_init_s(pbm_Natural_ptr _inatural, const pbm_Natural_ptr _inatural_copy)
{
    _pbm_natural_delete(_inatural);
    _pbm_natural_copy_init(_inatural, _inatural_copy); // inline 
}


void __pbm_natural_move_init(pbm_Natural_ptr _inatural, const pbm_Natural_ptr _inatural_move)
{
    _inatural = _inatural_move;
}

void __pbm_natural_move_init_s(pbm_Natural_ptr _inatural, const pbm_Natural_ptr _inatural_move)
{
    _pbm_natural_delete(_inatural);
    __pbm_natural_move_init(_inatural, _inatural_move);
}


void _pbm_natural_move_init(pbm_Natural_ptr _inatural, pbm_Natural_ptr _inatural_move)
{
    __pbm_natural_move_init(_inatural, _inatural_move);
    _inatural_move = NULL;
}

void _pbm_natural_move_init_s(pbm_Natural_ptr _inatural, pbm_Natural_ptr _inatural_move)
{
    __pbm_natural_move_init_s(_inatural, _inatural_move);
    _inatural_move = NULL;
}


void _pbm_natural_delete(pbm_Natural_ptr _inatural)
{
    if (_inatural) {
        if (_inatural->_size && _inatural->digits) {
            free(_inatural->digits);
        }
        free(_inatural);
        _inatural = NULL;
    }
}