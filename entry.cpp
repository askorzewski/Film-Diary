#include "entry.h"

Entry::Entry(int id) : Record(id)  {}

QString Entry::getLabel(){
    return film->getLabel();
}
