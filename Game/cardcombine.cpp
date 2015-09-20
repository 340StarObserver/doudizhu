#include "cardcombine.h"
#include <algorithm>
using std::sort;
using std::memset;

//构造
CardCombine::CardCombine()
{

}

//将牌组转换为字符串格式
QString CardCombine::toString()const
{
    unsigned int N=static_cast<unsigned int>(_list.size());
    if(N==0) return "empty cardcombine";
    QString str="";
    for(unsigned int i=0;i<N;i++)
        str.append(_list[i].toString()).append(",");
    return str;
}

//获得牌组序列
vector<Card> CardCombine::getList()const
{
    return _list;
}

//设置牌组序列
void CardCombine::setList(const vector<Card> &list)
{
    _list=list;
}

//往牌组中添加一张牌
void CardCombine::add(const Card &card)
{
    _list.push_back(card);
}

//牌组排序(按照点数大小升序排列: 3,4,5...J,Q,K,A,2,SG,BG)
void CardCombine::combineSort()
{
    sort(_list.begin(),_list.end());
}

//判断牌型是否是过
bool CardCombine::is_Guo()const
{
    return _list.size()==0;
}

//判断牌型是否是单牌
bool CardCombine::is_Single()const
{
    return _list.size()==1;
}

//判断牌型是否是顺子
bool CardCombine::is_Shunzi()
{
    /*
     * 顺子分为三种情况
     * 1.普通顺子,即最大牌不超A
     * 2.以A开头的顺子
     * 3.以2开头的顺子
    */
    return shunzi_type1(true)||shunzi_type2(true)||shunzi_type3(true);
}

//最大的牌不超过A的顺子
/*
 * 参数para是用来表示该顺子要不要求必须满5张
 * 当然顺子必须要满5张
 * 设置该参数是为了在判断连对的时候复用此方法
 * 因为连对可以拆成点数相同的两部分,每一部分只要是顺子就行而且不需要满5张
*/
/*
 * 若是严格的第一型顺子
 * 必须满5张
 * 按照点数排序后,最大牌不超过A
 * 相邻的牌点数差1
*/
bool CardCombine::shunzi_type1(bool para)
{
    unsigned int N=static_cast<unsigned int>(_list.size());
    if(para){
        if(N<5)
            return false;
    }
    combineSort();
    if(_list[N-1].getPoint()>Point::Card_A)
        return false;
    for(unsigned int i=0;i<N-1;i++){
        if(_list[i].getPoint()-_list[i+1].getPoint()!=-1)
            return false;
    }
    return true;
}

//以A开头的顺子
/*
 * 参数para是用来表示该顺子要不要求必须满5张
 * 当然顺子必须要满5张
 * 设置该参数是为了在判断连对的时候复用此方法
 * 因为连对可以拆成点数相同的两部分,每一部分只要是顺子就行而且不需要满5张
*/
/*
 * 以A开头的严格顺子必须首先满5张
 * 然后按点数排序后,最后两张必须依次是A,2
 * 然后第一张必须是3
 * 然后前面部分(A之前的)相邻牌点数差1
*/
bool CardCombine::shunzi_type2(bool para)
{
    unsigned int N=static_cast<unsigned int>(_list.size());
    if(para){
        if(N<5)
            return false;
    }
    combineSort();
    if(_list[0].getPoint()!=Point::Card_3)
        return false;
    if(_list[N-2].getPoint()!=Point::Card_A || _list[N-1].getPoint()!=Point::Card_2)
        return false;
    for(unsigned int i=0;i<N-3;i++){
        if(_list[i].getPoint()-_list[i+1].getPoint()!=-1)
            return false;
    }
    return true;
}

//以2开头的顺子
/*
 * 参数para是用来表示该顺子要不要求必须满5张
 * 当然顺子必须要满5张
 * 设置该参数是为了在判断连对的时候复用此方法
 * 因为连对可以拆成点数相同的两部分,每一部分只要是顺子就行而且不需要满5张
*/
/*
 * 以2开头的严格顺子必须首先满5张
 * 然后按点数排序后,第一张牌是3,最后一张牌是2
 * 然后前面部分(A之前)相邻牌点数差1
*/
bool CardCombine::shunzi_type3(bool para)
{
    unsigned int N=static_cast<unsigned int>(_list.size());
    if(para){
        if(N<5)
            return false;
    }
    combineSort();
    if(_list[0].getPoint()!=Point::Card_3)
        return false;
    if(_list[N-1].getPoint()!=Point::Card_2)
        return false;
    for(unsigned int i=0;i<N-2;i++){
        if(_list[i].getPoint()-_list[i+1].getPoint()!=-1)
            return false;
    }
    return true;
}

