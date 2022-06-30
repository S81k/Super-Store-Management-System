#include<bits/stdc++.h>
using namespace std;
int transID=1000100;     /*initializing with some random number,used to generate a transaction id while billing*/
struct Billing                                       
{
    long Product_Id;
    string Name;
    float Rate;
    int Quantity;
    float Amount;
    Billing *next;
};
/*-------------------------------------------------------------------------------------------------------------*/
struct Item
{
    long Item_Id=0;
    string Name;
    float Rate;
    int Quantity;
    Item *next=NULL;
};
/*-------------------------------------------------------------------------------------------------------------*/
struct Customer
{
    long Customer_Id;
    string Name;
    float Points;//which equals total price of products he bought
    Customer *next=NULL;
};
/*-------------------------------------------------------------------------------------------------------------*/
class Manager;
/*-------------------------------------------------------------------------------------------------------------*/
class Inventory
{
    Item *head;
    Item *tail;
    /*-------------------------------------------------------------------------------------------------------------*/
    protected:
  /*------------------------------------------------------------------------------------------------------------*/
    void Add_Item(long Id,string Name,float Price,int Quantity)
    {
        if(head==NULL)
        {
            Item *temp=new Item;
            temp->Item_Id=Id;
            temp->Name=Name;
            temp->Rate=Price;
            temp->Quantity=Quantity;
            head=temp;
            tail=temp;
            temp->next=NULL;
        }
        else
        {
            Item *temp=new Item;
            temp->Item_Id=Id;
            temp->Name=Name;
            temp->Rate=Price;
            temp->Quantity=Quantity;
            Item *a;
            Item *prev=NULL;
            a=head;
            if((head->Item_Id)>Id)
            {
                temp->next=head;
                head=temp;
            }
            else
            {
                while(a&&(a->Item_Id)<Id)
                {
                    prev=a;
                    a=a->next;
                }
                prev->next=temp;
                temp->next=a;
            }
        }
    }
    /*-------------------------------------------------------------------------------------------------------------*/
    void Delete_Item(long Id)
    {
        Item *temp;
        Item *prev;
        temp=head;
        while((temp->Item_Id)!=Id)
        {
            prev=temp;
            temp=temp->next;
        }
        if(temp==head)
        {
            head=temp->next;
            delete temp;
        }
        else if(temp==tail)
        {
            prev=tail;
            delete temp;
        }
        else 
        {
            prev->next=temp->next;
            delete temp;
        }
    }
    /*-------------------------------------------------------------------------------------------------------------*/
    void Update_Item(long Id,float Price,int Quantity)
    {
        Item *temp;
        temp=head;
        while((temp->Item_Id)!=Id)
        {
            temp=temp->next;
        }
        temp->Rate=Price;
        temp->Quantity=Quantity;
    }
    /*-------------------------------------------------------------------------------------------------------------*/
    public:
    /*-------------------------------------------------------------------------------------------------------------*/
    void Update_Stock(long Id,int Quantity_Dec) 
    { 
        Item *temp=new Item;
        temp=head;
        while(temp&&(temp->Item_Id)!=Id)
        {
            temp=temp->next;
        }
        temp->Quantity-=Quantity_Dec;
    }
    Item *Get_Product_Info(long Id)
    {
        Item *temp=new Item;
        temp=head;
        while(temp&&(temp->Item_Id)!=Id)
        {
            temp=temp->next;
        }
        if(temp!=NULL)
        {
            return temp;
        }
        else
        {
            cout<<"item___not___found"<<endl;
            return NULL;
        }
    }
    /*-------------------------------------------------------------------------------------------------------------*/
    Inventory()
    {
        head=NULL;
        tail=NULL;
    }
    /*-------------------------------------------------------------------------------------------------------------*/
    friend class Manager;
    /*-------------------------------------------------------------------------------------------------------------*/
};
Inventory Inventory_Hashtable[22];
/*-------------------------------------------------------------------------------------------------------------*/
class Manager
{
    public:
    /*-------------------------------------------------------------------------------------------------------------*/
    void Add_Item(long Id,string Name,float Price,int Quantity)
    {
        Inventory *a=&Inventory_Hashtable[Id%22];
        a->Add_Item(Id,Name,Price,Quantity);
    }
    /*-------------------------------------------------------------------------------------------------------------*/
    void Delete_Item(long Id)
    {
        Inventory *a=&Inventory_Hashtable[Id%22];
        a->Delete_Item(Id);
    }
    /*-------------------------------------------------------------------------------------------------------------*/
    void Update_Item(long Id,float Price,int Quantity)
    {
        Inventory *a=&Inventory_Hashtable[Id%22];
        a->Update_Item(Id,Price,Quantity);
    }
    /*-------------------------------------------------------------------------------------------------------------*/
    Item *Get_Product_Info(long Id)
    {
        Inventory *a=&Inventory_Hashtable[Id%22];
        return a->Get_Product_Info(Id);
    }
    /*-------------------------------------------------------------------------------------------------------------*/
    void Display_Item_Info(long Id)
    {
        Item *temp=Get_Product_Info(Id);
        cout<<Id<<" "<<temp->Name<<" "<<temp->Rate<<" "<<temp->Quantity<<endl;
    }
    /*-------------------------------------------------------------------------------------------------------------*/
};
class customer
{
    Customer *head;
    Customer *tail;
    /*-------------------------------------------------------------------------------------------------------------*/
    public:
    /*-------------------------------------------------------------------------------------------------------------*/
    customer()
    {
        head=NULL;
        tail=NULL;
    }
    /*-------------------------------------------------------------------------------------------------------------*/
    void Add_Customer(long Id,string Name) 
    {
        if(head==NULL)
        {
            Customer *temp=new Customer;
            temp->Customer_Id=Id;
            temp->Name=Name;
            temp->Points=0;
            head=temp;
            tail=temp;
            temp->next=NULL;
        }
        else
        {
            Customer *temp=new Customer;
            temp->Customer_Id=Id;
            temp->Name=Name;
            temp->Points=0;
            Customer *a;
            Customer *prev=NULL;
            a=head;
            if((head->Customer_Id)>Id)
            {
                temp->next=head;
                head=temp;
            }
            else
            {
                while(a&&(a->Customer_Id)<Id)
                {
                    prev=a;
                    a=a->next;
                }
                prev->next=temp;
                temp->next=a;
            }
        }
    }
    void Update_Points(long Id,int points_incr)
    {
        Customer *temp;
        temp=head;
        while(temp)
        {
            if(temp->Customer_Id==Id)
            {
                break;
            }
            temp=temp->next;
        }
        temp->Points+=points_incr;
    }
};
/*-----------------------------------------------------------------------------------------------------------
*/
customer Customer_Hashtable[22];
/*-------------------------------------------------------------------------------------------------------------*/
class Billings:public Inventory,public customer 
{
    int trans_ID;    
    Billing *head;
    Billing *tail;
    long CUSTOMER_ID;
    float Total_Amount;
    public:
    Billings()
    {
        head=NULL;
        tail=NULL;
        trans_ID=transID++;//increment of the default value assigned
    }
    /*-------------------------------------------------------------------------------------------------------------*/
    void Buy_Item(long Id,int Quantity)
    {
        Item *temp;
        Inventory *a=&Inventory_Hashtable[Id%22];
        temp=a->Get_Product_Info(Id);
        Billing *t=new Billing;
        t->Product_Id=Id;
        t->Name=temp->Name;
        t->Rate=temp->Rate;
        t->Quantity=Quantity;
        t->Amount=(t->Quantity)*(t->Rate);
        Total_Amount+=t->Amount;
        t->next=NULL;
        if(head==NULL)
        {
            head=t;
            tail=t;
        }
        else
        {
            Billing *m;
            m=head;
            while(m->next)
            {
                m=m->next;
            }
            m->next=t;
        }
    }
    void Cancel_Item(long Id)         // deletes item from link-list
    {
        Billing *temp;
        Billing *prev;
        temp=head;
        while((temp->Product_Id)!=Id)
        {
            prev=temp;
            temp=temp->next;
        }
        if(temp==head)
        {
            head=temp->next;
            Total_Amount-=temp->Amount;
            delete temp;
        }
        else if(temp==tail)
        {
            prev=tail;
            Total_Amount-=temp->Amount;
            delete temp;
        }
        else 
        {
            prev->next=temp->next;
            Total_Amount-=temp->Amount;
            delete temp;
        }
    }
    /*-------------------------------------------------------------------------------------------------------------*/
    void Generate_Cust(long Id,string Name)
    {
        customer *a;
        a=&Customer_Hashtable[Id%22];
        a->Add_Customer(Id,Name);
    }
 /*-------------------------------------------------------------------------------------------------------------*/
    void Generate_Customer_Id(long Id)
    {
        CUSTOMER_ID=Id;
    }
     /*-------------------------------------------------------------------------------------------------------------*/
    void Display_Bill()
    {
        cout<<"---------------------------------------------------\n";
        cout<<"Transaction_ID: "<<trans_ID<<"\n";
        cout<<"Customer_ID: "<<CUSTOMER_ID<<"\n";
        Billing *t;
        t=head;
        cout<<"ProductID    Name  Rate  Quantity  Amount\n";
        while(t)
        {
            cout<<t->Product_Id<<"  "<<t->Name<<"   "<<t->Rate<<"      "<<t->Quantity<<"      "<<t->Amount<<endl;
            t=t->next;
        }
        cout<<"                       Total : "<<Total_Amount<<endl;
        cout<<"---Thank You for Shopping---\n";
        cout<<"------Do come again---\n";
        cout<<"-----------------------------------------------------\n";
    }
     /*-------------------------------------------------------------------------------------------------------------*/
    void Make_Payment()   
    {
        Billing *temp;
        temp=head;
        customer *a;
        a=&Customer_Hashtable[CUSTOMER_ID%22];
        a->Update_Points(CUSTOMER_ID,Total_Amount);   
        while(temp)
        {
            Inventory *t;
            t=&Inventory_Hashtable[temp->Product_Id%22];
            t->Update_Stock(temp->Product_Id,temp->Quantity);    
            temp=temp->next;
        }
        Display_Bill();                               
    }
};
 /*-------------------------------------------------------------------------------------------------------------*/
 /*-------------------------------------------------------------------------------------------------------------*/
