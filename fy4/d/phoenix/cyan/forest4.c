// annie 07.2003
// dancing_faery@hotmail.com

#include <ansi.h>
inherit "/d/phoenix/ann_room.c";
string look_stone();

void create()
{
	set("short", YEL"������"NOR);
    set("long", @LONG
������խ��ɽ�죬ӭ�������һƬ���ص����֡���δ�����ĸ��ֲ����ľ
��������ں������������Ų��þ�Ȼ����ԶԶ��ȥ������ī���ϻ�δ������
ľ�塣��ͷ������������������ľҶ����һƬ�Ա̣���������ǳǳ�Ķ�ƣ�
֦����ƽ�ߣ�����Ϊһ��������ܵ�������
    ��֪���ļ��ڣ�΢�硣
    ��ɫ�Ĺ��ߴ�������ǳǳ��͸��������
LONG
NOR
        );
	set("objects", ([

	]));
	set("item_desc", ([

	]) );
	set("exits",([
  		"westup" : "path6",
  		"northup" : "forest5",
  		"southup" : "rock",
  		"eastdown" : "path4",
	]) );
	set("area","cyan");

	set("coor/x",-40);
	set("coor/y",30);
	set("coor/z",70);
	setup();
}

int	valid_leave(object who, string dir)
{
	object me;
	me = who;

	if (dir != "eastdown" && dir != "northup")
			return notify_fail("ʱ���ϲ����ˣ��ͱ𵽴��һ��˰ɣ�\n");

	return ::valid_leave(who,dir);
}


/*

���������������X�Y
���������������U�t�r
���������������U���t�r
���������������U�����t�r
���������������U��������
���������������^�k�k�k�_

��������������- FengYun - ������
������������annie 08.2003
������dancing_faery@hotmail.com
*/

