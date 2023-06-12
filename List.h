#ifndef LIST_H
#define LIST_H
#include <QTextStream>
#include <iostream>
using namespace std;
class Node{
public:
    int value;
    Node* next;
    Node* prev;
    Node(){next = nullptr;prev = nullptr;value = -1;}
    Node(int t, Node *prev, Node *next) {
        this->value = t;
        this->prev  = prev;
        this->next  = next;
    }

};

class List{
public:
    List();
    List(QString x);
    List(QString x,int i);
    ~List();
    int size();//大小
    int empty();//判断是否为空

    int get(int t);//获取节点
    int get_first();//获取首节点
    int get_last();//获取尾节点

    int insert(int index, int t); //插入节点
    int insert_first(int t);
    int append_last(int t);
    int setposition(int t,int num);
    int del(int t);
    int delete_first();
    int delete_last();
    QString show();
    QString show1();
    void operator=(List* ano);
    List* plus( List* ano) ;
    List* minus( List* ano) ;
    List* cheng( List* ano) ;
    List* chu(long long int ano) ;
    List* chulist(List* ano);
    List* zhi(long long int ano);
    List* zhii(List* ano);
    List* modd(List* ano);
    bool cmp(List* ano);

    List* doubleplus(List* ano);
    List* doubleminus(List* ano);
    List* doublecheng(List* ano);
    List* doublechu(List* ano);
    List* doublezhi(long long int ano);
    List* doublezhii(List* ano);
private:
    int cnt;
    Node *phead;
    Node *get_node(int t);
};



//倒序输出       即把逆序的链表转化成正序的字符串
QString List::show(){
    QString ans = "";
    Node* p = this->get_node(0);
    int i = 0;
    while(i<this->size()){
        QString t = QString::number(p->value);//问题一，输出八进制数组
        ans = t + ans;
        p = p->next;
        i++;
    }
    ans.remove(QRegExp("^(0+)"));
    return ans;

}
//正序输出       即把正序的链表转化成正序的字符串
QString List::show1(){
    QString ans = "";
    Node* p = this->get_node(0);
    int i = 0;
    while(i<this->size()){
        QString t = QString::number(p->value);//问题一，输出八进制数组
        ans = ans+t;
        p = p->next;
        i++;
    }
    ans.remove(QRegExp("^(0+)"));
    return ans;

}

bool List::cmp(List* ano){
    int a = this->size();
    int b = ano->size();//报错处，前导0的处理
    Node* q1 = this->get_node(0);
    Node* q2 = ano->get_node(0);
    while(q1->value == 0){a--;q1 = q1->next;}
    while(q2->value == 0){b--;q2 = q2->next;}
    if(a > b) return true;
    else if(a<b ||(a==0&&b == 0)) return false; //填写都等于0的情况以修补bug
    else{
        int i = 0;
        while(q1->value == q2->value){
               q1 = q1->next;
               q2 = q2->next;
               i++;
               if(i == this->size()) return true;
        }
        if (q1->value >= q2->value) return true;
        else return false;
    }
}


List::List():cnt(0){
    phead = new Node();
    phead->prev = phead->next = phead;
}
List::List(QString x):cnt(0){      //这里的加入是字符串的逆序插入，即开头为结尾
    phead = new Node();
    phead->prev = phead->next = phead;
    for(int i=0;i<x.size();i++){
         if(i == 0)this->insert(i,x.mid(x.size() - i - 1,1).toInt());
         else this->append_last(x.mid(x.size() - i - 1,1).toInt());
     }
}
List::List(QString x,int i):cnt(0){    //这里的插入是字符串的正序插入，即开头为开头
    phead = new Node();
    phead->prev = phead->next = phead;
    for(int i=0;i<x.size();i++){
         if(i == 0)this->insert(i,x.mid(i,1).toInt());
         else this->append_last(x.mid(i,1).toInt());
     }
}
void List::operator=(List* ano){
    phead = new Node();
    phead->prev = phead->next = phead;
    Node* t = ano->get_node(0);
    while(t){
      this->append_last(t->value);
        t = t->next;
    }
}
List::~List(){
    Node* ptmp;
    Node* temp = phead->next;
    while (temp!= phead){
        ptmp = temp;
        temp=temp->next;
        delete ptmp;
    }
    delete phead;
    phead = nullptr;
}

int List::size(){
    return cnt;
}

int List::empty(){
    return cnt==0;
}

Node* List::get_node(int t){
    // 判断参数有效性
    if (t<0 || t>=cnt){
        cout << "参数越界" << endl;
        return nullptr;
    }

    // 正向查找
    if (t <= cnt/2){
        int i=0;
        Node* pt = phead->next;
        while (i++ < t) {
            pt = pt->next;
        }
        return pt;
    }
    // 反向查找
    int j=0;
    int rt = cnt - t -1;
    Node* prt = phead->prev;
    while (j++ < rt){
        prt = prt->prev;
    }
    return prt;
}