//判断牌型是否是对子
bool CardCombine::is_Duizi()const
{
    unsigned int N=static_cast<unsigned int>(_list.size());
    return N==2&&_list[0]==_list[1];
}

//判断牌型是否是连对
bool CardCombine::is_LianDui()
{
    unsigned int N=static_cast<unsigned int>(_list.size());
    if(N<6||N%2!=0)
        return false;
    //判断能否两两同点数
    combineSort();
    unsigned int n=N/2;
    for(unsigned int i=0;i<n;i++){
        if(_list[2*i]!=_list[2*i+1])
            return false;
    }
    //再判断是否是连的
    //因为有A,2的存在,所以为了简化判断
    //拆成两部分,判断两部分是否都是顺子(并非是真正的顺子,因为不要求必须满5张)
    //又因为经过上面的逻辑已经验证过是两两成对的,即拆成的两部分点数都是相同的,
    //所以只判断一个部分即可
    CardCombine c;
    for(unsigned int i=0;i<n;i++)
        c.add(_list[2*i]);
    return c.shunzi_type1(false)||c.shunzi_type2(false)||c.shunzi_type3(false);
}

//判断牌型是否是三张
bool CardCombine::is_Three()const
{
    unsigned int N=static_cast<unsigned int>(_list.size());
    return N==3&&_list[0]==_list[1]&&_list[0]==_list[2];
}

//判断牌型是否是三带一
bool CardCombine::is_Three_One()
{
    unsigned int N=static_cast<unsigned int>(_list.size());
    if(N!=4)
        return false;
    combineSort();
    if(_list[0]==_list[1]&&_list[0]==_list[2]&&_list[0]!=_list[3])
        return true;
    if(_list[1]==_list[2]&&_list[1]==_list[3]&&_list[0]!=_list[1])
        return true;
    return false;
}

//判断牌型是否是三带二
bool CardCombine::is_Three_Two()
{
    unsigned int N=static_cast<unsigned int>(_list.size());
    if(N!=5)
        return false;
    combineSort();
    if(_list[0]==_list[1]&&_list[0]==_list[2]&&_list[3]==_list[4]&&_list[0]!=_list[3])
        return true;
    if(_list[0]==_list[1]&&_list[2]==_list[3]&&_list[2]==_list[4]&&_list[0]!=_list[2])
        return true;
    return false;
}

//判断牌型是否是四带二
bool CardCombine::is_Four_Two()const
{
    /*
     * 有四张同点数的牌,其余两张点数和这四张不同,但是那两张点数可以相等也可以不等
     * how to judge?
     * 首先牌数必须为6,然后按点数进行计数排序,结果为uint count[16]
     * 然后遍历count[],若存在count[i]==4,则符合要求
    */
    unsigned int N=static_cast<unsigned int>(_list.size());
    if(N!=6)
        return false;
    unsigned int count[16];
    memset(count,0,16*sizeof(unsigned int));
    for(unsigned int i=0;i<N;i++)
        count[_list[i].getPoint()]++;
    for(int i=0;i<16;i++){
        if(count[i]==4)
            return true;
    }
    return false;
}

//判断牌型是否是无翅飞机
bool CardCombine::is_Plane()
{
    unsigned int N=static_cast<unsigned int>(_list.size());
    if(N<6||N%3!=0)
        return false;
    //判断能否三三同点数
    combineSort();
    unsigned int n=N/3;
    for(unsigned int i=0;i<n;i++){
        if(_list[3*i]!=_list[3*i+1] || _list[3*i]!=_list[3*i+2])
            return false;
    }
    //AAA222是特殊中的特殊
    if(N==6&&_list[0].getPoint()==Point::Card_A&&_list[3].getPoint()==Point::Card_2)
        return true;
    //再判断是否是连的
    //因为有A,2的存在,所以为了简化判断
    //拆成三部分,判断三部分是否都是顺子(并非是真正的顺子,因为不要求必须满5张)
    //又因为经过上面的逻辑已经验证过是三三同点数的,即拆成的三部分点数都是相同的,
    //所以只判断一个部分即可
    CardCombine c;
    for(unsigned int i=0;i<n;i++)
        c.add(_list[3*i]);
    return c.shunzi_type1(false)||c.shunzi_type2(false)||c.shunzi_type3(false);
}

