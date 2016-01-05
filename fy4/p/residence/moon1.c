inherit __DIR__"ann_residence.c";

void create ()
{
  set("floor",1);

  set ("short", "新月楼底层");
  set ("long", @LONG
  
    星沉月落夜闻香 素手出锋芒 前缘再续新曲 
    
    心有意 爱无伤 江湖远 碧空长 路茫茫 
    
    闲愁滋味 多感情怀 无恨思量 

LONG);
        set("exits", ([
"117" : __DIR__"userroom/nianqc1309157266",
"116" : __DIR__"userroom/meteor1309071153",
"115" : __DIR__"userroom/shayn1308195477",
"114" : __DIR__"userroom/abby1307374505",
"113" : __DIR__"userroom/htb1306730807",
"102" : __DIR__"userroom/mtn1295025721",
"112" : __DIR__"userroom/meijin1265179528",
"111" : __DIR__"userroom/hetang1263316830",
"110" : __DIR__"userroom/giniussq1258897885",
"109" : __DIR__"userroom/hellboy1258877962",
"108" : __DIR__"userroom/giniustx1258724298",
"107" : __DIR__"userroom/giniushs1258628758",
"106" : __DIR__"userroom/zhaonan1258437195",
"105" : __DIR__"userroom/sqgirl1258436471",
"104" : __DIR__"userroom/dance1258426399",
"103" : __DIR__"userroom/giniusxg1258202558",
"102" : __DIR__"userroom/shanguan1257246137",
"101" : __DIR__"userroom/mengy1255936467",
  "up" : __DIR__"moon"+(query("floor")+1), 
  "southwest" : __DIR__"enterance",
]));
        set("coor/x",-15);
        set("coor/y",-35);
        set("coor/z",query("floor")*40);
        setup();
}

/*
*/