int main()
{
    long INVENTORY_DATASET[100][4] = {
{111100000001,1,100,20},{111100000002,2,110,20},
{111100000003,3,120,20},{111100000004,4,130,20},
{111100000005,5,140,20},{111100000006,6,150,20},
{111100000007,7,160,20},{111100000008,8,170,20},
{111100000009,9,180,20},{111100000010,10,190,20},
{111100000011,11,200,20},{111100000012,12,210,20},
{111100000013,13,220,20},{111100000014,14,230,20},
{111100000015,15,240,20},{111100000016,16,250,20},
{111100000017,17,260,20},{111100000018,18,270,20},
{111100000019,19,280,20},{111100000020,20,290,20},
{111100000021,21,300,20},{111100000022,22,310,20},
{111100000023,23,320,20},{111100000024,24,330,20},
{111100000025,25,340,20},{111100000026,26,350,20},
{111100000027,27,360,20},{111100000028,28,370,20},
{111100000029,29,380,20},{111100000030,30,390,20},
{111100000031,31,400,20},{111100000032,32,410,20},
{111100000033,33,420,20},{111100000034,34,430,20},
{111100000035,35,440,20},{111100000036,36,450,20},
{111100000037,37,460,20},{111100000038,38,470,20},
{111100000039,39,480,20},{111100000040,40,490,20},
{111100000041,41,500,20},{111100000042,42,510,20},
{111100000043,43,520,20},{111100000044,44,530,20},
{111100000045,45,540,20},{111100000046,46,550,20},
{111100000047,47,560,20},{111100000048,48,570,20},
{111100000049,49,580,20},{222200001111,50,590,20},
{222200001114,51,600,20},{222200001117,52,610,20},
{222200001120,53,620,20},{222200001123,54,630,20},
{222200001126,55,640,20},{222200001129,56,650,20},
{222200001132,57,660,20},{222200001135,58,670,20},
{222200001138,59,680,20},{222200001141,60,690,20},
{222200001144,61,700,20},{222200001147,62,710,20},
{222200001150,63,720,20},{222200001153,64,730,20},
{222200001156,65,740,20},{222200001159,66,750,20},
{222200001162,67,760,20},{222200001165,68,770,20},
{222200001168,69,780,20},{222200001171,70,790,20},
{222200001174,71,800,20},{222200001177,72,810,20},
{222200001180,73,820,20},{222200001183,74,830,20},
{222200001186,75,840,20},{222200001189,76,850,20},
{222200001192,77,860,20},{222200001195,78,870,20},
{222200001198,79,880,20},{222200001201,80,890,20},
{222200001204,81,900,20},{222200001207,82,910,20},
{222200001210,83,920,20},{222200001213,84,930,20},
{222200001216,85,940,20},{222200001219,86,950,20},
{222200001222,87,960,20},{222200001225,88,970,20},
{222200001228,89,980,20},{222200001231,90,990,20},
{222200001234,91,1000,20},{222200001237,92,1010,20},
{222200001240,93,1020,20},{222200001243,94,1030,20},
{222200001246,95,1040,20},{222200001249,96,1050,20},
{222200001252,97,1060,20},{222200001255,98,1070,20},
{222200001258,99,1080,20},{222200001261,100,1090,20},
};
    long CUSTOMER_DATASET[100][3] = {
{9400000001,1,0},{9400000002,2,0},{9400000003,3,0},{9400000004,4,0},
{9400000005,5,0},{9400000006,6,0},{9400000007,7,0},{9400000008,8,0},
{9400000009,9,0},{9400000010,10,0},
{9400000011,11,0},{9400000012,12,0},{9400000013,13,0},
{9400000014,14,0},{9400000015,15,0},{9400000016,16,0},
{9400000017,17,0},{9400000018,18,0},{9400000019,19,0},
{9400000020,20,0},
{9400000021,21,0},{9400000022,22,0},{9400000023,23,0},
{9400000024,24,0},{9400000025,25,0},{9400000026,26,0},
{9400000027,27,0},{9400000028,28,0},{9400000029,29,0},
{9400000030,30,0},
{9400000031,31,0},{9400000032,32,0},{9400000033,33,0},
{9400000034,34,0},{9400000035,35,0},{9400000036,36,0},
{9400000037,37,0},{9400000038,38,0},{9400000039,39,0},
{9400000040,40,0},
{9400000041,41,0},{9400000042,42,0},{9400000043,43,0},
{9400000044,44,0},{9400000045,45,0},{9400000046,46,0},
{9400000047,47,0},{9400000048,48,0},{9400000049,49,0},
{9400000050,50,0},
{9400000051,51,0},{9400000052,52,0},{9400000053,53,0},
{9400000054,54,0},{9400000055,55,0},{9400000056,56,0},
{9400000057,57,0},{9400000058,58,0},{9400000059,59,0},
{9400000060,60,0},
{9400000061,61,0},{9400000062,62,0},{9400000063,63,0},
{9400000064,64,0},{9400000065,65,0},{9400000066,66,0},
{9400000067,67,0},{9400000068,68,0},{9400000069,69,0},
{9400000070,70,0},
{9400000071,71,0},{9400000072,72,0},{9400000073,73,0},
{9400000074,74,0},{9400000075,75,0},{9400000076,76,0},
{9400000077,77,0},{9400000078,78,0},{9400000079,79,0},
{9400000080,80,0},
{9400000081,81,0},{9400000082,82,0},{9400000083,83,0},
{9400000084,84,0},{9400000085,85,0},{9400000086,86,0},
{9400000087,87,0},{9400000088,88,0},{9400000089,89,0},
{9400000090,90,0},
{9400000091,91,0},{9400000092,92,0},{9400000093,93,0},
{9400000094,94,0},{9400000095,95,0},{9400000096,96,0},
{9400000097,97,0},{9400000098,98,0},{9400000099,99,0},
{9400000100,100,0},
};

    Manager m;
    for(int i=0;i<100;i++)
    {
        string name=to_string(INVENTORY_DATASET[i][1]);  //name should be string,so conversion from long to string
        float rate=(float)INVENTORY_DATASET[i][2];      //rate must be float
        int quantity=(int)INVENTORY_DATASET[i][3];
        m.Add_Item(INVENTORY_DATASET[i][0],name,rate,quantity);
    }
    Billings B;
    for(int i=0;i<100;i++)
    {
        string a=to_string(CUSTOMER_DATASET[i][1]);
        B.Generate_Cust(CUSTOMER_DATASET[i][0],a);
    }
    Billings B1;
    B1.Generate_Customer_Id(9400000011);
    B1.Buy_Item(111100000011,3);
    B1.Buy_Item(222200001114,1);
    B1.Buy_Item(222200001234,2);

    B1.Make_Payment();
    m.Display_Item_Info(111100000011);
    m.Display_Item_Info(222200001114);
    m.Display_Item_Info(222200001234);
    cout<<"------------------------------------------------------";

    return 0;
}
