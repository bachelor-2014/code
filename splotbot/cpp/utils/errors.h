#include <exception>
#include "../component.h"

using namespace std;

class ComponentException: public exception {
    public:
        ComponentException(Component *component,const char* message);
        virtual const char* what() const throw();
        Component *component; // This is self
        const char* message;
};

class RucolaException: public exception {
    public:
        RucolaException(const char* error);
        virtual const char* what() const throw();
        const char* error;
};
