inherit __DIR__"ann_residence.c";

void create ()
{
  set("floor",9);

  set ("short", "ŭ�θ�"+CHINESE_D->chinese_number(query("floor"))+"��");
  set ("long", @LONG
    
    ���겻ʶ����ζ�����ϲ�¥�����ϲ�¥��Ϊ���´�ǿ˵�

    ����ʶ������ζ����˵���ݡ���˵���ݣ�ȴ�������ø��
    
LONG);
        set("exits", ([
"916" : __DIR__"userroom/zigogoa1320682410",
"915" : __DIR__"userroom/welldone1320639903",
"914" : __DIR__"userroom/hsppmm1320338344",
"913" : __DIR__"userroom/jwm1309465234",
"912" : __DIR__"userroom/hsfive1301287526",
"911" : __DIR__"userroom/hsthree1301112079",
"910" : __DIR__"userroom/hsone1301030245",
"909" : __DIR__"userroom/thesix1300635140",
"908" : __DIR__"userroom/thefive1300623724",
"907" : __DIR__"userroom/thefour1300556751",
"906" : __DIR__"userroom/thethree1300432676",
"905" : __DIR__"userroom/thetwo1300382189",
"904" : __DIR__"userroom/theone1300381895",
"901" : __DIR__"userroom/slone1291119488",
"902" : __DIR__"userroom/slthree1291120144",
"903" : __DIR__"userroom/slfive1291120592",
  "down" : __DIR__"surge"+(query("floor")-1),
]));
        set("coor/x",-15);
        set("coor/y",-45);
        set("coor/z",query("floor")*40);
        setup();
}

/*
*/