//判断牌型是否是飞机带同数量的单牌
bool CardCombine::is_Plane_Single()const
{
   /*
    * 1.先把原牌组拆成单牌部分和非单牌部分
    * 2.非单牌部分是否构成无翅飞机 且 非单牌部分的牌数是单牌部分牌数的3倍
    * then 怎样拆成两部分?
    *      可以先按点数进行计数排序,结果为uint count[16]
    *      然后遍历原牌组origin[],
    *      若count[origin[i].getPoint()]==1,则将此牌加入单牌部分
    *      反之,则将此牌加入非单牌部分
   */
    unsigned int count[16];
    memset(count,0,16*sizeof(unsigned int));
    unsigned int N=static_cast<unsigned int>(_list.size());
    for(unsigned int i=0;i<N;i++)
        count[_list[i].getPoint()]++;
    CardCombine c1,c2;
    for(unsigned int i=0;i<N;i++){
        if(count[_list[i].getPoint()]==1)
            c1.add(_list[i]);
        else
            c2.add(_list[i]);
    }
    return c2.getList().size()==3*c1.getList().size()&&c2.is_Plane();
}

//判断牌型是否是飞机带同数量的对子
bool CardCombine::is_Plane_Dui()const
{
    /*
     * 1.先把原牌组拆成对子部分和非对子部分
     * 2.非对子部分是否构成无翅飞机 且 非对子部分的牌数是对子部分的1.5倍
     * then 怎样拆成两部分?
     *      可以先按点数进行计数排序,结果为uint count[16]
     *      然后遍历原牌组origin[],
     *      若count[origin[i].getPoint()]==2,则将此牌加入对子部分
     *      反之,则将此牌加入非对子部分
    */
    unsigned int count[16];
    memset(count,0,16*sizeof(unsigned int));
    unsigned int N=static_cast<unsigned int>(_list.size());
    for(unsigned int i=0;i<N;i++)
        count[_list[i].getPoint()]++;
    CardCombine c1,c2;
    for(unsigned int i=0;i<N;i++){
        if(count[_list[i].getPoint()]==2)
            c1.add(_list[i]);
        else
            c2.add(_list[i]);
    }
    return 2*c2.getList().size()==3*c1.getList().size()&&c2.is_Plane();
}

//判断牌型是否是普通炸弹
bool CardCombine::is_Boom()const
{
    unsigned int N=static_cast<unsigned int>(_list.size());
    return N==4&&_list[0]==_list[1]&&_list[0]==_list[2]&&_list[0]==_list[3];
}

//判断牌型是否是王炸
bool CardCombine::is_KingBoom()const
{
    unsigned int N=static_cast<unsigned int>(_list.size());
    if(N!=2)
        return false;
    if(_list[0].getPoint()==Point::Card_SK&&_list[1].getPoint()==Point::Card_BK)
        return true;
    if(_list[0].getPoint()==Point::Card_BK&&_list[1].getPoint()==Point::Card_SK)
        return true;
    return false;
}

//返回该牌组的牌型
CardCombine::Type CardCombine::getType()
{
    if(is_Guo())
        return Type::Guo;
    if(is_Single())
        return Type::Single;
    if(is_Shunzi())
        return Type::Shunzi;
    if(is_Duizi())
        return Type::Duizi;
    if(is_LianDui())
        return Type::LianDui;
    if(is_Three())
        return Type::Three;
    if(is_Three_One())
        return Type::Three_One;
    if(is_Three_Two())
        return Type::Three_Two;
    if(is_Four_Two())
        return Type::Four_Two;
    if(is_Plane())
        return Type::Plane;
    if(is_Plane_Single())
        return Type::Plane_Single;
    if(is_Plane_Dui())
        return Type::Plane_Dui;
    if(is_Boom())
        return Type::Boom;
    if(is_KingBoom())
        return Type::KingBoom;
    return Type::Unknown;
}

//计算牌型对应的优先级
/*
 * 按照 王炸 > 普通炸弹 > 一般牌型 > 过 > 非法牌型
 * 优先级分别是 5,4,3,2,1(优先级大的,牌组的威力就大)
*/
int CardCombine::priority(CardCombine::Type type)
{
    switch(type)
    {
    case Type::KingBoom:
        return 5;
    case Type::Boom:
        return 4;
    case Type::Guo:
        return 2;
    case Type::Unknown:
        return 1;
    default:
        return 3;
    }
    return 1;
}

