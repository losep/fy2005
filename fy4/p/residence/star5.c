inherit __DIR__"ann_residence.c";

void create ()
{
  set("floor",5);

  set ("short", "ժ��¥"+CHINESE_D->chinese_number(query("floor"))+"��");
  set ("long", @LONG

    ��������ҷ˫��  �������ȹ  

    ��ϡ���λ�����  ��ʪǧ����
    
LONG);
        set("exits", ([
"517" : __DIR__"userroom/mrfx1314814704",
"516" : __DIR__"userroom/mrbx1314814294",
"515" : __DIR__"userroom/mrkf1314810764",
"514" : __DIR__"userroom/mrxx1314749261",
"513" : __DIR__"userroom/suna1306698110",
"512" : __DIR__"userroom/hsbo1301905333",
"511" : __DIR__"userroom/dbeg1299677109",
"510" : __DIR__"userroom/bbeg1299368788",
"509" : __DIR__"userroom/shi1298947845",
"508" : __DIR__"userroom/ljz1298639556",
"507" : __DIR__"userroom/fbeg1298003036",
"506" : __DIR__"userroom/rey1297012913",
"505" : __DIR__"userroom/dwxie1296899596",
"504" : __DIR__"userroom/sbw1296569965",
"503" : __DIR__"userroom/jennifer1281180054",
"502" : __DIR__"userroom/joe1279203755",
"501" : __DIR__"userroom/jojo1278862678",
  "down" : __DIR__"star"+(query("floor")-1),
  "up" : __DIR__"star"+(query("floor")+1), 
]));
        set("coor/x",-25);
        set("coor/y",-35);
        set("coor/z",query("floor")*40);
        setup();
}

/*
*/
