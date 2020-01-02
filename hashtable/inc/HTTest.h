#include "../inc/account.h"  // To get the account class
#include "../inc/hashtbl.h"  // To get the account class

class HTTest : public ::testing::Test {

public:

    HTTest(){/*empty*/}; 
        std::array<Account, 8> m_accounts; //!< our fixed account data base
        Account target; //!< Target account to search for.

    // ~HTTest(){/*empty*/}; 
    // Infrastructure to help the tests.

    struct KeyHash {
        std::size_t operator()( const Account::AcctKey &k_ ) const
        {
            return std::hash<int>()( k_ ) ;
        }
    };

    struct KeyEqual {
        bool operator()( const Account::AcctKey & lhs_, const Account::AcctKey & rhs_) const
        {
            return lhs_ == rhs_;
        }
    };

    /// This is the hash table we use in the tests.
    ac::HashTbl< Account::AcctKey, Account, KeyHash, KeyEqual > ht_accounts{ 4 };

protected:
    void SetUp() override
    {
// Set up our accounts.
        m_accounts[0] = {"Alex Bastos", 1, 1668, 54321, 1500.f};
        m_accounts[1] = {"Aline Souza", 1, 1668, 45794, 530.f};
        m_accounts[2] = {"Cristiano Ronaldo", 13, 557, 87629, 150000.f};
        m_accounts[3] = {"Jose Lima", 18, 331, 1231, 850.f};
        m_accounts[4] = {"Saulo Cunha", 116, 666, 1, 5490.f};
        m_accounts[5] = {"Lima Junior", 12, 123, 5671, 150.f};
        m_accounts[6] = {"Carlito Pardo", 28, 506, 9816, 50.f};
        m_accounts[7] = {"Januario Medeiros", 17, 324, 7777, 4850.f};

        target = m_accounts[0];
    }

    void TearDown() override {/* empty */}

    void insert_accounts();
};