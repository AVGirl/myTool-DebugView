#ifndef HEAD
#define HEAD

#include <map>
#include <list>

//�У������ַ�
typedef struct tagFilterData
{
    int m_col;
    BYTE m_data;
} filterData, *pfilterData;

//������
typedef std::list<filterData*> filterCol;

typedef std::map<int, filterCol*> filterTab;

#endif