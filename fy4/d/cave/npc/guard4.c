#include <ansi.h>

inherit NPC;

void create()
{
        set_name("ľ������", ({ "prison guard", "guard" }) );
        set("long", "�������������д��ε�ľ�����䡣\n");
        set("title","������ ����");
        set("attitude", "heroism");
	set("class","wudang");

        set("combat_exp", 2200000);

        set("chat_chance", 2);

        set("chat_msg", ({
        "ľ�����俴�˿�������Ѫ����������ޣ�̾�˿�����������������ӻ������ģ�������\n",
        }) );


        set_skill("unarmed", 150);
        set_skill("sword", 200);
        set_skill("parry", 120);
        set_skill("dodge", 130);
        set_skill("move", 130);
        set_skill("dragonstrike",130);
        set_skill("taiji-sword",150);
        set_skill("five-steps",120);
        
        map_skill("sword","taiji-sword");
        map_skill("parry","taiji-sword");
        map_skill("unarmed","dragonstrike");
        map_skill("dodge","five-steps");

        setup();

        carry_object("/obj/armor/cloth")->wear();
        carry_object("/obj/weapon/sword")->wield();
}

void init()
{
    object ob;

    ::init();
    if( interactive(ob = this_player()) && !is_fighting() ) 
    {
        remove_call_out("greeting");
        call_out("greeting", 1, ob);
    }
}

void greeting(object ob)
{   
	string where, location;
	if( !interactive(ob) || environment(ob) != environment() )
		return;
	if (!ob->query("vendetta/authority") ){
            message_vision("$N�ٺٵ�����������˽��������ĵ�ͷ���������ɣ�\n", this_object() );
      		this_object()->kill_ob(ob);
      		ob->kill_ob(this_object());
	}
   	return;
}