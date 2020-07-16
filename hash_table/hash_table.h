#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

namespace th
{
	struct Item{
		std::string key;
		std::string value;
		struct Item *next;
	};

	class hash_table{
		public:
			hash_table(const hash_table &) = delete;
			hash_table &operator=(const hash_table &) = delete;
			
			// hash function
			int hash(std::string key);
			// constructor
			hash_table(int size);
			// destructor
			~hash_table();
			// add an item
			void add(std::string key, std::string value);
			// remove an item
			void remove(std::string key);
			// if given key exists return the value of the given key else return null character '\0'
			const std::string get(std::string key);
			// return true if the key exists else return false
			bool exists(std::string key);
			
			void debug();
			
		private:
			struct Item **data;
			int size;
	};

	hash_table::hash_table(int size){
		this->size = size;
		this->data = new struct Item *[size];
		for(int i=0; i<size; i++)
			this->data[i] = NULL;
	}

	hash_table::~hash_table(){
		for(int i=0; i<size; i++){
			if(data[i]){
				struct Item *temp = data[i];
				while(temp){
					struct Item *next = temp->next;
					delete temp;
					temp = next;
				}
			}
		}
		delete[] data;
	}
	
	int hash_table::hash(std::string key){
		unsigned hashed = 0;
		for(int i=0; i<(int)key.length(); i++)
			hashed += ((i+1)*key[i])%size;
		return hashed % size;
	}
	
	void hash_table::add(std::string key, std::string value){
		int hashed = hash(key);
		struct Item *current = *(data+hashed);
		struct Item *prev = NULL;
		while(current){
			if(current->key == key){
				current->value = value;
				return;
			}
			prev = current;
			current = current->next;
		}
		struct Item *item = new struct Item;
		item->key = key;
		item->value = value;
		item->next = NULL;
		if(!prev){
			*(data+hashed) = item;
		}
		else{
			prev->next = item;
		}
	}
	
	void hash_table::remove(std::string key){
		int hashed = hash(key);
		struct Item *temp = data[hashed];
		struct Item *prev = NULL;
		while(temp){
			if(temp->key == key){
				struct Item *next = temp->next;
				delete temp;
				if(prev)
					prev->next = next;
				else
					data[hashed] = next;
				return;
			}
			prev = temp;
			temp = temp->next;
		}
	}
	
	const std::string hash_table::get(std::string key){
		int hashed = hash(key);
		struct Item *temp = *(data+hashed);
		while(temp){
			if(temp->key == key)
				return temp->value;
			temp = temp->next;
		}
		return "\0";
	}
	
	bool hash_table::exists(std::string key){
		int hashed = hash(key);
		struct Item *temp = *(data+hashed);
		while(temp){
			if(temp->key == key)
				return true;
			temp = temp->next;
		}
		return false;
	}
}

#endif