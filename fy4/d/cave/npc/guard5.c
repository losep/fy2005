#include <ansi.h>

inherit NPC;

void create()
{
        set_name("��������", ({ "prison guard", "guard" }) );
        set("long", "�������������д��ε��������䡣\n");
        set("title","������ ����");
        set("attitude", "heroism");
		set("class","wudang");
        set("combat_exp", 3500000);

        set("chat_chance", 2);

        set("chat_msg", ({
        "�������������������ձ�İ׷���է��������˼�ʮ��Ļ��ˣ������ͷһ�ؼ�������ͦ�����ġ���\n",
        }) );


        set_skill("unarmed", 150);
        set_skill("sword", 180);
        set_skill("parry", 150);
        set_skill("dodge", 150);
        set_skill("move", 150);
        set_skill("lingxi-zhi",160);
        set_skill("taiji-sword",170);
        set_skill("five-steps",150);
        
        map_skill("sword","taiji-sword");
        map_skill("parry","taiji-sword");
        map_skill("unarmed","lingxi-zhi");
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