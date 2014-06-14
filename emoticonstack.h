#ifndef EMOTICONSTACK_H
#define EMOTICONSTACK_H

#include <atomic>

#include <QThread>
#include <QMap>

#include "SkypeEmoticons.h"

#define MY_ATOMIC_LOCK_ACQUIRE(MY_ATOMIC_LOCK__lck) \
    bool MY_ATOMIC_LOCK__b_false = false; \
    while(!MY_ATOMIC_LOCK__lck.compare_exchange_strong(MY_ATOMIC_LOCK__b_false, true, std::memory_order_seq_cst, std::memory_order_relaxed)) { \
        Q_ASSERT(MY_ATOMIC_LOCK__b_false == false); \
        QThread::msleep(10); }

#define MY_ATOMIC_LOCK_RELEASE(MY_ATOMIC_LOCK__lck) \
    MY_ATOMIC_LOCK__lck.store(false, std::memory_order_seq_cst);

typedef struct Emoticon
{
    const char *id;
    const char *name;
    const char *shortcuts;
    const unsigned int dataSize;
    const unsigned char *data;
} Emoticon;

class EmoticonStack
{
public:
    explicit EmoticonStack();
    ~EmoticonStack();
    int count() const;
    const Emoticon *getEmoticonByName(const QString &name);
    SKYPE_EMOTICONS_CONTAINER_T::const_iterator getCIteratorBegin() const;
    SKYPE_EMOTICONS_CONTAINER_T::const_iterator getCIteratorEnd() const;

private:
    static std::atomic<bool> c_lock;
    static int i_counter;
    static SKYPE_EMOTICONS_CONTAINER_T *e_data;
};

#endif // EMOTICONSTACK_H
