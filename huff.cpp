#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <iterator>

using namespace std;

class NoeudH {
  friend class ArbreH;
  private:
    wchar_t c;
    NoeudH *gauche, *droit; 
  public:
    const unsigned int poids; 

    NoeudH(wchar_t c, unsigned int p): poids(p),gauche(nullptr),droit(nullptr) {
    this->c = c;
}

NoeudH(NoeudH *f1, NoeudH *f2): poids(f1->poids + f2->poids) {
    c      = '\0';
    gauche = f1;
    droit  = f2;
}
  wchar_t get(){
    return c;
  }
  void gau(NoeudH * a){
    gauche=a;
  }
  void dro(NoeudH * a){
    droit=a;
  }
  NoeudH* ga(){
    return gauche;
  }
  NoeudH* dr(){
    return droit;
  }

    NoeudH (const NoeudH &)=delete;
    
    class comp{
      public:
        inline bool operator() (unsigned int p1, const NoeudH *n2) const {return (p1 >  n2->poids);}
    };

    ~NoeudH (){}
};

NoeudH * construire_arbre(vector<wchar_t> &a,vector<int> &b){
    NoeudH * n;
    if (a.size() > 0) {
        n = new NoeudH(a.back(),b.back());
        a.pop_back();
        b.pop_back();
        vector<wchar_t> car1;
        vector<int> po1;
        vector<wchar_t> car2;
        vector<int> po2;
        int indice=a.size();
        for(int i=0;i<indice;i+=2){
        car1.push_back(a.back());
        po1.push_back(b.back());
        a.pop_back();
        b.pop_back();
        car2.push_back(a.back());
        po2.push_back(b.back());
        a.pop_back();
        b.pop_back();
        }
        n->gau(construire_arbre(car1,po1));
        n->dro(construire_arbre(car2,po2));}
    else{
      n=nullptr;
    }
    return n;  
}

void pri(NoeudH * a,string f){
  ofstream fichier(f.c_str(), ios::app);

    if(fichier){
  if(a!=nullptr){
    string res="";
    res+=(char)a->get();
    fichier<<res;
    fichier.close();
    pri(a->ga(),f);
    pri(a->dr(),f);
  }
  else{string res="";
      res+="0";
    fichier<<res;
    fichier.close();}
    }
}

void new_search(NoeudH * a,string f,char &b){

    if(f.length()==0)b= (char)a->get();
    else{
      char t=f[0];
      char t1='0';
      char t2='1';
      string c="";
      for(int i=1;i<f.length();i++)
        c+=f[i];
  if(t==t1){
    new_search(a->ga(),c,b);}
  if(t==t2){
    new_search(a->dr(),c,b);
  }
}}

int shearch(wchar_t val,NoeudH* ptr){
  if(!ptr){
    return 0;
  }
  else if(ptr->get()==val){
    return 1;
  }
  return 0+shearch(val,ptr->ga())+shearch(val,ptr->dr());
}

void find(wchar_t va,NoeudH* tree,vector<char> &b){
  wchar_t v=tree->get();
  NoeudH * ptr=tree;
  b.push_back('0');
    while(v != va){
        if(shearch(va,ptr->ga())==1){
          ptr=ptr->ga();
          v=ptr->get();
          b.push_back('0');
        }
        if(shearch(va,ptr->dr())==1){
          ptr=ptr->dr();
          v=ptr->get();
          b.push_back('1');
        }
        }
    }
class ArbreH{
  private:
    map<wchar_t, unsigned int> frequences;
    map<wchar_t, vector<bool>> codes;
    NoeudH *racine;
    string name;
    
    void majF (const string &);
    void majA ();
    void majC ();

  public:
    ArbreH (const string &nom){
        ifstream fichier(nom.c_str(), ios::in);

    if(fichier)
        {   name=nom;
            char caract;
        while(fichier.get(caract)){
            auto i=frequences.find(caract);
            auto it = frequences.find(caract);
            if(it == frequences.end())
                frequences.insert({caract, 1});
            else
                it->second += 1;
        }
        multimap<unsigned int,wchar_t> freq;
        for (auto it = frequences.begin(); it != frequences.end(); ++it) {
            freq.insert({it->second,it->first});
        }

        vector<wchar_t> car;
        vector<int> po;
        int i=0;
        for (auto it=freq.begin(); it != freq.end(); ++it,i++) {
            car.push_back((char)it->second);
            po.push_back(it->first);
        }
        racine=construire_arbre(car,po);
            fichier.close();
        }
        else
            cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
    //ArbreH (const ArbreH &)=delete;

    void coder   (const string & re, vector<bool> *){
      ifstream fichier(name.c_str(), ios::in);

    if(fichier)
        {
        /*string res="";
        bool vef=true;
          for(int i=0;i<name.length();i++){
            if(name[i]=='.'){
            vef=false;
            res+=".huffman";}
            if(vef)
            res+=name[i];
          }*/
          remove(re.c_str());
          ofstream new_fichier(re.c_str(), ios::app);
    if(new_fichier){
      char caract;
      while(fichier.get(caract)){
       vector<char> chemin;
        find(caract,racine,chemin);
        for (auto i: chemin)
         new_fichier<<i;
         new_fichier<<" ";
          
          }
          new_fichier<<"\n";
          new_fichier.close();}
          else{
            cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
    fichier.close();
    //pri(racine,re);
      }
        else{
            cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
    }
    void decoder (const vector <bool> &, string &res){
      string r="Huffman";
      ifstream fichier(r.c_str(), ios::in);
      string carac;
      while (fichier >> carac)
    {
        string new_carac="";
        for(int i=1;i<carac.length();i++)
        new_carac+=carac[i];
        char c;
        new_search(racine,new_carac,c);
        res+=c;
    }
    fichier.close();

    }

    ~ArbreH(){}
};


int main (){
  ArbreH h ("test.txt");
  vector <bool> v;
  h.coder ("Huffman", &v);
  /*copy (v.begin (), v.end (), ostream_iterator <bool> (cout));
  cout << endl;*/
  string s="";
  h.decoder (v, s);
  cout<<s<<endl;
}
