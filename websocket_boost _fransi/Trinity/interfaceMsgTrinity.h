#ifndef INTERFACEMSGTRINITY_H
#define INTERFACEMSGTRINITY_H

#include <vector>

struct StructMsgTrinity
{
    int msg_id;
    int time_stamp;

    StructMsgTrinity operator=(StructMsgTrinity _str_msg) 
    {
        msg_id  = _str_msg.msg_id;
        time_stamp = _str_msg.time_stamp ;

        return _str_msg;
    }
};

template <class T_STRUCT>
class IMensajeTrinity
{
public:
    IMensajeTrinity()
    {
        
    };

    virtual void pack() = 0;
    virtual void unpack() = 0;

    //getters and setters
    void setStruct(const T_STRUCT &_struct_oaris)
    {
        m_struct_oaris = _struct_oaris;
    };

    T_STRUCT getStruct() const 
    {
        return m_struct_oaris;
    };

    std::vector<unsigned char>  getBuffer() const 
    {
        return m_buffer;
    };

protected:
    T_STRUCT m_struct_oaris;

    std::vector<unsigned char> m_buffer;
};


#endif //INTERFACEMSGTRINITY_H