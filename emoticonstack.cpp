#include "emoticonstack.h"

std::atomic<bool> EmoticonStack::c_lock(false);
int EmoticonStack::i_counter = 0;
SKYPE_EMOTICONS_CONTAINER_T *EmoticonStack::e_data = 0;

EmoticonStack::EmoticonStack(QObject *parent) :
    QObject(parent)
{
    MY_ATOMIC_LOCK_ACQUIRE(c_lock)
    //If this is the first instance of the class, load data
    if(++i_counter == 1)
    {
        SKYPE_EMOTICONS_LOAD(e_data)
    }
    MY_ATOMIC_LOCK_RELEASE(c_lock)
}

EmoticonStack::~EmoticonStack()
{
    SKYPE_EMOTICONS_CONTAINER_T *temp_data_ptr = 0; //Temporary pointer

    MY_ATOMIC_LOCK_ACQUIRE(c_lock)
    //If this is the last instance of the class, unload data
    if(--i_counter == 0)
    {
        temp_data_ptr = e_data; //Freeing is done later
        e_data = 0; //Pointer is released immediatly
    }
    MY_ATOMIC_LOCK_RELEASE(c_lock)

    //Real freeing operation is done asynchronously
    if(temp_data_ptr != 0)
    {
       SKYPE_EMOTICONS_DELETE(temp_data_ptr)
       delete temp_data_ptr;
    }
}

int EmoticonStack::count() const
{
    return e_data->size();
}

Emoticon * EmoticonStack::getEmoticonByName(const QString &name)
{
    return e_data->value(name);
}

SKYPE_EMOTICONS_CONTAINER_T::const_iterator EmoticonStack::getCIteratorBegin() const
{
    return e_data->constBegin();
}

SKYPE_EMOTICONS_CONTAINER_T::const_iterator EmoticonStack::getCIteratorEnd() const
{
    return e_data->constEnd();
}
