#include "AForm.hpp"

AForm::AForm() : _is_signed(false), _sign_grade(150), _exec_grade(150) {}

AForm::AForm(const std::string &name, int sign_grade, int _exec_grade) 
    : _name(name), _is_signed(false), _sign_grade(sign_grade), _exec_grade(_exec_grade) {
    if (_sign_grade < GRADE_MAX)
        throw GradeTooHighException("Error: Form sign grade too high, max: 1\n");
    if (_sign_grade > GRADE_MIN)
        throw GradeTooLowException("Error: Form sign grade too low, min: 150\n");
    if (_exec_grade < GRADE_MAX)
        throw GradeTooHighException("Error: Form sign grade too high, max: 1\n");
    if (_exec_grade > GRADE_MIN)
        throw GradeTooLowException("Error: Form sign grade too low, min: 150\n");
}

AForm::AForm(const AForm &src) 
    : _name(src._name), _is_signed(src._is_signed), _sign_grade(src._sign_grade), _exec_grade(src._exec_grade) {
}

AForm::~AForm() {}

/**
 * @brief Equal operator overload. 
 * If src not equal to actual object, assign src non const atributtes.
 *
 * @param src 
 * @return Return this
 */
AForm &AForm::operator=(const AForm &src) {
    
    if (this != &src) {
        this->_is_signed = src._is_signed;
    }
    return *this;
}

/**
 * @brief AForm name getter.
 * 
 * @return AForm name
 */
std::string AForm::getName() const {
    return _name;
}

/**
 * @brief AForm sign grade getter.
 * 
 * @return AForm sign grade.
 */
int         AForm::getSignGrade() const {
    return _sign_grade;
}

/**
 * @brief AForm exec grade getter.
 * 
 * @return AForm exec grade.
 */
int         AForm::getExecGrade() const {
    return _exec_grade;
}

bool        AForm::getIsSigned() const {
    return _is_signed;
}

/**
 * @brief Ensure Bureaucrat grade is not lower than AForm sign grade,
 * else throw exception.
 * 
 * @param b Bureaucrat object.
 */
void        AForm::beSigned(const Bureaucrat &b) {
    if (_is_signed)
        throw AlreadySignedException("AForm is already signed\n");
    if (b.getGrade() > _sign_grade)
        throw GradeTooLowException("bureaucrat grade not enough to sign AForm\n");
    _is_signed = true;
}

/**
 * @brief Insertion operator overload.
 * 
 * @param os Ostream object.
 * @param obj Form object.
 * 
 * @return Ossteam object reference.
 */
std::ostream &operator<<(std::ostream & os, const AForm & obj) {
    os << obj.getName() << ", "
       << "signed: " << obj.getIsSigned()
       << ", sign grade: " << obj.getSignGrade()
       << ", exec grade: " << obj.getExecGrade()
       << std::endl;

    return os;
}

AForm::GradeTooHighException::GradeTooHighException(const std::string & msg) throw() {
    _msg = msg;
}

AForm::GradeTooHighException::~GradeTooHighException() throw() {}

/**
 * @brief Overrides std::exception 'what' method.
 * 
 * @return Exception message.
 */
const char * AForm::GradeTooHighException::what() const throw() {
    return _msg.c_str();
}

AForm::GradeTooLowException::GradeTooLowException(const std::string & msg) throw() {
    _msg = msg;
}

AForm::GradeTooLowException::~GradeTooLowException() throw() {}

/**
 * @brief Overrides std::exception 'what' method.
 * 
 * @return Exception message.
 */
const char * AForm::GradeTooLowException::what() const throw() {
    return _msg.c_str();
}

AForm::AlreadySignedException::AlreadySignedException(const std::string & msg) throw() {
    _msg = msg;
}

AForm::AlreadySignedException::~AlreadySignedException() throw() {}

/**
 * @brief Overrides std::exception 'what' method.
 * 
 * @return Exception message.
 */
const char * AForm::AlreadySignedException::what() const throw() {
    return _msg.c_str();
}

AForm::NotSignedException::NotSignedException(const std::string & msg) throw() {
    _msg = msg;
}

AForm::NotSignedException::~NotSignedException() throw() {}

/**
 * @brief Overrides std::exception 'what' method.
 * 
 * @return Exception message.
 */
const char * AForm::NotSignedException::what() const throw() {
    return _msg.c_str();
}
