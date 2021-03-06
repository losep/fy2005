inherit SMART_NPC;
#include <ansi.h>
void smart_fight();

void create()
{
    	set_name("杏花梅", ({ "xinghua mei"}) );
    	set("gender", "女性" );
    	set("nickname", BLK"女狩"NOR);
    	set("age", 22);
     	set("reward_npc", 1);
    	set("difficulty", 30);
    	set("class", "huangshan");
    	set("combat_exp", 12000000);
    	set("score", 90000);
     	
     	set_skill("unarmed", 200);
    	set_skill("sword", 300);
    	set_skill("force", 200);
    	set_skill("move", 200);
    	set_skill("dodge", 200);
    	set_skill("parry",200);
    	set_skill("perception",200);
    	
    	set_skill("siqi-sword", 200);
    	set_skill("xianjing", 150);
    	set_skill("liuquan-steps", 200);
    	set_skill("yunwu-strike", 200)

    	map_skill("unarmed", "yunwu-strike");
    	map_skill("sword", "siqi-sword");
    	map_skill("force", "xianjing");
    	map_skill("dodge", "liuquan-steps");
    	map_skill("parry","qiusheng-blade");	
    
    
    set("perform_busy_u", "/huangshan/unarmed/yunwu-strike/miwu");
    set("perform_busy_d", "/huangshan/dodge/liuquan-steps/liushuichanchan");
    set("perform_weapon_attack", "/huangshan/sword/siqi-sword/siqi");   


    	set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
               (: smart_fight() :),
        }) );

   
    	setup();

       	carry_object("/obj/weapon/sword",([	
    						"name":  CYN"彩云"NOR,
    						 ]))->wear();  
    						 
       	carry_object("/obj/armor/cloth",([	
    						"name":  "女之衣",
    						 ]))->wear();  
}


smart_fight()
{
	int i,j,count;
	object *enemy, who;
	who = this_object();
	enemy = this_object()->query_enemy();
	i = sizeof(enemy);
	if (who->query("kee")<6000) {
		count=0;
		for (j=0;j<sizeof(enemy);j++) {
			if (enemy[j]->is_zombie()) count++;
		}
		if (count>=3)
			command("perform zombie-wp1");
	}
	if (!random(3)&& who->query("kee")>8000) who->perform_action("sword.siqi");
	return;
}
