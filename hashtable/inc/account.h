 class Account{
	public:
    	Account(){/*empty*/};
    	Account(std::string n, int k, int b, int c, float a) : owner(n), key(k), bank_id(b), account_id(c), m_balance(a){/*empty*/};

    int getKey(){
        return key;
    }


	// protected:
	    using AcctKey = int;
	    std::string owner;
	    unsigned int key, bank_id, agencia_num, account_id;
	    float m_balance;

	// Account &operator=(Account &a){

		
	// 	this->key = a.key; 
	// 	this->owner = a.owner; 
	//     this->bank_id = a.bank_id;
	//     this->agencia_num = a.agencia_num;
	// 	this->account_id = a.account_id; 
	// 	this->m_balance = a.m_balance;

	// 	return *this;
	// }

	Account &operator=(const Account &a){
		// std::cout << "TESTE " << a.m_balance << " - " << this->m_balance << std::endl;
		this->key = a.key; 
		this->owner = a.owner; 
	    this->bank_id = a.bank_id;
	    this->agencia_num = a.agencia_num;
		this->account_id = a.account_id; 
		this->m_balance = a.m_balance;
		// std::cout << "TESTE " << a.m_balance << " - " << this->m_balance << std::endl;

		return *this;
	}

    friend bool operator==(const Account  lhs, const Account  rhs){

    	if(lhs.key == rhs.key &&  
	       lhs.bank_id == rhs.bank_id &&
	       lhs.owner == rhs.owner &&
		   lhs.agencia_num == rhs.agencia_num && 
		   lhs.account_id == rhs.account_id &&
		   lhs.m_balance == rhs.m_balance)
    	
    	{

    		return true;
    	}

    	return false;
    };
};