int List::get(int t){
    return get_node(t)->value;
}

// 获取第1个节点的值
int List::get_first(){
    return get_node(0)->value;
}

// 获取最后一个节点的值
int List::get_last(){
    return get_node(cnt-1)->value;
}

// 将节点插入到第index位置之前
int List::insert(int index, int t){
    if (index == 0)
        return insert_first(t);
    Node* pt = get_node(index);
    Node* pnode  = new Node(t, pt->prev, pt);
    pt->prev->next = pnode;
    pt->prev = pnode;
    cnt++;

    return 0;
}

// 将节点插入第一个节点处。
int List::insert_first(int t){
    Node* pnode  = new Node(t, phead, phead->next);
    phead->next->prev = pnode;
    phead->next = pnode;
    cnt++;
    return 0;
}

// 将节点追加到链表的末尾
int List::append_last(int t){
    Node* pnode = new Node(t, phead->prev, phead);
    phead->prev->next = pnode;
    phead->prev = pnode;
    cnt++;
    return 0;
}

// 删除t位置的节点
int List::del(int t){
    Node* pt = get_node(t);
    pt->next->prev = pt->prev;
    pt->prev->next = pt->next;
    delete pt;
    cnt--;
    return 0;
}
//修改值
int  List::setposition(int t,int num){
    this->del(t);
    this->insert(t,num);
    return 0;
}
// 删除第一个节点
int List::delete_first(){
    return del(0);
}

// 删除最后一个节点
int List::delete_last(){
    return del(cnt-1);
}

//逆序存储
//正 + 正
List* List::plus( List* ano){     //显而易见的逆序+逆序
    List* ans = new List;
    Node* t1 = get_node(0);
    Node* t2 = ano->get_node(0);
    int jw=0,cntp=0,cnta=0;
    while(cntp < this->size() && cnta<ano->size()){
        int temp = t1->value + t2->value + jw;
        jw = temp/10;
        if(cntp == 0)ans->insert_first(temp%10);
        else ans->append_last(temp%10);
        t1 = t1->next;
        t2 = t2->next;
        cnta++;
        cntp++;
    }
    while(cntp < this->size()){
        int  temp = t1->value +jw;
        jw = temp/10;
        ans->append_last(temp%10);
        t1 = t1->next;
        cntp++;
    }
    while(cnta < ano->size()){
        int  temp = t2->value +jw;
        jw = temp/10;
        ans->append_last(temp%10);
        t2 = t2->next;
        cnta++;
    }
    if(jw){
        ans->append_last(1);
    }
    return ans;
}

List* List::doubleplus(List* ano){
    List* ans = new List;
    Node* t1 = get_node(0);
    Node* t2 = ano->get_node(0);
    int jw=0,cntp=0,cnta=0;
    while(cntp < this->size() && cnta<ano->size()){
        int temp = t1->value + t2->value + jw;
        jw = temp/2;
        if(cntp == 0)ans->insert_first(temp%2);
        else ans->append_last(temp%2);
        t1 = t1->next;
        t2 = t2->next;
        cnta++;
        cntp++;
    }
    while(cntp < this->size()){
        int  temp = t1->value +jw;
        jw = temp/2;
        ans->append_last(temp%2);
        t1 = t1->next;
        cntp++;
    }
    while(cnta < ano->size()){
        int  temp = t2->value +jw;
        jw = temp/2;
        ans->append_last(temp%2);
        t2 = t2->next;
        cnta++;
    }
    if(jw){
        ans->append_last(1);
    }
    return ans;
}

//大 - 小
List* List::minus(List* ano){
    List* ans = new List;
    Node* t1 = get_node(0);
    Node* t2 = ano->get_node(0);
    int cntp=0,cnta=0;
     while(cntp < this->size() && cnta<ano->size()){
         if(t1->value < t2->value){
              t1->next->value--;
              t1->value+=10;
         }
         if(cntp == 0)ans->insert_first(t1->value - t2->value);
         else ans->append_last(t1->value - t2->value);
         t1 = t1->next;
         t2 = t2->next;
         cntp++;
         cnta++;
     }
     while(cntp < this->size()){
         if(t1->value<0){   //退位
             if(t1->next != nullptr){
                t1->next->value--;
                t1->value+=10;
              }
             else{
                t1->value+=10;
                cntp++;
             }
         }
         ans->append_last(t1->value);
         t1 = t1->next;
         cntp++;
     }
     return ans;
}

