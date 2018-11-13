#ifndef _HASH_TABLE_SH_CPP_
#define _HASH_TABLE_SH_CPP_

#include "table.hpp"
#include <stddef.h>
#include <iostream>



template <typename K, typename D>
Table<K, D>::Table(const uint32_t max_table_size, hash_func_type hash_function, re_hash_type re_hash)
{
	m_size = max_table_size;
	m_hash = hash_function;
	m_re_hash = re_hash;
	m_tab = new Cell<K, D>[m_size];
}

template <typename K, typename D>
Table<K, D>::~Table()
{
	m_hash = NULL;
	m_re_hash = NULL;
	delete[] m_tab;
	m_tab = NULL;
}

template <typename K, typename D>
uint32_t Table<K, D>::size() const
{
	return m_size;
}


template <typename K, typename D>
uint32_t Table<K, D>::insert(const K key, const D data)
{
	uint32_t index = m_hash(key, m_size);
	int i = index;
	uint32_t essai = 0;
	while (m_tab[i].m_state ==  taken)
	{
		// duplication is not allowed
		if(m_tab[i].m_key == key)
			return i;
		i = m_re_hash(essai++, m_size, i,key);
		//if (i == index)
		//	return size();
		if(essai == size())
			return size();
		
	}
	
	m_tab[i] = Cell<K, D>(key, data,  taken, essai);

	return i;
}

template <typename K, typename D>
void Table<K, D>::print_debug() const
{
	for (uint32_t i = 0; i < m_size; i++)
		std::cout << i << std::endl
				  << "key: " << m_tab[i].m_key << " -- " << get_state(m_tab[i].m_state)
				  << " nb_try: " << m_tab[i].nb_try_for_insert << std::endl
				  << "data: " << m_tab[i].m_data << std::endl
				  << std::endl;
}

template <typename K, typename D>
void Table<K, D>::print() const
{
	std::cout<<"size: "<<size()<<std::endl;
	for (uint32_t i = 0; i < m_size; ++i)
	{
		Cell<K,D> c = m_tab[i];
		std::cout<<"k:"<<c.m_key<<(char)9<<"s:"<<get_state(c.m_state)
			<<(char)9<<"   nb-t:"<<c.nb_try_for_insert<<(char)9<<"d:"<<c.m_data<<std::endl; 
	}


}

template <typename K, typename D>
void Table<K, D>::for_each(for_each_func_type f) const
{
	for(uint32_t i=0; i<m_size;i++) f(m_tab[i],i);
}


template <typename K, typename D>
void Table<K, D>::print_filled() const
{
	
	for(unsigned int i=0; i<m_size; i++)
	{
		if(m_tab[i].m_state == taken)
			std::cout<<"key:"<<m_tab[i].m_key<<" "; 
	}
	std::cout<<std::endl;

}


template <typename K, typename D>
void Table<K, D>::remove(const K & key)
{
	uint32_t index = find(key);

	if(index<size())
		m_tab[index].m_state =  released;
	
}


template <typename K, typename D>
uint32_t Table<K, D>::insert(const Cell<K, D> &cell)
{
	return insert(cell.m_key, cell.m_data);
}

// should be uint not int but prob ret -1.
template <typename K, typename D>
uint32_t Table<K, D>::find(const K &key) const
{
	uint32_t i = m_hash(key, m_size);
	uint32_t essai = 0;


	while (essai < size())
	{
		if(m_tab[i].m_state ==  empty)
			return size();
		if (m_tab[i].m_state ==  taken && m_tab[i].m_key == key )
			return i;

		i = m_re_hash(essai++, m_size, i,key);

	}

	return size();
}

template <typename K, typename D>
const char *Table<K, D>::get_state(const State &s) const
{
	if (s ==  empty)
		return "empty";
	if (s ==  released)
		return "released";
	return "taken";
}

template <typename K, typename D>
void Table<K, D>::modify(const K& key, const D& data)
{
	uint32_t i = find(key);
	if(i < size())
		m_tab[i].m_data = data;
}


#endif