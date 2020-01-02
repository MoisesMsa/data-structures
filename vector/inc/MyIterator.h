/**
 * @file MyIterator.h
 * @author     Moisés Sousa Araújo 
 * @brief      Class to encapsule a pointer (private *current)
 */


/**
 * @brief      struct to instace a iterator as const_iterator or iterator
 *
 * @tparam[bool]      flag     {set which use}
 * @tparam[class]     IsTrue   {typedef to set (e.g. const T&)} 
 * @tparam[class]     IsFalse  {typedef to set (e.g. T&)}
 */

template <bool flag, class IsTrue, class IsFalse> struct choose;

template <class IsTrue, class IsFalse> 
struct choose<true, IsTrue, IsFalse> {
	typedef IsTrue type;
};

template <class IsTrue, class IsFalse> 
struct choose<false, IsTrue, IsFalse> {
	typedef IsFalse type;
};


template <typename T, bool isconst = false> class MyIterator {
	public:
		// Below we have the iterator_traits common interface
		/// Difference type used to calculated distance between iterators.
		typedef std::ptrdiff_t difference_type;
		typedef T  value_type; //!< Value type the iterator points to.
		typedef typename choose<isconst, const T&, T&>::type reference;			
		typedef typename choose<isconst, const T*, T*>::type pointer;			
		typedef std::bidirectional_iterator_tag iterator_category; // !< Iterator category.


		/**
		 * @brief      {Constructs the object.}
		 *
		 * @param[T]  ptr   {ptr   The pointer}
		 */

		MyIterator(T *ptr = nullptr) : current(ptr){/*empty*/};
		
		/**
		 * @brief      {Constructs the object.}
		 *
		 * @param[const MyIterator&]   {ptr   The pointer}
		 */

		MyIterator(const MyIterator& ) = default;
	
		/**
		 * @brief      Constructs the object.
		 *
		 * @param[const MyIterator &itr] itr {itr   The itr}
		 *
		 * @return     {description_of_the_return_value}
		 */

		MyIterator& operator=(const MyIterator &itr) = default;
		
		/**
		 * @brief      {Constructs the object.}
		 *
		 * @param[const MyIterator &itr] itr {itr   The itr}
		 *
		 * @return     {description_of_the_return_value}
		 */
		MyIterator& operator=(const reference itr){
			current = itr.current;			
			return *this;
		};


		/**
		 * @brief      {pointer desreference}
		 *
		 * @return     {returns the content value} 
		 */
		reference operator*() const{
			return *this->current;
		};


		/**
		 * @brief       {pointer desreference} 
		 *
		 * @return      {returns the content value} 
		 */

		pointer operator->(void)const {   
			assert( current != nullptr );
			return current;
		}


		/**
		 * @brief      {increment operator}
		 *
		 * @return     {class private pointer ++current}
		 */

		MyIterator& operator++(void){
			++current;
			return *this;
		}; 


		/**
		 * @brief      {decrease operator}
		 *
		 * @return     {class private pointer  --current}
		 */


		MyIterator& operator--(void){
			--current;
			return *this;
		}; 



		/**
		 * @brief      {int incrment operator}
		 *
		 * @param[in]  
		 *
		 * @return    {the old current pointer value}
		 */

		MyIterator operator++ (int){
			MyIterator temp = *this;
			current++;
			return temp;
		}; 


		/**
		 * @brief    {decrease int operator}
		 *
		 * @param[in]  
		 *
		 * @return   {the old current pointer value}
		 */

		MyIterator operator--(int){
			MyIterator temp = *this;
			current--;
			return temp;
		}; 

		/**
		 * @brief      {add n positions to the current pointer}
		 *
		 * @param[MyIterator] itr {  the iterator }
		 * 
		 * @param[difference_type] n {the positions total to increment}
		 *
		 * @return     {class pointer current + n}
		 */

		friend MyIterator operator+( MyIterator itr, difference_type n){
			return itr.current + n;
		};


		friend MyIterator operator+( difference_type n, MyIterator itr){
			return n + itr.current;
		};

		/**
		 * @brief      {decrement n positions to the current pointer in inverse order}
		 *
		 * @param[difference_type] n  {the positions total to decrement}
		 *
		 * @param[MyIterator] itr  {the iterator}
		 *
		 * @return     {class pointer current - n}
		 */

		friend MyIterator operator-( difference_type n, MyIterator itr){
			return n - itr.current;
		};


		friend MyIterator operator-( MyIterator itr, difference_type n){
			return itr.current - n;
		};

		bool operator== (const MyIterator& itr) const{
			return itr.current == this->current;
		};

		bool operator!= (const MyIterator& itr) const{
			return itr.current != this->current;
		};

		/**
		 * @brief      { return distance betwen current and other iterator to lvalues }
		 *
		 * @param[MyIterator&] itr   The itr
		 *
		 * @return     { class current - itr.current}
		 */

		difference_type operator-(MyIterator& itr){
			return this->current - itr.current;
		};


		/**
		 * @brief      { return distance betwen current and other iterator to rvalues }
		 *
		 * @param[MyIterator&] itr   The itr
		 *
		 * @return     { class current - itr.current}
		 */

		difference_type operator-(MyIterator&& itr){
			return this->current - itr.current;
		};

	private:
		T *current;

};








