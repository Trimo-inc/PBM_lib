#include "../include/pbm_types.h"
#include "../include/pbm_nums.h"

#include <string.h>
#include <stdlib.h>

struct pbm_nums pbm_nums_create(const char* strings)
{   
    struct pbm_nums nums;
    nums.size = strlen(strings);
    if (nums.size) {
        nums.data = (char*)malloc(nums.size);
        memcpy(nums.data, strings, nums.size);
    }
    return nums;
}


void pbm_nums_init(struct pbm_nums* nums, const char* strings)
{
    pbm_nums_delete(nums);
    *nums = pbm_nums_create(strings);
}


void pbm_nums_delete(struct pbm_nums* nums)
{
    if (nums) {
        if (nums->data) {
            free(nums->data);
        }
    }
}