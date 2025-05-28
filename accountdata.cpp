#include "accountdata.h"

AccountData::AccountData(int id) : Database(id) {

}

QString AccountData::getName() const{
    return name;
}

