// thousand_hand.c

#include <ansi.h>

inherit NPC;
string	summon_more( object who);
void create()
{
	set_name( "����ѩ", ({"girl xue", "xue", "girl" }) );
	set("long", "����ǧ��¥���ϰ˽�֮һ��
����ѩ���缱�黹�ࡣ
��Ƭ��ʱ���񻧣��ػ�������β�����������ĥ��
��ˮԶ�����ɫ��͡�
����Ī˼��Է���������������˸裬��������Σ�
\n");
	set("attitude", "friendly");
	set("title", HIM "���ϰ˽�"NOR);
	set("age", 17);
        set("gender", "Ů��" );

	set("per", 40);
	set("combat_exp", 50000);
        set("chat_chance", 1);
        set("chat_msg", ({
"����ѩ���к��ᣬ����������
ʲôʱ����ܼ����ҵ�Ψһ���׸�磢�����ǣ�\n",
        }) );

	set("chat_chance_combat", 10);
	set("chat_msg_combat", ({
		(: summon_more(this_object()) :),
	}) );
	set_skill("unarmed", 1+random(200));
	setup();
        carry_object(__DIR__"obj/xue")->wear();


}

string summon_more(object who)
{
	int i;
	object *enemy,*ob;
	object another;
	seteuid(getuid());
	ob=all_inventory(environment(who));
	ob=filter_array(ob,(: $1->query("id")=="jianu" && $1->query("name")=="��ū": ));
	if (sizeof(ob)<1) {
	another = new(__DIR__"jianu");
	another->move(environment(who));
	message_vision(another->name()+ "���˹�����\n"
		, this_object() );
	enemy = who->query_enemy();
	i = sizeof(enemy);
	while(i--) {
		if( enemy[i] && living(enemy[i]) ) {
			another->kill_ob(enemy[i]);
			enemy[i]->kill_ob(another);
			another->set_leader(enemy[i]);
			}
		}
	}
	return "1";
}


int accept_object(object me, object obj)
{
	object pai;
    if( (string) me->name() == "������" 	&& me->query("name") != "������" )
	{
        message_vision("$N��$n���˸��򸣣�\n",this_object(),me);
        command("smile");
		command("say �磡���ڼ������ˣ�������㣡��˵�����и������ܣ�\n");
		pai = new(__DIR__"obj/xuepai");
		if(pai)
		pai->move(me);
        message_vision("$N�ó�ѩ��赸�$n��\n",this_object(),me);
		return 1;	
	}
	
	command("say ��ɲ��Ǳ�����ϲ����Ү��");
	return 0;
	
}
