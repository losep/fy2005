//Tushen@Fygroup
//Based on Silencer's code.Copyrights all reserved.
inherit SMART_NPC;
#include <ansi.h>

void create()
{
        set_name("����", ({ "feiqu" }) );
        set("gender", "����");
        set("age", 30);   
      	set("chat_chance", 1);
	      set("chat_msg", ({"�װ׵ķ���ͻȻŤ��������������\n",	}) );
        set("attitude", "friendly");
        set("title",HIG"����"NOR);
        set("nickname", HIW"�װ׵�"NOR);
        set("score", 80000);
        set("reward_npc", 1);
		    set("difficulty",20);
		    set("class","fugui");
        set("combat_exp", 12000000);
    
    set("perform_busy_d", "/fugui/dodge/hawk-steps/yingjichangkong");    
    set("perform_busy_w","/fugui/spear/xuezhan-spear/wulongbaiwei");
    set("perform_weapon_attack1", "/fugui/spear/xuezhan-spear/bafangfengyu");
    set("perform_weapon_attack2", "/fugui/spear/xuezhan-spear/jinshiweikai");
    set("perform_weapon_attack3", "/fugui/spear/xuezhan-spear/liguangsheshi");
    set("perform_weapon_attack4", "/fugui/spear/xuezhan-spear/xueyuxiaoxiao");    
    set("perform_weapon_attack5", "/fugui/spear/xuezhan-spear/yutianbigao");
    set("perform_buff_1", "/d/fugui/dodge/hawk-steps/jiyingbotu");
	
		  set("chat_chance_combat", 100);
    	set("chat_msg_combat", ({
	     	(: auto_smart_fight(100) :),
        }) );
          
        set_skill("move", 200);
        set_skill("force", 200);
        set_skill("spells", 200);
        set_skill("unarmed", 200);
        set_skill("spear", 300);
        set_skill("parry", 200);
        set_skill("dodge", 200);
        set_skill("magic", 200);
        set_skill("iron-cloth", 150);
        set_skill("perception", 200);
        
        set_skill("skyforce", 200);
        set_skill("hawk-steps", 200);
		    set_skill("eagle-claw", 200);
        set_skill("xuezhan-spear", 220);
        set_skill("henglian", 150);
        
        map_skill("unarmed","eagle-claw");
        map_skill("force", "skyforce");
        map_skill("dodge","hawk-steps");
        map_skill("move","hawk-steps");
        map_skill("parry","xuezhan-spear");
        map_skill("spear","xuezhan-spear");
        map_skill("iron-cloth","henglian");
        setup();

       	carry_object("/obj/weapon/spear",([	
    						"name":  HIW"����"NOR,
    						 ]))->wear();  

       	carry_object("/obj/armor/cloth",([	
    						"name":  "��֮��",
    						 ]))->wear();  

}

