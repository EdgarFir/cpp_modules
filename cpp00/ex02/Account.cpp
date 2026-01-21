#include "Account.hpp"

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit) 
	: _accountIndex(_nbAccounts), _amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0)
{
	_displayTimestamp();
	std::cout << "index:" << getNbAccounts() << ";";
	std::cout << "amount:" << initial_deposit << ";";
	std::cout << "created\n";

	_nbAccounts++;
	_totalAmount += _amount;
}

Account::~Account(void)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "amount:" << _amount << ";";
	std::cout << "closed\n";

}

int Account::getNbAccounts(void)
{
	return _nbAccounts;
}
int	Account::getTotalAmount( void )
{
	return _totalAmount;
}	

int	Account::getNbDeposits( void )
{
	return _totalNbDeposits;
}

int	Account::getNbWithdrawals( void )
{
	return _totalNbWithdrawals;
}

/**
 * @brief Class static function that display all acounts info.
 */
void Account::displayAccountsInfos( void )
{
	_displayTimestamp();
	std::cout << "accounts:" << getNbAccounts() << ";";
	std::cout << "total:" << getTotalAmount() << ";";
	std::cout << "deposits:" << getNbDeposits() << ";";
	std::cout << "withdrawals:" << getNbWithdrawals() << "\n";
}

/**
 * @brief Make a deposit in to acount.
 * 
 * @param deposit Cash to deposit.
 */
void Account::makeDeposit(int deposit)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "p_amount:" << _amount << ";";
	_amount += deposit;
	std::cout << "deposit:" << deposit << ";";
	std::cout << "amount:" << _amount << ";";
	_nbDeposits++;
	_totalNbDeposits++;
	_totalAmount += deposit;
	std::cout << "nb_deposits:" << _nbDeposits << "\n";
}

/**
 * @brief Make a cash withdrawal from account.
 * 
 * @param withdrawal Amount of cash to withdraw.
 * 
 * @return True if withdrawal succeed, else False. 
 */
bool Account::makeWithdrawal(int withdrawal)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "p_amount:" << _amount << ";";
	std::cout << "withdrawal:";
	if (_amount - withdrawal < 0)
	{
		std::cout << "refused\n";
		return false;
	}
	_amount -= withdrawal;
	_nbWithdrawals++;
	_totalNbWithdrawals++;
	_totalAmount -= withdrawal;
	std::cout << withdrawal << ";";
	std::cout << "amount:" << _amount << ";";
	std::cout << "nb_withdrawals:" << _nbWithdrawals << "\n";
	return true;
}

/**
 * @brief Check count amount and return.
 * 
 * @return Count amount.
 */
int Account::checkAmount(void) const
{
	return _amount;
}

/**
 * @brief Display actual account status.
 */
void Account::displayStatus(void) const
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "amount:" << _amount << ";";
	std::cout << "deposits:" << _nbDeposits << ";";
	std::cout << "withdrawals:" << _nbWithdrawals << "\n";
}

/**
 * @brief Display actual timestamp with this format(e.g): "[19920104_091532]" 
 */
void Account::_displayTimestamp(void)
{
	time_t timestamp;
	timestamp = time(NULL);
	struct tm datetime = *localtime(&timestamp);

	std::cout 
	<< "[" 
		<< datetime.tm_year + 1900
		<< std::setfill('0') << std::setw(2) << datetime.tm_mon + 1
		<< std::setfill('0') << std::setw(2) << datetime.tm_mday
		<< "_"
		<< std::setfill('0') << std::setw(2) << datetime.tm_hour 
		<< std::setfill('0') << std::setw(2) << datetime.tm_min
		<< std::setfill('0') << std::setw(2) << datetime.tm_sec
	<< "] ";
	return ;
}