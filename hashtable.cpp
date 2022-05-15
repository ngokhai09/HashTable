#include <bits/stdc++.h>
using namespace std;


class HashNode
{
  public:
	  string value;
	  string key;

  HashNode(string key, string value)
  {
    this->value = value;
    this->key = key;
  }
};


class HashTable
{
  HashNode **arr;
  int capacity;
  int size;
  HashNode *dummy;
  public:
	// constructor
  HashTable()
  {
    capacity = 20;
    size=0;
    arr = new HashNode*[capacity];

	dummy = new HashNode("-1", "-1");
    // Cai dat cac phan tu la null
    for(int i=0 ; i < capacity ; i++)
        arr[i] = NULL;
  }
  // ham bam
  int hashCode(string str)
  {
  	char *s = new char[str.length() ];
  	// chuyen tu string sang mang char
  	strcpy(s, str.c_str());
  	unsigned int hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval % capacity;
  }

  // chen nao tu dien theo key va value
  void insertNode(string key, string value)
  {
    HashNode *temp = new HashNode(key, value);

    // goi ham bam
    int hashIndex = hashCode(key);

    // tim cho de luu value. dung tuyen tinh
    while(arr[hashIndex] != NULL && arr[hashIndex]->key != key && arr[hashIndex]->key != "-1")
    {
      hashIndex++;
      hashIndex %= capacity;
    }

	// tang kich thuoc cua hashtable
	if(arr[hashIndex] == NULL || arr[hashIndex]->key == "-1")
    	size++;	
    arr[hashIndex] = temp;
  }

  //Xoa tu
  string deleteNode(string key)
  {
    int hashIndex = hashCode(key);

    // tim kiem key
    while(arr[hashIndex] != NULL)
    {
      if(arr[hashIndex]->key == key)
      {
        HashNode *temp = arr[hashIndex];
        // Xoa bang cach sua key thanh -1 va value thanh -1
		arr[hashIndex] = dummy;
        size--;
        return temp->value;
      }
      hashIndex++;
      hashIndex %= capacity;

    }
	// neu khong thay thi tra ve null
    return NULL;
  }
	
	// lay value theo key
  string get(string key)
  {
    int hashIndex = hashCode(key);
    int counter=0;

    while(arr[hashIndex] != NULL)
    {
      int counter =0;
      if(counter++>capacity)
        return NULL;

      if(arr[hashIndex]->key == key)
          return arr[hashIndex]->value;
      hashIndex++;
      hashIndex %= capacity;
    }

// neu khong thay thi tra ve null
    return "notfound";
  }

  // tra ve size cua hashtable
  int sizeofMap()
  {
    return size;
  }

// kiem tra rong
  bool isEmpty()
  {
    return size == 0;
  }

  void display()
  {
  	ofstream file("dictionary.txt");
    for(int i=0 ; i<capacity ; i++)
    {
      if(arr[i] != NULL)
        file <<arr[i]->key << ":" << arr[i]->value << endl;
    }
  }
};
// cat chuoi theo dau :
vector<string> split(string str){
	vector<string> s;
	string temp = "";
   
      for(int i=0; i<(int)str.size(); i++){
         if(str[i] != ':'){
            temp += str[i];
        }
        else{
        	s.push_back(temp);
            temp = "";
        }
    }
    s.push_back(temp);
    return s;
}
class Dictionary{
	HashTable *h;
	public:
		Dictionary(){
			h = new HashTable();
			readFile();
		}
		
		void readFile(){
			string s;
			ifstream file("dictionary.txt");
			
			while(getline(file, s)){
				vector<string> str = split(s);
				h->insertNode(str[0], str[1]);
			}
		}
		
		void writeFile(){
			h->display();
		}
		
		void search(string key){
			string value = h->get(key);
			if(value == "notfound"){
				cout << "Khong tim thay" << endl;
				return;
			}
			cout << key << ": " << value << endl;
		}
		void edit(string key, string newval){
			if(h->get(key) == "notfound"){
				cout << "Khong co tu";
				return;
			}
//			h->deleteNode(key);
			h->insertNode(key, newval);
			cout << "Sua thanh cong" << endl;
		}
		void deleteWord(string key){
			if(h->get(key) == "notfound"){
				cout << "Khong co tu" << endl;
				return;
			}
			h->deleteNode(key);
			cout << "Xoa thanh cong" << endl;
		}
};
int main()
{
  Dictionary d;
//  d.readFile();

//  d.edit("hello", "xin chao");
//  d.search("bye");
  d.deleteWord("bye");
//  d.search("hello");
  d.writeFile();
  return 0;
}
