#include <ansi.h>
inherit __DIR__"annieitem";

void create()
{
	set_name("泳池", ({ "swimming pool"}) );	// 让这个id有别于其他东西。不使用单字id!
	set_weight(30000);
	set("unit", "片");
	set("desc", "一座设施齐备的高级贵族游泳池，可以学到很好的游泳技能。\n");
	set("no_get",1);
	set("no_sell",1);
	set("no_drop",1);
	set("no_stack",1);
	set("no_reset",1);
	set("item_type","k");
	set("lore_item",1);
	set("outdoors",1);
	set("size",1);
	set("value", 2000000);
	set("tax",40);
	set("score_tax",1);
	
	set("liq",([
       "name":"过滤水",
       "container":"泳池旁的自动饮水机"
    ]));

	seteuid(getuid());
}

void init()
{
	::init();
	if (environment() != this_player())
	   	add_action("do_swim","swim");
}


int do_swim(string arg)
{
   	int	s, amount, da;
 	object me = this_player(),env=environment(me),ob=this_object();
	if (!env->is_owner(me->query("id")))
		return notify_fail("屋子里的物件只有主人才能使用。\n");
	if (me->is_fighting() || me->is_busy()){
		tell_object(me,"你现在正忙。\n"); 
		return 1;
	}
	
   	me->perform_busy(1);
   	s = me->query_skill("swimming", 1);
	if(random(me->query("kar")) && me->query("kar")>11 && s>=80 )
	{
		if(s >= 120)
		{
			message_vision("\n$N在泳池里游了一圈，神态轻松惬意。\n", me);
			tell_object(me, "你的游泳搏浪之技好象没有什么长进。\n");
			return 1;
		} 
		if(random(s) >= 50) 
			message_vision("\n$N在泳池里游了一圈，神态轻松惬意。\n", me);
		else 
			message_vision("\n$N战战兢兢的在泳池里游了一圈。\n", me);
	  
		tell_object(me, "你的游泳搏浪之技好象长进了一些。\n");
	   		amount = me->query("agi") + me->query("int") + me->query_skill("swimming",1)*50;
		if(amount < 1) amount = 1;
		me->improve_skill("swimming", amount);
		da = 20;
		me->set_temp("last_damage_from","在泳池中游水，不小心淹死了。");
		me->receive_damage("kee", da);
   	} else {
      		message_vision("\n$N在泳池里游了一圈，神态轻松惬意。\n", me);
      		message_vision("\n$N一不小心，连呛了几口水。\n", me);
			da = 100;
			me->set_temp("last_damage_from","在泳池中游水，不小心淹死了。");
			me->receive_damage("kee", da);
        }
   	return 1;
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
