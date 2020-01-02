/**
 * @file vector.h
 * @author     Moisés Sousa Araújo 
 * @brief      The vector TAD implementation
 */

#include "../inc/MyIterator.h"
#include <memory>
namespace sc{
	template<typename T> class vector {

		public: 

			using size_type = unsigned long;
			//!< The size type
			using value_type = T;
			//!< The value type
			using pointer = value_type*;
			//!< Pointer to a value stored in the container
			using reference = value_type&;
			//!< Reference to a value stored in the container.
			using const_reference = const value_type&;
			//!< Const reference to a value stored in the container
			using iterator = MyIterator <T, false>; // See Code 3
			using const_iterator = MyIterator<T, true>; // See Code 3

			//=== [I] SPECIAL MEMBERS



			/**
			 * @brief      The global Constructs the object, the others constructs are delegateds to that.
			 *
			 * @param[size_type]  count     Items total
			 * @param[size_type]  capacity  The capacity
			 */
			vector(size_type count, size_type capacity): m_end(count), m_capacity(capacity){

				this->m_storage = new T[this->m_capacity];
				
				this->m_first = &this->m_storage[0]; 
				this->cm_first = &this->m_storage[0];
				
				this->m_last = &this->m_storage[this->m_end]; 
				this->cm_last = &this->m_storage[this->m_end];
			};


			/**
			 * @brief      Constructs the object.
			 *
			 * @param[size_type]  count  members total
			 */

			explicit vector( size_type count = 0 ): vector(0, count){/*empty*/};
			

			/**
			 * @brief     	Destroys the object and delete the m_storage attribute.
			 *
			 * @param[void]  
			 */

			virtual ~vector(void){
				delete m_storage;
			};


			/**
			 * @brief      Constructs the object by reference of other vector
			 *
			 * @param[const vector&]  other  The other vector
			 */

			vector(const vector& other): vector(other.m_end, (other.m_end))
			{
				*this = other;
			};

			/**
			 * @brief      Constructs the object by the initializer_list
			 *
			 * @param[std::initializer_list<T>]  list
			 */

			vector( std::initializer_list<T> list): vector(list.size(), list.size()){
				std::copy(list.begin(), list.end(), this->m_storage);
			};


			/**
			 * @brief      Constructs the object by a rvalue vector
			 *
			 * @param[vector &&]  other  The other vector
			 */
		
			vector( vector && other) : vector(other.m_end, (other.m_end))
			{
				*this = other;
			};



			/**
			 * @brief      Constructs the object by a vector/list range
			 *
			 * @param[InputItr]  begin     The begin source iterato
			 * @param[InputItr]  end       The end source iterator
			 *
			 */

			template<typename InputItr > vector( InputItr begin, InputItr end) : vector((T)(end - begin), (end - begin)){
				std::copy(begin, end, this->m_storage);
			};
			

			/**
			 * @brief       change vector proprieties and elements to be equal to other vector 
			 *
			 * @param[const vector& ]  other  The other vector
			 *
			 * @return      the itself vector
			 */

			vector& operator=(const vector& other){

				reserve(other.size());
			
				this->m_end = other.size();
				this->m_last = &this->m_storage[this->m_end];
				this->cm_last = &this->m_storage[this->m_end];
				
				const_iterator first = other.begin(), last = other.end(); 
				iterator vec = this->begin();

				while(first != last){
					*vec = *first;
					++first; ++vec;
				}

				return *this;
			};

			/**
			 * @brief       change vector proprieties and elements to be equal the list value 
			 *
			 * @param[std::initializer_list<T>]  list  Source list
			 *
			 * @return  the itself vector
			 */

			vector& operator=(std::initializer_list<T> && list){

				reserve(list.size());
				
				this->m_end = list.size();
					
				this->m_first = &this->m_storage[0];
				this->cm_first = &this->m_storage[0];

				this->m_last = &this->m_storage[list.size()];
				this->cm_last = &this->m_storage[list.size()];

				std::copy(list.begin(), list.end(), this->m_storage);


				return *this;
			};

			/**
			 * @brief      Change vector proprieties and elements to be equal the rvalue vector.
			 *
			 * @param[vector &&]  other  Source vector
			 *
			 * @return     The itself vector
			 */

			vector& operator=(vector && other){

				this->m_storage = &other.m_storage[0];

				if(this->empty() == true){
					this->m_end = other.size();
					
					this->m_first = &this->m_storage[0];
					this->cm_first = &this->m_storage[0];

					this->m_last = &this->m_storage[other.size()];
					this->cm_last = &this->m_storage[other.size()];
				} 

				other.m_capacity = 0;
				other.m_end = 0;
				other.m_storage = nullptr; //clear the other

				return *this;
			};

			//=== [II] ITERATORS


			/**
			 * @brief      Used to acess the first list element.
			 *
			 * @return     The iterator m_first
			 */

			iterator begin(void){
				return this->m_first;
			};

			/**
			 * @brief      Used to acess the last list element.
			 *
			 * @return     The iterator m_last
			 */

			iterator end(void){
				return this->m_last;
			};

			/**
			 * @brief      Used to acess the first list elemen to const operations
			 *
			 * @return     The iterator cm_first
			 */

			const_iterator begin(void) const{
				return this->cm_first;
			};

			/**
			 * @brief      Used to acess the last list element to const operations
			 *
			 * @return     The iterator cm_last
			 */

			const_iterator end(void) const{
				return this->cm_last;
			};

			// [III] Capacity

			/**
			 * @brief      Return the total of valid elements.
			 *
			 * @return     The m_end represents the number last of the valid position.
			 */

			size_type size(void) const{
				return this->m_end;
			};

			/**
			 * @brief      Return the total vector capacity.
			 *
			 * @return     The m_capacity attribute.
			 */

			size_type capacity(void) const{
				return this->m_capacity;
			};
			
			/**
			 * @brief      Checks if the vector is empty.
			 *
			 * @return     False is the vector is not empty and true if is.
			 */

			bool empty(void) const{
				if(this->m_end == 0){
					return true;
				}else{
					return false;
				}
			};

			// [IV] Modifiers
		
			/**
			 * @brief      Remove all vector items.
			 */

			void clear(void){

				auto first = this->begin(), last = this->end();

				while(first != last){
					--this->m_end; --this->cm_last; --this->m_last;
					--last;
				}
			};


			/**
			 * @brief    Moves all elements to the right and insert a new int the list front.
			 *
			 * @param[const_reference]  val   The value.
			 */

			void push_front( const_reference val){
				this->reserve(this->size() + 1);
				++this->m_last; ++this->cm_last;

				auto first = this->begin(), last = this->end();

				while(last != first){
					*last = *(last-1);
					--last;
				}

				++this->m_end; 
				*this->m_first = val;
			};
			
			/**
			 * @brief      Increases the vector and insert a new item in the list end.
			 *
			 * @param[const_reference]  val  The value.
			 */

			void push_back(const_reference val){
				this->reserve(this->size() + 1);
				*this->m_last = val;
				++this->m_end; ++this->m_last; ++this->cm_last; 
			};



			/**
			 * @brief      Removes the first item.
			 */

			void pop_back(void){
				this->erase(this->end());
			};


			/**
			 * @brief      Removes the last item.
			 */

			void pop_front(void){
				this->erase(this->begin());
			};
			

			/**
			 * @brief      Insert val in specied position moving elments if necessary.
			 *
			 * @param[iterator]  pos   The position.
			 * @param[const_reference]  val   The value.
			 *
			 * @return     Iterator to the inserted item.
			 */

			iterator insert( iterator pos, const_reference val){

				auto distance = (pos - this->begin());
				
				this->reserve(this->size()+1);

				pos = (this->begin() + distance );
			
				iterator last = this->end();

				while (last != pos)
				{
					*last = *(last-1);
					--last;
				}

				*pos = val;
				
				++this->m_end; ++this->m_last; ++this->cm_last;

				return pos;
			};

			/**
			 * @brief      insert other vector/list range inside the vector.
			 *
			 * @param[iterator]  pos   The position.
			 * @param[InputItr]  begin   Source begin.
			 * @param[InputItr]  end   Source end.
			 *
			 * @return     Iterator to the inserted item.
			 */

			template <typename InputItr > iterator insert( iterator pos, InputItr begin, InputItr end){

				auto original_pos = (pos - this->begin()), source_size = end - begin, new_cap = this->size() + source_size + 1;
				
				//new size needs to add one to the loop goes till the end of the range
				if((this->end() - pos) < 0 )
					new_cap = this->size() + 1;
				
				reserve(new_cap);	

				//needs reduce the size 
				this->m_end = new_cap - 1;
				this->m_last = &this->m_storage[this->m_end];
				this->cm_last = &this->m_storage[this->m_end];
				
				auto first = this->begin() + original_pos;

				while (begin != end){
					*(first + source_size) = *first; 
					*first = *begin;
					++begin; ++first;
				}
				
				return first;
			};

			/**
			 * @brief      insert other list content inside the vector before the specified position.
			 *
			 * @param[iterator]  pos   The position
			 * @param[const std::initializer_list< value_type >&]  list 
			 *
			 * @return     iterator to the inserted item.
			 */
			
			iterator insert( iterator pos, const std::initializer_list< value_type >& list){

				auto pos_dis = (pos - this->begin()), new_cap = this->size() + list.size() + 1;			
				
				//new size needs to add one to the loop goes till the end of the range
				if((this->end() - pos) < 0 )
					new_cap = this->size() + 1;
				
				reserve(new_cap);	

				//needs reduce the size 
				this->m_end = new_cap - 1;
				this->m_last = &this->m_storage[this->m_end];
				this->cm_last = &this->m_storage[this->m_end];

				auto first = this->begin() + pos_dis, l_first = list.begin(), l_last = list.end();

				while (l_first != l_last){
					*(first + list.size()) = *first; 
					*first = *l_first;
					++first; ++l_first;
				}
				
				return first;
			};
			
			/**
			 * @brief       Allocate more memory to m_storage if necessary (when the size if bigger than the capacity).
			 *
			 * @param[size_type]  new_cap  The new capability.
			 */

			void reserve( size_type new_cap){
				if(new_cap > this->capacity())
				{
					this->m_capacity *= 2;
					T *temp = new T[this->m_capacity];

					std::copy(this->begin(), this->end(), &temp[0]);

					delete this->m_storage;
					
					this->m_storage = temp;

					this->m_first = &this->m_storage[0];
					this->cm_first = &this->m_storage[0];
					
					this->m_last = &this->m_storage[this->m_end];
					this->cm_last = &this->m_storage[this->m_end];

				}
			};

			/**
			 * @brief      Makes the capacity equals the size.
			 */

			void shrink_to_fit(void){
				if(!this->empty())
				{
					this->m_capacity = this->size();

					T *temp = new T[this->capacity()];

					std::copy(this->begin(), this->end(), &temp[0]);

					delete m_storage;

					this->m_storage = temp;

					this->m_first = &this->m_storage[0];
					this->cm_first = &this->m_storage[0];
					
					this->m_last = &this->m_storage[this->m_end];
					this->cm_last = &this->m_storage[this->m_end];

				}
			};

			/**
			 * @brief     Change the vector to size to n and all values to val.
			 *
			 * @param[size_type]  count The count.
			 * @param[const_reference]  val   The value.
			 */

			void assign(size_type count, const_reference val){

				reserve(count);
				
				this->m_last = &this->m_storage[count]; 
				this->cm_last = &this->m_storage[count]; 
				this->m_end = count;
				
				auto first = this->begin(), last = this->end();

				while(first != last){
					*first =  val;
					++first;
				}
			};
			
			/**
			 * @brief      Change the vector to the list content.
			 *
			 * @param[size_type]  count  The count
			 * @param[std::initializer_list<T>&]  list The list
			 */

			void assign(const std::initializer_list<T>& list){
				reserve(this->size() + list.size());
				
				if(list.size() > this->size()){
					this->m_last = this->m_last + (list.size() - this->m_end); 
					this->cm_last = this->cm_last + (list.size() - this->m_end); 
					this->m_end = this->m_end + list.size();
				}
				
				std::copy(list.begin(), list.end(), this->m_storage);
			};

			/**
			 * @brief      Change the vector to source range begin - end.
			 *
			 * @tparam[InputItr]  begin  The source range begin.
			 * @tparam[std::initializer_list<T>&]  end The source range end.
			 * 
			 */

			template<typename InputItr > void assign( InputItr begin, InputItr end){
				auto dist  = end - begin;
				reserve(this->size() + dist);
				
				if(dist > this->size()){
					this->m_last = this->m_last + dist; 
					this->cm_last = this->cm_last + dist; 
					this->m_end = this->m_end + dist;
				}
				
				auto first = this->begin(), last = this->end();
				
				while(first != last){
					*first = *begin;
					++first; ++begin;
				}
			};

			/**
			 * @brief      Erases the begin end vector range.
			 *
			 * @param[iterator]  begin  The range begin to erase.
			 * @param[iterator]  end    The range end to erase.
			 *
			 * @return     Return the next position after the erased range.
			 */

			iterator erase( iterator begin, iterator end){

				auto original_pos = begin;

				if(!this->empty()){

					auto dist = end - begin;
					while (begin != end){
						*begin = *(begin + dist); 
						++begin;
						--this->m_end; --this->m_last; --this->cm_last;
					}
				}


				return original_pos;
			};

			/**
			 * @brief      Erases one item.
			 *
			 * @param[iterator]  Begin  The range begin to erase.
			 *
			 * @return     Return the next position after the erased item.
			 */
			
			iterator erase(iterator itr){
				auto original_pos = itr;

				if(!this->empty()){
					iterator last = this->end(); 

					while(itr != last){
						*itr = *(itr+1);
						++itr;
					}

					--this->m_end; --this->m_last; --this->cm_last;
				}

				return original_pos;			
			};


			// [V] Element  access

			/**
			 * @brief       Give direct acess to the last m_storage vali item.
			 *
			 * @return      Reference to the last item.
			 */

			const_reference back(void) const{
				return this->m_storage[this->size() - 1];
			};

			reference back(void){
				return this->m_storage[this->size() - 1];
			};
			
			/**
			 * @brief      Give direct acess to the first m_storage vali item.
			 *
			 * @return     Reference to the first item.
			 */

			const_reference front(void) const{
				return this->m_storage[0];
			};

			/**
			 * @brief      Give direct acess to the first m_storage vali item, but to const operatios.
			 *
			 * @return     Reference to the first item.
			 */

			reference front(void){
				return this->m_storage[0];
			};

			/**
			 * @brief      Give direct acess to some valid item in the list, but to const operatios, but to const operatios. 
			 *
			 * @return     Reference to the n item. 
			 */

			const_reference operator[]( size_type n) const{
				return this->m_storage[n];
			};
			
			/**
			 * @brief      Give direct acess to some valid item in the list.
			 *
			 * @return     Reference to the n item.
			 */

			reference operator[]( size_type n){
				if(n >= this->size()){
					throw std::out_of_range("out of range");
				}else{
					return this->m_storage[n];
				}
			};
			
			/**
			 * @brief      Give direct acess to some valid item in the list, but to const operatios. 
			 *
			 * @return     Reference to the n item. 
			 */

			const_reference at(size_type n) const{
				if(n >= this->size()){
					throw std::out_of_range("out of range");
				}else{
					return this->m_storage[n];
				}
			};

			/**
			 * @brief      Give direct acess to some valid item in the list. 
			 *
			 * @return     Reference to the n item. 
			 */

			reference at(size_type n){
				if(n >= this->size()){
					throw std::out_of_range("out of range");
				}else{
					return this->m_storage[n];
				}
			};

			/**
			 * @brief     Give direct acess to m_storage member. 
			 *
			 * @return     Reference to the m_storage.
			 */

			pointer data(void){
				return this->m_storage;
			};

			/**
			 * @brief      Give direct acess to m_storage member, but to const operations.
			 *
			 * @return     Reference to the m_storage.
			 */

			const_reference data(void) const{
				return this->m_storage;
			};



			// [VII] Friend functions.
			friend std::ostream& operator<<( std::ostream& stream, const vector<T>& v){
				stream << "[";
			    for (auto i = v.begin(); i != v.end(); ++i)
			    {
			        stream << " " << *i;
			    }
			    stream << "]\n";

			    return stream;
			};

			/**
			 * @brief      { change the values between vector a and b }
			 * @params[vector<T>&] a 
			 * @params[vector<T>&] a
			 */

			friend void swap( vector<T>& a, vector<T>& b){
				
				T *temp = new T[a.size()];

				std::copy(&a.m_storage[0], &a.m_storage[a.size()], temp);
				std::copy(&b.m_storage[0], &b.m_storage[b.size()], a.m_storage);
				std::copy(&temp[0], &temp[a.size()], b.m_storage);

				a.m_last = &a.m_storage[b.size()];
				a.cm_last = &a.m_storage[b.size()];
				
				b.m_last = &b.m_storage[a.size()];
				b.cm_last = &b.m_storage[a.size()];

				auto aux_end = b.m_end;
				b.m_end = a.m_end;
				a.m_end = aux_end;

				delete temp;
			};

			/**
			 * @brief      {compare if two const vectors have same size and same items}
			 *
			 * @return     {bool} 
			 */

			friend bool operator==(const vector<T>& a, const vector<T>& b){
				if(a.size() != b.size()){
					return true;
				}else{
					const_iterator first = b.begin(), last = b.end(), ptr_other = a.begin();
					while(first != last){
						if(*first != *ptr_other) 
							return true;
						++first; ++ptr_other;
					}
				}

				return true;
			}

			/**
			 * @brief      {compare if two const vectors have diferent size or diferent items}
			 *
			 * @return     {bool} 
			 */

			friend bool operator!=(const vector<T>& a, const vector<T>& b){
				if(a.size() != b.size()){
					return true;
				}else{
					const_iterator first = b.begin(), last = b.end(), ptr_other = a.begin();
					
					while(first != last){
						if(*first != *ptr_other) 
							return true;
						++first; ++ptr_other;
					}

				}

				return false;
			}

			/**
			 * @brief      {compare if two vectors have same size and same items}
			 *
			 * @return     {bool} 
			 */

			friend bool operator==(vector<T>& a, vector<T>& b){
				if(a.size() != b.size()){
					return false;
				}else{
					iterator first = b.begin(), last = b.end(), ptr_other = a.begin();
					while(first != last){
						if(*first != *ptr_other) 
							return false;
						++first; ++ptr_other;
					}
				}

				return true;
			}

			/**
			 * @brief      {compare if two vectors have diferent size or diferent items}
			 *
			 * @return     {bool} 
			 */

			friend bool operator!=(vector<T>& a, vector<T>& b){
				if(a.size() != b.size()){
					return true;
				}else{
					iterator first = b.begin(), last = b.end(), ptr_other = a.begin();
					while(first != last){
						if(*first != *ptr_other) 
							return true;
						++first; ++ptr_other;
					}
				}

				return false;
			}


		private:
			size_type m_end = 0; //!< Current list size (or index past-last valid element).
			size_type m_capacity; //!< List’s storage capacity.
			T *m_storage; //!< Data storage area for the dynamic array.
			iterator m_first, m_last;
			const_iterator cm_first, cm_last;
	};
}