List* List::doubleminus(List* ano){
    List* ans = new List;
    Node* t1 = get_node(0);
    Node* t2 = ano->get_node(0);
    int cntp=0,cnta=0;
     while(cntp < this->size() && cnta<ano->size()){
         if(t1->value < t2->value){
              t1->next->value--;
              t1->value+=2;
         }
         if(cntp == 0)ans->insert_first(t1->value - t2->value);
         else ans->append_last(t1->value - t2->value);
         t1 = t1->next;
         t2 = t2->next;
         cntp++;
         cnta++;
     }
     while(cntp < this->size()){
         if(t1->value<0){   //退位
             if(t1->next != nullptr){
                t1->next->value--;
                t1->value+=2;
              }
             else{
                t1->value+=2;
                cntp++;
             }
         }
         ans->append_last(t1->value);
         t1 = t1->next;
         cntp++;
     }
     return ans;
}





//乘法 o(n^2)
List* List::cheng( List* ano){
    QString str = QString("").leftJustified(this->size() + ano->size(), '0');
    List* ans = new List(str);
    Node *p = ans->get_node(0), *temp;
    int jw=0;
    for (Node* t1 = get_node(0); t1->value != -1; t1 = t1->next){
          jw = 0;
          temp = p;
          for (Node* t2 = ano->get_node(0); t2->value != -1; t2 = t2->next,p = p->next){
              int temp = t1->value * t2->value + jw + p->value;    // 32 * 56 p->value为原始值
              p->value = temp % 10;                                //2 3 * 6 5
              jw = temp / 10; //进位
          }
          p->value+=jw;
          p = temp->next;
    }
    return ans;

}

List* List::doublecheng( List* ano){
    QString str = QString("").leftJustified(this->size() + ano->size(), '0');
    List* ans = new List(str);
    Node *p = ans->get_node(0), *temp;
    int jw=0;
    for (Node* t1 = get_node(0); t1->value != -1; t1 = t1->next){
          jw = 0;
          temp = p;
          for (Node* t2 = ano->get_node(0); t2->value != -1; t2 = t2->next,p = p->next){
              int temp = t1->value * t2->value + jw + p->value;
              p->value = temp % 2;
              jw = temp / 2;
          }
          p->value+=jw;
          p = temp->next;
    }
    return ans;

}

//除法,此处仅给出整除！！！！小于直接返回0
//输入的字符是正序带入，与前面不同，此处先做约定
//并且左大于右
//高精度除低精度
List* List::chu(long long int ano){
    List* ans = new List;
    Node* t1 = get_node(0);
    int cntp=0;
    int y = 0;//余数
    while(cntp < this->size()){
        int temp = (t1->value + y * 10)/ano; //值
        y = (t1->value + y * 10) % ano;
        t1 = t1->next;
        if(cntp == 0)ans->insert_first(temp);
        else ans->append_last(temp);
        cntp++;
    }
    return ans;
}

//链表除法
//减法模拟除法
List* List::chulist(List* ano){
    int leng = this->size(); //leng为目前链表大小
    List* ans = new List;
    for(int i = 0; i < leng; i++){
        if(i == 0)ans->insert_first(0);
        else ans->append_last(0);
    }
    //给ans全部赋上0

    while(1){
        List* temp = new List(ano->show()); //temp 为新除数

        if(!(this->cmp(temp))) break; //如果除数大于被除数，结束运算

        int cntt = 0;//写位数

        while(this->cmp(temp)){  //当被除数大于除数时

            temp->append_last(0); //除数尾部加0

            if(this->cmp(temp)) cntt++; //假如此时除数依旧大于被除数，进位数+1

            else{
                temp->delete_last();   //假如此时除数小于被除数，要么它们同级数，要么刚好差一位，但都构成减法的条件，也就不需要再进位了
                break;
            }
        }

        int h = 0;    //h是具体的数
        //注意此时是正序存入
        while(this->cmp(temp)){ //减法减到this小于temp的时候，问题在于前导0
            Node* p1 = this->get_node(this->cnt - 1); //最后一位
            Node* p2 = temp->get_node(temp->cnt - 1); //最后一位
            int t = temp->cnt;
            while(t--){ //当被除数还没遍历到首部位置时        //原来报错，用p2是否到0位的错误写法
                p1->value -= p2->value;     //做减法
                p1 = p1->prev;
                p2 = p2->prev;
            }

            Node* p3 = this->get_node(this->cnt - 1);//考虑退位
            //
            for (int x = cnt;x!=0;x--){
                if(p3->value<0){
                    p3->prev->value -= 1;
                    p3->value+=10;
                }
                p3=p3->prev;
            }

            h++; //做了第h次减法
        }
        Node* s = ans->get_node(ans->cnt - 1);
        for (; cntt > 0; cntt--) s = s->prev;
        s->value += h;
    }

    return ans;
}










