// annie 07.2003
// dancing_faery@hotmail.com

#include <ansi.h>
inherit ROOM;
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
  		"westup" : __DIR__"path4",
  		"southdown" : __DIR__"forest2",
  		"eastup" : __DIR__"path5",
	]) );

	set("coor/x",-20);
	set("coor/y",30);
	set("coor/z",50);
	setup();
}

int	valid_leave(object who, string dir)
{
	object me;
	me = who;
	if (!random(7))
		tell_object(me,YEL"�������ŵ���һ�ֵ����Ľ�ɫ��������\n"NOR);
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