//计算某牌型下的牌组的代表点数
/*
 * 过: 0
 * 单牌: 单牌的点数
 * 顺子: 按照顺子时候牌的顺序(注意顺子的顺序和点数的顺序可能是不同的),此时最后一张牌的点数
 * 对子: 对子中任意一张牌的点数
 * 连对: 按照连对的顺序(注意连对的顺序和点数的顺序可能是不同的),此时最后一张牌的点数
 * 三张: 三张中任意一张牌的点数
 * 三带一: 三张的那个点数
 * 三带二: 三张的那个点数
 * 四带二: 四张的那个点数
 * 无翅飞机: 按照飞机的顺序(注意飞机的顺序和点数的顺序可能是不同的),此时最后一张牌的点数
 * 飞机带单牌: 无翅飞机部分的代表点数
 * 飞机带对子: 无翅飞机部分的代表点数
 * 炸弹: 炸弹中任意一张的点数
 * 王炸: 大王的点数
*/
Point CardCombine::representPoint(Type type)
{
    switch(type)
    {
    case Type::Guo:
        return Point::Card_Zero;
    case Type::Single:
        return _list[0].getPoint();
    case Type::Shunzi:{
        combineSort();
        unsigned int N=static_cast<unsigned int>(_list.size());
        if(_list[N-1].getPoint()-_list[N-2].getPoint()==1){
            if(_list[N-2].getPoint()-_list[N-3].getPoint()==1)
                return _list[N-1].getPoint();
            return _list[N-3].getPoint();
        }
        return _list[N-2].getPoint();
    }
    case Type::Duizi:
        return _list[0].getPoint();
    case Type::LianDui:{
        combineSort();
        unsigned int N=static_cast<unsigned int>(_list.size());
        if(_list[N-1].getPoint()-_list[N-3].getPoint()==1){
            if(_list[N-3].getPoint()-_list[N-5].getPoint()==1)
                return _list[N-1].getPoint();
            return _list[N-5].getPoint();
        }
        return _list[N-3].getPoint();
    }
    case Type::Three:
        return _list[0].getPoint();
    case Type::Three_One:{
        combineSort();
        if(_list[0]==_list[1])
            return _list[0].getPoint();
        return _list[1].getPoint();
    }
    case Type::Three_Two:{
        combineSort();
        if(_list[2]==_list[3])
            return _list[2].getPoint();
        return _list[0].getPoint();
    }
    case Type::Four_Two:{
        combineSort();
        if(_list[1]==_list[2])
            return _list[1].getPoint();
        return _list[2].getPoint();
    }
    case Type::Plane:{
        combineSort();
        unsigned int N=static_cast<unsigned int>(_list.size());
        if(N==6){
            if(_list[0].getPoint()==Point::Card_A)
                return Point::Card_Zero;
            else if(_list[N-1].getPoint()==Point::Card_2)
                return Point::Card_3;
            return _list[N-1].getPoint();
        }else{
            if(_list[N-1].getPoint()==Point::Card_2){
                if(_list[N-4].getPoint()==Point::Card_A)
                    return _list[N-7].getPoint();
                return _list[N-4].getPoint();
            }
            return _list[N-1].getPoint();
        }
    }
    case Type::Plane_Single:{
        unsigned int count[16];
        memset(count,0,16*sizeof(unsigned int));
        unsigned int N=static_cast<unsigned int>(_list.size());
        for(unsigned int i=0;i<N;i++)
            count[_list[i].getPoint()]++;
        CardCombine tmp;
        for(unsigned int i=0;i<N;i++){
            if(count[_list[i].getPoint()]==3)
                tmp.add(_list[i]);
        }
        return tmp.representPoint(Type::Plane);
    }
    case Type::Plane_Dui:
        return this->representPoint(Type::Plane_Single);
    case Type::Boom:
        return _list[0].getPoint();
    case Type::KingBoom:
        return Point::Card_BK;
    }
    return Point::Card_Zero;
}

//牌组的权值比较
/*
 * 首先判断左右操作数的优先级
 * 若优先级不同,直接按照优先级判断牌组比得过比不过
 * 反之若优先级相同,按照代表点数来判断
 * 反之无法比较
*/
CardCombine::CompareRes CardCombine::compareTo(CardCombine& combine)
{
    Type L_type=getType();
    Type R_type=combine.getType();
    int L_priority=priority(L_type);
    int R_priority=priority(R_type);
    if(L_priority<R_priority)
        return CompareRes::Smaller;
    if(L_priority>R_priority)
        return CompareRes::Larger;
    if(L_type==R_type){
        Point L_point=representPoint(L_type);
        Point R_point=combine.representPoint(R_type);
        if(L_point<R_point)
            return CompareRes::Smaller;
        if(L_point>R_point)
            return CompareRes::Larger;
        return CompareRes::Equal;
    }
    return CompareRes::CannotCompare;
}
