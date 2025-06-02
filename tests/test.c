#include "../include/pbm_lib.h"

#include "testing.h"
#include <string.h>
#include <stdlib.h>

extern FILE* _log; 



// Using valgrind
void memory_test()
{
	pbm_Natural_ptr pt_big;
	{
		char const num[255] = "123456789ABCDEF";
		struct pbm_Natural* ibig =  __pbm_natural_create((char*)num, 16);
		
		__pbm_natural_move_init(&pt_big, &ibig);
		TEST(pt_big == ibig, "Error: not equal address");
	}
	_pbm_natural_delete(pt_big);
}

void correct_test()
{
	enum pbm_err err;
	char buff[64];
	{ // creating 
		pbm_Natural_ptr number = _pbm_natural_create_s("123V", hex, &err);
		TEST(err == IS_NOT_VALID, "Error: correct %s", buff);
		_pbm_natural_delete(number); // Free `number`
	}
	{
		char str[] = "123456789";
		char* pstr = str;
		pbm_Natural_ptr number, number_hex;
		TIME_TEST(number 	 =  _pbm_natural_create(str, 10);); // copy
		TIME_TEST(number_hex = __pbm_natural_create(str, 10););	// non-copy
		TEST(pstr == str, "pstr is new allocation");
		
		_pbm_natural_delete(number);
		_pbm_natural_delete(number_hex);
	}
	{
		char str_decimal[] = "12345678901234567890123456789012345678901234567890";
		char str_hex[]     = "8727F6369AAF83CA15026747AF8C7F196CE3F0AD2";
		char str_octal[]   = "2071177306646527603624124023164365743077431331617605322";
		char str_4[]       = "2013021333120312212222332003302201110002121310132233203013330121123032033300223102";
		char str_bin[]     = "10000111001001111111011000110110100110101010111110000011110010100001010100000010011001110100011110101111100011000111111100011001011011001110001111110000101011010010";
		// Что будет быстрее? time testing
		pbm_Natural_ptr num;
		const uint32_t RANGE = 0x1FFF; 
		TIME_TEST_RANGE({
			num = _pbm_natural_create(str_decimal, 10);
			_pbm_natural_delete(num);
		}, RANGE); // It's slow, because str_decimal a lot of copy and change
		TIME_TEST_RANGE({
			num = _pbm_natural_create(str_hex, 16);
			_pbm_natural_delete(num);
		}, RANGE); // It's faster
		TIME_TEST_RANGE({
			num = _pbm_natural_create(str_octal, 8);
			_pbm_natural_delete(num);
		}, RANGE);
		TIME_TEST_RANGE({
			num = _pbm_natural_create(str_4, 4);
			_pbm_natural_delete(num);
		}, RANGE);
		TIME_TEST_RANGE({
			num = _pbm_natural_create(str_bin, 2);
			_pbm_natural_delete(num);
		}, RANGE);
		// correct_testing
		{
			pbm_Natural_ptr decimal, hex, octal, _4, bin;
			decimal = _pbm_natural_create(str_decimal, 10);
			hex     = _pbm_natural_create(str_hex, 16);
			octal   = _pbm_natural_create(str_octal, 8);
			_4      = _pbm_natural_create(str_4, 4);  
			bin     = _pbm_natural_create(str_bin, 2); 
			TEST(
				(decimal->_size == hex->_size) && (decimal->_size == octal->_size) \
				&& (decimal->_size == _4->_size) && (_4->_size == bin->_size)
			, "Incorrect size!");

			for(size_t x = 0; x < decimal->_size; ++x) {
				pbm_digit_t d = decimal->digits[x],
				h = hex->digits[x], o = octal->digits[x], __4 = _4->digits[x], b = bin->digits[x];
				TEST((d == h) && (d == o) && (d == __4) && (d == b),
				"10: %u\n"
				"16: %u\n"
				"8:  %u\n"
				"4:  %u\n"
				"2:  %u\n",
				d, h, o, __4, b
				);

			}
			_pbm_natural_delete(decimal);
			_pbm_natural_delete(hex);
			_pbm_natural_delete(octal);
			_pbm_natural_delete(_4);
			_pbm_natural_delete(bin);
		}
	}
}

void comp_n(void)
{
	{
	pbm_Natural_ptr n1 = _pbm_natural_create("100000000000000", 10);
	pbm_Natural_ptr n2 = _pbm_natural_create("100000000000001", 10);
	{
		TEST(_pbm_natural_not_equal(n1, n2) == true, "Not equal");
		TEST(_pbm_natural_more(n1, n2) == false, "Not more");
		TEST(_pbm_natural_more_or_equal(n1, n2) == false, "Not more or equal");
		TEST((_pbm_natural_less(n1, n2) == true) && (_pbm_natural_less_or_equal(n1, n2) == true), "Not less or equal");
		_pbm_natural_delete(n1);
		_pbm_natural_delete(n2);
	}
	}
}

void bit_and(void)
{
	pbm_Natural_ptr n1 = _pbm_natural_create("10101", 2);
	pbm_Natural_ptr n2 = _pbm_natural_create("01110", 2);
	{
		pbm_Natural_ptr n = _pbm_natural_bit_and(n1, n2);
		pbm_Natural_ptr c = _pbm_natural_create("00100", 2);
		TEST(_pbm_natural_equal(n, c) == true, "NO");
		_pbm_natural_delete(n);
		_pbm_natural_delete(c);
	}
	_pbm_natural_delete(n1);
	_pbm_natural_delete(n2);
	n1 = _pbm_natural_create("1000000000010000000010001", 2);
	n2 = _pbm_natural_create("1000010000000010000100001", 2);
	{
		pbm_Natural_ptr n = _pbm_natural_bit_and(n1, n2);
		pbm_Natural_ptr c = _pbm_natural_create("1000000000000000000000001", 2);
		TEST(_pbm_natural_equal(n, c) == true, "NO");
		_pbm_natural_delete(n);
		_pbm_natural_delete(c);
	}
	_pbm_natural_delete(n1);
	_pbm_natural_delete(n2);
}

int main(void)
{
	_log = stdout;
	#if 0
	memory_test();
	correct_test();	
	comp_n();
	#endif
	bit_and();
	return 0;
}