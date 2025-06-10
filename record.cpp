#include "record.h"

Record::Record(int id) : id(id) {
}

int Record::getId() const{
    return this->id;
}

Record::~Record(){
}
