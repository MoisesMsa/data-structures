namespace sc{

	template <typename T> class list {

		private:

			struct Node {
				T data; //<! Data field
				Node *prev; //<! Pointer to the previous node in the list.
				Node *next; //<! Pointer to the next node in the list.
				//<! Basic constructor.
				Node( const T& d = T(), Node * p = nullptr, Node * n = nullptr ) : data( d ), prev(p), next( n ) { /* Empty */ }
			}; 

		public:

			class const_iterator {

				public:

					typedef std::ptrdiff_t difference_type;
					typedef std::bidirectional_iterator_tag iterator_category; // !< Iterator category.
					typedef T* pointer; //!< Pointer to the value type.
					typedef T& reference; //!< Reference to the value type.
					typedef T  value_type;


					// const_iterator() {/*empty*/};

					const T & operator* ( ) const{
						return this->current->data;
					};

					T & operator* ( ){
						return this->current->data;
					};

					// ++it;
					const_iterator &operator++ ( ){
						current = current->next;
						return *this;
					};

					// it++;
					const_iterator operator++ (int){
						return iterator(current->next);
					}; 

					// --it;
					const_iterator &operator--( ){
						current = current->prev;
						return *this;
					};
				
					// it--;
					const_iterator operator--(int){
						return iterator(current->prev);
					}; 

					bool operator== ( const const_iterator & rhs ) const{
						return this->current == rhs.current;
					};

					bool operator!= ( const const_iterator & rhs ) const{
						return this->current != rhs.current;
					};

					const const_iterator &operator+(size_t count){
						while(count != 0){
							current = current->next;
							--count;
						}

						return *this;
					}


				protected:
					Node *current;
					const_iterator( Node * p ) : current( p ){/*empty*/};
					friend class list<T>;
			};

			class iterator{

				public:

					typedef std::ptrdiff_t difference_type;
					typedef std::bidirectional_iterator_tag iterator_category; // !< Iterator category.
					typedef T* pointer; //!< Pointer to the value type.
					typedef T& reference; //!< Reference to the value type.
					typedef T  value_type;

					iterator(Node &p) : current(p) { /* Empty */ }

					const T &operator*( ) const{
						return current.data;
					};

					T& operator*( ){
						return current->data;
					};

					iterator &operator++( ){
						current = current->next;
						return *this;
					};

					iterator operator++(int){
						return iterator(current->next);
					};

					iterator &operator--( ){
						current = current->prev;
						return *this;
					};

					iterator operator--(int){
						return iterator(current->prev);
					}

					bool operator!= ( iterator & rhs ) {
						return this->current != rhs.current;
					};

					bool operator!= ( iterator && rhs ) {
						return this->current != rhs.current;
					};

					bool operator== ( iterator & rhs ) {
						return this->current != rhs.current;
					};

					iterator &operator+(size_t count){
						
						while(count != 0){
							current = current->next;
							--count;
						}

						return *this;
					}


				protected:

					Node *current;
					iterator( Node *p ) : current( p ){/*empty*/};
					friend class list<T>;
			};

			// [I] SPECIAL MEMBERS

			list() : m_size(0){
				this->m_head = new Node(T(), nullptr, m_tail);
				this->m_tail = new Node(T(), m_head, nullptr);
			
			};

			explicit list(int count) : list() {
				
				for (int i = 0; i < count; ++i)
					this->push_back(0);
			};


			list( std::initializer_list<T> ilist ): list() {

				auto it = ilist.begin(), end = ilist.end();

				while(it != end){
					this->push_back(*it);
					++it;
				}
			}


			template<typename InputItr >
			list( InputItr first,  InputItr last ): list() {

				while(first != last){
					this->push_back(*first);
					++first;
				}

			}

			~list( ){
				this->clear();
			};

			list( const list &l) : list(){
				
				auto first = l.cbegin(), last = l.cend();

				while(first != last){
					this->push_back(*first);
					++first;
				}
			};

			list &operator=( const list & l){
				
				if(!this->empty())
					this->clear();
				

				auto first = l.cbegin(), last = l.cend();

				while(first != last){
					this->push_back(*first);
					++first;
				}

				return *this;
			};


			// [II] ITERATORS

			iterator begin( ){
				return iterator(m_head->next);
			};

			const_iterator cbegin( ) const{
				return const_iterator(m_head->next);
			};

			iterator end( ){
				return iterator(m_tail);
			};

			const_iterator cend( ) const{
				return const_iterator(m_tail);
			};

			// [III] Capacity

			int size( ) const{
				return this->m_size;
			};

			bool empty( ) const{
				return this->m_size == 0;
			};

			// [IV] Modifiers

			void clear( ){
				if(!this->empty()){

					int size = this->size();
					
					for (int i = 0; i < size; ++i)
						this->pop_back();
				}
			};

			T & front( ){
				
				if(this->empty())
					throw std::out_of_range("out of range");
				
				return this->m_head->next->data;
			};

			const T & front( ) const{

				if(this->empty())
					throw std::out_of_range("out of range");

				return this->m_head->next->data;
			};

			T & back( ){

				if(this->empty())
					throw std::out_of_range("out of range");

				return this->m_tail->prev->data;
			};

			const T & back( ) const{

				if(this->empty())
					throw std::out_of_range("out of range");

				return this->m_tail->next->data;
			};

			void push_front( const T & value ){
				
				Node *new_item = new Node(value, m_head, m_head->next);
				
				if(!this->empty()){
					this->m_head->next->prev = new_item;
				}else{
					new_item->next = this->m_tail;
					this->m_tail->prev = new_item;
				}
				
				this->m_head->next = new_item;

				m_size++;
			};

			void push_back( const T & value ){
				
				Node *new_item = new Node(value, m_tail->prev, m_tail);
				this->m_tail->prev->next = new_item;
				this->m_tail->prev = new_item;

				m_size++;
			};

			void pop_front( ){
				
				if(!this->empty()){
					Node *temp = m_head->next;
					
					//avoid seg fault
					m_head->next->next->prev = m_head;
					m_head->next = m_head->next->next;

					delete temp;
					m_size--;
				}

			};

			void pop_back( ){
				
				if(!this->empty()){
					Node *temp = m_tail->prev;
					
					m_tail->prev->prev->next = m_tail;
					m_tail->prev = m_tail->prev->prev;

					delete temp;
					m_size--;
				}
			};


			// [IV-a] Modifiers with iterators

			template <typename InItr>


			void assign( InItr first, InItr last ){

				auto list = this->begin();
				
				while(first != last){
					*list = *first;
					++list;
					++first; 
				}

			};

			void assign( std::initializer_list<T> ilist ){

				auto it = ilist.begin(), end = ilist.end(), list = this->begin();

				while(it != end){
					*list = *it;
					++it;
					++list;
				}
			};
			
			void assign(int count, const T& value ){
				
				auto list = this->begin(), end = this->end();

				if(count < this->size()){
					
					auto dif = this->size() - count;
					
					for (int i = dif; i <= this->size(); ++i)
						this->pop_back();
				}

				for(int i = 0; i < count; ++i)				
				{
					
					if(i >= this->size()){
						this->push_back(value);
					}else{
						*list = value;
						
						if(list != end)
							++list;
					}

				}

			};
			
			void assign(const T& value ){
				
				auto it = this->begin(), end = this->end();

				while(it != end){
					*it = value;
					++it;
				}
			};

			iterator insert( iterator itr, const T & value ){
				
				Node *new_node = new Node(value, itr.current->prev, itr.current);

				itr.current->prev->next = new_node;
				itr.current->prev = new_node;

				++m_size;

				return iterator(new_node);
			};



			iterator insert( iterator pos, std::initializer_list<T> ilist ){
				
				auto l_init = ilist.begin(), l_end = ilist.end();

				while(l_init != l_end){
					this->insert(pos, *l_init);
					++l_init; 
				}
				
				return iterator(pos.current);
			};

			template < typename InItr>
			iterator insert( iterator pos, InItr first, InItr last){

				while(first != last){
					this->insert(iterator(pos.current), *first);
					++first; 
				}

				return --pos;
			}; 

			iterator erase( iterator itr ){
				
				
				iterator it(itr.current->prev);

				if(!this->empty()){
					
					Node *temp = itr.current;

					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;

					delete temp;
					
					--m_size;
				}

				return it;
			};

			iterator erase( iterator first, iterator last ){

				iterator it(first.current->prev);

				while(first != last){
					this->erase(first);
					++first;
				}

				return it;
			};

			const_iterator find( const T & value ) const{
				
				auto it = this->cbegin(), end = this->cend();

				while(it != end){
					if(*it == value)
						return it;
					++it;
				}

				return end;
			};

			friend bool operator==(const list<T>& a, const list<T>& b){
				if(a.size() != b.size()){
					return false;
				}else{

					auto begin_a = a.cbegin(), end_a = a.cend(), begin_b = b.cbegin();

					while(begin_a != end_a){
						if(*begin_a != *begin_b) 
							return false;
					
						++begin_a;
						++begin_b;
					}
				}

				return true;
			};


			friend bool operator!=(const list<T>& a, const list<T>& b){
				if(a.size() != b.size()){
					return true;
				}else{

					auto begin_a = a.cbegin(), end_a = a.cend(), begin_b = b.cbegin();

					while(begin_a != end_a){
						if(*begin_a != *begin_b) 
							return true;
						++begin_a;
						++begin_b;
					}
				}	

				return false;
			};



			friend std::ostream& operator<<( std::ostream& stream, const list<T>& list){

				stream << "[ ";
				
				auto l = list.cbegin();
				
				for (auto i = 0; i < list.size(); ++i)
				{

					std::cout << *l << " ";
					++l;
				}
				
				stream << "]";

				return stream;
			};

		private :
			int m_size = 0;
			Node *m_head, *m_tail;
	};
};