#ifndef __TEST_FUNCTIONS_H_SH__
#define __TEST_FUNCTIONS_H_SH__

#include <vector>


typedef uint32_t (*re_hash_int_type) (const uint32_t essai,const uint32_t m,const uint32_t index,const int& key);
typedef uint32_t (*hash_int_type) (const int& key,const uint32_t m);

void table_debug0(hash_int_type hash,re_hash_int_type re_hash);
void table_debug1(hash_int_type hash,re_hash_int_type re_hash);

bool devide(const std::vector<int>& v,int num);
std::vector<int> prime_number(int n);
std::vector<int> get_keys(int n,int max_key);



/**
performance pour insertion et recherche d'une seul clé
*/
void table_test_time1(hash_int_type hash,re_hash_int_type re_hash);
/**
performance pour insertion et recherche de n clés
*/
void table_test_time2(hash_int_type hash,re_hash_int_type re_hash,const std::string & file_name);


#endif