List* List::doublechu(List* ano){
    int leng = this->size(); //leng为目前链表大小
    List* ans = new List;
    for(int i = 0; i < leng; i++){
        if(i == 0)ans->insert_first(0);
        else ans->append_last(0);
    }
    //给ans全部赋上0

    while(1){
        List* temp = new List(ano->show()); //temp 为新除数

        if(!(this->cmp(temp))) break; //如果除数大于被除数，结束运算

        int cntt = 0;//写位数

        while(this->cmp(temp)){  //当被除数大于除数时

            temp->append_last(0); //除数尾部加0

            if(this->cmp(temp)) cntt++; //假如此时除数依旧大于被除数，进位数+1

            else{
                temp->delete_last();   //假如此时除数小于被除数，要么它们同级数，要么刚好差一位，但都构成减法的条件，也就不需要再进位了
                break;
            }
        }

        int h = 0;    //h是具体的数
        //注意此时是正序存入
        while(this->cmp(temp)){ //减法减到this小于temp的时候，问题在于前导0
            Node* p1 = this->get_node(this->cnt - 1); //最后一位
            Node* p2 = temp->get_node(temp->cnt - 1); //最后一位
            int t = temp->cnt;
            while(t--){ //当被除数还没遍历到首部位置时
                p1->value -= p2->value;     //做减法
                p1 = p1->prev;
                p2 = p2->prev;
            }

            Node* p3 = this->get_node(this->cnt - 1);//考虑退位
            //
            for (int x = cnt;x!=0;x--){
                if(p3->value<0){
                    p3->prev->value -= 1;
                    p3->value+=2;
                }
                p3=p3->prev;
            }

            h++; //做了第h次减法
        }
        Node* s = ans->get_node(ans->cnt - 1);
        for (; cntt > 0; cntt--) s = s->prev;
        s->value += h;
    }

    return ans;
}


//左值非0，0在上位处理
//左值非1，1在上位处理
//右值非1，非0，在上位处理

List* List::zhi(long long int ano){
    List* ans = this;
    ano--;
    while(ano--){
        ans = ans->cheng(this);
    }
    return ans;
}
//快速幂
List* List::zhii(List* ano){
    //逆序存储
    List* num0 = new List("0"); //用于判定指数是否结束
    List* num5 = new List("5"); //用于二进制移动位置
    List* shu = this;
    List* zhishu = ano;//10 -> 50/10 = 5     0 1 -> 0 5 -> 5 2 1
    List* ans = new List("1");
    while(zhishu->cmp(num0)){ //问题在于cmp的部分写的是大于等于，此处必须为大于
            if(zhishu->cnt == 1 && zhishu->get_node(0)->value == 0) break;//加上这句解决
            if((zhishu->get_node(0))->value % 2 == 1) ans = ans->cheng(shu);
            shu = shu->cheng(shu);//直接乘会有前导0问题,此处作用为叠加
            //整除2
            zhishu = zhishu->cheng(num5);
            zhishu->delete_first();     //前导零问题
            if(zhishu->cnt == 0) break; //指数为个位数不报错，十位数报错
    }
    return ans;
}

List* List::doublezhi(long long int ano){
    List* ans = this;
    ano--;
    while(ano--){
        ans = ans->cheng(this);
    }
    return ans;
}

List* List::doublezhii(List* ano){
    List* num0 = new List("0"); //用于判定指数是否结束
    List* shu = this;
    List* zhishu = ano;//10 -> 50/10 = 5     0 1 -> 0 5 -> 5 2 1
    List* ans = new List("1");
    while(zhishu->cmp(num0)){ //问题在于cmp的部分写的是大于等于，此处必须为大于
            if(zhishu->cnt == 1 && zhishu->get_node(0)->value == 0) break;//加上这句解决
            if((zhishu->get_node(0))->value % 2 == 1) ans = ans->doublecheng(shu);
            shu = shu->doublecheng(shu);//直接乘会有前导0问题,此处作用为叠加
            //整除2
            zhishu->delete_first();     //前导零问题,此时为二进制，不能简单取出首位（先乘5，可以直接取出首位）
            if(zhishu->cnt == 0) break; //指数为个位数不报错，十位数报错
    }
    return ans;
}


List* List::modd(List* ano){
    QString x = (this->chulist(ano))->show1(); //正序转逆序存储
    List* a = new List(x);
    List* b = a->cheng(ano);      //逆序存储
    List* ans = this->minus(b); //逆序存储
    return ans; //此处输出的是逆序
}
#endif // LIST_H
