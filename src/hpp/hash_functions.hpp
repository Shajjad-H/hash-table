#ifndef __HASH_FUNCTIONS_H_SH__
#define __HASH_FUNCTIONS_H_SH__

#include <cstdint>

uint32_t hash_int(const int& key,const uint32_t m )
{
    return key%m;   
}
/**
 * fonction re-hash linaire
*/
uint32_t re_hash_int(const uint32_t essai,const uint32_t m,const uint32_t index,const int& key)
{
    return (index+1)%m;
}

uint32_t re_hash_int_quad(const uint32_t essai,const uint32_t m,const uint32_t index,const int& key)
{
    return (essai*essai + index) % m;
}

uint32_t re_hash_int_double(const uint32_t essai,const uint32_t m,const uint32_t index,const int& key)
{
    return (index + 2*essai + 1) % m;
}

#endif