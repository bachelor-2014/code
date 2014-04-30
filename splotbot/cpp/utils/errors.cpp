#include "errors.h"

ComponentException::ComponentException(Component *component, const char* message){
    this->component = component;
    this->message = message;
}
const char* ComponentException::what() const throw(){
    return this->message;
}

RucolaException::RucolaException(const char* error): error(error){
}

const char* RucolaException::what() const throw(){
    return error;
}
