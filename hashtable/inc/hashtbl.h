/**
 * @file vector.h
 * @author     Moisés Sousa Araújo 
 * @brief      The HashTable TAD implementation
 */
#include <forward_list>

namespace ac{

	template <class KeyType, class DataType>

		class HashEntry {
			public:
				HashEntry (KeyType k_, DataType d_) : m_key (k_), m_data (d_){ /* Empty */ };
				KeyType m_key; //!< Stores the key for an entry .
				DataType m_data; //!< Stores the data for an entry .
		};

		template <typename KeyType,
			typename DataType,
			typename KeyHash = std::hash < KeyType >,
			typename KeyEqual = std::equal_to < KeyType > >

		class HashTbl {
			
			public:

				KeyHash hashFunc; // Instantiate the " functor " for primary hash .
				KeyEqual equalFunc; // Instantiate the " functor " for the equal to test .
				using Entry = HashEntry < KeyType , DataType >; //!< Alias

				//>>>>>>>>>>>>>> TAMANHO DE UM NUMERO PRIMO
				HashTbl ( size_t tbl_size_ = DEFAULT_SIZE ) : m_size(tbl_size_), m_count(0){
					this->m_data_table = new std::forward_list <Entry>[m_size];
				};

				// HashTbl ( const Hashtbl & );
				// HashTbl ( std::initializer_list < Entry > ilist );
				
				virtual ~HashTbl (){
					delete this->m_data_table;
				};

				HashTbl &operator=( const HashTbl & );
				HashTbl &operator=( std::initializer_list < Entry > ilist );

				bool insert (const KeyType & key_, const DataType & data_item_){
				
					// Apply double hashing method , one functor and the other with modulo function .
					auto end(hashFunc(key_)%m_size);
					
					Entry new_entry (key_, data_item_); // Create a new entry based on arguments .
					
					auto pos = &this->m_data_table[end];
				
					if(pos->empty()){

						pos->push_front(new_entry);
						++m_count;
						return true;

					}else{
						
						auto it = pos->begin();

						while(it != pos->end()){

							// Comparing keys inside the collision list .
							if ( true == equalFunc(it->m_key, new_entry.m_key)){
								it->m_data = new_entry.m_data;
								return false;
							}

							++it;
						}

						++m_count;
						pos->push_front(new_entry);
						return true;
					} 
					
				};
				
				bool erase ( const KeyType &k_ ){
				
					auto end(hashFunc(k_)%m_size);
					auto pos = this->m_data_table[end];
					
					if(pos->empty()){
						return false;
					}else{
						

						bool equal = false;
						auto it = pos->begin();

						while(it != pos->end()){
							if ( true == equalFunc(it->m_key, k_)){
								equal = true;
								break;
							}
							++it;
						}

						pos->remove(pos->m_key == k_);
					}

					return true;
				};
				
				bool retrieve ( const KeyType & k_ , DataType &d_ ) const {
					
					auto end(hashFunc(k_)%m_size);
				
					auto pos = &this->m_data_table[end];

					auto it = pos->begin();
					
					if(pos->empty()){
						return false;
					}else{

						while(it != pos->end()){
							if ( true == equalFunc(it->m_key, k_)){
								d_ = it->m_data;
							}
							++it;
						}
					}

					return true;
				};
				
				void clear ( void ){
					
					auto pos = &this->m_data_table.begin();

					auto it = pos->begin();

					if(this->m_data_table.empty()){
						return;
					}else{

						while(it != pos->end()){
							it.clear();
							++it;
						}
					}
				};
				
				bool empty ( void ) const {
					return this->m_count == 0;
				};

				size_t size ( void ) const{
					return this->m_count;
				} ;
				
				DataType & at ( const KeyType & k_ ){
					
					auto end(hashFunc(k_)%m_size);
					
					DataType d;

					if(end > this->size()){
						throw std::out_of_range("out of range");
					}else{
						
						auto pos = this->m_data_table[end];

						auto it = pos->begin();

						while(it != pos->end()){
							if ( true == equalFunc(it->m_key, k_)){
								d = it->m_data;
							}
							++it;
						}
						return d;
					}
				};
				
				DataType &operator[]( const KeyType & k_ ){
					
					DataType *temp;

					// if(!this->retrieve(k_, *temp)){
					// 	this->insert(k_, *temp);
					// 	this->retrieve(k_, *temp);
					// 	return *temp;
					// }

					this->retrieve(k_, *temp);

					return *temp;
				};
				
				size_t count ( const KeyType & k_ ) const {
				
					size_t count = 0;
				
					auto end(hashFunc(k_)%m_size);
					
					auto pos = this->m_data_table[end];
					
					if(pos->empty()){
						return count;
					}else{
						

						bool equal = false;
						auto it = pos->begin();

						while(it != pos->end()){
							if ( true == equalFunc(it->m_key, k_)){
								equal = true;
							}
							++count;
							++it;
						}
						
						if(!equal) count = 0;
					}

					return count;
				};
				
				friend std::ostream & operator<<( std::ostream &stream, const HashTbl &h){

					auto pos = h->m_data_table.begin();
				
					auto it = pos->begin();

					stream << "[";

			   		while(it != pos->end()){
			   			
			   			auto r = it->begin(), l = it->end();
						
						while(r != l){
							stream << " " << *r->m_key;
							++r;	
						}
						++it;
					}
				    stream << "]\n";

				    return stream;
				};
			
			private:
			
				void rehash (); //!< Change Hash table size if load factor λ > 1.0
				unsigned int m_size ; //!< Hash table size .
				unsigned int m_count ; //!< Number of elements currently stored in the table .
				//! < The table : array of pointers to collision list .
				std::forward_list <Entry> *m_data_table ;
				// std::unique_ptr < std::forward_list < Entry > [] > m_data_table ;
				//! Hash table ’s default size : 11 table entries .
				static const short DEFAULT_SIZE = 11;
		};
}
