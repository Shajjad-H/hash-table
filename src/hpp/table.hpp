#ifndef _HASH_TABLE_SH_H_
#define _HASH_TABLE_SH_H_


/**
	types for class:
		K: key, D: data
	in order to use the = operator for the key:K and data:K must be overloaded.
	
*/

#include <cstdint>


template<typename K, typename D>
class Table;

enum State
{
	empty, taken, released
};


template<typename K, typename D>
class Cell
{
protected:
	D m_data;
	K m_key;
	State m_state;
	uint32_t nb_try_for_insert;

public:
	Cell() { m_state =  empty; nb_try_for_insert=0; }
	Cell(const K & key,const D & data, const State & s,const uint32_t nb_try){
		m_key = key; m_data = data; m_state = s; nb_try_for_insert = nb_try;
	};
	~Cell(){};

	friend Table<K,D>;
};


template<typename K, typename D>
class Table 
{
protected:
    Cell<K,D> *m_tab;
    uint32_t m_size; // MAX TAB SIZE
	/**
	 * the function which is ponted has to garanty the same index for a given key
	*/
	typedef uint32_t(*hash_func_type)(const K&,const uint32_t m);
    hash_func_type m_hash;

	typedef uint32_t (*re_hash_type)(const uint32_t essai,const uint32_t m,const uint32_t index,const K& key);
	re_hash_type m_re_hash;

	typedef void (*for_each_func_type)(const Cell<K,D>&,uint32_t);

	const char * get_state(const State &s) const;
public:
	/**
	 * @param: {
	 *				max_table_size: the max size of the table. 
	 * 				recomended to a prime number as some hash_function uses '%' 
	 * 				operation for the index prime%int!=0. 
	 *			}
	 *			{
	 *				re_hash: this function should garanty after m_size call it will return the 
	 *				value of hash_function(). if not an infinit loop will occer
	 *			}
	*/
	Table(const uint32_t max_table_size, hash_func_type hash_function, re_hash_type re_hash);
	~Table();
	/**
	 * precondition: the same key may not be inserted. if it alredy exists then insert doesn't do anything.
	 * post-condition: find a place for key to inserts it and returns the index.
	 * 				   if no place is left or found in the table then size() is returned
	*/
	uint32_t insert(const Cell<K,D> & m_Cell);
	uint32_t insert(const K key,const D data);

	void for_each(for_each_func_type f) const;
	uint32_t size() const;

	void print() const;
	void print_debug() const;
	void print_filled() const;
	/**
	 * precondition: none
	 * postcondition: if key is in the tble returns the index else size().
	 * note: if element doesn't belong to the table then we have two ways to inform the calling function
	 *			- we return -1. this case we loose the advantage of uint
	 *			- or we could return the m_size as this index is also not valid.
	*/
	uint32_t find(const K & key) const;
	Cell<K,D> & get_Cell(const K & key) const;
	D & get_data(const K&) const;
	/**
	 * precondition: none
	 * post-condition: if the key already existes then the Cell is released.
	*/
	void remove(const K & key);
	/**
	 * precondition: the key may not be absent from the table. if the key is absent then 
	 * 				 nothing is done.
	 * post-condition: if the key is in the table then the data asociated is updated. 
	 * 				   otherwise an warning is printed on the console. 
	*/
	void modify(const K& key, const D& data);

};

#endif

#include "../table.cpp"



