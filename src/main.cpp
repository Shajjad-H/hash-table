#include <ctime>

#include "table.hpp"
#include "hash_functions.hpp"
#include "test_functions.hpp"

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
using namespace std::chrono;

void teste_fonctions();
void test_perf();




int main()
{
    srand(time(NULL));
    table_debug1(hash_int,re_hash_int);
    //table_test_time1(hash_int,re_hash_int_quad);

    //table_test_time1(hash_int,re_hash_int_double);
    //table_test_time2(hash_int,re_hash_int,"re_hash_linaire_n_keys.txt");
    //table_test_time2(hash_int,re_hash_int_quad,"re_hash_quad_n_keys.txt");
    //teste_fonctions();
    test_perf();



    return 0;
}

int get_choix_f_re_hash();
re_hash_int_type get_func_re_hash(int n,string &f_name);
void fill_table(Table<int,int> &t,const vector<int> &vals);
void insert_man(Table<int,int> &t);
void test_search(const Table<int,int> &t);
void test_modif(Table<int,int> &t);
void test_supp(Table<int,int> &t);
void test_perf();

void teste_fonctions()
{
    cout<<"Entrez un taille pour le table: ";
    u_int32_t taille;
    cin>>taille;
    cout<<"les types de donées sont des int pour la cle et pour les donée"<<endl;
    cout<<"0: re-hash-linaire"<<endl
        <<"1: re-hash-quadratique"<<endl
        <<"2: re-hash-double"<<endl
        <<"Entrez voutre choix: ";
    int max_key = 10000;
    string f_name;

    int re_hash = get_choix_f_re_hash();
    re_hash_int_type f_re_hash = get_func_re_hash(re_hash,f_name);

    Table<int,int> table(taille,hash_int,f_re_hash);
    vector<int> keys = get_keys(taille*0.25,max_key);
    fill_table(table,keys);
    insert_man(table);
    cout<<"ces sont les cles qui sont inseré + des valeur inseré automatiquement"<<endl;
    table.print();
    test_search(table);
    test_modif(table);
    test_supp(table);
    test_perf();


}
void mesure_time(re_hash_int_type,const string &file_name,int taille, int step,Table<int,int> &t)
{
    int max_key = taille*2;
    ofstream file(file_name);
    for(int i=step; i<taille; i+=step)
    {
        fill_table(t,get_keys(step,max_key));
        time_point <system_clock> start , end;
        start = system_clock::now();
        for(int j=0; j<i; j++)
        {
            int key = rand()%max_key;
                t.find(key);
        }
        end = system_clock::now();
		int diff = duration_cast<nanoseconds>(end-start).count();
        file<<i<<" "<<diff<<endl;
    }
    
    file.close();
}

void test_perf()
{
    cout<<"Les test de performance vont etre generere"<<endl;
    int taille = 50000;
    int step = 100;
    Table<int,int> tab(taille,hash_int,re_hash_int);
    mesure_time(re_hash_int,"re_hash_int.txt",taille,step,tab);
    mesure_time(re_hash_int_quad,"re_hash_quad.txt",taille,step,tab);
    //mesure_time(re_hash_int_double,"re_hash_double.txt",taille,step,tab);




}

void test_supp(Table<int,int> &t)
{
    cout<<"modification de cle"<<endl;
    cout<<"combien de valeurs voulez vous supprimez: ";
    int nb_cle = 0;
    cin>>nb_cle;
    int i = 0;
    while(i<nb_cle)
    {
        cout<<"cle n° "<<i+1<<": ";
        int key;
        cin>>key;
        t.remove(key);
        
        cout<<"La clé à été supprimé"<<endl
            <<"voulez vous afficher la table \n0 pour non 1 pour oui: ";
        bool affiche;
        cin>>affiche;
        if(affiche)
            t.print();

        i++;
    }
}

void test_modif(Table<int,int> &t)
{
    cout<<"modification de cle"<<endl;
    cout<<"combien de valeurs voulez vous modifiez: ";
    int nb_cle = 0;
    cin>>nb_cle;
    int i = 0;
    while(i<nb_cle)
    {
        cout<<"cle n° "<<i+1<<": ";
        int key;
        cin>>key;
        cout<<"valeur: ";
        int val;
        cin>>val;
        t.modify(key,val);
        
        cout<<"La clé à été modifié"<<endl
            <<"voulez vous afficher la table \n0 pour non 1 pour oui: ";
        bool affiche;
        cin>>affiche;
        if(affiche)
            t.print();

        i++;
    }
}

void test_search(const Table<int,int> &t)
{
    cout<<"recherche de cle"<<endl;
    cout<<"combien de valeurs voulez vous cherchez: ";
    int nb_cle = 0;
    cin>>nb_cle;
    int i = 0;
    while(i<nb_cle)
    {
        cout<<"cle n° "<<i+1<<": ";
        int key;
        cin>>key;
        if(t.find(key) < t.size())
        {
            cout<<"La clé est dans la table"<<endl<<"et se trouve à indice: "<<t.find(key)<<endl;
        }
        else {

            cout<<"La clé n'est pas dans la table"<<endl
                <<"voulez vous afficher la table \n0 pour non 1 pour oui: ";
            bool affiche;
            cin>>affiche;
            if(affiche)
                t.print();

        }
        i++;
    }
}

int get_choix_f_re_hash()
{
    int re_hash = -1;
    
    cin>>re_hash;
    while(re_hash != 0 && re_hash != 1 && re_hash != 2)
    {
        cout<<"mouvais choix"<<endl<<" a nouveau: ";
        cin>>re_hash;
    } 
    return re_hash;
}

re_hash_int_type get_func_re_hash(int n,string &f_name)
{
    
    switch (n)
    {
        case 0:
            f_name = "re_hash_linaire";
            return re_hash_int;
        case 1:
            f_name = "re_hash_quad";
            return re_hash_int_quad;
        case 2: 
            f_name = "re_hash_double";
            return re_hash_int_double;
        default:
            return NULL;
    }
}

void fill_table(Table<int,int> &t,const vector<int> &vals)
{
    for(int i=0; i<vals.size(); i++)
        t.insert(vals[i],vals[i]);
}

void insert_man(Table<int,int> &t)
{
    cout<<"la donée est inserer aumatiquement vous insrerez que les clé"<<endl;
    cout<<"combien de valeur vous voulez inserer: ";
    int nb_val;
    cin>>nb_val;
    if(nb_val>=t.size())
        cout<<"Warning vous auriez pas assez de place"<<endl;
    int i = 0;
    while(i<nb_val)
    {
        int key;
        cout<<"cle n° "<<i+1<<": ";
        cin>>key;
        t.insert(key,key);
        i++;
    }
}