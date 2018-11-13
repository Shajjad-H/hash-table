
#include "table.hpp"
#include "test_functions.hpp"

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
using namespace std::chrono;

void table_test_time2(hash_int_type hash,re_hash_int_type re_hash,const string &file_name)
{
	
	struct nb_time
	{
		int nb, time;
	};

	int n = 600;
	int max_key = n;

	std::vector<int> primes = prime_number(n);


    time_point <system_clock> start , end;
    vector<nb_time> insert_times;
    vector<nb_time> find_times;

	int diff;

	for(int i=0; i<n; i++)
	{
		Table<int,int> t(primes[i],hash,re_hash);

		std::vector<int> keys = get_keys(primes[i],max_key);

        start = system_clock::now();
		for(int j=0; j< primes[i]; j++ )
			t.insert(keys[i],keys[i]);
		
		end = system_clock::now();
		diff = duration_cast<nanoseconds>(end-start).count();
		insert_times.push_back({primes[i],diff});

		keys = get_keys(primes[i],max_key);
        start = system_clock::now();

		for(int j=0; j< keys.size(); j++ )
			t.find(keys[i]);

		end = system_clock::now();
		diff = duration_cast<nanoseconds>(end-start).count();

		find_times.push_back({primes[i],diff});
		
	}
	
	ofstream file("insert_" + file_name);
	for(int i=0; i<insert_times.size(); i++)
	{
		file<<insert_times[i].nb<<" "<<(float)insert_times[i].time/insert_times[i].nb<<endl;
	}
	file.close();

	file.open("find_" + file_name);
	for(int i=0; i<find_times.size(); i++)
	{
		file<<find_times[i].nb<<" "<<(float)find_times[i].time/find_times[i].nb<<endl;
	}
	file.close();
}


void table_test_time1(hash_int_type hash,re_hash_int_type re_hash)
{
	struct nb_time
	{
		int nb, time;
	};

	int n = 600;
	int max_key = n;

	std::vector<int> primes = prime_number(n);


    time_point <system_clock> start , end;
    vector<nb_time> insert_times;
    vector<nb_time> find_times;

	int diff;

	for(int i=0; i<n; i++)
	{
		int key;
		Table<int,int> t(primes[i],hash,re_hash);
		
		for(int j=0; j< primes[i] - 1 ; j++ )
		{
			t.insert(rand()%max_key + 1,rand()%n);
		}
		key = rand()%100 + max_key;
        start = system_clock::now();
        t.insert(key,key);
		end = system_clock::now();
		diff = duration_cast<nanoseconds>(end-start).count();
		insert_times.push_back({primes[i],diff});

		key = rand() % max_key + 1;
        start = system_clock::now();
		t.find(key);
		end = system_clock::now();
		diff = duration_cast<nanoseconds>(end-start).count();
		find_times.push_back({primes[i],diff});
	}
	
	ofstream file("insert_times_one_key.txt");
	for(int i=0; i<insert_times.size(); i++)
	{
		file<<insert_times[i].nb<<" "<<(float)insert_times[i].time/insert_times[i].nb<<endl;
	}
	file.close();

	file.open("find_times_one_key.txt");
	for(int i=0; i<find_times.size(); i++)
	{
		file<<find_times[i].nb<<" "<<(float)find_times[i].time/find_times[i].nb<<endl;
	}
	file.close();
}


void table_debug0(hash_int_type hash,re_hash_int_type re_hash)
{
        Table<int,int> t(17,hash, re_hash);
        for(int i=0; i<10; i++)
        {
            t.insert(rand()%100 + 1,i*2);
        }
        t.insert(90,90);
        t.print();
        t.remove(90);
        t.print();

}

void table_debug1(hash_int_type hash,re_hash_int_type re_hash)
{
    for(int k=0; k<100; k++)
    {
        Table<int,int> t(17,hash, re_hash);
        for(int i=0; i<10; i++)
        {
            t.insert(rand()%100 + 1,i*2);
        }
        t.insert(90,90);
        t.remove(90);
        t.insert(90,90);
        if(t.find(90) == t.size())
        {
            cout<<"porb"<<endl;
        }
        t.remove(90);


        if(t.find(90) != t.size())
        {
            cout<<"porb rem"<<endl;
            t.print_debug();
        }
    }
}


bool devide(const std::vector<int>& v,int num)
{
	for (int i = 0; i < v.size(); i++)

		if(num % v[i] == 0)
			return true;

	return false;
}

vector<int> prime_number(int n)
{
	std::vector<int> primes;
	primes.push_back(2);
	primes.push_back(3);
	int i = 2;
	int p = 5;
	while(i<n)
	{
		if(!devide(primes,p))
		{
			primes.push_back(p);
			i++;
		}
		p++;

	}
	return primes;
}

vector<int> get_keys(int n,int max_key)
{
	std::vector<int> res;
	for(int i=0; i<n; i++)
		res.push_back(rand()%max_key+1);

	return res;
}
