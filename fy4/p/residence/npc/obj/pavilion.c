#include <ansi.h>
inherit __DIR__"annieitem";

void create()
{
	set_name("亭阁", ({ "pavilion"}) );	// 让这个id有别于其他东西。不使用单字id!
	set_weight(30000);
	set("unit", "座");
	set("desc", "飞架水面的小小亭阁。\n");
	set("no_get",1);
	set("no_sell",1);
	set("no_drop",1);
	set("no_stack",1);
	set("no_reset",1);
	set("item_type","n");
	set("outdoors",1);
	set("size",1);
	set("value", 50000);
set("tax",5);
set("score_tax",1);
seteuid(getuid());
}

/*

　　　　　　　╔╕
　　　　　　　║╰╮
　　　　　　　║│╰╮
　　　　　　　║││╰╮
　　　　　　　║││││
　　　　　　　╚╧╧╧╛

　　　　　　　- FengYun - 　　　
　　　　　　annie 08.2003
　　　dancing_faery@hotmail.com
*/
